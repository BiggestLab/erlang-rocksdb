-module(unknown_option_test).

%%
%% PersistenceStore#321: an option the binding cannot apply is refused, not
%% discarded.
%%
%% Why this could not be done inside either parser: open/2 folds
%% parse_db_option AND parse_cf_option over the SAME list, so each legitimately
%% ignores the other's options. "Unknown" is only decidable after both have
%% looked, which is why an option nobody applied used to be answered `ok`.
%%
%% PersistenceStore#320 is what that cost -- {read_only, true} asked for on every
%% sealed archive, discarded, and every archive opened WRITABLE for as long as
%% the option had existed. OptionSamurai confirmed on 2026-09-17 that the
%% binding still accepted it silently.
%%

-include_lib("eunit/include/eunit.hrl").

%% An option name no parser owns.
an_unknown_option_is_refused_test() ->
    Dir = scratch("unknown"),
    ?assertError(
        badarg,
        rocksdb:open(Dir, [{create_if_missing, true}, {no_such_option_at_all, true}])
    ).

%% The one that actually bit us, refused by its own branch with a clearer
%% answer than "unknown": read_only is not a DBOptions field at all, it selects
%% a different FUNCTION.
read_only_is_refused_test() ->
    Dir = scratch("readonly_opt"),
    ?assertError(badarg, rocksdb:open(Dir, [{create_if_missing, true}, {read_only, true}])).

%% The property that makes the pairwise fold necessary, and the control for the
%% two cases above: a list holding a DB option AND a column-family option is
%% accepted, because between them the two parsers recognise every entry. A
%% parser made strict on its own would reject this.
a_mixed_db_and_cf_option_list_is_accepted_test() ->
    Dir = scratch("mixed"),
    {ok, DB} = rocksdb:open(Dir, [
        %% db options
        {create_if_missing, true},
        {max_open_files, 64},
        %% column-family options -- parse_db_option does not know these
        {write_buffer_size, 4 * 1024 * 1024},
        {num_levels, 4}
    ]),
    ok = rocksdb:close(DB).

%% fold/3 stays TOLERANT of "not mine". Every other caller folds ONE parser over
%% a list, and if fold stopped there those would quietly stop parsing at the
%% first option that parser did not own -- a NEW way to ignore an option, which
%% is the opposite of this card. destroy/2 takes the same mixed list.
destroy_still_tolerates_a_list_one_parser_does_not_own_test() ->
    Dir = scratch("destroy"),
    {ok, DB} = rocksdb:open(Dir, [{create_if_missing, true}]),
    ok = rocksdb:close(DB),
    ?assertEqual(ok, rocksdb:destroy(Dir, [{create_if_missing, true}, {num_levels, 4}])).

scratch(Name) ->
    Dir = filename:join([
        "/tmp", "unknown_opt_test", Name ++ integer_to_list(erlang:unique_integer([positive]))
    ]),
    _ = file:del_dir_r(Dir),
    ok = filelib:ensure_path(Dir),
    Dir.
