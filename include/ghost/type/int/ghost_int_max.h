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

#ifndef GHOST_INT_MAX_H_INCLUDED
#define GHOST_INT_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT_MAX INT_MAX
 *
 * The maximum value of signed int.
 */
#endif

#ifndef ghost_has_GHOST_INT_MAX
    #ifdef GHOST_INT_MAX
        #define ghost_has_GHOST_INT_MAX 1
    #endif
#endif

#ifndef ghost_has_GHOST_INT_WIDTH
    #include "ghost/type/int/ghost_int.h"
    #if !ghost_has(ghost_int)
        #define ghost_has_GHOST_INT_WIDTH 0
    #endif
#endif

/* <limits.h> has INT_MAX */
#ifndef ghost_has_GHOST_INT_MAX
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef INT_MAX
        #define GHOST_INT_MAX INT_MAX
        #define ghost_has_GHOST_INT_MAX 1
    #endif
#endif

/* GNU C compilers define __INT_MAX__. */
#ifndef ghost_has_GHOST_INT_MAX
    #ifdef __INT_MAX__
        #define GHOST_INT_MAX __INT_MAX__
        #define ghost_has_GHOST_INT_MAX 1
    #endif
#endif

/* Calculate max directly from width, assuming arithmetic types have no padding
 * bits. */
#ifndef ghost_has_GHOST_INT_MAX
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/type/int/ghost_int_width.h"
        #if ghost_has(GHOST_INT_WIDTH)
            /* Use hardcoded values if possible to make nicer compiler errors */
            #if GHOST_INT_WIDTH == 64
                #define GHOST_INT_MAX 9223372036854775807
            #elif GHOST_INT_WIDTH == 32
                #define GHOST_INT_MAX 2147483647
            #elif GHOST_INT_WIDTH == 16
                #define GHOST_INT_MAX 32767
            #elif GHOST_INT_WIDTH == 8
                #define GHOST_INT_MAX 127
            #else
                /* Careful not to overflow... */
                #define GHOST_INT_MAX ((((1 << (GHOST_INT_WIDTH - 2)) - 1) << 1) + 1)
            #endif
            #define ghost_has_GHOST_INT_MAX 1
        #endif
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_INT_MAX
    #define ghost_has_GHOST_INT_MAX 0
#endif

/* Test max from sizeof, assuming no padding bits */
#if ghost_has(GHOST_INT_MAX)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(GHOST_INT_MAX ==
                    ((((1L << (sizeof(int) * GHOST_CHAR_WIDTH - 2)) - 1L) << 1) + 1L),
                "GHOST_INT_MAX is incorrect");
    #endif
#endif

#endif
