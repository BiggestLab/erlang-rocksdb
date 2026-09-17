%% -------------------------------------------------------------------
%% cards#315 items 4 and 8: background events, and compaction-time rules.
%%
%% Both are OPTIONS, not functions, so the failure mode they share is being
%% silently ignored: a store that never notifies reads exactly like a store
%% with nothing to report, and a filter that never fires reads exactly like a
%% store with nothing to drop. Every case here therefore asserts that the
%% thing HAPPENED, and the refusal cases assert that a bad option is refused at
%% open time rather than accepted and forgotten.
%% -------------------------------------------------------------------
-module(cards_315_events).

-compile(export_all).

-include_lib("eunit/include/eunit.hrl").

-define(DIR, "cards315events").

key(I) -> list_to_binary(io_lib:format("k~6.10.0b", [I])).
value(I) -> list_to_binary(io_lib:format("v~6.10.0b", [I])).

put_seq(Ref, From, To) ->
    [ok = rocksdb:put(Ref, key(I), value(I), []) || I <- lists:seq(From, To)],
    ok.

%% Drain the mailbox of rocksdb_event messages, waiting up to Timeout in TOTAL
%% for the background threads that raise them.
%%
%% The first draft waited Timeout after EACH message, so a compaction raising
%% four events waited four times over and blew eunit's per-case limit -- which
%% cancels the rest of the module, so five cases reported and seven never ran.
collect_events(Timeout) ->
    Deadline = erlang:monotonic_time(millisecond) + Timeout,
    collect_events(Deadline, []).

collect_events(Deadline, Acc) ->
    Remaining = Deadline - erlang:monotonic_time(millisecond),
    case Remaining > 0 of
        false ->
            lists:reverse(Acc);
        true ->
            receive
                {rocksdb_event, Name, Info} ->
                    collect_events(Deadline, [{Name, Info} | Acc])
            after Remaining ->
                lists:reverse(Acc)
            end
    end.

flush_mailbox() ->
    receive
        _ -> flush_mailbox()
    after 0 -> ok
    end.

%%====================================================================
%% item 4: EventListener
%%====================================================================

%% A flush is the event a caller can provoke deterministically, so it is the
%% one that proves the channel works at all: the message arrives, it names the
%% column family, and it carries the row count of the file that was written.
listener_reports_a_flush_test_() ->
    {timeout, 30, fun listener_reports_a_flush/0}.

listener_reports_a_flush() ->
    flush_mailbox(),
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref} = rocksdb:open(
        ?DIR, [{create_if_missing, true}, {listener, self()}]),
    try
        ok = put_seq(Ref, 1, 100),
        ok = rocksdb:flush(Ref, []),
        Events = collect_events(2000),
        Names = [N || {N, _} <- Events],
        ?assert(lists:member(flush_completed, Names)),
        {flush_completed, Info} = lists:keyfind(flush_completed, 1, Events),
        ?assertEqual(<<"default">>, maps:get(cf_name, Info)),
        ?assertEqual(100, maps:get(num_entries, Info)),
        ?assert(is_binary(maps:get(file_path, Info))),
        ?assert(is_integer(maps:get(job_id, Info))),
        %% begin and completed are distinct events, not one delivered twice
        ?assert(lists:member(flush_begin, Names))
    after
        rocksdb:close(Ref)
    end.

%% The control for every case above: WITHOUT the option, nothing arrives. A
%% test that only asserts a message can pass against a build that sends the
%% same message for some other reason.
no_listener_means_no_messages_test() ->
    flush_mailbox(),
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref} = rocksdb:open(?DIR, [{create_if_missing, true}]),
    try
        ok = put_seq(Ref, 1, 100),
        ok = rocksdb:flush(Ref, []),
        ?assertEqual([], collect_events(500))
    after
        rocksdb:close(Ref)
    end.

%% A named subset delivers those events and NOT the others. Without this a
%% filter that ignored its argument and sent everything would pass the case
%% above.
listener_honours_an_event_subset_test_() ->
    {timeout, 30, fun listener_honours_an_event_subset/0}.

listener_honours_an_event_subset() ->
    flush_mailbox(),
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref} = rocksdb:open(
        ?DIR,
        [{create_if_missing, true}, {listener, {self(), [flush_completed]}}]),
    try
        ok = put_seq(Ref, 1, 50),
        ok = rocksdb:flush(Ref, []),
        Names = lists:usort([N || {N, _} <- collect_events(2000)]),
        ?assertEqual([flush_completed], Names)
    after
        rocksdb:close(Ref)
    end.

%% An unknown event name is refused at OPEN, not accepted and forgotten.
listener_refuses_an_unknown_event_name_test() ->
    rocksdb_test_util:rm_rf(?DIR),
    ?assertError(
        badarg,
        rocksdb:open(
            ?DIR,
            [{create_if_missing, true}, {listener, {self(), [flush_complete]}}])),
    %% ... and the correctly spelled one opens, so the refusal is about the
    %% name and not about the shape
    {ok, Ref} = rocksdb:open(
        ?DIR,
        [{create_if_missing, true}, {listener, {self(), [flush_completed]}}]),
    rocksdb:close(Ref).

listener_refuses_a_value_that_is_not_a_pid_test() ->
    rocksdb_test_util:rm_rf(?DIR),
    ?assertError(
        badarg,
        rocksdb:open(?DIR, [{create_if_missing, true}, {listener, not_a_pid}])).

%% A compaction raises its own events, with the input and output row counts a
%% caller watching for backlog needs.
listener_reports_a_compaction_test_() ->
    {timeout, 60, fun listener_reports_a_compaction/0}.

listener_reports_a_compaction() ->
    flush_mailbox(),
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref} = rocksdb:open(
        ?DIR,
        [{create_if_missing, true},
         {listener, {self(), [compaction_begin, compaction_completed]}}]),
    try
        %% Two files whose key ranges OVERLAP, so the compaction has something
        %% to merge and cannot be satisfied by a trivial move.
        ok = put_seq(Ref, 1, 100),
        ok = rocksdb:flush(Ref, []),
        ok = put_seq(Ref, 50, 150),
        ok = rocksdb:flush(Ref, []),
        ok = rocksdb:compact_range(Ref, undefined, undefined, []),
        Events = collect_events(5000),
        Names = [N || {N, _} <- Events],
        ?assert(lists:member(compaction_completed, Names)),
        {compaction_completed, Info} = lists:keyfind(compaction_completed, 1, Events),
        ?assertEqual(<<"default">>, maps:get(cf_name, Info)),
        %% 201 rows written across two files, 51 of them twice: the merge reads
        %% every version and emits one per key.
        ?assertEqual(201, maps:get(num_input_records, Info)),
        ?assertEqual(150, maps:get(num_output_records, Info)),
        ?assertEqual(<<"OK">>, maps:get(status, Info)),
        ?assert(is_integer(maps:get(output_level, Info)))
    after
        rocksdb:close(Ref)
    end.

%%====================================================================
%% item 8: compaction-time rules
%%====================================================================

%% The quarantine shape. The rows are written normally and are readable; the
%% rule removes them when RocksDB next rewrites the file, and the rows OUTSIDE
%% the range survive -- which is the half that catches a filter dropping
%% everything.
compaction_rule_drops_a_key_range_test() ->
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref, [CF]} = rocksdb:open(
        ?DIR,
        [{create_if_missing, true}],
        [{"default", [{compaction_filter, [{drop_key_range, key(20), key(30)}]}]}]),
    try
        ok = put_seq(Ref, 1, 50),
        ok = rocksdb:flush(Ref, CF, []),

        %% Before the compaction the rows are all still there: the filter runs
        %% at compaction time, not at write time.
        ?assertEqual({ok, value(25)}, rocksdb:get(Ref, key(25), [])),

        ok = rocksdb:compact_range(Ref, CF, undefined, undefined, []),

        %% [20, 30) is gone ...
        ?assertEqual(not_found, rocksdb:get(Ref, key(20), [])),
        ?assertEqual(not_found, rocksdb:get(Ref, key(25), [])),
        ?assertEqual(not_found, rocksdb:get(Ref, key(29), [])),
        %% ... and the boundaries are half-open, as the range says
        ?assertEqual({ok, value(19)}, rocksdb:get(Ref, key(19), [])),
        ?assertEqual({ok, value(30)}, rocksdb:get(Ref, key(30), [])),
        %% ... and everything else survived
        ?assertEqual({ok, value(1)}, rocksdb:get(Ref, key(1), [])),
        ?assertEqual({ok, value(50)}, rocksdb:get(Ref, key(50), [])),
        {ok, Props} = rocksdb:get_properties_of_all_tables(Ref, CF),
        ?assertEqual(40, lists:sum([maps:get(num_entries, P) || P <- Props]))
    after
        rocksdb:close(Ref)
    end.

%% The retention shape, against the key layout this platform actually uses:
%% a 4-byte type hash, a separator, then a 19-digit zero-padded publisher
%% timestamp at offset 5.
compaction_rule_drops_below_a_decimal_field_test_() ->
    {timeout, 30, fun compaction_rule_drops_below_a_decimal_field/0}.

compaction_rule_drops_below_a_decimal_field() ->
    rocksdb_test_util:rm_rf(?DIR),
    Base = 1775895451995000000,
    Cutoff = Base + 25,
    {ok, Ref, [CF]} = rocksdb:open(
        ?DIR,
        [{create_if_missing, true}],
        [{"default", [{compaction_filter, [{drop_below_decimal, 5, 19, Cutoff}]}]}]),
    try
        Ts = fun(I) -> list_to_binary(io_lib:format("~19.10.0b", [Base + I])) end,
        TsKey = fun(I) -> <<1, 2, 3, 4, ":", (Ts(I))/binary>> end,
        [ok = rocksdb:put(Ref, TsKey(I), value(I), []) || I <- lists:seq(1, 50)],

        %% A key too SHORT to hold the field must survive: a rule that cannot
        %% read a key has not decided anything about it, and dropping on a
        %% failed parse is how retention silently eats malformed keys.
        ok = rocksdb:put(Ref, <<1, 2, 3, 4, ":short">>, <<"keepme">>, []),
        %% ... and so must one whose field is not all digits.
        NotDigits = <<1, 2, 3, 4, ":", "not-a-number-here!!", "tail">>,
        ok = rocksdb:put(Ref, NotDigits, <<"keepme">>, []),

        ok = rocksdb:flush(Ref, CF, []),
        ok = rocksdb:compact_range(Ref, CF, undefined, undefined, []),

        ?assertEqual(not_found, rocksdb:get(Ref, TsKey(1), [])),
        ?assertEqual(not_found, rocksdb:get(Ref, TsKey(24), [])),
        ?assertEqual({ok, value(25)}, rocksdb:get(Ref, TsKey(25), [])),
        ?assertEqual({ok, value(50)}, rocksdb:get(Ref, TsKey(50), [])),
        ?assertEqual({ok, <<"keepme">>}, rocksdb:get(Ref, <<1, 2, 3, 4, ":short">>, [])),
        ?assertEqual({ok, <<"keepme">>}, rocksdb:get(Ref, NotDigits, []))
    after
        rocksdb:close(Ref)
    end.

%% Several rules, any of which drops.
compaction_rules_combine_test() ->
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref, [CF]} = rocksdb:open(
        ?DIR,
        [{create_if_missing, true}],
        [{"default", [{compaction_filter,
                       [{drop_key_range, key(10), key(15)},
                        {drop_key_range, key(40), key(45)}]}]}]),
    try
        ok = put_seq(Ref, 1, 50),
        ok = rocksdb:flush(Ref, CF, []),
        ok = rocksdb:compact_range(Ref, CF, undefined, undefined, []),
        ?assertEqual(not_found, rocksdb:get(Ref, key(12), [])),
        ?assertEqual(not_found, rocksdb:get(Ref, key(42), [])),
        ?assertEqual({ok, value(25)}, rocksdb:get(Ref, key(25), [])),
        {ok, Props} = rocksdb:get_properties_of_all_tables(Ref, CF),
        ?assertEqual(40, lists:sum([maps:get(num_entries, P) || P <- Props]))
    after
        rocksdb:close(Ref)
    end.

%% Without the option the same corpus and the same compaction keep every row.
%% This is what makes the cases above statements about the filter rather than
%% about compaction.
no_compaction_filter_drops_nothing_test() ->
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref, [CF]} = rocksdb:open(
        ?DIR, [{create_if_missing, true}], [{"default", []}]),
    try
        ok = put_seq(Ref, 1, 50),
        ok = rocksdb:flush(Ref, CF, []),
        ok = rocksdb:compact_range(Ref, CF, undefined, undefined, []),
        ?assertEqual({ok, value(25)}, rocksdb:get(Ref, key(25), [])),
        {ok, Props} = rocksdb:get_properties_of_all_tables(Ref, CF),
        ?assertEqual(50, lists:sum([maps:get(num_entries, P) || P <- Props]))
    after
        rocksdb:close(Ref)
    end.

%% A rule this build does not know, an empty rule list, and an inverted range
%% are all refused at open. Each of them would otherwise install a filter that
%% quietly does nothing.
compaction_filter_refuses_a_rule_it_cannot_apply_test() ->
    rocksdb_test_util:rm_rf(?DIR),
    Bad = [
        [{drop_everything, <<"a">>}],
        [],
        [{drop_key_range, key(30), key(20)}],
        [{drop_key_range, key(1), key(2)}, {nonsense, 1, 2, 3}],
        [{drop_below_decimal, 5, 0, 100}]
    ],
    lists:foreach(
        fun(Rules) ->
            ?assertError(
                badarg,
                rocksdb:open(
                    ?DIR,
                    [{create_if_missing, true}],
                    [{"default", [{compaction_filter, Rules}]}]))
        end,
        Bad).

%% compact_on_deletion is configuration, so the assertion is that it is
%% ACCEPTED in both arities and that a malformed one is refused -- there is no
%% observable behaviour to assert without driving RocksDB's own compaction
%% heuristics, and a test that pretended otherwise would be asserting RocksDB.
compact_on_deletion_is_accepted_and_validated_test() ->
    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref, [_]} = rocksdb:open(
        ?DIR,
        [{create_if_missing, true}],
        [{"default", [{compact_on_deletion, {1000, 100}}]}]),
    rocksdb:close(Ref),

    rocksdb_test_util:rm_rf(?DIR),
    {ok, Ref2, [_]} = rocksdb:open(
        ?DIR,
        [{create_if_missing, true}],
        [{"default", [{compact_on_deletion, {1000, 100, 0.5}}]}]),
    rocksdb:close(Ref2),

    rocksdb_test_util:rm_rf(?DIR),
    ?assertError(
        badarg,
        rocksdb:open(
            ?DIR,
            [{create_if_missing, true}],
            [{"default", [{compact_on_deletion, {0, 100}}]}])),
    ?assertError(
        badarg,
        rocksdb:open(
            ?DIR,
            [{create_if_missing, true}],
            [{"default", [{compact_on_deletion, not_a_tuple}]}])).
