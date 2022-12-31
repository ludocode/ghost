/*
 * MIT No Attribution
 *
 * Copyright (c) 2022 Fraser Heavy Software
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

#include "ghost/string/ghost_strncmp.h"

#ifndef ghost_has_ghost_strncmp
    #error "ghost/string/ghost_strncmp.h must define ghost_has_ghost_strncmp."
#endif

#include "test_common.h"

#if !ghost_has_ghost_strncmp
    #error "ghost_strncmp must exist."
#endif

mirror() {
    mirror_eq(0, ghost_strncmp("abc", "abc", 3));
    mirror_gt(0, ghost_strncmp("aaa", "aba", 3));
    mirror_lt(0, ghost_strncmp("aba", "aaa", 3));
    mirror_lt(0, ghost_strncmp("aba", "", 1));
    mirror_gt(0, ghost_strncmp("aba", "xyz", 1));
    mirror_eq(0, ghost_strncmp("aba", "ad", 1));
    mirror_eq(0, ghost_strncmp("aaa", "aaaa", 3));
    mirror_gt(0, ghost_strncmp("aaa", "aaaa", 100));
    mirror_lt(0, ghost_strncmp("aaa", "aa", 100));
}
