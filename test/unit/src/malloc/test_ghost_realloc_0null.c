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

#include "ghost/malloc/ghost_realloc_0null.h"

#ifndef ghost_has_ghost_realloc_0null
    #error "ghost/malloc/ghost_realloc_0null.h must define ghost_has_ghost_realloc_0null."
#endif

#include "test_common.h"

#if ghost_has_ghost_realloc_0null
#define TEST_GHOST_REALLOC_FN ghost_realloc_0null
#include "test_ghost_realloc.t.h"

mirror_1(it("should return null with null and size 0")) {
    void* x = ghost_realloc_0null(ghost_null, 0);
    mirror_eq_p(x, ghost_null);
}

mirror_1(it("should free with non-null and size 0")) {
    void* x = ghost_realloc_0null(ghost_null, 1024);
    mirror_nn(x);
    x = ghost_realloc_0null(x, 0);
    mirror_eq_p(x, ghost_null);
}
#endif
