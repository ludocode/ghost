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

#ifndef GHOST_INT32_T_H_INCLUDED
#define GHOST_INT32_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A signed two's complement integer type exactly 32 bits wide with no padding
 * bits.
 *
 * If the implementation does not support an integer exactly 32 bits wide, this
 * type will not exist. Check ghost_has(ghost_int32_t) to see whether it exists.
 */
typedef int32_t ghost_int32_t;
#endif

/* Allow override */
#ifndef ghost_has_ghost_int32_t
    #ifdef ghost_int32_t
        #define ghost_has_ghost_int32_t 1
    #endif
#endif

/* <stdint.h> optionally has int32_t in C99. We can't tell with the
 * preprocessor whether a typedef exists so instead we check whether INT32_MAX
 * and INT32_MIN are defined. We assume that an implementation of <stdint.h>
 * would define these macros if and only if it defines int32_t.
 *     https://en.cppreference.com/w/c/types/integer */
#ifndef ghost_has_ghost_int32_t
    #include "ghost/header/c/ghost_stdint_h.h"
    #if ghost_has(ghost_stdint_h) && defined(INT32_MAX) && defined(INT32_MIN)
        typedef int32_t ghost_int32_t;
        #define ghost_has_ghost_int32_t 1
    #endif
#endif

/* GNU C compilers define __INT32_TYPE__. */
#ifndef ghost_has_ghost_int32_t
    #ifdef __INT32_TYPE__
        typedef __INT32_TYPE__ ghost_int32_t;
        #define ghost_has_ghost_int32_t 1
    #endif
#endif

/* MSVC has __int32 as a built-in synonym for a fundamental type.
 *     https://learn.microsoft.com/en-us/cpp/cpp/int8-int16-int32-int64 */
#ifndef ghost_has_ghost_int32_t
    #ifdef _MSC_VER
        typedef __int32 ghost_int32_t;
        #define ghost_has_ghost_int32_t 1
    #endif
#endif

/*
 * Otherwise we check the widths of the fundamental types. We check from
 * smallest to largest for consistency with all fixed-width types.
 *
 * This requires that we actually know the widths of the fundamental types. If
 * you are compiling on a platform where the below code doesn't work because
 * the fundamental type widths are missing, it's better to define those widths
 * and let the below code work.
 */

/* The rest of this assumes fundamental types have no padding bits. */
#ifndef ghost_has_ghost_int32_t
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if !GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #define ghost_has_ghost_int32_t 0
    #endif
#endif

/* Check if signed char is the correct width */
#ifndef ghost_has_ghost_int32_t
    #include "ghost/type/schar/ghost_schar_width.h"
    #if ghost_has(GHOST_SCHAR_WIDTH)
        #if GHOST_SCHAR_WIDTH == 32
            typedef signed char ghost_int32_t;
            #define ghost_has_ghost_int32_t 1
        #endif
    #endif
#endif

/* Check if short is the correct width */
#ifndef ghost_has_ghost_int32_t
    #include "ghost/type/short/ghost_short_width.h"
    #if ghost_has(GHOST_SHORT_WIDTH)
        #if GHOST_SHORT_WIDTH == 32
            typedef short ghost_int32_t;
            #define ghost_has_ghost_int32_t 1
        #endif
    #endif
#endif

/* Check if int is the correct width */
#ifndef ghost_has_ghost_int32_t
    #include "ghost/type/int/ghost_int_width.h"
    #if ghost_has(GHOST_INT_WIDTH)
        #if GHOST_INT_WIDTH == 32
            typedef int ghost_int32_t;
            #define ghost_has_ghost_int32_t 1
        #endif
    #endif
#endif

/* Check if long is the correct width */
#ifndef ghost_has_ghost_int32_t
    #include "ghost/type/long/ghost_long_width.h"
    #if ghost_has(GHOST_LONG_WIDTH)
        #if GHOST_LONG_WIDTH == 32
            typedef long ghost_int32_t;
            #define ghost_has_ghost_int32_t 1
        #endif
    #endif
#endif

/* Check if long long is the correct width */
#ifndef ghost_has_ghost_int32_t
    #include "ghost/type/llong/ghost_llong_width.h"
    #if ghost_has(GHOST_LLONG_WIDTH)
        #if GHOST_LLONG_WIDTH == 32
            #include "ghost/type/llong/ghost_llong.h"
            typedef ghost_llong ghost_int32_t;
            #define ghost_has_ghost_int32_t 1
        #endif
    #endif
#endif

/* Otherwise we don't have this. */
#ifndef ghost_has_ghost_int32_t
    #define ghost_has_ghost_int32_t 0
#endif

#endif
