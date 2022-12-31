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

#include "ghost/preprocessor/ghost_counter.h"

#ifndef ghost_has_GHOST_COUNTER
    #error "ghost/preprocessor/ghost_count_args.h must define ghost_has_GHOST_COUNTER."
#endif

#include "test_common.h"

#if !ghost_has_GHOST_COUNTER
    #error "GHOST_COUNTER must exist."
#endif

#define NAME "ghost/preprocessor/ghost_counter"

mirror_2(name("ghost/preprocessor/ghost_counter$unique"), it("should have a unique value each time")) {
    /* fallback is based on __LINE__ so we use line breaks to test it */
    int a = GHOST_COUNTER;
    int b = GHOST_COUNTER;
    mirror_ne(a, b);
}

mirror_2(name("ghost/preprocessor/ghost_counter$fixed"), it("should have a fixed value when passed through to another macro")) {
    #undef X
    #undef X2
    #define X() X2(GHOST_COUNTER)
    #define X2(counter) mirror_eq(counter, counter)
    X();
    X();
}
