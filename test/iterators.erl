%% -------------------------------------------------------------------
%%
%%  eleveldb: Erlang Wrapper for LevelDB (http://code.google.com/p/leveldb/)
%%
%% Copyright (c) 2010-2013 Basho Technologies, Inc. All Rights Reserved.
%%
%% This file is provided to you under the Apache License,
%% Version 2.0 (the "License"); you may not use this file
%% except in compliance with the License.  You may obtain
%% a copy of the License at
%%
%%   http://www.apache.org/licenses/LICENSE-2.0
%%
%% Unless required by applicable law or agreed to in writing,
%% software distributed under the License is distributed on an
%% "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
%% KIND, either express or implied.  See the License for the
%% specific language governing permissions and limitations
%% under the License.
%%
%% -------------------------------------------------------------------
-module(iterators).

-compile(export_all).

-include_lib("eunit/include/eunit.hrl").

prev_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"x">>, []),
    rocksdb:put(Ref, <<"b">>, <<"y">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(I, <<>>)),
    ?assertEqual({ok, <<"b">>, <<"y">>},rocksdb:iterator_move(I, next)),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(I, prev)),
    ?assertEqual(ok, rocksdb:iterator_close(I))
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

seek_for_prev_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"1">>, []),
    rocksdb:put(Ref, <<"b">>, <<"2">>, []),
    rocksdb:put(Ref, <<"c">>, <<"3">>, []),
    rocksdb:put(Ref, <<"e">>, <<"4">>, []),

    {ok, I} = rocksdb:iterator(Ref, []),
    ?assertEqual({ok, <<"b">>, <<"2">>},rocksdb:iterator_move(I, {seek_for_prev, <<"b">>})),
    ?assertEqual({ok, <<"c">>, <<"3">>},rocksdb:iterator_move(I, {seek_for_prev, <<"d">>})),
    ?assertEqual({ok, <<"e">>, <<"4">>},rocksdb:iterator_move(I, next)),
    ?assertEqual(ok, rocksdb:iterator_close(I))
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").


cf_iterator_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref, [DefaultH]} = rocksdb:open_with_cf("ltest", [{create_if_missing, true}], [{"default", []}]),
  {ok, TestH} = rocksdb:create_column_family(Ref, "test", []),
  try
    rocksdb:put(Ref, DefaultH, <<"a">>, <<"x">>, []),
    rocksdb:put(Ref, DefaultH, <<"b">>, <<"y">>, []),
    rocksdb:put(Ref, TestH, <<"a">>, <<"x1">>, []),
    rocksdb:put(Ref, TestH, <<"b">>, <<"y1">>, []),

    {ok, DefaultIt} = rocksdb:iterator(Ref, DefaultH, []),
    {ok, TestIt} = rocksdb:iterator(Ref, TestH, []),

    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(DefaultIt, <<>>)),
    ?assertEqual({ok, <<"a">>, <<"x1">>},rocksdb:iterator_move(TestIt, <<>>)),
    ?assertEqual({ok, <<"b">>, <<"y">>},rocksdb:iterator_move(DefaultIt, next)),
    ?assertEqual({ok, <<"b">>, <<"y1">>},rocksdb:iterator_move(TestIt, next)),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(DefaultIt, prev)),
    ?assertEqual({ok, <<"a">>, <<"x1">>},rocksdb:iterator_move(TestIt, prev)),
    ok = rocksdb:iterator_close(TestIt),
    ok = rocksdb:iterator_close(DefaultIt)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

cf_iterators_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref, [DefaultH]} = rocksdb:open_with_cf("ltest", [{create_if_missing, true}], [{"default", []}]),
  {ok, TestH} = rocksdb:create_column_family(Ref, "test", []),
  try
    rocksdb:put(Ref, DefaultH, <<"a">>, <<"x">>, []),
    rocksdb:put(Ref, DefaultH, <<"b">>, <<"y">>, []),
    rocksdb:put(Ref, TestH, <<"a">>, <<"x1">>, []),
    rocksdb:put(Ref, TestH, <<"b">>, <<"y1">>, []),

    {ok, [DefaultIt, TestIt]} = rocksdb:iterators(Ref, [DefaultH, TestH], []),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(DefaultIt, <<>>)),
    ?assertEqual({ok, <<"a">>, <<"x1">>},rocksdb:iterator_move(TestIt, <<>>)),
    ?assertEqual({ok, <<"b">>, <<"y">>},rocksdb:iterator_move(DefaultIt, next)),
    ?assertEqual({ok, <<"b">>, <<"y1">>},rocksdb:iterator_move(TestIt, next)),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(DefaultIt, prev)),
    ?assertEqual({ok, <<"a">>, <<"x1">>},rocksdb:iterator_move(TestIt, prev)),
    ok = rocksdb:iterator_close(TestIt),
    ok = rocksdb:iterator_close(DefaultIt)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").


drop_cf_with_iterator_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref, [DefaultH]} = rocksdb:open_with_cf("ltest", [{create_if_missing, true}], [{"default", []}]),
  {ok, TestH} = rocksdb:create_column_family(Ref, "test", []),
  try
    rocksdb:put(Ref, DefaultH, <<"a">>, <<"x">>, []),
    rocksdb:put(Ref, DefaultH, <<"b">>, <<"y">>, []),
    rocksdb:put(Ref, TestH, <<"a">>, <<"x1">>, []),
    rocksdb:put(Ref, TestH, <<"b">>, <<"y1">>, []),

    {ok, DefaultIt} = rocksdb:iterator(Ref, DefaultH, []),
    {ok, TestIt} = rocksdb:iterator(Ref, TestH, []),

    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(DefaultIt, <<>>)),
    ?assertEqual({ok, <<"a">>, <<"x1">>},rocksdb:iterator_move(TestIt, <<>>)),

    ok = rocksdb:drop_column_family(TestH),

    %% make sure we can read the read iterator
    ?assertEqual({ok, <<"b">>, <<"y">>},rocksdb:iterator_move(DefaultIt, next)),
    ?assertEqual({ok, <<"b">>, <<"y1">>},rocksdb:iterator_move(TestIt, next)),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(DefaultIt, prev)),
    ?assertEqual({ok, <<"a">>, <<"x1">>},rocksdb:iterator_move(TestIt, prev)),
    ok = rocksdb:iterator_close(TestIt),
    ok = rocksdb:iterator_close(DefaultIt)

  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

refresh_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"x">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    rocksdb:put(Ref, <<"b">>, <<"y">>, []),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(I, <<>>)),
    ?assertEqual({error, invalid_iterator},rocksdb:iterator_move(I, next)),
    ?assertEqual(ok, rocksdb:iterator_refresh(I)),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(I, <<>>)),
    ?assertEqual({ok, <<"b">>, <<"y">>},rocksdb:iterator_move(I, next)),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(I, prev)),
    ?assertEqual(ok, rocksdb:iterator_refresh(I)),
    ?assertEqual({error, invalid_iterator},rocksdb:iterator_move(I, next)),
    ?assertEqual(ok, rocksdb:iterator_close(I)),
    ?assertError(badarg, rocksdb:iterator_refresh(I))
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

iterate_upper_bound_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"x">>, []),
    rocksdb:put(Ref, <<"b">>, <<"y">>, []),
    rocksdb:put(Ref, <<"d">>, <<"z">>, []),
    {ok, I} = rocksdb:iterator(Ref, [{iterate_upper_bound, <<"c">>}]),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(I, <<>>)),
    ?assertEqual({ok, <<"b">>, <<"y">>},rocksdb:iterator_move(I, next)),
    ?assertEqual({error, invalid_iterator},rocksdb:iterator_move(I, next)),
    ?assertEqual(ok, rocksdb:iterator_close(I))
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

iterate_outer_bound_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"x">>, []),
    rocksdb:put(Ref, <<"c">>, <<"y">>, []),
    rocksdb:put(Ref, <<"d">>, <<"z">>, []),
    {ok, I} = rocksdb:iterator(Ref, [{iterate_lower_bound, <<"b">>}]),
    ?assertEqual({ok, <<"d">>, <<"z">>},rocksdb:iterator_move(I, last)),
    ?assertEqual({ok, <<"c">>, <<"y">>},rocksdb:iterator_move(I, prev)),
    ?assertEqual({error, invalid_iterator},rocksdb:iterator_move(I, prev)),
    ?assertEqual(ok, rocksdb:iterator_close(I))
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

prefix_same_as_start_test() ->
  rocksdb_test_util:rm_rf("test_prefix"),  % NOTE
  {ok, Ref} = rocksdb:open("test_prefix", [{create_if_missing, true},
                                           {prefix_extractor, {fixed_prefix_transform, 8}}]),
  try

    ok = put_key(Ref, 12345, 6, <<"v16">>),
    ok = put_key(Ref, 12345, 7, <<"v17">>),
    ok = put_key(Ref, 12345, 8, <<"v18">>),
    ok = put_key(Ref, 12345, 9, <<"v19">>),
    ok = put_key(Ref, 12346, 8, <<"v16">>),
    ok = rocksdb:flush(Ref, []),

    {ok, I} = rocksdb:iterator(Ref, [{prefix_same_as_start, true}]),

    ?assertEqual({ok, test_key(12345, 6), <<"v16">>}, rocksdb:iterator_move(I, test_key(12345, 6))),
    ?assertEqual({ok, test_key(12345, 7), <<"v17">>}, rocksdb:iterator_move(I, next)),
    ?assertEqual({ok, test_key(12345, 8), <<"v18">>}, rocksdb:iterator_move(I, next)),
    ?assertEqual({ok, test_key(12345, 9), <<"v19">>}, rocksdb:iterator_move(I, next)),
    ?assertEqual({error, invalid_iterator}, rocksdb:iterator_move(I, next)),

    ?assertEqual(ok, rocksdb:iterator_close(I)),
    ?assertError(badarg, rocksdb:iterator_refresh(I))
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("test_prefix", []),
  rocksdb_test_util:rm_rf("test_prefix").


invalid_test() ->
  rocksdb_test_util:rm_rf("ltest"),  % NOTE
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"x">>, []),
    rocksdb:put(Ref, <<"b">>, <<"y">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    ?assertEqual({error, invalid_iterator}, rocksdb:iterator_move(I, next)),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(I, <<>>)),
    ?assertEqual({ok, <<"b">>, <<"y">>},rocksdb:iterator_move(I, next)),
    ?assertEqual({ok, <<"a">>, <<"x">>},rocksdb:iterator_move(I, prev)),
    ?assertEqual(ok, rocksdb:iterator_close(I))
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").


%% ---- iterator_move_n tests ----

move_n_next_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"1">>, []),
    rocksdb:put(Ref, <<"b">>, <<"2">>, []),
    rocksdb:put(Ref, <<"c">>, <<"3">>, []),
    rocksdb:put(Ref, <<"d">>, <<"4">>, []),
    rocksdb:put(Ref, <<"e">>, <<"5">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    %% Position at first entry
    ?assertEqual({ok, <<"a">>, <<"1">>}, rocksdb:iterator_move(I, first)),
    %% Batch read next 3
    {ok, Results} = rocksdb:iterator_move_n(I, next, 3),
    ?assertEqual([{<<"b">>, <<"2">>}, {<<"c">>, <<"3">>}, {<<"d">>, <<"4">>}], Results),
    %% Iterator should now be at <<"d">>, so next should be <<"e">>
    ?assertEqual({ok, <<"e">>, <<"5">>}, rocksdb:iterator_move(I, next)),
    ok = rocksdb:iterator_close(I)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

move_n_prev_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"1">>, []),
    rocksdb:put(Ref, <<"b">>, <<"2">>, []),
    rocksdb:put(Ref, <<"c">>, <<"3">>, []),
    rocksdb:put(Ref, <<"d">>, <<"4">>, []),
    rocksdb:put(Ref, <<"e">>, <<"5">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    %% Position at last entry
    ?assertEqual({ok, <<"e">>, <<"5">>}, rocksdb:iterator_move(I, last)),
    %% Batch read prev 3
    {ok, Results} = rocksdb:iterator_move_n(I, prev, 3),
    ?assertEqual([{<<"d">>, <<"4">>}, {<<"c">>, <<"3">>}, {<<"b">>, <<"2">>}], Results),
    %% Iterator should now be at <<"b">>, so prev should be <<"a">>
    ?assertEqual({ok, <<"a">>, <<"1">>}, rocksdb:iterator_move(I, prev)),
    ok = rocksdb:iterator_close(I)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

move_n_partial_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"1">>, []),
    rocksdb:put(Ref, <<"b">>, <<"2">>, []),
    rocksdb:put(Ref, <<"c">>, <<"3">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    %% Position at first
    ?assertEqual({ok, <<"a">>, <<"1">>}, rocksdb:iterator_move(I, first)),
    %% Request 10 but only 2 remain after current position
    {ok, Results} = rocksdb:iterator_move_n(I, next, 10),
    ?assertEqual([{<<"b">>, <<"2">>}, {<<"c">>, <<"3">>}], Results),
    ok = rocksdb:iterator_close(I)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

move_n_empty_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"a">>, <<"1">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    %% Position at last (and only) entry
    ?assertEqual({ok, <<"a">>, <<"1">>}, rocksdb:iterator_move(I, last)),
    %% No more entries to read forward
    {ok, Results} = rocksdb:iterator_move_n(I, next, 5),
    ?assertEqual([], Results),
    ok = rocksdb:iterator_close(I)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

move_n_cf_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref, [DefaultH]} = rocksdb:open_with_cf("ltest", [{create_if_missing, true}], [{"default", []}]),
  {ok, TestH} = rocksdb:create_column_family(Ref, "test", []),
  try
    rocksdb:put(Ref, TestH, <<"a">>, <<"x1">>, []),
    rocksdb:put(Ref, TestH, <<"b">>, <<"x2">>, []),
    rocksdb:put(Ref, TestH, <<"c">>, <<"x3">>, []),
    rocksdb:put(Ref, TestH, <<"d">>, <<"x4">>, []),
    %% Also put in default CF to make sure we don't cross CFs
    rocksdb:put(Ref, DefaultH, <<"a">>, <<"y1">>, []),
    {ok, TestIt} = rocksdb:iterator(Ref, TestH, []),
    ?assertEqual({ok, <<"a">>, <<"x1">>}, rocksdb:iterator_move(TestIt, first)),
    {ok, Results} = rocksdb:iterator_move_n(TestIt, next, 10),
    ?assertEqual([{<<"b">>, <<"x2">>}, {<<"c">>, <<"x3">>}, {<<"d">>, <<"x4">>}], Results),
    ok = rocksdb:iterator_close(TestIt)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

move_n_large_batch_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    %% Write 1000 entries
    lists:foreach(fun(N) ->
        Key = list_to_binary(io_lib:format("key_~5..0B", [N])),
        Val = list_to_binary(io_lib:format("val_~5..0B", [N])),
        rocksdb:put(Ref, Key, Val, [])
    end, lists:seq(1, 1000)),
    {ok, I} = rocksdb:iterator(Ref, []),
    ?assertEqual({ok, <<"key_00001">>, <<"val_00001">>}, rocksdb:iterator_move(I, first)),
    %% Batch read 500
    {ok, Results} = rocksdb:iterator_move_n(I, next, 500),
    ?assertEqual(500, length(Results)),
    %% First result should be key_00002
    [{FirstKey, _} | _] = Results,
    ?assertEqual(<<"key_00002">>, FirstKey),
    %% Last result should be key_00501
    {LastKey, _} = lists:last(Results),
    ?assertEqual(<<"key_00501">>, LastKey),
    %% Iterator should be positioned at key_00501, next should be key_00502
    ?assertEqual({ok, <<"key_00502">>, <<"val_00502">>}, rocksdb:iterator_move(I, next)),
    ok = rocksdb:iterator_close(I)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

%% Test: seek then batch_next — mimics PersistenceStore fetch pattern
move_n_after_seek_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    %% Keys with prefix structure like PersistenceStore: prefix:timestamp
    rocksdb:put(Ref, <<"AAAA:100">>, <<"v1">>, []),
    rocksdb:put(Ref, <<"AAAA:200">>, <<"v2">>, []),
    rocksdb:put(Ref, <<"AAAA:300">>, <<"v3">>, []),
    rocksdb:put(Ref, <<"AAAA:400">>, <<"v4">>, []),
    rocksdb:put(Ref, <<"AAAA:500">>, <<"v5">>, []),
    rocksdb:put(Ref, <<"BBBB:100">>, <<"other1">>, []),
    rocksdb:put(Ref, <<"BBBB:200">>, <<"other2">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    %% Seek to beginning of prefix
    ?assertEqual({ok, <<"AAAA:100">>, <<"v1">>}, rocksdb:iterator_move(I, {seek, <<"AAAA:0">>})),
    %% Batch read next 4 (should get v2-v5, NOT crossing into BBBB)
    {ok, Results} = rocksdb:iterator_move_n(I, next, 4),
    ?assertEqual(4, length(Results)),
    [{K1, _}, {K2, _}, {K3, _}, {K4, _}] = Results,
    ?assertEqual(<<"AAAA:200">>, K1),
    ?assertEqual(<<"AAAA:500">>, K4),
    %% Next batch should cross into BBBB prefix
    {ok, Results2} = rocksdb:iterator_move_n(I, next, 10),
    ?assertEqual(2, length(Results2)),
    [{K5, _}, {K6, _}] = Results2,
    ?assertEqual(<<"BBBB:100">>, K5),
    ?assertEqual(<<"BBBB:200">>, K6),
    ok = rocksdb:iterator_close(I)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

%% Test: seek_for_prev then batch_prev — mimics PersistenceStore direction=last
move_n_after_seek_for_prev_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    rocksdb:put(Ref, <<"AAAA:100">>, <<"v1">>, []),
    rocksdb:put(Ref, <<"AAAA:200">>, <<"v2">>, []),
    rocksdb:put(Ref, <<"AAAA:300">>, <<"v3">>, []),
    rocksdb:put(Ref, <<"AAAA:400">>, <<"v4">>, []),
    rocksdb:put(Ref, <<"AAAA:500">>, <<"v5">>, []),
    {ok, I} = rocksdb:iterator(Ref, []),
    %% Seek to end of prefix range
    ?assertEqual({ok, <<"AAAA:500">>, <<"v5">>}, rocksdb:iterator_move(I, {seek_for_prev, <<"AAAA:999">>})),
    %% Batch read prev 3
    {ok, Results} = rocksdb:iterator_move_n(I, prev, 3),
    ?assertEqual(3, length(Results)),
    [{K1, _}, {K2, _}, {K3, _}] = Results,
    ?assertEqual(<<"AAAA:400">>, K1),
    ?assertEqual(<<"AAAA:200">>, K3),
    %% Continue prev — should get v1 then stop
    {ok, Results2} = rocksdb:iterator_move_n(I, prev, 10),
    ?assertEqual(1, length(Results2)),
    [{K4, _}] = Results2,
    ?assertEqual(<<"AAAA:100">>, K4),
    ok = rocksdb:iterator_close(I)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

%% Test: mixed iterator_move and iterator_move_n calls
move_n_mixed_test() ->
  rocksdb_test_util:rm_rf("ltest"),
  {ok, Ref} = rocksdb:open("ltest", [{create_if_missing, true}]),
  try
    lists:foreach(fun(N) ->
        Key = list_to_binary(io_lib:format("k~3..0B", [N])),
        rocksdb:put(Ref, Key, Key, [])
    end, lists:seq(1, 20)),
    {ok, I} = rocksdb:iterator(Ref, []),
    %% Seek to first
    {ok, <<"k001">>, _} = rocksdb:iterator_move(I, first),
    %% Single next
    {ok, <<"k002">>, _} = rocksdb:iterator_move(I, next),
    %% Batch next 3
    {ok, Batch1} = rocksdb:iterator_move_n(I, next, 3),
    ?assertEqual(3, length(Batch1)),
    [{<<"k003">>, _}, {<<"k004">>, _}, {<<"k005">>, _}] = Batch1,
    %% Single next again — should be at k006
    {ok, <<"k006">>, _} = rocksdb:iterator_move(I, next),
    %% Batch next 5
    {ok, Batch2} = rocksdb:iterator_move_n(I, next, 5),
    ?assertEqual(5, length(Batch2)),
    [{<<"k007">>, _} | _] = Batch2,
    ok = rocksdb:iterator_close(I)
  after
    rocksdb:close(Ref)
  end,
  rocksdb:destroy("ltest", []),
  rocksdb_test_util:rm_rf("ltest").

seek_iterator(Itr, Prefix, Suffix) ->
  rocksdb:iterator_move(Itr, test_key(Prefix, Suffix)).

test_key(Prefix, Suffix) when is_integer(Prefix), is_integer(Suffix) ->
  << Prefix:64, Suffix:64 >>.

put_key(Db, Prefix, Suffix, Value) ->
  rocksdb:put(Db, test_key(Prefix, Suffix), Value, []).
