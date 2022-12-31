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

#ifndef GHOST_UINT_LEAST8_T_H_INCLUDED
#define GHOST_UINT_LEAST8_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * An unsigned integer type at least 8 bits wide.
 *
 * If the implementation does not support an unsigned integer at least 8 bits
 * wide, this type will not exist. Check ghost_has(ghost_uint_least8_t) to see
 * whether it exists.
 */
typedef uint_least8_t ghost_uint_least8_t;
#endif

/* Allow override */
#ifndef ghost_has_ghost_uint_least8_t
    #ifdef ghost_uint_least8_t
        #define ghost_has_ghost_uint_least8_t 1
    #endif
#endif

/* <stdint.h> optionally has uint_least8_t in C99. We can't tell with the
 * preprocessor whether a typedef exists so instead we check whether
 * UINT_LEAST8_MAX is defined. We assume that an implementation of <stdint.h>
 * would define this macro if and only if it defines uint_least8_t.
 *     https://en.cppreference.com/w/c/types/unsigned integer */
#ifndef ghost_has_ghost_uint_least8_t
    #include "ghost/header/c/ghost_stdint_h.h"
    #if ghost_has(ghost_stdint_h) && defined(UINT_LEAST8_MAX)
        typedef uint_least8_t ghost_uint_least8_t;
        #define ghost_has_ghost_uint_least8_t 1
    #endif
#endif

/* GNU C compilers define __UINT_LEAST8_TYPE__. */
#ifndef ghost_has_ghost_uint_least8_t
    #ifdef __UINT_LEAST8_TYPE__
        typedef __UINT_LEAST8_TYPE__ ghost_uint_least8_t;
        #define ghost_has_ghost_uint_least8_t 1
    #endif
#endif

/* MSVC has __int8 as a built-in synonym for a fundamental type.
 *     https://learn.microsoft.com/en-us/cpp/cpp/int8-int16-int8-int64 */
#ifndef ghost_has_ghost_uint_least8_t
    #ifdef _MSC_VER
        typedef unsigned __int8 ghost_uint_least8_t;
        #define ghost_has_ghost_uint_least8_t 1
    #endif
#endif

/*
 * Otherwise we check the widths of the fundamental types, using the smallest
 * type that is at least 8 bits.
 *
 * This requires that we actually know the widths of the fundamental types. If
 * you are compiling on a platform where the below code doesn't work because
 * the fundamental type widths are missing, it's better to define those widths
 * and let the below code work.
 */

/* Check if unsigned char is wide enough */
#ifndef ghost_has_ghost_uint_least8_t
    #include "ghost/type/uchar/ghost_uchar_width.h"
    #if ghost_has(GHOST_UCHAR_WIDTH)
        #if GHOST_UCHAR_WIDTH >= 8
            typedef unsigned char ghost_uint_least8_t;
            #define ghost_has_ghost_uint_least8_t 1
        #endif
    #endif
#endif

/* Check if unsigned short is wide enough */
#ifndef ghost_has_ghost_uint_least8_t
    #include "ghost/type/ushort/ghost_ushort_width.h"
    #if ghost_has(GHOST_USHORT_WIDTH)
        #if GHOST_USHORT_WIDTH >= 8
            typedef unsigned short ghost_uint_least8_t;
            #define ghost_has_ghost_uint_least8_t 1
        #endif
    #endif
#endif

/* Check if unsigned int is wide enough */
#ifndef ghost_has_ghost_uint_least8_t
    #include "ghost/type/uint/ghost_uint_width.h"
    #if ghost_has(GHOST_UINT_WIDTH)
        #if GHOST_UINT_WIDTH >= 8
            typedef unsigned int ghost_uint_least8_t;
            #define ghost_has_ghost_uint_least8_t 1
        #endif
    #endif
#endif

/* Check if unsigned long is wide enough */
#ifndef ghost_has_ghost_uint_least8_t
    #include "ghost/type/ulong/ghost_ulong_width.h"
    #if ghost_has(GHOST_ULONG_WIDTH)
        #if GHOST_ULONG_WIDTH >= 8
            typedef unsigned long ghost_uint_least8_t;
            #define ghost_has_ghost_uint_least8_t 1
        #endif
    #endif
#endif

/* Check if unsigned long long is wide enough */
#ifndef ghost_has_ghost_uint_least8_t
    #include "ghost/type/ullong/ghost_ullong_width.h"
    #if ghost_has(GHOST_ULLONG_WIDTH)
        #if GHOST_ULLONG_WIDTH >= 8
            #include "ghost/type/ullong/ghost_ullong.h"
            typedef ghost_ullong ghost_uint_least8_t;
            #define ghost_has_ghost_uint_least8_t 1
        #endif
    #endif
#endif

/* Otherwise we don't have this. */
#ifndef ghost_has_ghost_uint_least8_t
    #define ghost_has_ghost_uint_least8_t 0
#endif

#endif
