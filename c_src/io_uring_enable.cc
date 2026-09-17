// io_uring: the switch, not the wiring.
//
// RocksDB gates every io_uring path on IsIOUringEnabled(), which reaches the
// embedding application through a WEAK declaration -- deps/rocksdb/env/fs_posix.cc:
//
//     extern "C" bool RocksDbIOUringEnable() __attribute__((__weak__));
//     ...
//     bool IsIOUringEnabled() {
//       if (RocksDbIOUringEnable && RocksDbIOUringEnable()) {
//
// An embedder that never defines it leaves the weak symbol null, so
// IsIOUringEnabled() is false and RocksDB takes the synchronous path -- however
// carefully liburing was linked.
//
// That is what this fork shipped until now. `nm` on the built NIF:
//
//     liburing.so.2 => /lib/x86_64-linux-gnu/liburing.so.2   <- DT_NEEDED, fine
//     U io_uring_queue_init@LIBURING_2.0                     <- imported, fine
//     w RocksDbIOUringEnable                                 <- weak UNDEFINED
//
// The lowercase `w` is the whole defect. Making WITH_LIBURING a hard build
// error (see CMakeLists) fixed a real and different bug -- the NIF used to load
// with "undefined symbol: io_uring_queue_init" -- but it linked a feature that
// was never switched on.
//
// Defining it strong here is the switch. RocksDB's own tests do exactly this;
// see deps/rocksdb/env/env_test.cc and block_based_table_reader_test.cc.
//
// What it turns on, both from env/fs_posix.cc:
//
//   - SupportedOps() advertises kAsyncIO, which is what gives the `async_io`
//     read option any meaning at all;
//   - PosixRandomAccessFile is handed the thread-local async-read and
//     multi-read io_uring instances, so MultiRead -- and therefore MultiGet --
//     submits batched reads through io_uring instead of one pread at a time.
//
// Both only pay on reads that MISS the block cache and reach the disk. A
// workload served out of the 512 MB block cache will not notice this, and a
// measurement that does not separate cold reads from warm ones will report
// nothing either way.
//
// ROCKSDB_IOURING_PRESENT is set by RocksDB's own build when it detects
// liburing; the io_uring_* imports above prove it was set for this artifact.
// If it were not, the code this enables would be compiled out and this
// definition would be inert rather than wrong.

extern "C" bool RocksDbIOUringEnable() { return true; }
