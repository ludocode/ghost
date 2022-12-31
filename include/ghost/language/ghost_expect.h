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

#ifndef GHOST_EXPECT_H_INCLUDED
#define GHOST_EXPECT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_expect(expression, value) (expression)
 *
 * Evaluates to the given expression, but gives a hint to the compiler that we
 * expect it to have the given value most of the time.
 *
 * The given value is not evaluated. It should be a compile-time constant.
 *
 * You probably want to use ghost_expect_true() and ghost_expect_false()
 * instead of this.
 *
 * @see ghost_expect_true
 * @see ghost_expect_false
 */
#endif

#ifndef ghost_has_ghost_expect
    #ifdef ghost_expect
        #define ghost_has_ghost_expect 1
    #endif
#endif

#ifndef ghost_has_ghost_expect
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_expect)
            #define ghost_expect(x, v) (__builtin_expect((x), (v)))
            #define ghost_has_ghost_expect 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* GCC has had this since basically forever so we don't bother with a
             * version check. */
            #define ghost_expect(x, v) (__builtin_expect((x), (v)))
            #define ghost_has_ghost_expect 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_expect
    #define ghost_expect(x, v) (x)
    #define ghost_has_ghost_expect 1
#endif

#endif
