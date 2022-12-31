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

#ifndef GHOST_INT_LEAST8_MAX_H_INCLUDED
#define GHOST_INT_LEAST8_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT_LEAST8_MAX INT_LEAST8_MAX
 *
 * The maximum value of ghost_int_least8_t.
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #ifdef GHOST_INT_LEAST8_MAX
        #define ghost_has_GHOST_INT_LEAST8_MAX 1
    #endif
#endif

/* ghost_int_least8_t is required. */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #include "ghost/type/int_least8_t/ghost_int_least8_t.h"
    #if !ghost_has(ghost_int_least8_t)
        #define ghost_has_GHOST_INT_LEAST8_MAX 0
    #endif
#endif

/* <stdint.h> has INT_LEAST8_MAX in C99. It might be backported. */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef INT_LEAST8_MAX
        #define GHOST_INT_LEAST8_MAX INT_LEAST8_MAX
        #define ghost_has_GHOST_INT_LEAST8_MAX 1
    #endif
#endif

/* GNU C compilers define __INT_LEAST8_MAX__. */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #ifdef __INT_LEAST8_MAX__
        #define GHOST_INT_LEAST8_MAX __INT_LEAST8_MAX__
        #define ghost_has_GHOST_INT_LEAST8_MAX 1
    #endif
#endif

/*
 * Otherwise, as with ghost_int_least8_t, we check the widths of the
 * fundamental types from smallest to largest.
 */

/* Check if signed char is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #include "ghost/type/schar/ghost_schar_width.h"
    #if ghost_has(GHOST_SCHAR_WIDTH)
        #if GHOST_SCHAR_WIDTH >= 8
            #include "ghost/type/schar/ghost_schar_max.h"
            #if ghost_has(GHOST_SCHAR_MAX)
                #define GHOST_INT_LEAST8_MAX GHOST_SCHAR_MAX
                #define ghost_has_GHOST_INT_LEAST8_MAX 1
            #else
                #define ghost_has_GHOST_INT_LEAST8_MAX 0
            #endif
        #endif
    #endif
#endif

/* Check if short is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #include "ghost/type/short/ghost_short_width.h"
    #if ghost_has(GHOST_SHORT_WIDTH)
        #if GHOST_SHORT_WIDTH >= 8
            #include "ghost/type/short/ghost_short_max.h"
            #if ghost_has(GHOST_SHORT_MAX)
                #define GHOST_INT_LEAST8_MAX GHOST_SHORT_MAX
                #define ghost_has_GHOST_INT_LEAST8_MAX 1
            #else
                #define ghost_has_GHOST_INT_LEAST8_MAX 0
            #endif
        #endif
    #endif
#endif

/* Check if int is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #include "ghost/type/int/ghost_int_width.h"
    #if ghost_has(GHOST_INT_WIDTH)
        #if GHOST_INT_WIDTH >= 8
            #include "ghost/type/int/ghost_int_max.h"
            #if ghost_has(GHOST_INT_MAX)
                #define GHOST_INT_LEAST8_MAX GHOST_INT_MAX
                #define ghost_has_GHOST_INT_LEAST8_MAX 1
            #else
                #define ghost_has_GHOST_INT_LEAST8_MAX 0
            #endif
        #endif
    #endif
#endif

/* Check if long is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #include "ghost/type/long/ghost_long_width.h"
    #if ghost_has(GHOST_LONG_WIDTH)
        #if GHOST_LONG_WIDTH >= 8
            #include "ghost/type/long/ghost_long_max.h"
            #if ghost_has(GHOST_LONG_MAX)
                #define GHOST_INT_LEAST8_MAX GHOST_LONG_MAX
                #define ghost_has_GHOST_INT_LEAST8_MAX 1
            #else
                #define ghost_has_GHOST_INT_LEAST8_MAX 0
            #endif
        #endif
    #endif
#endif

/* Check if long long is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #include "ghost/type/llong/ghost_llong_width.h"
    #if ghost_has(GHOST_LLONG_WIDTH)
        #if GHOST_LLONG_WIDTH >= 8
            #include "ghost/type/llong/ghost_llong_max.h"
            #if ghost_has(GHOST_LLONG_MAX)
                #define GHOST_INT_LEAST8_MAX GHOST_LLONG_MAX
                #define ghost_has_GHOST_INT_LEAST8_MAX 1
            #else
                #define ghost_has_GHOST_INT_LEAST8_MAX 0
            #endif
        #endif
    #endif
#endif

/* Otherwise we don't know the max. */
#ifndef ghost_has_GHOST_INT_LEAST8_MAX
    #define ghost_has_GHOST_INT_LEAST8_MAX 0
#endif

/* Test max from sizeof, assuming no padding bits */
#if ghost_has(GHOST_INT_LEAST8_MAX)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(GHOST_INT_LEAST8_MAX ==
                    ((((ghost_static_cast(ghost_int_least8_t, 1) << (sizeof(ghost_int_least8_t) * GHOST_CHAR_WIDTH - 2)) - 1) << 1) + 1),
                "GHOST_INT_LEAST8_MAX is incorrect");
    #endif
#endif

#endif
