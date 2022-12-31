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

#ifndef GHOST_UINT64_C_H_INCLUDED
#define GHOST_UINT64_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_UINT64_C(x) x
 *
 * Defines a preprocessor constant of the promoted type of ghost_uint64_t.
 *
 * Note that this exists under different conditions than the standard
 * UINT64_C(). UINT64_C() is a constant of the promoted type of uint_least64_t,
 * which may exist even if uint64_t does not. Ghost provides separate macros
 * for these (even though they are the same if both exist.) If ghost_uint64_t
 * does not exist, GHOST_UINT64_C() will not exist either.
 *
 * @see ghost_uint64_t
 * @see ghost_uint_least64_t
 * @see GHOST_UINT_LEAST64_C
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_UINT64_C
    #ifdef GHOST_UINT64_C
        #define ghost_has_GHOST_UINT64_C 1
    #endif
#endif

/* ghost_uint64_t is required. */
#ifndef ghost_has_GHOST_UINT64_C
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #if !ghost_has(ghost_uint64_t)
        #define ghost_has_GHOST_UINT64_C 0
    #endif
#endif

/* <stdint.h> has UINT64_C() in C99. It might be backported. UINT64_C()
 * actually defines a constant of the promoted type of uint_least64_t, but if
 * uint64_t exists, then uint_least64_t must be the same width. */
#ifndef ghost_has_GHOST_UINT64_C
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef UINT64_C
        /* cparser workaround */
        #ifdef __CPARSER__
            #define GHOST_UINT64_C(x) UINT64_C(x)
        #else
            #define GHOST_UINT64_C UINT64_C
        #endif
        #define ghost_has_GHOST_UINT64_C 1
    #endif
#endif

/* GNU C compilers define __UINT64_C. */
#ifndef ghost_has_GHOST_UINT64_C
    #ifdef __UINT64_C
        /* cparser workaround */
        #ifdef __CPARSER__
            #define GHOST_UINT64_C(x) __UINT64_C(x)
        #else
            #define GHOST_UINT64_C __UINT64_C
        #endif
        #define ghost_has_GHOST_UINT64_C 1
    #endif
#endif

/*
 * Otherwise, as with ghost_uint64_t, we check the widths of the fundamental
 * types from smallest to largest.
 */

/* Assume fundamental types have no padding bits */
#ifndef ghost_has_GHOST_UINT64_C
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if !GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #define ghost_has_GHOST_UINT64_C 0
    #endif
#endif

/* Check if signed char is the correct width */
#ifndef ghost_has_GHOST_UINT64_C
    #include "ghost/type/uchar/ghost_uchar_width.h"
    #if ghost_has(GHOST_UCHAR_WIDTH)
        #if GHOST_UCHAR_WIDTH == 64
            #define GHOST_UINT64_C(x) x ## U
            #define ghost_has_GHOST_UINT64_C 1
        #endif
    #endif
#endif

/* Check if short is the correct width */
#ifndef ghost_has_GHOST_UINT64_C
    #include "ghost/type/ushort/ghost_ushort_width.h"
    #if ghost_has(GHOST_USHORT_WIDTH)
        #if GHOST_USHORT_WIDTH == 64
            #define GHOST_UINT64_C(x) x ## U
            #define ghost_has_GHOST_UINT64_C 1
        #endif
    #endif
#endif

/* Check if int is the correct width */
#ifndef ghost_has_GHOST_UINT64_C
    #include "ghost/type/uint/ghost_uint_width.h"
    #if ghost_has(GHOST_UINT_WIDTH)
        #if GHOST_UINT_WIDTH == 64
            #define GHOST_UINT64_C(x) x ## U
            #define ghost_has_GHOST_UINT64_C 1
        #endif
    #endif
#endif

/* Check if long is the correct width */
#ifndef ghost_has_GHOST_UINT64_C
    #include "ghost/type/ulong/ghost_ulong_width.h"
    #if ghost_has(GHOST_ULONG_WIDTH)
        #if GHOST_ULONG_WIDTH == 64
            #define GHOST_UINT64_C(x) x ## UL
            #define ghost_has_GHOST_UINT64_C 1
        #endif
    #endif
#endif

/* Check if long long is the correct width */
#ifndef ghost_has_GHOST_UINT64_C
    #include "ghost/type/ullong/ghost_ullong_width.h"
    #if ghost_has(GHOST_ULLONG_WIDTH)
        #if GHOST_LLONG_WIDTH == 64
            #define GHOST_UINT64_C(x) x ## ULL
            #define ghost_has_GHOST_UINT64_C 1
        #endif
    #endif
#endif

/* Otherwise we can't declare ghost_uint64_t constants. */
#ifndef ghost_has_GHOST_UINT64_C
    #define ghost_has_GHOST_UINT64_C 0
#endif

#endif
