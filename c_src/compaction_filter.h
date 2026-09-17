// -------------------------------------------------------------------
// Compaction-time rules. PersistenceStore#315 item 8.
//
// Retention and the PersistenceStore#313 quarantine both want to express themselves as a
// rule applied while RocksDB is already rewriting the data, rather than as a
// separate rewrite pass that reads and writes everything a second time.
//
// The rule is supplied from Erlang as DATA and evaluated in C++. The other
// shape -- RocksDB calling a BEAM process per key and waiting -- would put one
// blocking round trip on every key of every compaction, on a thread that holds
// the compaction up, and a stalled compaction stalls writes.
// -------------------------------------------------------------------

#pragma once
#ifndef INCL_COMPACTION_FILTER_H
#define INCL_COMPACTION_FILTER_H

#include <cstdint>
#include <string>
#include <vector>

#include "erl_nif.h"

namespace rocksdb {
    struct ColumnFamilyOptions;
}

namespace erocksdb {

  enum class RuleKind {
      DropKeyRange,
      DropBelowDecimal
  };

  struct CompactionRule {
      RuleKind kind;
      // DropKeyRange: [start, limit)
      std::string start;
      std::string limit;
      // DropBelowDecimal: the fixed-width decimal field at [offset, offset+width)
      size_t offset = 0;
      size_t width = 0;
      uint64_t cutoff = 0;
  };

  // Parses `{compaction_filter, [Rule]}` and installs a factory on `opts`.
  // Returns 0 on a shape it does not recognise.
  int parse_compaction_filter_option(
      ErlNifEnv* env, ERL_NIF_TERM value, rocksdb::ColumnFamilyOptions& opts);

  // Parses `{compact_on_deletion, {Window, Trigger}}` or
  // `{compact_on_deletion, {Window, Trigger, Ratio}}`.
  int parse_compact_on_deletion_option(
      ErlNifEnv* env, ERL_NIF_TERM value, rocksdb::ColumnFamilyOptions& opts);

}

#endif
