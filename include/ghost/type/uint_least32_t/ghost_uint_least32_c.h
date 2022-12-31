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

#ifndef GHOST_UINT_LEAST32_C_H_INCLUDED
#define GHOST_UINT_LEAST32_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_UINT_LEAST32_C(x) x
 *
 * Defines a preprocessor constant of the promoted type of ghost_uint_least32_t.
 *
 * @see ghost_uint_least32_t
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #ifdef GHOST_UINT_LEAST32_C
        #define ghost_has_GHOST_UINT_LEAST32_C 1
    #endif
#endif

/* ghost_uint_least32_t is required. */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #include "ghost/type/uint_least32_t/ghost_uint_least32_t.h"
    #if !ghost_has(ghost_uint_least32_t)
        #define ghost_has_GHOST_UINT_LEAST32_C 0
    #endif
#endif

/* <stdint.h> has UINT32_C() in C99. It might be backported. It gives us a
 * constant of the promoted type of uint_least32_t (and not necessarily
 * uint32_t) which is what we want. */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef UINT32_C
        /* cparser workaround */
        #ifdef __CPARSER__
            #define GHOST_UINT_LEAST32_C(x) UINT32_C(x)
        #else
            #define GHOST_UINT_LEAST32_C UINT32_C
        #endif
        #define ghost_has_GHOST_UINT_LEAST32_C 1
    #endif
#endif

/* GNU C compilers define __UINT32_C. */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #ifdef __UINT32_C
        /* cparser workaround */
        #ifdef __CPARSER__
            #define GHOST_UINT_LEAST32_C(x) __UINT32_C(x)
        #else
            #define GHOST_UINT_LEAST32_C __UINT32_C
        #endif
        #define ghost_has_GHOST_UINT_LEAST32_C 1
    #endif
#endif

/*
 * Otherwise, as with ghost_uint_least32_t, we check the widths of the
 * fundamental types from smallest to largest.
 */

/* Check if unsigned char is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #include "ghost/type/uchar/ghost_uchar_width.h"
    #if ghost_has(GHOST_UCHAR_WIDTH)
        #if GHOST_UCHAR_WIDTH >= 32
            #define GHOST_UINT_LEAST32_C(x) x ## U
            #define ghost_has_GHOST_UINT_LEAST32_C 1
        #endif
    #endif
#endif

/* Check if unsigned short is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #include "ghost/type/ushort/ghost_ushort_width.h"
    #if ghost_has(GHOST_USHORT_WIDTH)
        #if GHOST_USHORT_WIDTH >= 32
            #define GHOST_UINT_LEAST32_C(x) x ## U
            #define ghost_has_GHOST_UINT_LEAST32_C 1
        #endif
    #endif
#endif

/* Check if unsigned int is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #include "ghost/type/uint/ghost_uint_width.h"
    #if ghost_has(GHOST_UINT_WIDTH)
        #if GHOST_UINT_WIDTH >= 32
            #define GHOST_UINT_LEAST32_C(x) x ## U
            #define ghost_has_GHOST_UINT_LEAST32_C 1
        #endif
    #endif
#endif

/* Check if unsigned long is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #include "ghost/type/ulong/ghost_ulong_width.h"
    #if ghost_has(GHOST_ULONG_WIDTH)
        #if GHOST_ULONG_WIDTH >= 32
            #define GHOST_UINT_LEAST32_C(x) x ## UL
            #define ghost_has_GHOST_UINT_LEAST32_C 1
        #endif
    #endif
#endif

/* Check if unsigned long long is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #include "ghost/type/ullong/ghost_ullong_width.h"
    #if ghost_has(GHOST_ULLONG_WIDTH)
        #if GHOST_ULLONG_WIDTH >= 32
            #define GHOST_UINT_LEAST32_C(x) x ## ULL
            #define ghost_has_GHOST_UINT_LEAST32_C 1
        #endif
    #endif
#endif

/* Otherwise we can't declare ghost_uint_least32_t constants. */
#ifndef ghost_has_GHOST_UINT_LEAST32_C
    #define ghost_has_GHOST_UINT_LEAST32_C 0
#endif

#endif
