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

#include "ghost/malloc/ghost_malloc.h"

#ifndef ghost_has_ghost_malloc
    #error "ghost/malloc/ghost_malloc.h must define ghost_has_ghost_malloc."
#endif

#include "test_common.h"

#if ghost_has_ghost_malloc
#define TEST_GHOST_MALLOC_FN ghost_malloc
#include "test_ghost_malloc.t.h"

mirror_1(it("should return unique allocations when called with size 0")) {
    void* x;
    void* y;

    x = ghost_malloc(0);
    mirror_check(x != ghost_null);

    y = ghost_malloc(0);
    mirror_check(y != ghost_null);

    mirror_ne_p(x, y);

    #if ghost_has(ghost_free)
    ghost_free(x);
    ghost_free(y);
    #endif
}

GHOST_SILENCE_PUSH_OPT
GHOST_SILENCE_CXX_COMPAT
mirror_1(it("should autocast")) {
    int* x = TEST_GHOST_MALLOC_FN(sizeof(int));
    mirror_check(x != ghost_null);
    *x = 4;
    #if ghost_has(ghost_free)
    ghost_free(x);
    #endif
}
GHOST_SILENCE_POP_OPT

#endif
