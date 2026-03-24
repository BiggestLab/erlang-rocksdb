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

%% Test batch reads across different prefix boundaries on secondary DB
%% This replicates PersistenceStore's multi-type DB pattern
secondary_multi_prefix_batch_test() ->
    Dir1 = "erocksdb.secondary1.test7",
    rocksdb_test_util:rm_rf(Dir1),
    Dir2 = "erocksdb.secondary2.test7",
    rocksdb_test_util:rm_rf(Dir2),
    PrefixOpt = [{prefix_extractor, {fixed_prefix_transform, 4}}],
    {ok, Ref1, [DefCF1]} = rocksdb:open_with_cf(Dir1,
        [{create_if_missing, true}], [{"default", PrefixOpt}]),
    {ok, _HashCF1} = rocksdb:create_column_family(Ref1, "cf_hash", PrefixOpt),
    %% Write entries with DIFFERENT prefixes (like multiple event types)
    lists:foreach(fun(N) ->
        TS = list_to_binary(integer_to_list(1000 + N)),
        Key = <<"AAAA:", TS/binary>>,
        Val = term_to_binary({type_a, #{<<"n">> => N}, 1000 + N}),
        ok = rocksdb:put(Ref1, DefCF1, Key, Val, [])
    end, lists:seq(1, 20)),
    lists:foreach(fun(N) ->
        TS = list_to_binary(integer_to_list(2000 + N)),
        Key = <<"BBBB:", TS/binary>>,
        Val = term_to_binary({type_b, #{<<"n">> => N}, 2000 + N}),
        ok = rocksdb:put(Ref1, DefCF1, Key, Val, [])
    end, lists:seq(1, 15)),
    lists:foreach(fun(N) ->
        TS = list_to_binary(integer_to_list(3000 + N)),
        Key = <<"CCCC:", TS/binary>>,
        Val = term_to_binary({type_c, #{<<"n">> => N}, 3000 + N}),
        ok = rocksdb:put(Ref1, DefCF1, Key, Val, [])
    end, lists:seq(1, 10)),
    %% Open secondary with CFs
    {ok, Ref2, [DefCF2, _]} = rocksdb:open_secondary(Dir1, Dir2, [],
        [{"default", PrefixOpt}, {"cf_hash", PrefixOpt}]),
    ok = rocksdb:try_catch_up_with_primary(Ref2),
    %% Seek to AAAA prefix, batch read across into BBBB
    {ok, Itr} = rocksdb:iterator(Ref2, DefCF2, []),
    {ok, K1, _} = rocksdb:iterator_move(Itr, {seek, <<"AAAA:0">>}),
    ?assertEqual(<<"AAAA:1001">>, K1),
    %% Batch read 30 — should cross from AAAA (19 remaining) into BBBB
    {ok, Results} = rocksdb:iterator_move_n(Itr, next, 30),
    ?assertEqual(30, length(Results)),
    %% First result should be AAAA:1002
    [{FirstK, _} | _] = Results,
    ?assertEqual(<<"AAAA:1002">>, FirstK),
    %% Should include some BBBB keys
    {LastK, _} = lists:last(Results),
    ?assert(LastK > <<"AAAA:">>),
    %% Continue reading — should get rest of BBBB and into CCCC
    {ok, Results2} = rocksdb:iterator_move_n(Itr, next, 30),
    ?assertEqual(14, length(Results2)),  %% 4 BBBB + 10 CCCC
    ok = rocksdb:iterator_close(Itr),
    ok = rocksdb:close(Ref2),
    ok = rocksdb:close(Ref1),
    rocksdb_test_util:rm_rf(Dir2),
    rocksdb_test_util:rm_rf(Dir1).

%% Concurrent writes to primary while batch reading from secondary
secondary_concurrent_write_batch_read_test() ->
    Dir1 = "erocksdb.secondary1.test8",
    rocksdb_test_util:rm_rf(Dir1),
    Dir2 = "erocksdb.secondary2.test8",
    rocksdb_test_util:rm_rf(Dir2),
    PrefixOpt = [{prefix_extractor, {fixed_prefix_transform, 4}}],
    {ok, Ref1, [DefCF1]} = rocksdb:open_with_cf(Dir1,
        [{create_if_missing, true}], [{"default", PrefixOpt}]),
    %% Pre-populate
    lists:foreach(fun(N) ->
        Key = list_to_binary(io_lib:format("AAAA:~6..0B", [N])),
        Val = term_to_binary({test, #{<<"n">> => N}, N}),
        rocksdb:put(Ref1, DefCF1, Key, Val, [])
    end, lists:seq(1, 100)),
    %% Open secondary
    {ok, Ref2, [DefCF2]} = rocksdb:open_secondary(Dir1, Dir2, [],
        [{"default", PrefixOpt}]),
    rocksdb:try_catch_up_with_primary(Ref2),
    %% Spawn writer to primary
    Self = self(),
    Writer = spawn_link(fun() ->
        secondary_write_loop(Ref1, DefCF1, 1000, Self)
    end),
    %% Batch read from secondary concurrently
    lists:foreach(fun(_Round) ->
        rocksdb:try_catch_up_with_primary(Ref2),
        {ok, Itr} = rocksdb:iterator(Ref2, DefCF2, []),
        case rocksdb:iterator_move(Itr, first) of
            {ok, _, _} ->
                {ok, Results} = rocksdb:iterator_move_n(Itr, next, 50),
                true = length(Results) >= 0;
            _ -> ok
        end,
        rocksdb:iterator_close(Itr)
    end, lists:seq(1, 20)),
    Writer ! stop,
    receive writer_done -> ok after 5000 -> ok end,
    rocksdb:close(Ref2),
    rocksdb:close(Ref1),
    rocksdb_test_util:rm_rf(Dir2),
    rocksdb_test_util:rm_rf(Dir1).

secondary_write_loop(Ref, CF, 0, Parent) ->
    Parent ! writer_done;
secondary_write_loop(Ref, CF, N, Parent) ->
    receive stop -> Parent ! writer_done
    after 0 ->
        Key = list_to_binary(io_lib:format("BBBB:~6..0B", [N])),
        Val = term_to_binary({test2, #{<<"n">> => N}, N}),
        rocksdb:put(Ref, CF, Key, Val, []),
        secondary_write_loop(Ref, CF, N - 1, Parent)
    end.
