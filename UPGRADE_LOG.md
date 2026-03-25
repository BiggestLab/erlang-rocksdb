# RocksDB Upgrade Log: 7.7.3 → 10.10.1

## Status: ALL 115 TESTS PASSING

## Issues Found & Fixed

### Issue 1: C++20 Required ✅ FIXED
- RocksDB 10.7+ requires C++20
- Changed `CXX_STANDARD 17` → `CXX_STANDARD 20` in CMakeLists.txt

### Issue 2: `access_hint_on_compaction_start` Removed ✅ FIXED
- Removed in RocksDB 9.0
- Commented out the ATOM_ACCESS_HINT handler in erocksdb_db.cc

### Issue 3: Snappy symbol missing (`_ZTIN6snappy4SinkE`) ✅ FIXED
- RocksDB 10.x compiled with USE_RTTI=1 requires typeinfo from snappy's Sink class
- Bundled snappy had `-fno-rtti` in CMakeLists.txt which stripped typeinfo
- Fix: Patched deps/snappy/CMakeLists.txt to keep RTTI enabled
- Also needed `--whole-archive` for static linking of rocksdb + compression libs

### Issue 4: cmake dependency paths ✅ FIXED
- RocksDB 10.x uses `find_package(Snappy CONFIG)` which needs cmake config files
- Fixed by passing `Snappy_DIR=NOTFOUND` to skip CONFIG mode, falling back to FindSnappy.cmake
- Passing `*_ROOT_DIR` variables which FindSnappy/FindLZ4/Findzstd use for path hints

### Issue 5: ExternalProject cmake cache conflict ✅ FIXED (via ROOT_DIR approach)

## Files Changed
- `c_src/CMakeLists.txt` — C++20, --whole-archive linking
- `c_src/CMake/build-rocksdb.cmake` — cmake dependency paths
- `c_src/CMake/build-snappy.cmake` — RTTI flag
- `c_src/erocksdb_db.cc` — removed access_hint handler
- `deps/rocksdb/` — replaced 7.7.3 with 10.10.1
- `deps/snappy/CMakeLists.txt` — RTTI patch
