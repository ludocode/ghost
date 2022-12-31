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

/* This is a template used to test ghost_realloc_*() functions */

#include "ghost/malloc/ghost_free.h"
#include "ghost/language/ghost_null.h"
#include "ghost/language/ghost_bless.h"
#include "ghost/language/ghost_static_cast.h"

#include "ghost/detect/ghost_cproc.h"
#if GHOST_CPROC
    #define VOLATILE /*nothing*/
#else
    #define VOLATILE volatile
#endif

mirror_1(it("should allocate on null")) {
    void* x = TEST_GHOST_REALLOC_FN(ghost_null, 1);
    mirror_check(x != ghost_null);
    #if ghost_has(ghost_free)
    ghost_free(x);
    #endif
}

mirror_1(it("should grow")) {
    int* x = ghost_bless(int, 1, TEST_GHOST_REALLOC_FN(ghost_null, sizeof(int)));
    mirror_nn(x);
    x[0] = 12345;

    x = ghost_bless(int, 256, TEST_GHOST_REALLOC_FN(ghost_static_cast(void*, x), 256 * sizeof(int)));
    mirror_nn(x);
    mirror_eq_i(x[0], 12345); /* data is preserved */

    ghost_static_cast(VOLATILE int*, x)[255] = 23456; /* it is at least the requested size */

    #if ghost_has(ghost_free)
    ghost_free(x);
    #endif
}

mirror_1(it("should shrink")) {
    int* x = ghost_bless(int, 256, TEST_GHOST_REALLOC_FN(ghost_null, 256 * sizeof(int)));
    mirror_nn(x);
    x[0] = 34567;
    x[255] = 45678; /* it is at least the requested size */

    x = ghost_bless(int, 1, TEST_GHOST_REALLOC_FN(ghost_static_cast(void*, x), sizeof(int)));
    mirror_nn(x);
    mirror_eq_i(x[0], 34567); /* data is preserved */

    #if ghost_has(ghost_free)
    ghost_free(x);
    #endif
}
