#!/bin/sh

set -eu

if [ "${BUILD_RELEASE:-}" = 1 ]; then
    # never download when building a new release
    exit 1
fi

if [ ! -f priv/liberocksdb.so ]; then
    PKGNAME="$(./pkgname.sh)"
    if [ -n "$PKGNAME" ]; then
        if ./download.sh $PKGNAME; then
            exit 0
        else
            exit 1
        fi
    fi
    exit 2
fi

# An existing .so is only evidence of a PREVIOUS build. If anything under
# c_src has changed since it was linked, it is the wrong .so, and answering
# "already built" here makes do_cmake.sh and do_rocksdb.sh exit 0 without
# compiling -- so an edit to the NIF is silently discarded and the build
# reports success. Found while adding the cards#315 surface: the first
# `rebar3 compile` after writing three new source files rebuilt nothing and
# exited 0.
NEWER=$(find c_src -type f \
    \( -name '*.cc' -o -name '*.h' -o -name '*.hpp' -o -name 'CMakeLists.txt' \) \
    -newer priv/liberocksdb.so -print 2>/dev/null | head -n 1)
if [ -n "$NEWER" ]; then
    echo "do_prebuilt: $NEWER is newer than priv/liberocksdb.so; building from source" >&2
    exit 1
fi

# Sanity check
erlc src/rocksdb.erl
trap "rm -f rocksdb.beam" EXIT
if erl -noshell -eval '[_|_]=rocksdb:module_info(), halt(0)'; then
    exit 0
else
    exit 1
fi
