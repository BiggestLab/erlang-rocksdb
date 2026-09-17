// -------------------------------------------------------------------
// PersistenceStore#315 item 8: compaction-time rules.
// -------------------------------------------------------------------

#include <memory>
#include <string>
#include <vector>

#include "rocksdb/compaction_filter.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"
#include "rocksdb/utilities/table_properties_collectors.h"

#include "atoms.h"
#include "compaction_filter.h"
#include "erl_nif.h"
#include "util.h"

namespace erocksdb {

// A filter built from rules the caller supplied at open time.
//
// Every callback runs on a RocksDB compaction thread. Nothing here allocates,
// takes a lock, or calls into the VM: it is byte comparison and a decimal
// parse, so the cost is proportional to the key length and nothing else.
//
// 🔴 A rule can only ever DROP. There is no kChangeValue and no kKeep-with-new
// -value, because a rewrite that alters values during a compaction is a
// migration wearing a filter's clothes, and a migration should be visible in
// the code that asked for it.
class RuleCompactionFilter : public rocksdb::CompactionFilter {
public:
    explicit RuleCompactionFilter(std::vector<CompactionRule> rules)
        : rules_(std::move(rules)) {}

    const char* Name() const override { return "erocksdb.RuleCompactionFilter"; }

    rocksdb::CompactionFilter::Decision FilterV2(
        int /*level*/,
        const rocksdb::Slice& key,
        rocksdb::CompactionFilter::ValueType value_type,
        const rocksdb::Slice& /*existing_value*/,
        std::string* /*new_value*/,
        std::string* /*skip_until*/) const override
    {
        // Plain values only. Dropping a merge operand changes what a later
        // merge computes, and the RocksDB header warns that filtering one
        // under a TransactionDB can let a conflicting transaction commit.
        if (value_type != rocksdb::CompactionFilter::ValueType::kValue)
            return rocksdb::CompactionFilter::Decision::kKeep;

        for (const auto& rule : rules_)
        {
            if (matches(rule, key))
                return rocksdb::CompactionFilter::Decision::kRemove;
        }
        return rocksdb::CompactionFilter::Decision::kKeep;
    }

private:
    static bool matches(const CompactionRule& rule, const rocksdb::Slice& key)
    {
        switch (rule.kind)
        {
            case RuleKind::DropKeyRange:
                return in_range(rule, key);
            case RuleKind::DropBelowDecimal:
                return below_decimal(rule, key);
        }
        return false;
    }

    // [start, limit): start inclusive, limit exclusive, the same convention
    // delete_range and the iterator bounds use.
    static bool in_range(const CompactionRule& rule, const rocksdb::Slice& key)
    {
        rocksdb::Slice start(rule.start);
        rocksdb::Slice limit(rule.limit);
        return key.compare(start) >= 0 && key.compare(limit) < 0;
    }

    // A fixed-width decimal field inside the key, below a cutoff.
    //
    // 🔴 A key too short to hold the field, or holding something that is not
    // all digits, is KEPT. A rule that cannot read a key has not decided
    // anything about it, and dropping on a failed parse is how a retention
    // rule silently deletes the rows whose keys it did not understand --
    // which, on this platform, is exactly the malformed-key population
    // PersistenceStore#313 exists to deal with.
    static bool below_decimal(const CompactionRule& rule, const rocksdb::Slice& key)
    {
        if (rule.width == 0 || key.size() < rule.offset + rule.width)
            return false;

        const char* p = key.data() + rule.offset;
        uint64_t value = 0;
        for (size_t i = 0; i < rule.width; i++)
        {
            char c = p[i];
            if (c < '0' || c > '9')
                return false;
            uint64_t digit = static_cast<uint64_t>(c - '0');
            // A field wide enough to overflow is not a number we can compare.
            if (value > (UINT64_MAX - digit) / 10)
                return false;
            value = value * 10 + digit;
        }
        return value < rule.cutoff;
    }

    std::vector<CompactionRule> rules_;
};

class RuleCompactionFilterFactory : public rocksdb::CompactionFilterFactory {
public:
    explicit RuleCompactionFilterFactory(std::vector<CompactionRule> rules)
        : rules_(std::move(rules)) {}

    const char* Name() const override { return "erocksdb.RuleCompactionFilterFactory"; }

    std::unique_ptr<rocksdb::CompactionFilter> CreateCompactionFilter(
        const rocksdb::CompactionFilter::Context& /*context*/) override
    {
        return std::unique_ptr<rocksdb::CompactionFilter>(new RuleCompactionFilter(rules_));
    }

private:
    std::vector<CompactionRule> rules_;
};

static int
get_binary_string(ErlNifEnv* env, ERL_NIF_TERM term, std::string& out)
{
    ErlNifBinary bin;
    if (!enif_inspect_binary(env, term, &bin))
        return 0;
    out.assign(reinterpret_cast<const char*>(bin.data), bin.size);
    return 1;
}

static int
parse_rule(ErlNifEnv* env, ERL_NIF_TERM term, CompactionRule& rule)
{
    int arity;
    const ERL_NIF_TERM* t;
    if (!enif_get_tuple(env, term, &arity, &t))
        return 0;

    if (arity == 3 && t[0] == ATOM_DROP_KEY_RANGE)
    {
        rule.kind = RuleKind::DropKeyRange;
        if (!get_binary_string(env, t[1], rule.start))
            return 0;
        if (!get_binary_string(env, t[2], rule.limit))
            return 0;
        // An empty or inverted range would match nothing, which is a rule that
        // cannot fire -- refuse it rather than install it.
        return rule.start < rule.limit ? 1 : 0;
    }

    if (arity == 4 && t[0] == ATOM_DROP_BELOW_DECIMAL)
    {
        rule.kind = RuleKind::DropBelowDecimal;
        ErlNifUInt64 offset, width, cutoff;
        if (!enif_get_uint64(env, t[1], &offset))
            return 0;
        if (!enif_get_uint64(env, t[2], &width) || width == 0 || width > 20)
            return 0;
        if (!enif_get_uint64(env, t[3], &cutoff))
            return 0;
        rule.offset = static_cast<size_t>(offset);
        rule.width = static_cast<size_t>(width);
        rule.cutoff = static_cast<uint64_t>(cutoff);
        return 1;
    }

    return 0;
}

int
parse_compaction_filter_option(
    ErlNifEnv* env, ERL_NIF_TERM value, rocksdb::ColumnFamilyOptions& opts)
{
    if (!enif_is_list(env, value))
        return 0;

    std::vector<CompactionRule> rules;
    ERL_NIF_TERM head, tail = value;
    while (enif_get_list_cell(env, tail, &head, &tail))
    {
        CompactionRule rule;
        if (!parse_rule(env, head, rule))
            return 0;
        rules.push_back(rule);
    }

    // An empty rule list is refused rather than installing a filter that keeps
    // everything: a caller who built the list from a query that returned
    // nothing should hear about it, not get a filter that quietly does nothing.
    if (rules.empty())
        return 0;

    opts.compaction_filter_factory =
        std::make_shared<RuleCompactionFilterFactory>(std::move(rules));
    return 1;
}

// A table-property collector that marks a file as needing compaction once it
// holds enough tombstones. Pure configuration -- no filter, no callback -- and
// the other half of what a retention rule needs: the rule decides WHAT to drop,
// this decides WHEN RocksDB bothers to rewrite the file that holds it.
int
parse_compact_on_deletion_option(
    ErlNifEnv* env, ERL_NIF_TERM value, rocksdb::ColumnFamilyOptions& opts)
{
    int arity;
    const ERL_NIF_TERM* t;
    if (!enif_get_tuple(env, value, &arity, &t))
        return 0;
    if (arity != 2 && arity != 3)
        return 0;

    ErlNifUInt64 window, trigger;
    if (!enif_get_uint64(env, t[0], &window) || window == 0)
        return 0;
    if (!enif_get_uint64(env, t[1], &trigger) || trigger == 0)
        return 0;

    double ratio = 0.0;
    if (arity == 3)
    {
        if (!enif_get_double(env, t[2], &ratio))
        {
            ErlNifUInt64 as_int;
            if (!enif_get_uint64(env, t[2], &as_int))
                return 0;
            ratio = static_cast<double>(as_int);
        }
    }

    opts.table_properties_collector_factories.emplace_back(
        rocksdb::NewCompactOnDeletionCollectorFactory(
            static_cast<size_t>(window), static_cast<size_t>(trigger), ratio));
    return 1;
}

}  // namespace erocksdb
