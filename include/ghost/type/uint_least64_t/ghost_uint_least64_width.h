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

#ifndef GHOST_UINT_LEAST64_WIDTH_H_INCLUDED
#define GHOST_UINT_LEAST64_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_UINT_LEAST64_WIDTH 64
 *
 * The width in bits of ghost_uint_least64_t (always exactly 64 if it exists.)
 */
#endif

/* Always include <stdint.h> so the user can use UINT_LEAST64_MAX if available. */
#include "ghost/header/c/ghost_stdint_h.h"

/* Allow override */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #ifdef GHOST_UINT_LEAST64_WIDTH
        #define ghost_has_GHOST_UINT_LEAST64_WIDTH 1
    #endif
#endif

/* ghost_uint_least64_t is required. */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #include "ghost/type/uint_least64_t/ghost_uint_least64_t.h"
    #if !ghost_has(ghost_uint_least64_t)
        #define ghost_has_GHOST_UINT_LEAST64_WIDTH 0
    #endif
#endif

/* <stdint.h> has UINT_LEAST64_WIDTH in C23. It might be backported. */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef UINT_LEAST64_WIDTH
        #define GHOST_UINT_LEAST64_WIDTH UINT_LEAST64_WIDTH
        #define ghost_has_GHOST_UINT_LEAST64_WIDTH 1
    #endif
#endif

/* GNU C compilers define __INT_LEAST64_WIDTH__. We assume signed and unsigned
 * are the same width. */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_SIGNED_UNSIGNED_SAME_WIDTH
        #ifdef __INT_LEAST64_WIDTH__
            #define GHOST_UINT_LEAST64_WIDTH __INT_LEAST64_WIDTH__
            #define ghost_has_GHOST_UINT_LEAST64_WIDTH 1
        #endif
    #endif
#endif

/* MSVC has unsigned __int64 which is always 64 bits.
 *     https://learn.microsoft.com/en-us/cpp/cpp/int8-int16-int64-int64 */
#ifndef ghost_has_ghost_uint_least64_t
    #ifdef _MSC_VER
        #define GHOST_UINT_LEAST64_WIDTH 64
        #define ghost_has_ghost_uint_least64_t 1
    #endif
#endif

/*
 * Otherwise, as with ghost_uint_least64_t, we check the widths of the
 * fundamental types from smallest to largest.
 */

/* Check if signed char is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #include "ghost/type/uchar/ghost_uchar_width.h"
    #if ghost_has(GHOST_UCHAR_WIDTH)
        #if GHOST_UCHAR_WIDTH >= 64
            #define GHOST_UINT_LEAST64_WIDTH GHOST_UCHAR_WIDTH
            #define ghost_has_GHOST_UINT_LEAST64_WIDTH 1
        #endif
    #endif
#endif

/* Check if unsigned short is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #include "ghost/type/ushort/ghost_ushort_width.h"
    #if ghost_has(GHOST_USHORT_WIDTH)
        #if GHOST_USHORT_WIDTH >= 64
            #define GHOST_UINT_LEAST64_WIDTH GHOST_USHORT_WIDTH
            #define ghost_has_GHOST_UINT_LEAST64_WIDTH 1
        #endif
    #endif
#endif

/* Check if unsigned int is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #include "ghost/type/uint/ghost_uint_width.h"
    #if ghost_has(GHOST_UINT_WIDTH)
        #if GHOST_UINT_WIDTH >= 64
            #define GHOST_UINT_LEAST64_WIDTH GHOST_UINT_WIDTH
            #define ghost_has_GHOST_UINT_LEAST64_WIDTH 1
        #endif
    #endif
#endif

/* Check if unsigned long is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #include "ghost/type/ulong/ghost_ulong_width.h"
    #if ghost_has(GHOST_ULONG_WIDTH)
        #if GHOST_ULONG_WIDTH >= 64
            #define GHOST_UINT_LEAST64_WIDTH GHOST_ULONG_WIDTH
            #define ghost_has_GHOST_UINT_LEAST64_WIDTH 1
        #endif
    #endif
#endif

/* Check if unsigned long long is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #include "ghost/type/ullong/ghost_ullong_width.h"
    #if ghost_has(GHOST_ULLONG_WIDTH)
        #if GHOST_ULLONG_WIDTH >= 64
            #define GHOST_UINT_LEAST64_WIDTH GHOST_ULLONG_WIDTH
            #define ghost_has_GHOST_UINT_LEAST64_WIDTH 1
        #endif
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_UINT_LEAST64_WIDTH
    #define ghost_has_GHOST_UINT_LEAST64_WIDTH 0
#endif

/* Test width with sizeof, assuming no padding bits */
#if ghost_has(GHOST_UINT_LEAST64_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(sizeof(ghost_uint_least64_t) * GHOST_CHAR_WIDTH == GHOST_UINT_LEAST64_WIDTH,
                "GHOST_UINT_LEAST64_WIDTH is incorrect");
    #endif
#endif

#endif
