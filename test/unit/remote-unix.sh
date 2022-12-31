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

# Copies your working copy of Ghost onto a remote UNIX machine and runs unit
# tests on it.
#
# Set the following env vars:
#
#     GHOST_REMOTE_LOGIN -- [user@]host
#     GHOST_REMOTE_PATH -- path to rsync to, e.g. $HOME/ghost/
#
# The machine needs:
#
#     - SSH Server
#     - rsync
#     - ninja-build
#     - python3
#     - build tools (GCC, Clang, etc.)
#
# Pass -c as first argument to clean first. Pass -- to stop interpreting
# arguments.
#
# All other arguments are forwarded to test/unit.sh so you can set
# architecture, build tools version, etc.

set -e
cd "$(dirname "$0")"/../..

# Note, we pass -L to dereference symlinks in case mirror is a symlink.
echo "Rsyncing files to $GHOST_REMOTE_LOGIN ..."
rsync -avL --exclude .build --exclude .ninja\* --delete \
    ./ $GHOST_REMOTE_LOGIN:$GHOST_REMOTE_PATH

if [ "$1" = "-c" ]; then
    echo "Cleaning..."
    shift
    ssh $GHOST_REMOTE_LOGIN $GHOST_REMOTE_PATH/test/clean.sh
fi
if [ "$1" = "--" ]; then
    shift
fi

echo "Running unit tests on $GHOST_REMOTE_LOGIN ..."
ssh $GHOST_REMOTE_LOGIN $GHOST_REMOTE_PATH/test/unit.sh "$@"
