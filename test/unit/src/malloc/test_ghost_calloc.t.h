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

/* This is a template used to test ghost_calloc_*() functions */

#include "ghost/malloc/ghost_free.h"
#include "ghost/language/ghost_null.h"
#include "ghost/language/ghost_bless.h"

mirror_1(it("should allocate zeroed")) {
    char* x = ghost_bless(char, 1, TEST_GHOST_CALLOC_FN(1, 1));
    mirror_check(x != ghost_null);
    mirror_check(x[0] == 0);
    #if ghost_has(ghost_free)
    ghost_free(x);
    #endif
}

mirror_1(it("should return unique zeroed allocations")) {
    char* x;
    char* y;

    x = ghost_bless(char, 1, TEST_GHOST_CALLOC_FN(1, 1));
    mirror_check(x != ghost_null);
    mirror_check(x[0] == 0);

    y = ghost_bless(char, 1, TEST_GHOST_CALLOC_FN(1, 1));
    mirror_check(y != ghost_null);
    mirror_check(y[0] == 0);

    mirror_check(x != y);

    #if ghost_has(ghost_free)
    ghost_free(x);
    ghost_free(y);
    #endif
}

