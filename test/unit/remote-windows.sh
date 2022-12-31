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

# Copies your working copy of Ghost onto a Windows machine and runs unit tests
# on it.
#
# Set the following env vars:
#
#     GHOST_REMOTE_LOGIN -- [user@]host
#     GHOST_REMOTE_PATH -- path to rsync to, e.g. /Users/%username%/ghost/
#     GHOST_REMOTE_DRIVE -- drive letter
#
# The Windows machine needs:
#     - SSH Server
#     - rsync (from e.g. Cygwin) on PATH
#     - Python on PATH
#     - Visual Studio with the build tools you intend to use
#
# Pass -c as first argument to clean first. Pass -- to stop interpreting
# arguments.
#
# All other arguments are forwarded to test/unit.bat so you can set
# architecture, build tools version, targets, etc.

cd "$(dirname "$0")"/../..

# Set these environment variables to configure the remote machine
GHOST_WINDOWS_LOGIN=${GHOST_WINDOWS_LOGIN:-nick@smyrno}
GHOST_WINDOWS_DRIVE=${GHOST_WINDOWS_DRIVE:-C}
GHOST_WINDOWS_PATH=${GHOST_WINDOWS_PATH:-/Users/%username%/code/ghost/ghost/}

# Note, we pass -L to dereference symlinks in case mirror is a symlink.
echo "rsyncing files..."
rsync -avL --exclude .build --exclude .ninja\* --delete \
    ./ $GHOST_WINDOWS_LOGIN:/cygdrive/${GHOST_WINDOWS_DRIVE}$GHOST_WINDOWS_PATH

if [ "$1" = "-c" ]; then
    echo "cleaning..."
    shift
    ssh $GHOST_WINDOWS_LOGIN ${GHOST_WINDOWS_DRIVE}:$GHOST_WINDOWS_PATH/test/clean.bat
fi
if [ "$1" = "--" ]; then
    shift
fi

# hack to look for legacy -vcvars_ver and use alternate build script
BATCH_SCRIPT=unit.bat
vcvars_ver_found=0
for arg in "$@"; do
    if [ "$arg" = "-vcvars_ver" ]; then
        vcvars_ver_found=1
    fi
    if [ "$vcvars_ver_found" = 1 ]; then
        if [ "$arg" = "12.0" ]; then
            BATCH_SCRIPT=unit-vs2013.bat
        elif [ "$arg" = "11.0" ]; then
            BATCH_SCRIPT=unit-vs2012.bat
        fi
    fi
done

echo "Running $BATCH_SCRIPT ..."
ssh $GHOST_WINDOWS_LOGIN ${GHOST_WINDOWS_DRIVE}:$GHOST_WINDOWS_PATH/test/$BATCH_SCRIPT "$@"
