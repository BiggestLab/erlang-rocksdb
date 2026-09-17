// -------------------------------------------------------------------
// Table properties and column-family metadata.
//
// PersistenceStore#315 item 2 and item 7. `count` is O(rows in the window) with no
// summary and no index; `get_approximate_sizes` is already exposed and answers
// in COMPRESSED BYTES, which cannot be divided by a row size to get a row count
// (measured: 1,097,568 bytes for a type holding 20,000 rows of 623 B, giving
// ~1,761 against a true 20,000). Per-SST `num_entries` is the number that can.
//
// Everything here is a metadata read: it consults the table property blocks
// RocksDB already keeps, never the data blocks. Measured on the same store as
// the count above, reading every range in one call takes 0.045 ms against a
// 29.8 ms exact walk of 20,000 rows.
// -------------------------------------------------------------------

#include <memory>
#include <string>
#include <vector>

#include "rocksdb/db.h"
#include "rocksdb/metadata.h"
#include "rocksdb/table_properties.h"

#include "atoms.h"
#include "erl_nif.h"
#include "erocksdb_db.h"
#include "refobjects.h"
#include "util.h"

namespace erocksdb {

static ERL_NIF_TERM
string_to_binary(ErlNifEnv* env, const std::string& s)
{
    ERL_NIF_TERM term;
    unsigned char* buf = enif_make_new_binary(env, s.size(), &term);
    if (s.size() > 0)
        memcpy(buf, s.data(), s.size());
    return term;
}

static void
put_u64(ErlNifEnv* env, ERL_NIF_TERM* map, ERL_NIF_TERM key, uint64_t value)
{
    enif_make_map_put(env, *map, key, enif_make_uint64(env, value), map);
}

// One SST file's property block, as a map. `num_entries` is the field this
// whole file exists for; the rest are free once the block has been read.
static ERL_NIF_TERM
table_properties_to_map(
    ErlNifEnv* env,
    const std::string& file_name,
    const rocksdb::TableProperties& props)
{
    ERL_NIF_TERM map = enif_make_new_map(env);
    enif_make_map_put(env, map, ATOM_FILE_NAME, string_to_binary(env, file_name), &map);
    put_u64(env, &map, ATOM_NUM_ENTRIES, props.num_entries);
    put_u64(env, &map, ATOM_NUM_DELETIONS, props.num_deletions);
    put_u64(env, &map, ATOM_NUM_MERGE_OPERANDS, props.num_merge_operands);
    put_u64(env, &map, ATOM_NUM_RANGE_DELETIONS, props.num_range_deletions);
    put_u64(env, &map, ATOM_NUM_DATA_BLOCKS, props.num_data_blocks);
    put_u64(env, &map, ATOM_DATA_SIZE, props.data_size);
    put_u64(env, &map, ATOM_INDEX_SIZE, props.index_size);
    put_u64(env, &map, ATOM_FILTER_SIZE, props.filter_size);
    put_u64(env, &map, ATOM_RAW_KEY_SIZE, props.raw_key_size);
    put_u64(env, &map, ATOM_RAW_VALUE_SIZE, props.raw_value_size);
    put_u64(env, &map, ATOM_CREATION_TIME, props.creation_time);
    put_u64(env, &map, ATOM_OLDEST_KEY_TIME, props.oldest_key_time);
    enif_make_map_put(
        env, map, ATOM_COLUMN_FAMILY_NAME,
        string_to_binary(env, props.column_family_name), &map);
    return map;
}

static ERL_NIF_TERM
collection_to_list(ErlNifEnv* env, const rocksdb::TablePropertiesCollection& props)
{
    ERL_NIF_TERM list = enif_make_list(env, 0);
    for (const auto& entry : props)
    {
        if (!entry.second)
            continue;
        list = enif_make_list_cell(
            env, table_properties_to_map(env, entry.first, *entry.second), list);
    }
    ERL_NIF_TERM out;
    enif_make_reverse_list(env, list, &out);
    return out;
}

// get_properties_of_all_tables(DB) | get_properties_of_all_tables(DB, CF)
ERL_NIF_TERM
GetPropertiesOfAllTables(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ReferencePtr<DbObject> db_ptr;
    if (!enif_get_db(env, argv[0], &db_ptr))
        return enif_make_badarg(env);

    rocksdb::TablePropertiesCollection props;
    rocksdb::Status status;

    if (argc == 2)
    {
        ReferencePtr<ColumnFamilyObject> cf_ptr;
        if (!enif_get_cf(env, argv[1], &cf_ptr))
            return enif_make_badarg(env);
        status = db_ptr->m_Db->GetPropertiesOfAllTables(cf_ptr->m_ColumnFamily, &props);
    }
    else
    {
        status = db_ptr->m_Db->GetPropertiesOfAllTables(&props);
    }

    if (!status.ok())
        return error_tuple(env, ATOM_ERROR, status);

    return enif_make_tuple2(env, ATOM_OK, collection_to_list(env, props));
}

// get_properties_of_tables_in_range(DB, CF, [{Start, Limit}])
//
// The binaries the ranges point into are owned by the caller's env and stay
// alive for the duration of this call, which is all RocksDB needs: it copies
// nothing and the collection it fills holds no reference to them.
ERL_NIF_TERM
GetPropertiesOfTablesInRange(ErlNifEnv* env, int /*argc*/, const ERL_NIF_TERM argv[])
{
    ReferencePtr<DbObject> db_ptr;
    if (!enif_get_db(env, argv[0], &db_ptr))
        return enif_make_badarg(env);

    ReferencePtr<ColumnFamilyObject> cf_ptr;
    if (!enif_get_cf(env, argv[1], &cf_ptr))
        return enif_make_badarg(env);

    if (!enif_is_list(env, argv[2]))
        return enif_make_badarg(env);

    std::vector<rocksdb::Range> ranges;
    ERL_NIF_TERM head, tail = argv[2];
    while (enif_get_list_cell(env, tail, &head, &tail))
    {
        int arity;
        const ERL_NIF_TERM* pair;
        if (!enif_get_tuple(env, head, &arity, &pair) || arity != 2)
            return enif_make_badarg(env);

        rocksdb::Slice start, limit;
        if (!binary_to_slice(env, pair[0], &start))
            return enif_make_badarg(env);
        if (!binary_to_slice(env, pair[1], &limit))
            return enif_make_badarg(env);
        ranges.push_back(rocksdb::Range(start, limit));
    }

    if (ranges.empty())
        return enif_make_tuple2(env, ATOM_OK, enif_make_list(env, 0));

    rocksdb::TablePropertiesCollection props;
    rocksdb::Status status = db_ptr->m_Db->GetPropertiesOfTablesInRange(
        cf_ptr->m_ColumnFamily, ranges.data(), ranges.size(), &props);

    if (!status.ok())
        return error_tuple(env, ATOM_ERROR, status);

    return enif_make_tuple2(env, ATOM_OK, collection_to_list(env, props));
}

static ERL_NIF_TERM
sst_file_to_map(ErlNifEnv* env, const rocksdb::SstFileMetaData& file)
{
    ERL_NIF_TERM map = enif_make_new_map(env);
    enif_make_map_put(env, map, ATOM_FILE_NAME, string_to_binary(env, file.name), &map);
    put_u64(env, &map, ATOM_SIZE, file.size);
    put_u64(env, &map, ATOM_NUM_ENTRIES, file.num_entries);
    put_u64(env, &map, ATOM_NUM_DELETIONS, file.num_deletions);
    enif_make_map_put(
        env, map, ATOM_SMALLEST_KEY, string_to_binary(env, file.smallestkey), &map);
    enif_make_map_put(
        env, map, ATOM_LARGEST_KEY, string_to_binary(env, file.largestkey), &map);
    enif_make_map_put(
        env, map, ATOM_BEING_COMPACTED,
        file.being_compacted ? ATOM_TRUE : ATOM_FALSE, &map);
    return map;
}

// get_column_family_metadata(DB) | get_column_family_metadata(DB, CF)
//
// PersistenceStore#315 item 7, and the storage-health half of PersistenceStore#295: per-level file
// listing and sizes, which `get_property` cannot give as structured data.
ERL_NIF_TERM
GetColumnFamilyMetaData(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ReferencePtr<DbObject> db_ptr;
    if (!enif_get_db(env, argv[0], &db_ptr))
        return enif_make_badarg(env);

    rocksdb::ColumnFamilyMetaData meta;
    if (argc == 2)
    {
        ReferencePtr<ColumnFamilyObject> cf_ptr;
        if (!enif_get_cf(env, argv[1], &cf_ptr))
            return enif_make_badarg(env);
        db_ptr->m_Db->GetColumnFamilyMetaData(cf_ptr->m_ColumnFamily, &meta);
    }
    else
    {
        db_ptr->m_Db->GetColumnFamilyMetaData(&meta);
    }

    ERL_NIF_TERM levels = enif_make_list(env, 0);
    for (auto it = meta.levels.rbegin(); it != meta.levels.rend(); ++it)
    {
        ERL_NIF_TERM files = enif_make_list(env, 0);
        for (auto f = it->files.rbegin(); f != it->files.rend(); ++f)
            files = enif_make_list_cell(env, sst_file_to_map(env, *f), files);

        ERL_NIF_TERM level = enif_make_new_map(env);
        enif_make_map_put(
            env, level, ATOM_LEVEL, enif_make_int(env, it->level), &level);
        put_u64(env, &level, ATOM_SIZE, it->size);
        enif_make_map_put(env, level, ATOM_FILES, files, &level);
        levels = enif_make_list_cell(env, level, levels);
    }

    ERL_NIF_TERM map = enif_make_new_map(env);
    enif_make_map_put(env, map, ATOM_NAME, string_to_binary(env, meta.name), &map);
    put_u64(env, &map, ATOM_SIZE, meta.size);
    put_u64(env, &map, ATOM_FILE_COUNT, meta.file_count);
    enif_make_map_put(env, map, ATOM_LEVELS, levels, &map);
    return enif_make_tuple2(env, ATOM_OK, map);
}

}  // namespace erocksdb
