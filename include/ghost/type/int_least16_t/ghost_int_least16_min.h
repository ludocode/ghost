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

#ifndef GHOST_INT_LEAST16_MIN_H_INCLUDED
#define GHOST_INT_LEAST16_MIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT_LEAST16_MIN INT_LEAST16_MIN
 *
 * The minimum value of ghost_int_least16_t.
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #ifdef GHOST_INT_LEAST16_MIN
        #define ghost_has_GHOST_INT_LEAST16_MIN 1
    #endif
#endif

/* ghost_int_least16_t is required. */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #include "ghost/type/int_least16_t/ghost_int_least16_t.h"
    #if !ghost_has(ghost_int_least16_t)
        #define ghost_has_GHOST_INT_LEAST16_MIN 0
    #endif
#endif

/* <stdint.h> has INT_LEAST16_MIN in C99. It might be backported. */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef INT_LEAST16_MIN
        #define GHOST_INT_LEAST16_MIN INT_LEAST16_MIN
        #define ghost_has_GHOST_INT_LEAST16_MIN 1
    #endif
#endif

/* GNU C compilers define __INT_LEAST16_MIN__. */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #ifdef __INT_LEAST16_MIN__
        #define GHOST_INT_LEAST16_MIN __INT_LEAST16_MIN__
        #define ghost_has_GHOST_INT_LEAST16_MIN 1
    #endif
#endif

/*
 * Otherwise, as with ghost_int_least16_t, we check the widths of the
 * fundamental types from smallest to largest.
 */

/* Check if signed char is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #include "ghost/type/schar/ghost_schar_width.h"
    #if ghost_has(GHOST_SCHAR_WIDTH)
        #if GHOST_SCHAR_WIDTH >= 16
            #include "ghost/type/schar/ghost_schar_max.h"
            #if ghost_has(GHOST_SCHAR_MIN)
                #define GHOST_INT_LEAST16_MIN GHOST_SCHAR_MIN
                #define ghost_has_GHOST_INT_LEAST16_MIN 1
            #else
                #define ghost_has_GHOST_INT_LEAST16_MIN 0
            #endif
        #endif
    #endif
#endif

/* Check if short is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #include "ghost/type/short/ghost_short_width.h"
    #if ghost_has(GHOST_SHORT_WIDTH)
        #if GHOST_SHORT_WIDTH >= 16
            #include "ghost/type/short/ghost_short_max.h"
            #if ghost_has(GHOST_SHORT_MIN)
                #define GHOST_INT_LEAST16_MIN GHOST_SHORT_MIN
                #define ghost_has_GHOST_INT_LEAST16_MIN 1
            #else
                #define ghost_has_GHOST_INT_LEAST16_MIN 0
            #endif
        #endif
    #endif
#endif

/* Check if int is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #include "ghost/type/int/ghost_int_width.h"
    #if ghost_has(GHOST_INT_WIDTH)
        #if GHOST_INT_WIDTH >= 16
            #include "ghost/type/int/ghost_int_max.h"
            #if ghost_has(GHOST_INT_MIN)
                #define GHOST_INT_LEAST16_MIN GHOST_INT_MIN
                #define ghost_has_GHOST_INT_LEAST16_MIN 1
            #else
                #define ghost_has_GHOST_INT_LEAST16_MIN 0
            #endif
        #endif
    #endif
#endif

/* Check if long is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #include "ghost/type/long/ghost_long_width.h"
    #if ghost_has(GHOST_LONG_WIDTH)
        #if GHOST_LONG_WIDTH >= 16
            #include "ghost/type/long/ghost_long_max.h"
            #if ghost_has(GHOST_LONG_MIN)
                #define GHOST_INT_LEAST16_MIN GHOST_LONG_MIN
                #define ghost_has_GHOST_INT_LEAST16_MIN 1
            #else
                #define ghost_has_GHOST_INT_LEAST16_MIN 0
            #endif
        #endif
    #endif
#endif

/* Check if long long is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #include "ghost/type/llong/ghost_llong_width.h"
    #if ghost_has(GHOST_LLONG_WIDTH)
        #if GHOST_LLONG_WIDTH >= 16
            #include "ghost/type/llong/ghost_llong_max.h"
            #if ghost_has(GHOST_LLONG_MIN)
                #define GHOST_INT_LEAST16_MIN GHOST_LLONG_MIN
                #define ghost_has_GHOST_INT_LEAST16_MIN 1
            #else
                #define ghost_has_GHOST_INT_LEAST16_MIN 0
            #endif
        #endif
    #endif
#endif

/* Otherwise we don't know the min. */
#ifndef ghost_has_GHOST_INT_LEAST16_MIN
    #define ghost_has_GHOST_INT_LEAST16_MIN 0
#endif

/* Test min from max (assuming two's complement) */
#if ghost_has(GHOST_INT_LEAST16_MIN)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
        #include "ghost/type/int_least16_t/ghost_int_least16_max.h"
        #if ghost_has(GHOST_INT_LEAST16_MAX)
            #include "ghost/debug/ghost_static_assert.h"
            #include "ghost/language/ghost_static_cast.h"
            ghost_static_assert(GHOST_INT_LEAST16_MIN == -1 - GHOST_INT_LEAST16_MAX,
                    "GHOST_INT_LEAST16_MIN is incorrect");
        #endif
    #endif
#endif

#endif
