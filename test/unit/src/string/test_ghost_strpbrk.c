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

#include "ghost/string/ghost_strpbrk.h"

#ifndef ghost_has_ghost_strpbrk
    #error "ghost/string/ghost_strpbrk.h must define ghost_has_ghost_strpbrk."
#endif

#include "test_common.h"

#if !ghost_has_ghost_strpbrk
    #error "ghost_strpbrk must exist."
#endif

mirror() {
    const char* s = "hello";
    mirror_check(ghost_strpbrk(s, "oh") == s);
    mirror_check(ghost_strpbrk(s, "eXo") == s + 1);
    mirror_check(ghost_strpbrk(s, "XXooXXoo") == s + 4);
    mirror_check(ghost_strpbrk(s, "XYZ") == ghost_null);
    mirror_check(ghost_strpbrk(s, "") == ghost_null);
}
