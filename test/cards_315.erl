%% -------------------------------------------------------------------
%% PersistenceStore#315: the RocksDB surface this binding did not expose.
%%
%% Every case here asserts BEHAVIOUR that the binding could not produce before,
%% not that a function compiles. A green compile of a NIF stub proves only that
%% the atom table has a new name in it.
%% -------------------------------------------------------------------
-module(cards_315).

-compile(export_all).

-include_lib("eunit/include/eunit.hrl").

-define(DIR, "cards315test").

open() ->
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref} = rocksdb:open(?DIR, [{create_if_missing, true}]),
    Ref.

with_db(Fun) ->
    Ref = open(),
    try
        Fun(Ref)
    after
        rocksdb:close(Ref)
    end.

put_seq(Ref, N) ->
    [ok = rocksdb:put(Ref, key(I), value(I), []) || I <- lists:seq(1, N)],
    ok.

key(I) -> list_to_binary(io_lib:format("k~6.10.0b", [I])).
value(I) -> list_to_binary(io_lib:format("v~6.10.0b", [I])).

%%====================================================================
%% item 1: key-only iteration
%%====================================================================

%% The discriminator is the SHAPE of the reply. iterator_move/2 answers
%% {ok, Key, Value} and there was no way to ask for the key alone -- fold_keys/4
%% drops the value in Erlang, after the NIF has copied it.
iterator_move_key_returns_the_key_alone_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 3),
        {ok, I} = rocksdb:iterator(Ref, []),
        try
            ?assertEqual({ok, key(1)}, rocksdb:iterator_move_key(I, first)),
            ?assertEqual({ok, key(2)}, rocksdb:iterator_move_key(I, next)),
            ?assertEqual({ok, key(1)}, rocksdb:iterator_move_key(I, prev)),
            ?assertEqual({ok, key(2)}, rocksdb:iterator_move_key(I, {seek, key(2)})),
            %% and the same iterator still answers the pair form, so the two
            %% share a position rather than being separate cursors
            ?assertEqual({ok, key(3), value(3)}, rocksdb:iterator_move(I, next))
        after
            rocksdb:iterator_close(I)
        end
    end).

iterator_move_key_reports_the_end_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 1),
        {ok, I} = rocksdb:iterator(Ref, []),
        try
            ?assertEqual({ok, key(1)}, rocksdb:iterator_move_key(I, first)),
            ?assertEqual({error, invalid_iterator}, rocksdb:iterator_move_key(I, next))
        after
            rocksdb:iterator_close(I)
        end
    end).

%% Batched, and it must return exactly the keys iterator_move_n/3 returns
%% values for -- the control that catches a key-only path walking a different
%% set of rows from the pair path.
iterator_move_keys_n_matches_the_pair_form_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 10),

        {ok, I1} = rocksdb:iterator(Ref, []),
        {ok, _, _} = rocksdb:iterator_move(I1, first),
        {ok, Pairs} = rocksdb:iterator_move_n(I1, next, 5),
        rocksdb:iterator_close(I1),

        {ok, I2} = rocksdb:iterator(Ref, []),
        {ok, _} = rocksdb:iterator_move_key(I2, first),
        {ok, Keys} = rocksdb:iterator_move_keys_n(I2, next, 5),
        rocksdb:iterator_close(I2),

        ?assertEqual(5, length(Keys)),
        ?assertEqual([K || {K, _V} <- Pairs], Keys),
        %% not vacuous: the pair form really did carry values
        ?assertEqual([value(I) || I <- lists:seq(2, 6)], [V || {_K, V} <- Pairs])
    end).

iterator_move_keys_n_stops_at_the_end_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 3),
        {ok, I} = rocksdb:iterator(Ref, []),
        try
            {ok, _} = rocksdb:iterator_move_key(I, first),
            %% asked for 100, three rows exist, two remain after the seek
            {ok, Keys} = rocksdb:iterator_move_keys_n(I, next, 100),
            ?assertEqual([key(2), key(3)], Keys)
        after
            rocksdb:iterator_close(I)
        end
    end).

%%====================================================================
%% item 2: table properties
%%====================================================================

%% num_entries is the whole point: a ROW COUNT without walking the rows.
%% get_approximate_sizes is already exposed and answers in compressed bytes,
%% which cannot be divided by a row size to get this.
table_properties_count_the_rows_without_reading_them_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 500),
        ok = rocksdb:flush(Ref, []),
        {ok, Props} = rocksdb:get_properties_of_all_tables(Ref),
        ?assert(length(Props) >= 1),
        Total = lists:sum([maps:get(num_entries, P) || P <- Props]),
        ?assertEqual(500, Total),
        [First | _] = Props,
        %% the rest of the property block came back too, and is plausible
        ?assert(maps:get(raw_key_size, First) > 0),
        ?assert(maps:get(raw_value_size, First) > 0),
        ?assert(maps:get(num_data_blocks, First) > 0),
        ?assert(is_binary(maps:get(file_name, First)))
    end).

%% A memtable has no SST file, so a store that has not flushed reports nothing
%% rather than a wrong number. Stating that here because it is the trap a
%% caller reconciling against disk would otherwise walk into.
table_properties_see_only_what_is_on_disk_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 10),
        {ok, Before} = rocksdb:get_properties_of_all_tables(Ref),
        ?assertEqual(0, lists:sum([maps:get(num_entries, P) || P <- Before])),
        ok = rocksdb:flush(Ref, []),
        {ok, After} = rocksdb:get_properties_of_all_tables(Ref),
        ?assertEqual(10, lists:sum([maps:get(num_entries, P) || P <- After]))
    end).

%% A range selects files, and a range outside the data selects none.
table_properties_in_range_select_files_test() ->
    %% Opened with an explicit column family, because the range call needs a
    %% CF handle and open/2 does not hand one back.
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref, [CF]} = rocksdb:open(
        ?DIR, [{create_if_missing, true}], [{"default", []}]),
    try
        ok = put_seq(Ref, 200),
        ok = rocksdb:flush(Ref, CF, []),

        {ok, Covering} = rocksdb:get_properties_of_tables_in_range(
            Ref, CF, [{key(1), key(999999)}]),
        ?assertEqual(200, lists:sum([maps:get(num_entries, P) || P <- Covering])),

        {ok, Beyond} = rocksdb:get_properties_of_tables_in_range(
            Ref, CF, [{<<"zzzz">>, <<"zzzzz">>}]),
        ?assertEqual([], Beyond),

        %% an empty range list is an empty answer, not an error
        ?assertEqual({ok, []}, rocksdb:get_properties_of_tables_in_range(Ref, CF, []))
    after
        rocksdb:close(Ref)
    end.

%%====================================================================
%% item 7: column family metadata
%%====================================================================

column_family_metadata_lists_the_files_per_level_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 100),
        ok = rocksdb:flush(Ref, []),
        {ok, Meta} = rocksdb:get_column_family_metadata(Ref),
        ?assertEqual(<<"default">>, maps:get(name, Meta)),
        ?assert(maps:get(size, Meta) > 0),
        ?assertEqual(1, maps:get(file_count, Meta)),

        Files = lists:append([maps:get(files, L) || L <- maps:get(levels, Meta)]),
        ?assertEqual(1, length(Files)),
        [File] = Files,
        ?assertEqual(100, maps:get(num_entries, File)),
        ?assertEqual(false, maps:get(being_compacted, File)),
        ?assertEqual(key(1), maps:get(smallest_key, File)),
        ?assertEqual(key(100), maps:get(largest_key, File)),
        ?assert(maps:get(size, File) > 0)
    end).

%%====================================================================
%% item 5: MultiGet
%%====================================================================

%% One result per key, in the order the keys were given, with a miss occupying
%% its own position. A shorter list would make a lost key indistinguishable
%% from a key that was never asked for.
multi_get_answers_in_key_order_with_misses_in_place_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 5),
        {ok, Res} = rocksdb:multi_get(
            Ref, [key(3), <<"absent">>, key(1), key(5)], []),
        ?assertEqual(
            [{ok, value(3)}, not_found, {ok, value(1)}, {ok, value(5)}],
            Res),
        %% and it agrees with get/3 key by key
        ?assertEqual({ok, value(3)}, rocksdb:get(Ref, key(3), [])),
        ?assertEqual(not_found, rocksdb:get(Ref, <<"absent">>, []))
    end).

multi_get_handles_an_empty_key_list_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 2),
        ?assertEqual({ok, []}, rocksdb:multi_get(Ref, [], []))
    end).

%%====================================================================
%% item 6: readahead_size and async_io
%%====================================================================

%% Both are performance hints with no visible effect on the answer, so the only
%% honest assertion is that they are ACCEPTED and change nothing about what
%% comes back. Before this they were silently ignored by the option parser,
%% which is indistinguishable from here -- so the real evidence is the read
%% below returning the same rows under every combination, plus the C++ parser
%% now having a branch for each. A test cannot see more than that without
%% instrumenting RocksDB itself.
readahead_and_async_io_are_accepted_read_options_test() ->
    with_db(fun(Ref) ->
        ok = put_seq(Ref, 20),
        ok = rocksdb:flush(Ref, []),
        Expected = [{key(I), value(I)} || I <- lists:seq(1, 20)],
        lists:foreach(
            fun(Opts) ->
                {ok, I} = rocksdb:iterator(Ref, Opts),
                try
                    ?assertEqual(Expected, drain(I))
                after
                    rocksdb:iterator_close(I)
                end
            end,
            [
                [],
                [{readahead_size, 1048576}],
                [{async_io, true}],
                [{readahead_size, 262144}, {async_io, true}]
            ]),
        %% the point form takes them too
        ?assertEqual(
            {ok, value(7)},
            rocksdb:get(Ref, key(7), [{readahead_size, 65536}, {async_io, false}]))
    end).

drain(I) ->
    case rocksdb:iterator_move(I, first) of
        {ok, K, V} -> drain(I, [{K, V}]);
        _ -> []
    end.

drain(I, Acc) ->
    case rocksdb:iterator_move(I, next) of
        {ok, K, V} -> drain(I, [{K, V} | Acc]);
        _ -> lists:reverse(Acc)
    end.

%%====================================================================
%% item 3: SstFileWriter + IngestExternalFile
%%====================================================================

%% The whole round trip: build a file outside the database, ingest it, read the
%% rows back through the normal read path.
sst_file_writer_builds_a_file_that_ingests_test() ->
    with_db(fun(Ref) ->
        Path = ?DIR ++ "/bulk.sst",
        {ok, W} = rocksdb:sst_file_writer_open(Path, []),
        [ok = rocksdb:sst_file_writer_put(W, key(I), value(I)) || I <- lists:seq(1, 50)],
        {ok, Info} = rocksdb:sst_file_writer_finish(W),
        ok = rocksdb:sst_file_writer_close(W),

        %% what was written is reported, so a rewrite that came out empty says so
        ?assertEqual(50, maps:get(num_entries, Info)),
        ?assertEqual(key(1), maps:get(smallest_key, Info)),
        ?assertEqual(key(50), maps:get(largest_key, Info)),
        ?assert(maps:get(file_size, Info) > 0),

        %% nothing is in the database until it is ingested
        ?assertEqual(not_found, rocksdb:get(Ref, key(1), [])),

        ok = rocksdb:ingest_external_file(Ref, [Path], []),
        ?assertEqual({ok, value(1)}, rocksdb:get(Ref, key(1), [])),
        ?assertEqual({ok, value(50)}, rocksdb:get(Ref, key(50), [])),

        %% and it arrived as a FILE, not row by row through the write path
        {ok, Props} = rocksdb:get_properties_of_all_tables(Ref),
        ?assertEqual(50, lists:sum([maps:get(num_entries, P) || P <- Props]))
    end).

%% Out-of-order keys are refused rather than written into a file nothing can
%% read. This is the failure mode a bulk rewrite is most likely to hit.
sst_file_writer_refuses_an_out_of_order_key_test() ->
    with_db(fun(_Ref) ->
        Path = ?DIR ++ "/unsorted.sst",
        {ok, W} = rocksdb:sst_file_writer_open(Path, []),
        try
            ok = rocksdb:sst_file_writer_put(W, key(10), value(10)),
            ?assertMatch({error, _}, rocksdb:sst_file_writer_put(W, key(2), value(2)))
        after
            rocksdb:sst_file_writer_close(W)
        end
    end).

%% close/1 is idempotent and safe after finish/1: a writer handle that goes out
%% of scope twice must not double-free the C++ object.
sst_file_writer_close_is_idempotent_test() ->
    with_db(fun(_Ref) ->
        Path = ?DIR ++ "/idem.sst",
        {ok, W} = rocksdb:sst_file_writer_open(Path, []),
        ok = rocksdb:sst_file_writer_put(W, key(1), value(1)),
        {ok, _} = rocksdb:sst_file_writer_finish(W),
        ?assertEqual(ok, rocksdb:sst_file_writer_close(W)),
        ?assertEqual(ok, rocksdb:sst_file_writer_close(W))
    end).

%%====================================================================
