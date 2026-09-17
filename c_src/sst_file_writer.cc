// -------------------------------------------------------------------
// SstFileWriter + IngestExternalFile. cards#315 item 3.
// -------------------------------------------------------------------

#include <string>
#include <vector>

#include "rocksdb/db.h"
#include "rocksdb/env.h"
#include "rocksdb/options.h"
#include "rocksdb/sst_file_writer.h"

#include "atoms.h"
#include "erl_nif.h"
#include "erocksdb_db.h"
#include "refobjects.h"
#include "sst_file_writer.h"
#include "util.h"

namespace erocksdb {

ErlNifResourceType* SstFileWriterObject::m_SstFileWriter_RESOURCE(NULL);

void
SstFileWriterObject::CreateSstFileWriterType(ErlNifEnv* env)
{
    ErlNifResourceFlags flags = (ErlNifResourceFlags)(ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER);
    m_SstFileWriter_RESOURCE = enif_open_resource_type(
        env, NULL, "erocksdb_SstFileWriter",
        &SstFileWriterObject::SstFileWriterResourceCleanup, flags, NULL);
}

// The writer is deleted here and nowhere else, so a handle that goes out of
// scope without sst_file_writer_close/1 still releases the open file.
void
SstFileWriterObject::SstFileWriterResourceCleanup(ErlNifEnv* /*env*/, void* arg)
{
    SstFileWriterObject* ptr = (SstFileWriterObject*)arg;
    ptr->~SstFileWriterObject();
}

SstFileWriterObject*
SstFileWriterObject::CreateSstFileWriterResource(rocksdb::SstFileWriter* writer)
{
    void* alloc_ptr = enif_alloc_resource(m_SstFileWriter_RESOURCE, sizeof(SstFileWriterObject));
    return new (alloc_ptr) SstFileWriterObject(writer);
}

SstFileWriterObject*
SstFileWriterObject::RetrieveSstFileWriterResource(ErlNifEnv* env, const ERL_NIF_TERM& term)
{
    SstFileWriterObject* ptr;
    if (!enif_get_resource(env, term, m_SstFileWriter_RESOURCE, (void**)&ptr))
        return NULL;
    return ptr;
}

SstFileWriterObject::SstFileWriterObject(rocksdb::SstFileWriter* writer) : writer_(writer) {}

SstFileWriterObject::~SstFileWriterObject()
{
    reset();
}

rocksdb::SstFileWriter* SstFileWriterObject::writer() { return writer_; }

void SstFileWriterObject::reset()
{
    if (writer_ != nullptr)
    {
        delete writer_;
        writer_ = nullptr;
    }
}

static SstFileWriterObject*
open_writer(ErlNifEnv* env, const ERL_NIF_TERM& term)
{
    SstFileWriterObject* ptr = SstFileWriterObject::RetrieveSstFileWriterResource(env, term);
    if (ptr == NULL || ptr->writer() == nullptr)
        return NULL;
    return ptr;
}

// sst_file_writer_open(Path, CFOptions) -> {ok, Writer}
//
// The options are the same column-family options `open/3` takes, because the
// file has to be readable by the column family it will be ingested into --
// comparator, compression and prefix extractor all have to match or the
// ingest is refused.
ERL_NIF_TERM
SstFileWriterOpen(ErlNifEnv* env, int /*argc*/, const ERL_NIF_TERM argv[])
{
    std::string path;
    if (!enif_get_std_string(env, argv[0], path))
        return enif_make_badarg(env);

    if (!enif_is_list(env, argv[1]))
        return enif_make_badarg(env);

    rocksdb::ColumnFamilyOptions cf_options;
    ERL_NIF_TERM result = fold(env, argv[1], parse_cf_option, cf_options);
    if (result != ATOM_OK)
        return enif_make_badarg(env);

    rocksdb::Options options(rocksdb::DBOptions(), cf_options);
    rocksdb::EnvOptions env_options;

    rocksdb::SstFileWriter* writer = new rocksdb::SstFileWriter(env_options, options);
    rocksdb::Status status = writer->Open(path);
    if (!status.ok())
    {
        delete writer;
        return error_tuple(env, ATOM_ERROR, status);
    }

    SstFileWriterObject* ptr = SstFileWriterObject::CreateSstFileWriterResource(writer);
    ERL_NIF_TERM handle = enif_make_resource(env, ptr);
    enif_release_resource(ptr);
    return enif_make_tuple2(env, ATOM_OK, handle);
}

// sst_file_writer_put(Writer, Key, Value) -> ok | {error, _}
//
// Keys must be added in COMPARATOR ORDER. RocksDB refuses an out-of-order key
// rather than writing a file that cannot be read, and the refusal is returned
// here rather than swallowed.
ERL_NIF_TERM
SstFileWriterPut(ErlNifEnv* env, int /*argc*/, const ERL_NIF_TERM argv[])
{
    SstFileWriterObject* ptr = open_writer(env, argv[0]);
    if (ptr == NULL)
        return enif_make_badarg(env);

    rocksdb::Slice key, value;
    if (!binary_to_slice(env, argv[1], &key) || !binary_to_slice(env, argv[2], &value))
        return enif_make_badarg(env);

    rocksdb::Status status = ptr->writer()->Put(key, value);
    if (!status.ok())
        return error_tuple(env, ATOM_ERROR, status);
    return ATOM_OK;
}

// sst_file_writer_delete(Writer, Key) -> ok | {error, _}
ERL_NIF_TERM
SstFileWriterDelete(ErlNifEnv* env, int /*argc*/, const ERL_NIF_TERM argv[])
{
    SstFileWriterObject* ptr = open_writer(env, argv[0]);
    if (ptr == NULL)
        return enif_make_badarg(env);

    rocksdb::Slice key;
    if (!binary_to_slice(env, argv[1], &key))
        return enif_make_badarg(env);

    rocksdb::Status status = ptr->writer()->Delete(key);
    if (!status.ok())
        return error_tuple(env, ATOM_ERROR, status);
    return ATOM_OK;
}

// sst_file_writer_finish(Writer) -> {ok, Info} | {error, _}
//
// Info carries what was written, so a caller can assert the file holds the
// rows it put in it before ingesting -- a bulk rewrite that quietly produced
// an empty file is the failure this returns evidence against.
ERL_NIF_TERM
SstFileWriterFinish(ErlNifEnv* env, int /*argc*/, const ERL_NIF_TERM argv[])
{
    SstFileWriterObject* ptr = open_writer(env, argv[0]);
    if (ptr == NULL)
        return enif_make_badarg(env);

    rocksdb::ExternalSstFileInfo info;
    rocksdb::Status status = ptr->writer()->Finish(&info);
    if (!status.ok())
        return error_tuple(env, ATOM_ERROR, status);

    ERL_NIF_TERM map = enif_make_new_map(env);
    ERL_NIF_TERM term;

    unsigned char* buf = enif_make_new_binary(env, info.file_path.size(), &term);
    if (info.file_path.size() > 0)
        memcpy(buf, info.file_path.data(), info.file_path.size());
    enif_make_map_put(env, map, ATOM_FILE_PATH, term, &map);

    buf = enif_make_new_binary(env, info.smallest_key.size(), &term);
    if (info.smallest_key.size() > 0)
        memcpy(buf, info.smallest_key.data(), info.smallest_key.size());
    enif_make_map_put(env, map, ATOM_SMALLEST_KEY, term, &map);

    buf = enif_make_new_binary(env, info.largest_key.size(), &term);
    if (info.largest_key.size() > 0)
        memcpy(buf, info.largest_key.data(), info.largest_key.size());
    enif_make_map_put(env, map, ATOM_LARGEST_KEY, term, &map);

    enif_make_map_put(env, map, ATOM_FILE_SIZE, enif_make_uint64(env, info.file_size), &map);
    enif_make_map_put(env, map, ATOM_NUM_ENTRIES, enif_make_uint64(env, info.num_entries), &map);

    return enif_make_tuple2(env, ATOM_OK, map);
}

// sst_file_writer_close(Writer) -> ok
//
// Idempotent, and safe on a writer that was already finished: it releases the
// C++ object rather than closing the file a second time.
ERL_NIF_TERM
SstFileWriterClose(ErlNifEnv* env, int /*argc*/, const ERL_NIF_TERM argv[])
{
    SstFileWriterObject* ptr = SstFileWriterObject::RetrieveSstFileWriterResource(env, argv[0]);
    if (ptr == NULL)
        return enif_make_badarg(env);
    ptr->reset();
    return ATOM_OK;
}

static void
parse_ingest_option(ErlNifEnv* env, ERL_NIF_TERM item, rocksdb::IngestExternalFileOptions& opts)
{
    int arity;
    const ERL_NIF_TERM* option;
    if (!enif_get_tuple(env, item, &arity, &option) || arity != 2)
        return;

    bool on = (option[1] == ATOM_TRUE);
    if (option[0] == ATOM_MOVE_FILES)
        opts.move_files = on;
    else if (option[0] == ATOM_SNAPSHOT_CONSISTENCY)
        opts.snapshot_consistency = on;
    else if (option[0] == ATOM_ALLOW_GLOBAL_SEQNO)
        opts.allow_global_seqno = on;
    else if (option[0] == ATOM_ALLOW_BLOCKING_FLUSH)
        opts.allow_blocking_flush = on;
    else if (option[0] == ATOM_INGEST_BEHIND)
        opts.ingest_behind = on;
    else if (option[0] == ATOM_WRITE_GLOBAL_SEQNO)
        opts.write_global_seqno = on;
    else if (option[0] == ATOM_VERIFY_CHECKSUMS_BEFORE_INGEST)
        opts.verify_checksums_before_ingest = on;
}

// ingest_external_file(DB, Files, Opts) | ingest_external_file(DB, CF, Files, Opts)
ERL_NIF_TERM
IngestExternalFile(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ReferencePtr<DbObject> db_ptr;
    if (!enif_get_db(env, argv[0], &db_ptr))
        return enif_make_badarg(env);

    int i = (argc == 4) ? 2 : 1;

    if (!enif_is_list(env, argv[i]) || !enif_is_list(env, argv[i + 1]))
        return enif_make_badarg(env);

    std::vector<std::string> files;
    ERL_NIF_TERM head, tail = argv[i];
    while (enif_get_list_cell(env, tail, &head, &tail))
    {
        std::string file;
        if (!enif_get_std_string(env, head, file))
            return enif_make_badarg(env);
        files.push_back(file);
    }

    if (files.empty())
        return enif_make_badarg(env);

    rocksdb::IngestExternalFileOptions opts;
    tail = argv[i + 1];
    while (enif_get_list_cell(env, tail, &head, &tail))
        parse_ingest_option(env, head, opts);

    rocksdb::Status status;
    if (argc == 4)
    {
        ReferencePtr<ColumnFamilyObject> cf_ptr;
        if (!enif_get_cf(env, argv[1], &cf_ptr))
            return enif_make_badarg(env);
        status = db_ptr->m_Db->IngestExternalFile(cf_ptr->m_ColumnFamily, files, opts);
    }
    else
    {
        status = db_ptr->m_Db->IngestExternalFile(files, opts);
    }

    if (!status.ok())
        return error_tuple(env, ATOM_ERROR, status);
    return ATOM_OK;
}

}  // namespace erocksdb
