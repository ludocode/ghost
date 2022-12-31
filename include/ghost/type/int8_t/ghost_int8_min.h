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

#ifndef GHOST_INT8_MIN_H_INCLUDED
#define GHOST_INT8_MIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT8_MIN -128
 *
 * The minimum value of ghost_int8_t (always exactly -128 if it exists.)
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_INT8_MIN
    #ifdef GHOST_INT8_MIN
        #define ghost_has_GHOST_INT8_MIN 1
    #endif
#endif

/* ghost_int8_t is required. */
#ifndef ghost_has_GHOST_INT8_MIN
    #include "ghost/type/int8_t/ghost_int8_t.h"
    #if !ghost_has(ghost_int8_t)
        #define ghost_has_GHOST_INT8_MIN 0
    #endif
#endif

/* <stdint.h> has INT8_MIN in C99. It might be backported. */
#ifndef ghost_has_GHOST_INT8_MIN
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef INT8_MIN
        #define GHOST_INT8_MIN INT8_MIN
        #define ghost_has_GHOST_INT8_MIN 1
    #endif
#endif

/* GNU C compilers define __INT8_MIN__. */
#ifndef ghost_has_GHOST_INT8_MIN
    #ifdef __INT8_MIN__
        #define GHOST_INT8_MIN __INT8_MIN__
        #define ghost_has_GHOST_INT8_MIN 1
    #endif
#endif

/* Define it ourselves, provided we can declare constants properly. */
#ifndef ghost_has_GHOST_INT8_MIN
    #include "ghost/type/int8_t/ghost_int8_c.h"
    #if ghost_has(GHOST_INT8_C)
        #define GHOST_INT8_MIN (-GHOST_INT8_C(127) - GHOST_INT8_C(1))
        #define ghost_has_GHOST_INT8_MIN 1
    #endif
#endif

/* Otherwise we have no way to define it. */
#ifndef ghost_has_GHOST_INT8_MIN
    #define ghost_has_GHOST_INT8_MIN 0
#endif

/* Test min from max (int8_t is required to be two's complement) */
#if ghost_has(GHOST_INT8_MIN)
    #include "ghost/type/int8_t/ghost_int8_max.h"
    #if ghost_has(GHOST_INT8_MAX)
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        ghost_static_assert(GHOST_INT8_MIN == -1 - GHOST_INT8_MAX,
                "GHOST_INT8_MIN is incorrect");
    #endif
#endif

#endif
