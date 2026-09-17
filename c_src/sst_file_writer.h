// -------------------------------------------------------------------
// SstFileWriter as an Erlang resource. cards#315 item 3.
//
// Bulk-build a rewritten store and ingest it, instead of re-keying row by row
// through the write path. This is the shape the cards#313 repair migration
// wants, and the shape any future rewrite wants.
// -------------------------------------------------------------------

#pragma once
#ifndef INCL_SST_FILE_WRITER_H
#define INCL_SST_FILE_WRITER_H

#include <memory>

#include "erl_nif.h"

namespace rocksdb {
    class SstFileWriter;
}

namespace erocksdb {

  class SstFileWriterObject {
    protected:
      static ErlNifResourceType* m_SstFileWriter_RESOURCE;

    public:
      explicit SstFileWriterObject(rocksdb::SstFileWriter* writer);
      ~SstFileWriterObject();

      rocksdb::SstFileWriter* writer();
      void reset();

      static void CreateSstFileWriterType(ErlNifEnv* env);
      static void SstFileWriterResourceCleanup(ErlNifEnv* env, void* arg);

      static SstFileWriterObject* CreateSstFileWriterResource(rocksdb::SstFileWriter* writer);
      static SstFileWriterObject* RetrieveSstFileWriterResource(
          ErlNifEnv* env, const ERL_NIF_TERM& term);

    private:
      rocksdb::SstFileWriter* writer_;
  };

  ERL_NIF_TERM SstFileWriterOpen(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
  ERL_NIF_TERM SstFileWriterPut(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
  ERL_NIF_TERM SstFileWriterDelete(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
  ERL_NIF_TERM SstFileWriterFinish(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
  ERL_NIF_TERM SstFileWriterClose(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
  ERL_NIF_TERM IngestExternalFile(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);

}

#endif
