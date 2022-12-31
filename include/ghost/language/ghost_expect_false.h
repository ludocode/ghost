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

#ifndef GHOST_EXPECT_FALSE_H_INCLUDED
#define GHOST_EXPECT_FALSE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_expect_false(expression) (expression)
 *
 * Evaluates to the given expression, but gives a hint to the compiler that we
 * expect it to be false most of the time.
 *
 * Many projects call this macro "UNLIKELY()" or something similar. We call it
 * "expect_false" to more closely match the "__builtin_expect()" GNU C feature
 * it is wrapping, and because there is a different [[unlikely]] feature in
 * C++20 with a very different syntax.
 */
#endif

#include "ghost/language/ghost_expect.h"

#ifndef ghost_has_ghost_expect_false
    #ifdef ghost_expect_false
        #define ghost_has_ghost_expect_false 1
    #endif
#endif

#ifndef ghost_has_ghost_expect_false
    #define ghost_expect_false(x) ghost_expect(!!(x), 0)
    #define ghost_has_ghost_expect_false 1
#endif

#endif
