/*
 * MIT No Attribution
 *
 * Copyright (c) 2022-2026 Fraser Heavy Software
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

#include "ghost/string/ghost_strnstr.h"

#ifndef ghost_has_ghost_strnstr
    #error "ghost/string/ghost_strnstr.h must define ghost_has_ghost_strnstr."
#endif

#include "test_common.h"

#if !ghost_has_ghost_strnstr
    #error "ghost_strnstr must exist."
#endif

mirror() {
    const char* haystack = "abcdefgh";
    mirror_check(haystack + 3 == ghost_strnstr(haystack, "de", 99));
    mirror_check(haystack + 3 == ghost_strnstr(haystack, "de", 5));
    mirror_check(NULL == ghost_strnstr(haystack, "de", 4));
    mirror_check(haystack + 7 == ghost_strnstr(haystack, "h", 8));
    mirror_check(NULL == ghost_strnstr(haystack, "h", 7));
    mirror_check(NULL == ghost_strnstr(haystack, "a", 0));
    mirror_check(NULL == ghost_strnstr(haystack, "z", 99));
    mirror_check(NULL == ghost_strnstr(haystack, "z", 4));
    mirror_check(NULL == ghost_strnstr(haystack, "z", 0));
}
