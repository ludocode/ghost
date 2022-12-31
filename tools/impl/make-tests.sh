#!/bin/bash

# Generates an empty test case for any headers that don't yet have a
# corresponding test file.
#
# Note that this doesn't handle cases where the feature doesn't exactly match
# the filename. For example ghost_counter.h contains GHOST_COUNTER. For these
# you just have to fix it manually.

for header in $(cd include; find ghost -type f -name \*.h); do
    name=$(echo $header|sed 's@.*/@@'|sed 's@\.h$@@')
    folder=$(echo $header|sed 's@^ghost/@@'|sed 's@[^/]*$@@')
    srcfolder=test/unit/src/${folder}
    src=test/unit/src/${folder}test_$name.c

    # don't generate tests for impl/ headers
    if [[ $folder == impl/* ]]; then
        continue
    fi

    if ! [ -e $src ]; then
        echo "Creating $src"
        mkdir -p $srcfolder
        cat - >$src <<EOF
/*
 * MIT No Attribution
 *
 * Copyright (c) $(date +%Y) Fraser Heavy Software
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "$header"

#ifndef ghost_has_$name
    #error "$header must define ghost_has_$name."
#endif

#include "test_common.h"

#if ghost_has_$name
mirror() {
    /* TODO */
}
#endif
EOF
    fi
done
