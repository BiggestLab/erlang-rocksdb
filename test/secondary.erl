-module(secondary).


-include_lib("eunit/include/eunit.hrl").


secondary_connection_test() ->
    Dir1 = "erocksdb.secondary1.test1",
    rocksdb_test_util:rm_rf(Dir1),
    Dir2 = "erocksdb.secondary2.test1",
    rocksdb_test_util:rm_rf(Dir2),
    {ok, Ref1} = rocksdb:open(Dir1, [{create_if_missing, true}]),
    ok = rocksdb:put(Ref1, <<"abc">>, <<"123">>, []),
    {ok, Ref2} = rocksdb:open_secondary(Dir1, Dir2, []),
    {ok, <<"123">>} = rocksdb:get(Ref2, <<"abc">>, []),
    ok = rocksdb:put(Ref1, <<"def">>, <<"456">>, []),
    not_found = rocksdb:get(Ref2, <<"def">>, []),
    ok = rocksdb:try_catch_up_with_primary(Ref2),
    {ok, <<"456">>} = rocksdb:get(Ref2, <<"def">>, []),
    ok = rocksdb:close(Ref2),
    ok = rocksdb:close(Ref1),
    rocksdb_test_util:rm_rf(Dir2),
    rocksdb_test_util:rm_rf(Dir1).


secondary_connection_with_cf_test() ->
    Dir1 = "erocksdb.secondary1.test2",
    rocksdb_test_util:rm_rf(Dir1),
    Dir2 = "erocksdb.secondary2.test2",
    rocksdb_test_util:rm_rf(Dir2),
    {ok, Ref1, [DefaultCF1, AnotherCF1]} = rocksdb:open(Dir1,
        [{create_if_missing, true}, {create_missing_column_families, true}],
        [{"default", []}, {"another", []}]),
    ok = rocksdb:put(Ref1, <<"abc">>, <<"123">>, []),
    {ok, Ref2, [DefaultCF2, AnotherCF2]} = rocksdb:open_secondary(Dir1, Dir2, [],
        [{"default", []}, {"another", []}]),
    {ok, <<"123">>} = rocksdb:get(Ref2, <<"abc">>, []),
    ok = rocksdb:put(Ref1, <<"def">>, <<"456">>, []),
    not_found = rocksdb:get(Ref2, <<"def">>, []),
    ok = rocksdb:try_catch_up_with_primary(Ref2),
    {ok, <<"456">>} = rocksdb:get(Ref2, <<"def">>, []),
    ok = rocksdb:close(Ref2),
    ok = rocksdb:close(Ref1),
    rocksdb_test_util:rm_rf(Dir2),
    rocksdb_test_util:rm_rf(Dir1).

%% Exact PersistenceStore pattern: prefix_extractor + secondary with CFs
secondary_prefix_batch_test() ->
    Dir1 = "erocksdb.secondary1.test6",
    rocksdb_test_util:rm_rf(Dir1),
    Dir2 = "erocksdb.secondary2.test6",
    rocksdb_test_util:rm_rf(Dir2),
    PrefixOpt = [{prefix_extractor, {fixed_prefix_transform, 4}}],
    {ok, Ref1, [DefCF1]} = rocksdb:open_with_cf(Dir1,
        [{create_if_missing, true}], [{"default", PrefixOpt}]),
    {ok, _HashCF1} = rocksdb:create_column_family(Ref1, "cf_hash", PrefixOpt),
    lists:foreach(fun(N) ->
        TS = list_to_binary(integer_to_list(1000 + N)),
        Key = <<"AAAA:", TS/binary>>,
        Val = term_to_binary({test_type, #{<<"n">> => N}, 1000 + N}),
        ok = rocksdb:put(Ref1, DefCF1, Key, Val, [])
    end, lists:seq(1, 30)),
    {ok, Ref2, [DefCF2, _HashCF2]} = rocksdb:open_secondary(Dir1, Dir2, [],
        [{"default", PrefixOpt}, {"cf_hash", PrefixOpt}]),
    ok = rocksdb:try_catch_up_with_primary(Ref2),
    {ok, Itr} = rocksdb:iterator(Ref2, DefCF2, []),
    {ok, K1, _V1} = rocksdb:iterator_move(Itr, {seek, <<"AAAA:0">>}),
    ?assertEqual(<<"AAAA:1001">>, K1),
    {ok, Results} = rocksdb:iterator_move_n(Itr, next, 10),
    ?assertEqual(10, length(Results)),
    {ok, Results2} = rocksdb:iterator_move_n(Itr, next, 20),
    ?assertEqual(19, length(Results2)),
    ok = rocksdb:iterator_close(Itr),
    ok = rocksdb:close(Ref2),
    ok = rocksdb:close(Ref1),
    rocksdb_test_util:rm_rf(Dir2),
    rocksdb_test_util:rm_rf(Dir1).
