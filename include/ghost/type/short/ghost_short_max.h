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

#ifndef GHOST_SHORT_MAX_H_INCLUDED
#define GHOST_SHORT_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SHORT_MAX SHRT_MAX
 *
 * The maximum value of signed short.
 */
#endif

#ifndef ghost_has_GHOST_SHORT_MAX
    #ifdef GHOST_SHORT_MAX
        #define ghost_has_GHOST_SHORT_MAX 1
    #endif
#endif

#ifndef ghost_has_GHOST_SHORT_MAX
    #include "ghost/type/short/ghost_short.h"
    #if !ghost_has(ghost_short)
        #define ghost_has_GHOST_SHORT_MAX 0
    #endif
#endif

/* <limits.h> has SHRT_MAX */
#ifndef ghost_has_GHOST_SHORT_MAX
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef SHRT_MAX
        #define GHOST_SHORT_MAX SHRT_MAX
        #define ghost_has_GHOST_SHORT_MAX 1
    #endif
#endif

/* GNU C compilers define __SHRT_MAX__. */
#ifndef ghost_has_GHOST_SHORT_MAX
    #ifdef __SHRT_MAX__
        #define GHOST_SHORT_MAX __SHRT_MAX__
        #define ghost_has_GHOST_SHORT_MAX 1
    #endif
#endif

/* Calculate max directly from width, assuming arithmetic types have no padding
 * bits. */
#ifndef ghost_has_GHOST_SHORT_MAX
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/type/short/ghost_short_width.h"
        #if ghost_has(GHOST_SHORT_WIDTH)
            /* Use hardcoded values if possible to make nicer compiler errors */
            #if GHOST_SHORT_WIDTH == 64
                #define GHOST_SHORT_MAX 9223372036854775807
            #elif GHOST_SHORT_WIDTH == 32
                #define GHOST_SHORT_MAX 2147483647
            #elif GHOST_SHORT_WIDTH == 16
                #define GHOST_SHORT_MAX 32767
            #elif GHOST_SHORT_WIDTH == 8
                #define GHOST_SHORT_MAX 127
            #else
                /* Careful not to overflow... */
                #define GHOST_SHORT_MAX ((((1 << (GHOST_SHORT_WIDTH - 2)) - 1) << 1) + 1)
            #endif
            #define ghost_has_GHOST_SHORT_MAX 1
        #endif
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_SHORT_MAX
    #define ghost_has_GHOST_SHORT_MAX 0
#endif

/* Test max from sizeof, assuming no padding bits */
#if ghost_has(GHOST_SHORT_MAX)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(GHOST_SHORT_MAX ==
                    ((((1L << (sizeof(short) * GHOST_CHAR_WIDTH - 2)) - 1L) << 1) + 1L),
                "GHOST_SHORT_MAX is incorrect");
    #endif
#endif

#endif
