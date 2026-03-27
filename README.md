# erlang-rocksdb

Erlang NIF wrapper for [RocksDB](https://rocksdb.org/).

Originally by Benoit Chesneau (barrel-db). Forked and maintained by [BiggestLab](https://github.com/BiggestLab/erlang-rocksdb).

## Features

- RocksDB 10.10.1 (upgraded from 7.7.3)
- Bundled compression: Snappy, LZ4, LZ4HC, ZSTD (all statically linked, no runtime dependencies)
- Erlang/OTP 27+ with dirty-nif scheduling
- C++20 required (GCC 11+ or Clang 10+)
- All core DB operations: open, get, put, delete, merge
- Batch writes (WriteBatch)
- Snapshots and checkpoints
- Column families
- Secondary database instances (read replicas)
- Transaction log iteration
- Backup and restore
- Erlang merge operators (including bitset and counter)
- Batch iterator: `iterator_move_n/3` for reading N key-value pairs in a single NIF call
- `compact_range/5` with `bottommost_level_compaction` option (force, skip, force_optimized)
- Cache management: `new_cache/2` for shared LRU/Clock caches
- Configurable compression per column family and per LSM level
- Tested on Linux and macOS

## Requirements

- Erlang/OTP 27 or later
- cmake >= 3.5
- C++20 compiler (GCC 12+, Clang 14+)
- make, git

## Installation

Add to your `rebar.config`:

```erlang
{deps, [
    {rocksdb, {git, "https://github.com/BiggestLab/erlang-rocksdb.git", {branch, "master"}}}
]}.
```

The first build compiles the bundled RocksDB C++ library (takes 1-2 minutes).

## Quick Start

```erlang
%% Open a database
{ok, DB} = rocksdb:open("/tmp/mydb", [{create_if_missing, true}]).

%% Put and get
ok = rocksdb:put(DB, <<"key1">>, <<"value1">>, []).
{ok, <<"value1">>} = rocksdb:get(DB, <<"key1">>, []).

%% Delete
ok = rocksdb:delete(DB, <<"key1">>, []).
not_found = rocksdb:get(DB, <<"key1">>, []).

%% Close
ok = rocksdb:close(DB).
```

## Column Families

```erlang
%% Open with column families
{ok, DB, [DefaultCF, DataCF]} = rocksdb:open_with_cf(
    "/tmp/mydb",
    [{create_if_missing, true}],
    [{"default", []}, {"data", [{compression, zstd}]}]
).

%% Put/get with column family
ok = rocksdb:put(DB, DataCF, <<"key">>, <<"value">>, []).
{ok, <<"value">>} = rocksdb:get(DB, DataCF, <<"key">>, []).

ok = rocksdb:close(DB).
```

## Compression

All compression algorithms are statically linked. Configure per column family:

```erlang
%% Available: snappy | lz4 | lz4h | zstd | zlib | bzip2 | none
CFOpts = [
    {compression, zstd},
    {bottommost_compression, zstd},
    {compression_opts, [{level, 9}]}   %% ZSTD compression level (1-22)
].

{ok, DB, [CF]} = rocksdb:open_with_cf(
    "/tmp/compressed",
    [{create_if_missing, true}],
    [{"default", CFOpts}]
).
```

## Block Cache

Create a shared LRU cache for improved read performance:

```erlang
{ok, Cache} = rocksdb:new_cache(lru, 536870912),  %% 512 MB
CFOpts = [
    {block_based_table_options, [{block_cache, Cache}]}
].
```

## Iterators

```erlang
%% Basic iteration
{ok, Iter} = rocksdb:iterator(DB, []).
{ok, Key, Value} = rocksdb:iterator_move(Iter, first).
{ok, Key2, Value2} = rocksdb:iterator_move(Iter, next).
ok = rocksdb:iterator_close(Iter).

%% Batch iteration: read N entries in a single NIF call
{ok, Iter} = rocksdb:iterator(DB, []).
{ok, _, _} = rocksdb:iterator_move(Iter, first).
{ok, Pairs} = rocksdb:iterator_move_n(Iter, next, 200).
%% Pairs = [{Key, Value}, ...]
ok = rocksdb:iterator_close(Iter).
```

## Compaction

```erlang
%% Force compaction on a column family
ok = rocksdb:compact_range(DB, CF, undefined, undefined, []).

%% Force rewrite of bottommost level (applies new compression settings)
ok = rocksdb:compact_range(DB, CF, undefined, undefined,
    [{bottommost_level_compaction, force}]).
```

## Secondary Instances

Open a read-only secondary that follows the primary:

```erlang
{ok, SecDB} = rocksdb:open_secondary("/tmp/mydb", "/tmp/mydb_sec", []).
{ok, Value} = rocksdb:get(SecDB, <<"key">>, []).
ok = rocksdb:try_catch_up_with_primary(SecDB).
```

## Customized Build

Override cmake options via the `ERLANG_ROCKSDB_OPTS` environment variable:

```bash
export ERLANG_ROCKSDB_OPTS="-DWITH_BUNDLE_LZ4=ON -DWITH_BUNDLE_SNAPPY=ON -DWITH_BUNDLE_ZSTD=ON"
rebar3 compile
```

See [doc/customize_rocksdb_build.md](doc/customize_rocksdb_build.md) for details.

## License

Apache License 2.0 (same as RocksDB).
