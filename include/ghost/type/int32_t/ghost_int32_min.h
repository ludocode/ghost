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

#ifndef GHOST_INT32_MIN_H_INCLUDED
#define GHOST_INT32_MIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT32_MIN -2147483648
 *
 * The minimum value of ghost_int32_t (always exactly -2147483648 if it exists.)
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_INT32_MIN
    #ifdef GHOST_INT32_MIN
        #define ghost_has_GHOST_INT32_MIN 1
    #endif
#endif

/* ghost_int32_t is required. */
#ifndef ghost_has_GHOST_INT32_MIN
    #include "ghost/type/int32_t/ghost_int32_t.h"
    #if !ghost_has(ghost_int32_t)
        #define ghost_has_GHOST_INT32_MIN 0
    #endif
#endif

/* <stdint.h> has INT32_MIN in C99. It might be backported. */
#ifndef ghost_has_GHOST_INT32_MIN
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef INT32_MIN
        #define GHOST_INT32_MIN INT32_MIN
        #define ghost_has_GHOST_INT32_MIN 1
    #endif
#endif

/* GNU C compilers define __INT32_MIN__. */
#ifndef ghost_has_GHOST_INT32_MIN
    #ifdef __INT32_MIN__
        #define GHOST_INT32_MIN __INT32_MIN__
        #define ghost_has_GHOST_INT32_MIN 1
    #endif
#endif

/* Define it ourselves, provided we can declare constants properly. */
#ifndef ghost_has_GHOST_INT32_MIN
    #include "ghost/type/int32_t/ghost_int32_c.h"
    #if ghost_has(GHOST_INT32_C)
        #define GHOST_INT32_MIN (-GHOST_INT32_C(2147483647) - GHOST_INT32_C(1))
        #define ghost_has_GHOST_INT32_MIN 1
    #endif
#endif

/* Otherwise we have no way to define it. */
#ifndef ghost_has_GHOST_INT32_MIN
    #define ghost_has_GHOST_INT32_MIN 0
#endif

/* Test min from max (int32_t is required to be two's complement) */
#if ghost_has(GHOST_INT32_MIN)
    #include "ghost/type/int32_t/ghost_int32_max.h"
    #if ghost_has(GHOST_INT32_MAX)
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        ghost_static_assert(GHOST_INT32_MIN == -1 - GHOST_INT32_MAX,
                "GHOST_INT32_MIN is incorrect");
    #endif
#endif

#endif
