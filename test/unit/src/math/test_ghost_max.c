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

#include "ghost/math/ghost_max.h"

#ifndef ghost_has_ghost_max
    #error "ghost/math/ghost_max.h must define ghost_has_ghost_max."
#endif

#include "test_common.h"

#if ghost_has_ghost_max
mirror() {
    {
        int x = ghost_max(5, 3);
        mirror_eq(x, 5);
    }

    {
        long y = ghost_max(1L, 2L);
        mirror_eq(y, 2L);
    }

    #if ghost_has_ghost_float
    {
        float z = ghost_max(3.14F, 2.71F);
        mirror_gt(z, 3.F);
    }
    #endif

    #ifndef GHOST_IMPL_GENERIC_NO_CV
    {
        const volatile short h = 12;
        short j = 13;
        mirror_eq(13, ghost_max(h, j));
    }
    #endif
}
#endif
