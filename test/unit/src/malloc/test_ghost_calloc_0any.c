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

#include "ghost/malloc/ghost_calloc_0any.h"

#ifndef ghost_has_ghost_calloc_0any
    #error "ghost/malloc/ghost_calloc_0any.h must define ghost_has_ghost_calloc_0any."
#endif

#include "test_common.h"

#if ghost_has_ghost_calloc_0any
#define TEST_GHOST_CALLOC_FN ghost_calloc_0any
#include "test_ghost_calloc.t.h"

mirror_1(it("should not crash when called with size 0")) {
    void* x = ghost_calloc_0any(1, 0);
    /* x may or may not be null. the behaviour is implementation-defined. */
    #if ghost_has(ghost_free)
    ghost_free(x);
    #endif
}
#endif
