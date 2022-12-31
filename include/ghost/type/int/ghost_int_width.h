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

#ifndef GHOST_INT_WIDTH_H_INCLUDED
#define GHOST_INT_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT_WIDTH INT_WIDTH
 *
 * The width of signed int in bits.
 */
#endif

#ifndef ghost_has_GHOST_INT_WIDTH
    #ifdef GHOST_INT_WIDTH
        #define ghost_has_GHOST_INT_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_INT_WIDTH
    #include "ghost/type/int/ghost_int.h"
    #if !ghost_has(ghost_int)
        #define ghost_has_GHOST_INT_WIDTH 0
    #endif
#endif

/* C23 adds INT_WIDTH to <limits.h>. It might be backported. */
#ifndef ghost_has_GHOST_INT_WIDTH
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef INT_WIDTH
        #define GHOST_INT_WIDTH INT_WIDTH
        #define ghost_has_GHOST_INT_WIDTH 1
    #endif
#endif

/* GNU C compilers define __INT_WIDTH__. Older GNU C compilers define
 * __SIZEOF_INT__. */
#ifndef ghost_has_GHOST_INT_WIDTH
    #ifdef __INT_WIDTH__
        #define GHOST_INT_WIDTH __INT_WIDTH__
        #define ghost_has_GHOST_INT_WIDTH 1
    #elif defined(__SIZEOF_INT__)
        #include "ghost/type/char/ghost_char_width.h"
        #define GHOST_INT_WIDTH (__SIZEOF_INT__ * GHOST_CHAR_WIDTH)
        #define ghost_has_GHOST_INT_WIDTH 1
    #endif
#endif

/* We don't compare e.g. INT_MAX. See discussion in ghost_llong_width.h. */

/* On virtually all modern machines, int is 32 bits. */
#ifndef ghost_has_GHOST_INT_WIDTH
    #if defined(_WIN32) || \
            defined(__LP64__) || defined(_LP64) || \
            defined(__ILP32__) || defined(_ILP32) || \
            defined(__x86_64__) || defined(__i386__) || \
            defined(__arm__) || defined(__aarch64__) || \
            defined(__riscv) || defined(__riscv__) || \
            defined(__wasm) || defined(__wasm__)
        #define GHOST_INT_WIDTH 32
        #define ghost_has_GHOST_INT_WIDTH 1
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_INT_WIDTH
    #define ghost_has_GHOST_INT_WIDTH 0
#endif

/* Test width with sizeof, assuming no padding bits */
#if ghost_has(GHOST_INT_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(sizeof(int) * GHOST_CHAR_WIDTH == GHOST_INT_WIDTH,
                "GHOST_INT_WIDTH is incorrect");
    #endif
#endif

#endif
