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

#ifndef GHOST_INT32_C_H_INCLUDED
#define GHOST_INT32_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT32_C(x) x
 *
 * Defines a preprocessor constant of the promoted type of ghost_int32_t.
 *
 * Note that this exists under different conditions than the standard
 * INT32_C(). INT32_C() is a constant of the promoted type of int_least32_t,
 * which may exist even if int32_t does not. Ghost provides separate macros for
 * these (even though they are the same if both exist.) If ghost_int32_t does
 * not exist, GHOST_INT32_C() will not exist either.
 *
 * @see ghost_int32_t
 * @see ghost_int_least32_t
 * @see GHOST_INT_LEAST32_C
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_INT32_C
    #ifdef GHOST_INT32_C
        #define ghost_has_GHOST_INT32_C 1
    #endif
#endif

/* ghost_int32_t is required. */
#ifndef ghost_has_GHOST_INT32_C
    #include "ghost/type/int32_t/ghost_int32_t.h"
    #if !ghost_has(ghost_int32_t)
        #define ghost_has_GHOST_INT32_C 0
    #endif
#endif

/* <stdint.h> has INT32_C() in C99. It might be backported. INT32_C() actually
 * defines a constant of the promoted type of int_least32_t, but if int32_t
 * exists, then int_least32_t must be the same width. */
#ifndef ghost_has_GHOST_INT32_C
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef INT32_C
        /* cparser workaround */
        #ifdef __CPARSER__
            #define GHOST_INT32_C(x) INT32_C(x)
        #else
            #define GHOST_INT32_C INT32_C
        #endif
        #define ghost_has_GHOST_INT32_C 1
    #endif
#endif

/* GNU C compilers define __INT32_C. */
#ifndef ghost_has_GHOST_INT32_C
    #ifdef __INT32_C
        /* cparser workaround */
        #ifdef __CPARSER__
            #define GHOST_INT32_C(x) __INT32_C(x)
        #else
            #define GHOST_INT32_C __INT32_C
        #endif
        #define ghost_has_GHOST_INT32_C 1
    #endif
#endif

/*
 * Otherwise, as with ghost_int32_t, we check the widths of the fundamental
 * types from smallest to largest.
 */

/* Assume fundamental types have no padding bits */
#ifndef ghost_has_GHOST_INT32_C
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if !GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #define ghost_has_GHOST_INT32_C 0
    #endif
#endif

/* Check if signed char is the correct width */
#ifndef ghost_has_GHOST_INT32_C
    #include "ghost/type/schar/ghost_schar_width.h"
    #if ghost_has(GHOST_SCHAR_WIDTH)
        #if GHOST_SCHAR_WIDTH == 32
            #define GHOST_INT32_C(x) x
            #define ghost_has_GHOST_INT32_C 1
        #endif
    #endif
#endif

/* Check if short is the correct width */
#ifndef ghost_has_GHOST_INT32_C
    #include "ghost/type/short/ghost_short_width.h"
    #if ghost_has(GHOST_SHORT_WIDTH)
        #if GHOST_SHORT_WIDTH == 32
            #define GHOST_INT32_C(x) x
            #define ghost_has_GHOST_INT32_C 1
        #endif
    #endif
#endif

/* Check if int is the correct width */
#ifndef ghost_has_GHOST_INT32_C
    #include "ghost/type/int/ghost_int_width.h"
    #if ghost_has(GHOST_INT_WIDTH)
        #if GHOST_INT_WIDTH == 32
            #define GHOST_INT32_C(x) x
            #define ghost_has_GHOST_INT32_C 1
        #endif
    #endif
#endif

/* Check if long is the correct width */
#ifndef ghost_has_GHOST_INT32_C
    #include "ghost/type/long/ghost_long_width.h"
    #if ghost_has(GHOST_LONG_WIDTH)
        #if GHOST_LONG_WIDTH == 32
            #define GHOST_INT32_C(x) x ## L
            #define ghost_has_GHOST_INT32_C 1
        #endif
    #endif
#endif

/* Check if long long is the correct width */
#ifndef ghost_has_GHOST_INT32_C
    #include "ghost/type/llong/ghost_llong_width.h"
    #if ghost_has(GHOST_LLONG_WIDTH)
        #if GHOST_LLONG_WIDTH == 32
            #define GHOST_INT32_C(x) x ## LL
            #define ghost_has_GHOST_INT32_C 1
        #endif
    #endif
#endif

/* Otherwise we can't declare ghost_int32_t constants. */
#ifndef ghost_has_GHOST_INT32_C
    #define ghost_has_GHOST_INT32_C 0
#endif

#endif
