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

#ifndef GHOST_INT_LEAST16_WIDTH_H_INCLUDED
#define GHOST_INT_LEAST16_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT_LEAST16_WIDTH 16
 *
 * The width in bits of ghost_int_least16_t (always exactly 16 if it exists.)
 */
#endif

/* Always include <stdint.h> so the user can use INT_LEAST16_MAX if available. */
#include "ghost/header/c/ghost_stdint_h.h"

/* Allow override */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #ifdef GHOST_INT_LEAST16_WIDTH
        #define ghost_has_GHOST_INT_LEAST16_WIDTH 1
    #endif
#endif

/* ghost_int_least16_t is required. */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #include "ghost/type/int_least16_t/ghost_int_least16_t.h"
    #if !ghost_has(ghost_int_least16_t)
        #define ghost_has_GHOST_INT_LEAST16_WIDTH 0
    #endif
#endif

/* <stdint.h> has INT_LEAST16_WIDTH in C23. It might be backported. */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef INT_LEAST16_WIDTH
        #define GHOST_INT_LEAST16_WIDTH INT_LEAST16_WIDTH
        #define ghost_has_GHOST_INT_LEAST16_WIDTH 1
    #endif
#endif

/* GNU C compilers define __INT_LEAST16_WIDTH__. */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #ifdef __INT_LEAST16_WIDTH__
        #define GHOST_INT_LEAST16_WIDTH __INT_LEAST16_WIDTH__
        #define ghost_has_GHOST_INT_LEAST16_WIDTH 1
    #endif
#endif

/* MSVC has __int16 which is always 16 bits.
 *     https://learn.microsoft.com/en-us/cpp/cpp/int8-int16-int16-int64 */
#ifndef ghost_has_ghost_int_least16_t
    #ifdef _MSC_VER
        #define GHOST_INT_LEAST16_WIDTH 16
        #define ghost_has_ghost_int_least16_t 1
    #endif
#endif

/*
 * Otherwise, as with ghost_int_least16_t, we check the widths of the
 * fundamental types from smallest to largest.
 */

/* Check if signed char is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #include "ghost/type/schar/ghost_schar_width.h"
    #if ghost_has(GHOST_SCHAR_WIDTH)
        #if GHOST_SCHAR_WIDTH >= 16
            #define GHOST_INT_LEAST16_WIDTH GHOST_SCHAR_WIDTH
            #define ghost_has_GHOST_INT_LEAST16_WIDTH 1
        #endif
    #endif
#endif

/* Check if short is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #include "ghost/type/short/ghost_short_width.h"
    #if ghost_has(GHOST_SHORT_WIDTH)
        #if GHOST_SHORT_WIDTH >= 16
            #define GHOST_INT_LEAST16_WIDTH GHOST_SHORT_WIDTH
            #define ghost_has_GHOST_INT_LEAST16_WIDTH 1
        #endif
    #endif
#endif

/* Check if int is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #include "ghost/type/int/ghost_int_width.h"
    #if ghost_has(GHOST_INT_WIDTH)
        #if GHOST_INT_WIDTH >= 16
            #define GHOST_INT_LEAST16_WIDTH GHOST_INT_WIDTH
            #define ghost_has_GHOST_INT_LEAST16_WIDTH 1
        #endif
    #endif
#endif

/* Check if long is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #include "ghost/type/long/ghost_long_width.h"
    #if ghost_has(GHOST_LONG_WIDTH)
        #if GHOST_LONG_WIDTH >= 16
            #define GHOST_INT_LEAST16_WIDTH GHOST_LONG_WIDTH
            #define ghost_has_GHOST_INT_LEAST16_WIDTH 1
        #endif
    #endif
#endif

/* Check if long long is wide enough */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #include "ghost/type/llong/ghost_llong_width.h"
    #if ghost_has(GHOST_LLONG_WIDTH)
        #if GHOST_LLONG_WIDTH >= 16
            #define GHOST_INT_LEAST16_WIDTH GHOST_LLONG_WIDTH
            #define ghost_has_GHOST_INT_LEAST16_WIDTH 1
        #endif
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_INT_LEAST16_WIDTH
    #define ghost_has_GHOST_INT_LEAST16_WIDTH 0
#endif

/* Test width with sizeof, assuming no padding bits */
#if ghost_has(GHOST_INT_LEAST16_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(sizeof(ghost_int_least16_t) * GHOST_CHAR_WIDTH == GHOST_INT_LEAST16_WIDTH,
                "GHOST_INT_LEAST16_WIDTH is incorrect");
    #endif
#endif

#endif
