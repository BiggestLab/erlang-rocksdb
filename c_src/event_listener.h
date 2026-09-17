// -------------------------------------------------------------------
// EventListener: RocksDB background events delivered to an Erlang process.
// PersistenceStore#315 item 4, for PersistenceStore#295.
//
// Write stalls, compaction backlog and memtable flushes can only be POLLED
// through get_property/2 and stats, and a poll cannot see an event that starts
// and ends between two polls. These are the events themselves.
// -------------------------------------------------------------------

#pragma once
#ifndef INCL_EVENT_LISTENER_H
#define INCL_EVENT_LISTENER_H

#include <cstdint>

#include "erl_nif.h"

namespace rocksdb {
    struct DBOptions;
}

namespace erocksdb {

  // One bit per event, so a listener can ask for the three PersistenceStore#295 wants
  // without also taking every table-file deletion on a busy store.
  enum EventBit : uint32_t {
      EVENT_FLUSH_BEGIN             = 1u << 0,
      EVENT_FLUSH_COMPLETED         = 1u << 1,
      EVENT_COMPACTION_BEGIN        = 1u << 2,
      EVENT_COMPACTION_COMPLETED    = 1u << 3,
      EVENT_MEMTABLE_SEALED         = 1u << 4,
      EVENT_STALL_CONDITIONS_CHANGED = 1u << 5,
      EVENT_BACKGROUND_ERROR        = 1u << 6,
      EVENT_EXTERNAL_FILE_INGESTED  = 1u << 7,
      EVENT_TABLE_FILE_DELETED      = 1u << 8,
      EVENT_ALL                     = 0xFFFFFFFFu
  };

  // Parses `{listener, Pid}` or `{listener, {Pid, [EventAtom]}}` and appends a
  // listener to `opts.listeners`. Returns 0 on a shape it does not recognise.
  int parse_listener_option(ErlNifEnv* env, ERL_NIF_TERM value, rocksdb::DBOptions& opts);

}

#endif
