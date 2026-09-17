-module(read_only_test).

%%
%% PersistenceStore#321: `read_only` is not a DBOptions field. Read-only is a
%% different FUNCTION -- OpenForReadOnly, exposed here as open_readonly/3 -- so
%% `{read_only, true}` passed to open/2 used to fall off the end of
%% parse_db_option and be answered `ok`.
%%
%% PersistenceStore#320 is what that cost: db_lib asked for it on every sealed
%% archive, the request was discarded, and every archive opened WRITABLE for as
%% long as the option had existed. Nothing errored, and the intent sat in the
%% source in a variable named ReadOnly.
%%
%% OptionSamurai confirmed on 2026-09-17 that the binding still accepted it
%% silently, which is why this case exists.
%%

-include_lib("eunit/include/eunit.hrl").

read_only_is_refused_not_ignored_test() ->
    Dir = scratch("refused"),
    ?assertError(badarg, rocksdb:open(Dir, [{create_if_missing, true}, {read_only, true}])).

%% The control. If open/2 refused everything the case above would pass for the
%% wrong reason, and the option lists this store really uses have to keep working
%% -- open/2 folds the DB and column-family parsers over the SAME list, so each
%% one sees the other's options and must not reject them.
an_ordinary_option_list_still_opens_test() ->
    Dir = scratch("ordinary"),
    {ok, DB} = rocksdb:open(Dir, [
        {create_if_missing, true},
        {max_open_files, 64},
        {compression, none}
    ]),
    ok = rocksdb:close(DB).

%% And the function that actually does what the option was asking for.
open_readonly_is_the_supported_route_test() ->
    Dir = scratch("readonly"),
    {ok, DB0} = rocksdb:open(Dir, [{create_if_missing, true}]),
    ok = rocksdb:put(DB0, <<"k">>, <<"v">>, []),
    ok = rocksdb:close(DB0),
    {ok, DB, [_CF]} = rocksdb:open_readonly(Dir, [{create_if_missing, false}], [{"default", []}]),
    ?assertEqual({ok, <<"v">>}, rocksdb:get(DB, <<"k">>, [])),
    ?assertMatch({error, _}, rocksdb:put(DB, <<"k">>, <<"mutated">>, [])),
    ok = rocksdb:close(DB).

scratch(Name) ->
    Dir = filename:join(["/tmp", "ro_test", Name ++ integer_to_list(erlang:unique_integer([positive]))]),
    _ = file:del_dir_r(Dir),
    ok = filelib:ensure_path(Dir),
    Dir.
