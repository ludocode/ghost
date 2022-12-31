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

#include "ghost/malloc/ghost_calloc.h"

#ifndef ghost_has_ghost_calloc
    #error "ghost/malloc/ghost_calloc.h must define ghost_has_ghost_calloc."
#endif

#include "test_common.h"

#if ghost_has_ghost_calloc
#define TEST_GHOST_CALLOC_FN ghost_calloc
#include "test_ghost_calloc.t.h"

mirror_1(it("should return unique allocations when called with size 0")) {
    void* x;
    void* y;

    x = ghost_calloc(1, 0);
    mirror_nn(x);

    y = ghost_calloc(0, 1);
    mirror_nn(y);

    mirror_ne_p(x, y);

    #if ghost_has(ghost_free)
    ghost_free(x);
    ghost_free(y);
    #endif
}
#endif
