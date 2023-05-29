/*
 * MIT No Attribution
 *
 * Copyright (c) 2022-2023 Fraser Heavy Software
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

#include "ghost/string/ghost_strset.h"

#ifndef ghost_has_ghost_strset
    #error "ghost/string/ghost_strset.h must define ghost_has_ghost_strset."
#endif

#include "test_common.h"

#if !ghost_has_ghost_strset
    #error "ghost_strset must exist."
#endif

mirror() {
    char s[] = "hello";
    ghost_strset(s, 'X');
    mirror_eq_s(s, "XXXXX");

    /* test setting empty string */
    s[0] = '\000';
    ghost_strset(s, 'Y');
    mirror_eq_c(s[0], '\000');
    mirror_eq_s(s + 1, "XXXX");
}
