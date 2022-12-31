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

#ifndef GHOST_UINT_LEAST64_MAX_H_INCLUDED
#define GHOST_UINT_LEAST64_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_UINT_LEAST64_MAX UINT_LEAST64_MAX
 *
 * The maximum value of ghost_uint_least64_t.
 */
#endif

/* Allow override */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #ifdef GHOST_UINT_LEAST64_MAX
        #define ghost_has_GHOST_UINT_LEAST64_MAX 1
    #endif
#endif

/* ghost_uint_least64_t is required. */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #include "ghost/type/uint_least64_t/ghost_uint_least64_t.h"
    #if !ghost_has(ghost_uint_least64_t)
        #define ghost_has_GHOST_UINT_LEAST64_MAX 0
    #endif
#endif

/* <stdint.h> has UINT_LEAST64_MAX in C99. It might be backported. */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #include "ghost/header/c/ghost_stdint_h.h"
    #ifdef UINT_LEAST64_MAX
        #define GHOST_UINT_LEAST64_MAX UINT_LEAST64_MAX
        #define ghost_has_GHOST_UINT_LEAST64_MAX 1
    #endif
#endif

/* GNU C compilers define __UINT_LEAST64_MAX__. */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #ifdef __UINT_LEAST64_MAX__
        #define GHOST_UINT_LEAST64_MAX __UINT_LEAST64_MAX__
        #define ghost_has_GHOST_UINT_LEAST64_MAX 1
    #endif
#endif

/*
 * Otherwise, as with ghost_uint_least64_t, we check the widths of the
 * fundamental types from smallest to largest.
 */

/* Check if unsigned char is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #include "ghost/type/uchar/ghost_uchar_width.h"
    #if ghost_has(GHOST_UCHAR_WIDTH)
        #if GHOST_UCHAR_WIDTH >= 64
            #include "ghost/type/uchar/ghost_uchar_max.h"
            #if ghost_has(GHOST_UCHAR_MAX)
                #define GHOST_UINT_LEAST64_MAX GHOST_UCHAR_MAX
                #define ghost_has_GHOST_UINT_LEAST64_MAX 1
            #else
                #define ghost_has_GHOST_UINT_LEAST64_MAX 0
            #endif
        #endif
    #endif
#endif

/* Check if unsigned short is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #include "ghost/type/ushort/ghost_ushort_width.h"
    #if ghost_has(GHOST_USHORT_WIDTH)
        #if GHOST_USHORT_WIDTH >= 64
            #include "ghost/type/ushort/ghost_ushort_max.h"
            #if ghost_has(GHOST_USHORT_MAX)
                #define GHOST_UINT_LEAST64_MAX GHOST_USHORT_MAX
                #define ghost_has_GHOST_UINT_LEAST64_MAX 1
            #else
                #define ghost_has_GHOST_UINT_LEAST64_MAX 0
            #endif
        #endif
    #endif
#endif

/* Check if unsigned int is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #include "ghost/type/uint/ghost_uint_width.h"
    #if ghost_has(GHOST_UINT_WIDTH)
        #if GHOST_UINT_WIDTH >= 64
            #include "ghost/type/uint/ghost_uint_max.h"
            #if ghost_has(GHOST_UINT_MAX)
                #define GHOST_UINT_LEAST64_MAX GHOST_UINT_MAX
                #define ghost_has_GHOST_UINT_LEAST64_MAX 1
            #else
                #define ghost_has_GHOST_UINT_LEAST64_MAX 0
            #endif
        #endif
    #endif
#endif

/* Check if unsigned long is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #include "ghost/type/ulong/ghost_ulong_width.h"
    #if ghost_has(GHOST_ULONG_WIDTH)
        #if GHOST_ULONG_WIDTH >= 64
            #include "ghost/type/ulong/ghost_ulong_max.h"
            #if ghost_has(GHOST_ULONG_MAX)
                #define GHOST_UINT_LEAST64_MAX GHOST_ULONG_MAX
                #define ghost_has_GHOST_UINT_LEAST64_MAX 1
            #else
                #define ghost_has_GHOST_UINT_LEAST64_MAX 0
            #endif
        #endif
    #endif
#endif

/* Check if unsigned long long is wide enough */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #include "ghost/type/ullong/ghost_ullong_width.h"
    #if ghost_has(GHOST_ULLONG_WIDTH)
        #if GHOST_ULLONG_WIDTH >= 64
            #include "ghost/type/ullong/ghost_ullong_max.h"
            #if ghost_has(GHOST_ULLONG_MAX)
                #define GHOST_UINT_LEAST64_MAX GHOST_ULLONG_MAX
                #define ghost_has_GHOST_UINT_LEAST64_MAX 1
            #else
                #define ghost_has_GHOST_UINT_LEAST64_MAX 0
            #endif
        #endif
    #endif
#endif

/* Otherwise we don't know the max. */
#ifndef ghost_has_GHOST_UINT_LEAST64_MAX
    #define ghost_has_GHOST_UINT_LEAST64_MAX 0
#endif

/* Test max from sizeof, assuming no padding bits */
#if ghost_has(GHOST_UINT_LEAST64_MAX)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(GHOST_UINT_LEAST64_MAX ==
                    ((((ghost_static_cast(ghost_uint_least64_t, 1U) << (sizeof(ghost_uint_least64_t) * GHOST_CHAR_WIDTH - 1)) - 1U) << 1) + 1U),
                "GHOST_UINT_LEAST64_MAX is incorrect");
    #endif
#endif

#endif
