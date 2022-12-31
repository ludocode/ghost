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

#ifndef GHOST_SHORT_WIDTH_H_INCLUDED
#define GHOST_SHORT_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SHORT_WIDTH SHRT_WIDTH
 *
 * The width of signed short in bits.
 */
#endif

#ifndef ghost_has_GHOST_SHORT_WIDTH
    #ifdef GHOST_SHORT_WIDTH
        #define ghost_has_GHOST_SHORT_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_SHORT_WIDTH
    #include "ghost/type/short/ghost_short.h"
    #if !ghost_has(ghost_short)
        #define ghost_has_GHOST_SHORT_WIDTH 0
    #endif
#endif

/* C23 adds SHRT_WIDTH to <limits.h>. It might be backported. */
#ifndef ghost_has_GHOST_SHORT_WIDTH
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef SHRT_WIDTH
        #define GHOST_SHORT_WIDTH SHRT_WIDTH
        #define ghost_has_GHOST_SHORT_WIDTH 1
    #endif
#endif

/* GNU C compilers define __SHRT_WIDTH__. Older GNU C compilers define
 * __SIZEOF_SHORT__. */
#ifndef ghost_has_GHOST_SHORT_WIDTH
    #ifdef __SHRT_WIDTH__
        #define GHOST_SHORT_WIDTH __SHRT_WIDTH__
        #define ghost_has_GHOST_SHORT_WIDTH 1
    #elif defined(__SIZEOF_SHORT__)
        #include "ghost/type/char/ghost_char_width.h"
        #define GHOST_SHORT_WIDTH (__SIZEOF_SHORT__ * GHOST_CHAR_WIDTH)
        #define ghost_has_GHOST_SHORT_WIDTH 1
    #endif
#endif

/* We don't compare e.g. SHRT_MAX. See discussion in ghost_llong_width.h. */

/* On virtually all modern machines, short is 16 bits. */
#ifndef ghost_has_GHOST_SHORT_WIDTH
    #if defined(_WIN32) || \
            defined(__LP64__) || defined(_LP64) || \
            defined(__ILP32__) || defined(_ILP32) || \
            defined(__x86_64__) || defined(__i386__) || \
            defined(__arm__) || defined(__aarch64__) || \
            defined(__riscv) || defined(__riscv__) || \
            defined(__wasm) || defined(__wasm__)
        #define GHOST_SHORT_WIDTH 16
        #define ghost_has_GHOST_SHORT_WIDTH 1
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_SHORT_WIDTH
    #define ghost_has_GHOST_SHORT_WIDTH 0
#endif

/* Test width with sizeof, assuming no padding bits */
#if ghost_has(GHOST_SHORT_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(sizeof(short) * GHOST_CHAR_WIDTH == GHOST_SHORT_WIDTH,
                "GHOST_SHORT_WIDTH is incorrect");
    #endif
#endif

#endif
