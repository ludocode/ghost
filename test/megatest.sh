#!/bin/bash

# MIT No Attribution
#
# Copyright (c) 2022 Fraser Heavy Software
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

set -e

# This script runs all variations of the Ghost unit test suite under many
# compilers and on various machines. It takes many hours to run. It's designed
# to run on Linux and it will rsync/ssh the working copy to various remote
# machines running Windows, macOS, FreeBSD, etc. to run tests.
#
# You need to set up environment variables for remote machines if you want
# Ghost to run unit tests on them. See the variables in the sections below and
# the docs in remote-unix.sh and remote-windows.sh .

go() {

test/fetch-dependencies.sh


# Emscripten SDK path
# (note: wasmtime is also required)
EMSDK_PATH=${EMSDK_PATH:-~/.local/share/emsdk}

# Also check out the env vars in test/unit/remote-windows.sh


if false; then

##################
# Misc Checks
##################

# check that all the header guards are correct
tools/impl/check-header-guards.py

# test that our musl detection works
test/test-musl.sh -ansi
test/test-musl.sh -ansi -D_GNU_SOURCE
test/test-musl.sh -ansi -D_BSD_SOURCE
test/test-musl.sh -std=c11
test/test-musl.sh -std=gnu89
test/test-musl.sh -std=gnu11
test/test-musl.sh -std=gnu11 -D_GNU_SOURCE
test/test-musl.sh -std=gnu11 -D_BSD_SOURCE
test/test-musl.sh -xc++ -std=c++98
test/test-musl.sh -xc++ -std=c++17



##################
# Linux
##################

# You can build these compilers for Arch Linux with my build script here:
#
#     TODO fill in link

# Run the compile time test to make sure all headers compile both amalgamated
# and not.
test/compile-time.sh

LINUX_SKIPPED=0

# GCC
CC=gcc test/unit.sh all

# GCC 4.0.4 is the version used in live-bootstrap, possibly because it's the
# latest version that can be built with TinyCC.
# TODO skip for now
#CC=gcc-4.0.4 test/unit.sh all

# GCC 4.7 is the last version of GCC written in C. We want to maintain support
# for it since it's the only way to bootstrap C++.
# GCC 4.7 declares C11 support but it was not fully completed until 4.9. 4.7,
# 4.8 and 4.9 therefore have varying C11 features that Ghost needs to handle
# mostly with manual version checks.
# TODO skip for now
#CC=gcc-4.7.4 test/unit.sh all
CC=gcc-4.8.2 test/unit.sh all
CC=gcc-4.8.5 test/unit.sh all
CC=gcc-4.9.4 test/unit.sh all
CC=gcc-5.3.0 test/unit.sh all
CC=gcc-5.5.0 test/unit.sh all
CC=gcc-6.5.0 test/unit.sh all
CC=gcc-7.5.0 test/unit.sh all
CC=gcc-8.5.0 test/unit.sh all
CC=gcc-9.4.0 test/unit.sh all
CC=gcc-10.3.0 test/unit.sh all
CC=gcc-11.2.0 test/unit.sh all
CC=gcc-12.1.0 test/unit.sh all

# Clang
CC=clang test/unit.sh all
CC=clang-3.4 test/unit.sh all
CC=clang-3.8.1 test/unit.sh all
CC=clang-6.0.0 test/unit.sh all
CC=clang-6.0.1 test/unit.sh all
CC=clang-10.0.0 test/unit.sh all
CC=clang-14 test/unit.sh all

# Other C compilers
CC=nvc-22.5 test/unit.sh all
#CC=nvc++-22.5 test/unit.sh all # TODO remove, should happen as part of above
CC=tcc-20220526-afc13626 test/unit.sh all
CC=chibicc-20201206-90d1f7f1 test/unit.sh all
CC=lacc-20220521-30839843 test/unit.sh
CC=kefir-20220714-76cbf506 test/unit.sh all
CC=cproc-20220519-c88c649f test/unit.sh all
#CC=pcc-20221220 test/unit.sh # TODO not entirely working yet
#CC=cparser-20200429-8ec1a761 test/unit.sh all # TODO fix later
( . ${EMSDK_PATH}/emsdk_env.sh ; CC=emcc test/unit.sh all )

# TODO lcc not working yet
#CC=lcc-20210111-3fd0acc0 test/unit.sh all
# TODO dmc not working yet
#CC=dmc-857 test/unit.sh all


# TODO test riscv against spike:
# https://github.com/riscv-software-src/riscv-isa-sim


##################
# Windows (x86_64)
##################

if [ "$GHOST_WINDOWS_LOGIN" != "" ]; then
    WINDOWS_SKIPPED=0
    export GHOST_REMOTE_LOGIN=$GHOST_WINDOWS_LOGIN
    export GHOST_REMOTE_PATH=$GHOST_WINDOWS_PATH
    export GHOST_REMOTE_DRIVE=$GHOST_WINDOWS_DRIVE

    # ARM cross tests are currently disabled, we need to make the ninja file
    # not try to actually run the tests
    #
    # x86_amd64 cross tests are currently disabled due to linking errors,
    # haven't bothered to fix yet

    # 2012
    test/unit/remote-windows.sh -c -arch x86        -vcvars_ver 11.0 all
    #test/unit/remote-windows.sh -c -arch x86_amd64  -vcvars_ver 11.0 all
    #test/unit/remote-windows.sh -c -arch x86_arm    -vcvars_ver 11.0 all

    # 2013
    test/unit/remote-windows.sh -c -arch x86        -vcvars_ver 12.0 all
    #test/unit/remote-windows.sh -c -arch x86_amd64  -vcvars_ver 12.0 all
    #test/unit/remote-windows.sh -c -arch x86_arm    -vcvars_ver 12.0 all

    # 2015
    test/unit/remote-windows.sh -c -arch amd64      -vcvars_ver 14.0 all
    test/unit/remote-windows.sh -c -arch x86        -vcvars_ver 14.0 all
    #test/unit/remote-windows.sh -c -arch amd64_arm  -vcvars_ver 14.0 all

    # 2017 (Update 9)
    test/unit/remote-windows.sh -c -arch amd64      -vcvars_ver 14.16 all
    test/unit/remote-windows.sh -c -arch x86        -vcvars_ver 14.16 all
    #test/unit/remote-windows.sh -c -arch amd64_arm  -vcvars_ver 14.16 all

    # 2019 (Update 11)
    test/unit/remote-windows.sh -c -arch amd64      -vcvars_ver 14.29 all
    test/unit/remote-windows.sh -c -arch x86        -vcvars_ver 14.29 all

    # 2022
    test/unit/remote-windows.sh -c -arch amd64      -vcvars_ver 14.30 all
    test/unit/remote-windows.sh -c -arch x86        -vcvars_ver 14.30 all
    test/unit/remote-windows.sh -c -arch amd64      -vcvars_ver 14.31 all
    test/unit/remote-windows.sh -c -arch x86        -vcvars_ver 14.31 all
    #test/unit/remote-windows.sh -c -arch amd64_arm  -vcvars_ver 14.31 all

    # Cygwin TODO
fi

fi



##################
# macOS (x86_64)
##################

if [ "$GHOST_MACOS_LOGIN" != "" ]; then
    MACOS_SKIPPED=0
    export GHOST_REMOTE_LOGIN=$GHOST_MACOS_LOGIN
    export GHOST_REMOTE_PATH=$GHOST_MACOS_PATH
    test/unit/remote-unix.sh -c all
fi



##################
# FreeBSD (x86_64)
##################

if [ "$GHOST_FREEBSD_LOGIN" != "" ]; then
    FREEBSD_SKIPPED=0
    export GHOST_REMOTE_LOGIN=$GHOST_FREEBSD_LOGIN
    export GHOST_REMOTE_PATH=$GHOST_FREEBSD_PATH
    test/unit/remote-unix.sh -c all
fi



##################
# Raspberry Pi
##################

# TODO test with several compilers



##################
# Done
##################

echo "Megatest completed successfully."

if [ "$LINUX_SKIPPED" != "0" ]; then echo "WARNING: Linux tests skipped."; fi
if [ "$WINDOWS_SKIPPED" != "0" ]; then echo "WARNING: Windows tests skipped."; fi
if [ "$MACOS_SKIPPED" != "0" ]; then echo "WARNING: macOS tests skipped."; fi
if [ "$FREEBSD_SKIPPED" != "0" ]; then echo "WARNING: FreeBSD tests skipped."; fi

}
time go
