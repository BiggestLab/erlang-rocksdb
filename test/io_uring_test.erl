-module(io_uring_test).

%%
%% The artifact gate for io_uring.
%%
%% RocksDB reaches the embedder through a weak `RocksDbIOUringEnable`. Left
%% undefined it resolves to null, IsIOUringEnabled() is false, and every
%% io_uring path is dead -- while liburing is linked, its symbols are imported,
%% and nothing at build or load time complains. That is precisely the state this
%% fork shipped in, and no Erlang-level call could observe it: there is no API
%% that reports whether io_uring is in use.
%%
%% So the gate reads the ARTIFACT. `nm` on the loaded .so must show the symbol
%% DEFINED (T/W/t/w-with-address), not weak-undefined (`w` with no address) and
%% not undefined (`U`).
%%
%% This case failed before the definition was added, which is the only reason to
%% trust it.
%%

-include_lib("eunit/include/eunit.hrl").

io_uring_enable_symbol_is_defined_test() ->
    So = nif_path(),
    ?assert(filelib:is_regular(So)),
    Out = os:cmd("nm " ++ So ++ " 2>&1 | grep RocksDbIOUringEnable"),
    case Out of
        "" ->
            erlang:error(
                {io_uring_gate_could_not_run,
                    "nm produced no RocksDbIOUringEnable line for " ++ So ++
                        " -- either nm is missing or the symbol was stripped. "
                        "A gate that cannot run is not a passing gate."}
            );
        _ ->
            ok
    end,
    %% nm prints "<addr> <type> <name>" for a defined symbol and "         w name"
    %% for a weak UNDEFINED one. The address is what separates them.
    Lines = [L || L <- string:split(string:trim(Out), "\n", all), L =/= ""],
    Defined = lists:any(fun is_defined_line/1, Lines),
    ?assertEqual(
        {defined, true, Lines},
        {defined, Defined, Lines}
    ).

%% A defined symbol carries an address; `w` and `U` entries do not.
is_defined_line(Line) ->
    case string:lexemes(string:trim(Line), " ") of
        [Addr, Type, _Name] ->
            is_hex(Addr) andalso lists:member(Type, ["T", "t", "W", "w", "D", "d", "B", "b"]);
        _NoAddress ->
            false
    end.

is_hex([]) -> false;
is_hex(S) -> lists:all(fun(C) -> (C >= $0 andalso C =< $9) orelse (C >= $a andalso C =< $f) end, S).

nif_path() ->
    filename:join([code:priv_dir(rocksdb), "liberocksdb.so"]).
