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

/* This is a template used to test ghost_malloc_*() functions */

#include "ghost/malloc/ghost_free.h"
#include "ghost/language/ghost_null.h"

mirror_1(it("should allocate")) {
    void* x = TEST_GHOST_MALLOC_FN(1);
    mirror_check(x != ghost_null);
    #if ghost_has(ghost_free)
    ghost_free(x);
    #endif
}

mirror_1(it("should return unique allocations")) {
    void* x;
    void* y;

    x = TEST_GHOST_MALLOC_FN(1);
    mirror_check(x != ghost_null);

    y = TEST_GHOST_MALLOC_FN(1);
    mirror_check(y != ghost_null);

    mirror_check(x != y);

    #if ghost_has(ghost_free)
    ghost_free(x);
    ghost_free(y);
    #endif
}

#include "ghost/silence/ghost_silence_cxx_compat.h"
#include "ghost/silence/ghost_silence_push_pop_opt.h"
