// -------------------------------------------------------------------
// PersistenceStore#315 item 4: RocksDB background events, delivered to an Erlang process.
// -------------------------------------------------------------------

#include <memory>
#include <string>

#include "rocksdb/db.h"
#include "rocksdb/listener.h"
#include "rocksdb/options.h"
#include "rocksdb/types.h"

#include "atoms.h"
#include "erl_nif.h"
#include "event_listener.h"
#include "util.h"

namespace erocksdb {

static ERL_NIF_TERM
cstring_to_binary(ErlNifEnv* env, const std::string& s)
{
    ERL_NIF_TERM term;
    unsigned char* buf = enif_make_new_binary(env, s.size(), &term);
    if (s.size() > 0)
        memcpy(buf, s.data(), s.size());
    return term;
}

static ERL_NIF_TERM
stall_condition_atom(rocksdb::WriteStallCondition c)
{
    switch (c)
    {
        case rocksdb::WriteStallCondition::kDelayed: return ATOM_DELAYED;
        case rocksdb::WriteStallCondition::kStopped: return ATOM_STOPPED;
        default: return ATOM_NORMAL;
    }
}

static ERL_NIF_TERM
background_error_reason_atom(rocksdb::BackgroundErrorReason reason)
{
    switch (reason)
    {
        case rocksdb::BackgroundErrorReason::kFlush: return ATOM_FLUSH;
        case rocksdb::BackgroundErrorReason::kCompaction: return ATOM_COMPACTION;
        case rocksdb::BackgroundErrorReason::kWriteCallback: return ATOM_WRITE_CALLBACK;
        case rocksdb::BackgroundErrorReason::kMemTable: return ATOM_MEMTABLE;
        case rocksdb::BackgroundErrorReason::kManifestWrite: return ATOM_MANIFEST_WRITE;
        case rocksdb::BackgroundErrorReason::kFlushNoWAL: return ATOM_FLUSH_NO_WAL;
        default: return ATOM_MANIFEST_WRITE_NO_WAL;
    }
}

// A RocksDB EventListener that forwards to an Erlang process.
//
// Every callback here runs on a ROCKSDB BACKGROUND THREAD, which is not an
// Erlang scheduler. Three things follow, and all three are why this is the
// only shape this feature can take:
//
//   - the message environment is allocated per event with enif_alloc_env() and
//     the send passes NULL for caller_env, which is the documented form for a
//     thread the VM does not own;
//   - if the target process is gone, enif_send answers 0 and nothing else
//     happens -- a dead listener must not take a compaction with it;
//   - nothing here calls back into the DB. A RocksDB callback that re-enters
//     the DB deadlocks, and the documentation says so.
//
// The work per event is building a small map and one send. A callback that
// blocked would stall the compaction or flush that raised it.
class ErlangEventListener : public rocksdb::EventListener {
public:
    ErlangEventListener(ErlNifPid pid, uint32_t mask) : pid_(pid), mask_(mask) {}

    const char* Name() const override { return "ErlangEventListener"; }

    void OnFlushBegin(rocksdb::DB*, const rocksdb::FlushJobInfo& info) override
    {
        if (!wants(EVENT_FLUSH_BEGIN)) return;
        send_flush(ATOM_FLUSH_BEGIN, info);
    }

    void OnFlushCompleted(rocksdb::DB*, const rocksdb::FlushJobInfo& info) override
    {
        if (!wants(EVENT_FLUSH_COMPLETED)) return;
        send_flush(ATOM_FLUSH_COMPLETED, info);
    }

    void OnCompactionBegin(rocksdb::DB*, const rocksdb::CompactionJobInfo& info) override
    {
        if (!wants(EVENT_COMPACTION_BEGIN)) return;
        send_compaction(ATOM_COMPACTION_BEGIN, info);
    }

    void OnCompactionCompleted(rocksdb::DB*, const rocksdb::CompactionJobInfo& info) override
    {
        if (!wants(EVENT_COMPACTION_COMPLETED)) return;
        send_compaction(ATOM_COMPACTION_COMPLETED, info);
    }

    void OnMemTableSealed(const rocksdb::MemTableInfo& info) override
    {
        if (!wants(EVENT_MEMTABLE_SEALED)) return;
        ErlNifEnv* env = enif_alloc_env();
        ERL_NIF_TERM map = enif_make_new_map(env);
        put(env, &map, ATOM_CF_NAME, cstring_to_binary(env, info.cf_name));
        put(env, &map, ATOM_NUM_ENTRIES, enif_make_uint64(env, info.num_entries));
        put(env, &map, ATOM_NUM_DELETIONS, enif_make_uint64(env, info.num_deletes));
        emit(env, ATOM_MEMTABLE_SEALED, map);
    }

    // The PersistenceStore#295 event a poll cannot see: a stall that begins and ends
    // between two samples leaves no trace in get_property.
    void OnStallConditionsChanged(const rocksdb::WriteStallInfo& info) override
    {
        if (!wants(EVENT_STALL_CONDITIONS_CHANGED)) return;
        ErlNifEnv* env = enif_alloc_env();
        ERL_NIF_TERM map = enif_make_new_map(env);
        put(env, &map, ATOM_CF_NAME, cstring_to_binary(env, info.cf_name));
        put(env, &map, ATOM_PREV, stall_condition_atom(info.condition.prev));
        put(env, &map, ATOM_CUR, stall_condition_atom(info.condition.cur));
        emit(env, ATOM_STALL_CONDITIONS_CHANGED, map);
    }

    void OnBackgroundError(rocksdb::BackgroundErrorReason reason, rocksdb::Status* status) override
    {
        if (!wants(EVENT_BACKGROUND_ERROR)) return;
        ErlNifEnv* env = enif_alloc_env();
        ERL_NIF_TERM map = enif_make_new_map(env);
        put(env, &map, ATOM_REASON, background_error_reason_atom(reason));
        std::string msg = (status == nullptr) ? std::string("") : status->ToString();
        put(env, &map, ATOM_STATUS, cstring_to_binary(env, msg));
        emit(env, ATOM_BACKGROUND_ERROR, map);
        // The Status is NOT cleared here. Deciding that a background error is
        // recoverable is a RocksDB decision, and overriding it from a
        // notification would turn a reported failure into a silent one.
    }

    void OnExternalFileIngested(
        rocksdb::DB*, const rocksdb::ExternalFileIngestionInfo& info) override
    {
        if (!wants(EVENT_EXTERNAL_FILE_INGESTED)) return;
        ErlNifEnv* env = enif_alloc_env();
        ERL_NIF_TERM map = enif_make_new_map(env);
        put(env, &map, ATOM_CF_NAME, cstring_to_binary(env, info.cf_name));
        put(env, &map, ATOM_EXTERNAL_FILE_PATH,
            cstring_to_binary(env, info.external_file_path));
        put(env, &map, ATOM_FILE_PATH, cstring_to_binary(env, info.internal_file_path));
        emit(env, ATOM_EXTERNAL_FILE_INGESTED, map);
    }

    void OnTableFileDeleted(const rocksdb::TableFileDeletionInfo& info) override
    {
        if (!wants(EVENT_TABLE_FILE_DELETED)) return;
        ErlNifEnv* env = enif_alloc_env();
        ERL_NIF_TERM map = enif_make_new_map(env);
        put(env, &map, ATOM_FILE_PATH, cstring_to_binary(env, info.file_path));
        put(env, &map, ATOM_JOB_ID, enif_make_int(env, info.job_id));
        emit(env, ATOM_TABLE_FILE_DELETED, map);
    }

private:
    bool wants(uint32_t bit) const { return (mask_ & bit) != 0; }

    static void put(ErlNifEnv* env, ERL_NIF_TERM* map, ERL_NIF_TERM key, ERL_NIF_TERM value)
    {
        enif_make_map_put(env, *map, key, value, map);
    }

    void send_flush(ERL_NIF_TERM name, const rocksdb::FlushJobInfo& info)
    {
        ErlNifEnv* env = enif_alloc_env();
        ERL_NIF_TERM map = enif_make_new_map(env);
        put(env, &map, ATOM_CF_NAME, cstring_to_binary(env, info.cf_name));
        put(env, &map, ATOM_FILE_PATH, cstring_to_binary(env, info.file_path));
        put(env, &map, ATOM_JOB_ID, enif_make_int(env, info.job_id));
        put(env, &map, ATOM_TRIGGERED_WRITES_SLOWDOWN,
            info.triggered_writes_slowdown ? ATOM_TRUE : ATOM_FALSE);
        put(env, &map, ATOM_TRIGGERED_WRITES_STOP,
            info.triggered_writes_stop ? ATOM_TRUE : ATOM_FALSE);
        put(env, &map, ATOM_NUM_ENTRIES,
            enif_make_uint64(env, info.table_properties.num_entries));
        emit(env, name, map);
    }

    void send_compaction(ERL_NIF_TERM name, const rocksdb::CompactionJobInfo& info)
    {
        ErlNifEnv* env = enif_alloc_env();
        ERL_NIF_TERM map = enif_make_new_map(env);
        put(env, &map, ATOM_CF_NAME, cstring_to_binary(env, info.cf_name));
        put(env, &map, ATOM_JOB_ID, enif_make_int(env, info.job_id));
        put(env, &map, ATOM_BASE_INPUT_LEVEL, enif_make_int(env, info.base_input_level));
        put(env, &map, ATOM_OUTPUT_LEVEL, enif_make_int(env, info.output_level));
        put(env, &map, ATOM_NUM_L0_FILES, enif_make_int(env, info.num_l0_files));
        put(env, &map, ATOM_NUM_INPUT_RECORDS,
            enif_make_uint64(env, info.stats.num_input_records));
        put(env, &map, ATOM_NUM_OUTPUT_RECORDS,
            enif_make_uint64(env, info.stats.num_output_records));
        put(env, &map, ATOM_ELAPSED_MICROS, enif_make_uint64(env, info.stats.elapsed_micros));
        std::string status = info.status.ToString();
        put(env, &map, ATOM_STATUS, cstring_to_binary(env, status));
        emit(env, name, map);
    }

    // enif_send with a NULL caller_env is the form for a thread the VM does not
    // own. The message environment is freed here whatever the send answered:
    // a listener whose process has exited must leak nothing.
    void emit(ErlNifEnv* env, ERL_NIF_TERM name, ERL_NIF_TERM map)
    {
        ERL_NIF_TERM msg = enif_make_tuple3(env, ATOM_ROCKSDB_EVENT, name, map);
        enif_send(NULL, &pid_, env, msg);
        enif_free_env(env);
    }

    ErlNifPid pid_;
    uint32_t mask_;
};

static uint32_t
event_bit(ERL_NIF_TERM name)
{
    if (name == ATOM_FLUSH_BEGIN) return EVENT_FLUSH_BEGIN;
    if (name == ATOM_FLUSH_COMPLETED) return EVENT_FLUSH_COMPLETED;
    if (name == ATOM_COMPACTION_BEGIN) return EVENT_COMPACTION_BEGIN;
    if (name == ATOM_COMPACTION_COMPLETED) return EVENT_COMPACTION_COMPLETED;
    if (name == ATOM_MEMTABLE_SEALED) return EVENT_MEMTABLE_SEALED;
    if (name == ATOM_STALL_CONDITIONS_CHANGED) return EVENT_STALL_CONDITIONS_CHANGED;
    if (name == ATOM_BACKGROUND_ERROR) return EVENT_BACKGROUND_ERROR;
    if (name == ATOM_EXTERNAL_FILE_INGESTED) return EVENT_EXTERNAL_FILE_INGESTED;
    if (name == ATOM_TABLE_FILE_DELETED) return EVENT_TABLE_FILE_DELETED;
    return 0;
}

int
parse_listener_option(ErlNifEnv* env, ERL_NIF_TERM value, rocksdb::DBOptions& opts)
{
    ErlNifPid pid;
    uint32_t mask = EVENT_ALL;

    if (enif_get_local_pid(env, value, &pid))
    {
        // {listener, Pid}: every event.
    }
    else
    {
        int arity;
        const ERL_NIF_TERM* pair;
        if (!enif_get_tuple(env, value, &arity, &pair) || arity != 2)
            return 0;
        if (!enif_get_local_pid(env, pair[0], &pid))
            return 0;
        if (!enif_is_list(env, pair[1]))
            return 0;

        // An explicit list selects events, and an UNKNOWN name is refused
        // rather than ignored: a caller that misspells `compaction_completed`
        // would otherwise get a listener that silently never fires.
        mask = 0;
        ERL_NIF_TERM head, tail = pair[1];
        while (enif_get_list_cell(env, tail, &head, &tail))
        {
            uint32_t bit = event_bit(head);
            if (bit == 0)
                return 0;
            mask |= bit;
        }
        if (mask == 0)
            return 0;
    }

    opts.listeners.push_back(std::make_shared<ErlangEventListener>(pid, mask));
    return 1;
}

}  // namespace erocksdb
