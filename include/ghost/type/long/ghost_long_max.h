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

#ifndef GHOST_LONG_MAX_H_INCLUDED
#define GHOST_LONG_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_LONG_MAX LONG_MAX
 *
 * The maximum value of signed long.
 */
#endif

#ifndef ghost_has_GHOST_LONG_MAX
    #ifdef GHOST_LONG_MAX
        #define ghost_has_GHOST_LONG_MAX 1
    #endif
#endif

#ifndef ghost_has_GHOST_LONG_MAX
    #include "ghost/type/long/ghost_long.h"
    #if !ghost_has(ghost_long)
        #define ghost_has_GHOST_LONG_MAX 0
    #endif
#endif

/* <limits.h> has LONG_MAX */
#ifndef ghost_has_GHOST_LONG_MAX
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef LONG_MAX
        #define GHOST_LONG_MAX LONG_MAX
        #define ghost_has_GHOST_LONG_MAX 1
    #endif
#endif

/* GNU C compilers define __LONG_MAX__. */
#ifndef ghost_has_GHOST_LONG_MAX
    #ifdef __LONG_MAX__
        #define GHOST_LONG_MAX __LONG_MAX__
        #define ghost_has_GHOST_LONG_MAX 1
    #endif
#endif

/* Calculate max directly from width, assuming arithmetic types have no padding
 * bits. */
#ifndef ghost_has_GHOST_LONG_MAX
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/type/long/ghost_long_width.h"
        #if ghost_has(GHOST_LONG_WIDTH)
            /* Use hardcoded values if possible to make nicer compiler errors */
            #if GHOST_LONG_WIDTH == 64
                #define GHOST_LONG_MAX 9223372036854775807L
            #elif GHOST_LONG_WIDTH == 32
                #define GHOST_LONG_MAX 2147483647L
            #elif GHOST_LONG_WIDTH == 16
                #define GHOST_LONG_MAX 32767L
            #elif GHOST_LONG_WIDTH == 8
                #define GHOST_LONG_MAX 127L
            #else
                /* Careful not to overflow... */
                #define GHOST_LONG_MAX ((((1L << (GHOST_LONG_WIDTH - 2)) - 1L) << 1) + 1L)
            #endif
            #define ghost_has_GHOST_LONG_MAX 1
        #endif
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_LONG_MAX
    #define ghost_has_GHOST_LONG_MAX 0
#endif

/* Test max from sizeof, assuming no padding bits */
#if ghost_has(GHOST_LONG_MAX)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(GHOST_LONG_MAX ==
                    ((((1L << (sizeof(long) * GHOST_CHAR_WIDTH - 2)) - 1L) << 1) + 1L),
                "GHOST_LONG_MAX is incorrect");
    #endif
#endif

#endif
