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

#ifndef GHOST_LONG_WIDTH_H_INCLUDED
#define GHOST_LONG_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_LONG_WIDTH LONG_WIDTH
 *
 * The width of (signed) long in bits.
 */
#endif

#ifndef ghost_has_GHOST_LONG_WIDTH
    #ifdef GHOST_LONG_WIDTH
        #define ghost_has_GHOST_LONG_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_LONG_WIDTH
    #include "ghost/type/long/ghost_long.h"
    #if !ghost_has(ghost_long)
        #define ghost_has_GHOST_LONG_WIDTH 0
    #endif
#endif

/* C23 adds LONG_WIDTH to <limits.h>. It might be backported. */
#ifndef ghost_has_GHOST_LONG_WIDTH
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef LONG_WIDTH
        #define GHOST_LONG_WIDTH LONG_WIDTH
        #define ghost_has_GHOST_LONG_WIDTH 1
    #endif
#endif

/* GNU C compilers define __LONG_WIDTH__. Older GNU C compilers define
 * __SIZEOF_LONG__. */
#ifndef ghost_has_GHOST_LONG_WIDTH
    #ifdef __LONG_WIDTH__
        #define GHOST_LONG_WIDTH __LONG_WIDTH__
        #define ghost_has_GHOST_LONG_WIDTH 1
    #elif defined(__SIZEOF_LONG__)
        #include "ghost/type/char/ghost_char_width.h"
        #define GHOST_LONG_WIDTH (__SIZEOF_LONG__ * GHOST_CHAR_WIDTH)
        #define ghost_has_GHOST_LONG_WIDTH 1
    #endif
#endif

/* We don't compare e.g. LONG_MAX. See discussion in ghost_llong_width.h. */

/* See if the data model is declared explicitly. */
#ifndef ghost_has_GHOST_LONG_WIDTH
    #if defined(__ILP32__) || defined(_ILP32)
        #define GHOST_LONG_WIDTH 32
        #define ghost_has_GHOST_LONG_WIDTH 1
    #elif defined(__LP64__) || defined(_LP64)
        #define GHOST_LONG_WIDTH 64
        #define ghost_has_GHOST_LONG_WIDTH 1
    #endif
#endif

/* Note: WebAssembly is currently ILP32 but there are 64-bit extensions in the
 * works. It's not clear how we will detect the difference yet so for now we
 * expect WASM compilers to define _ILP32 or _LP64 as detected above. */

/* On Windows long is 32 bits on both 32-bit and 64-bit architectures. */
#ifndef ghost_has_GHOST_LONG_WIDTH
    #if defined(_WIN32)
        #define GHOST_LONG_WIDTH 32
        #define ghost_has_GHOST_LONG_WIDTH 1
    #endif
#endif

/* For virtually all other modern platforms, long is 32 bits on 32-bit
 * architectures and 64 bits on 64-bit architectures. */
#ifndef ghost_has_GHOST_LONG_WIDTH
    /* We need to handle riscv first because its architecture width is declared
     * specially. */
    #ifdef __riscv_xlen
        #if __riscv_xlen == 64
            #define GHOST_LONG_WIDTH 64
            #define ghost_has_GHOST_LONG_WIDTH 1
        #elif __riscv_xlen == 32
            #define GHOST_LONG_WIDTH 32
            #define ghost_has_GHOST_LONG_WIDTH 1
        #endif
    #elif \
            (defined(__i386__) && !defined(__x86_64__)) || \
            (defined(__arm__) && !defined(__aarch64__))
        #define GHOST_LONG_WIDTH 32
        #define ghost_has_GHOST_LONG_WIDTH 1
    #elif \
            defined(__x86_64__) || \
            defined(__aarch64__)
        #define GHOST_LONG_WIDTH 64
        #define ghost_has_GHOST_LONG_WIDTH 1
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_LONG_WIDTH
    #define ghost_has_GHOST_LONG_WIDTH 0
#endif

/* Test width with sizeof, assuming no padding bits */
#if ghost_has(GHOST_LONG_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(sizeof(long) * GHOST_CHAR_WIDTH == GHOST_LONG_WIDTH,
                "GHOST_LONG_WIDTH is incorrect");
    #endif
#endif

#endif
