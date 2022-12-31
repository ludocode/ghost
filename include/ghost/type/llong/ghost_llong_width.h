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

#ifndef GHOST_LLONG_WIDTH_H_INCLUDED
#define GHOST_LLONG_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_LLONG_WIDTH LLONG_WIDTH
 *
 * The width of (signed) long long in bits.
 */
#endif

#ifndef ghost_has_GHOST_LLONG_WIDTH
    #ifdef GHOST_LLONG_WIDTH
        #define ghost_has_GHOST_LLONG_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_LLONG_WIDTH
    #include "ghost/type/llong/ghost_llong.h"
    #if !ghost_has(ghost_llong)
        #define ghost_has_GHOST_LLONG_WIDTH 0
    #endif
#endif

/* C23 adds LLONG_WIDTH to <limits.h>. It might be backported. */
#ifndef ghost_has_GHOST_LLONG_WIDTH
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef LLONG_WIDTH
        #define GHOST_LLONG_WIDTH LLONG_WIDTH
        #define ghost_has_GHOST_LLONG_WIDTH 1
    #endif
#endif

/* GNU C compilers define __LONG_LONG_WIDTH__. Older GNU C compilers define
 * __SIZEOF_LONG_LONG__. */
#ifndef ghost_has_GHOST_LLONG_WIDTH
    #ifdef __LONG_LONG_WIDTH__
        #define GHOST_LLONG_WIDTH __LONG_LONG_WIDTH__
        #define ghost_has_GHOST_LLONG_WIDTH 1
    #elif defined(__SIZEOF_LONG_LONG__)
        #include "ghost/type/char/ghost_char_width.h"
        #define GHOST_LLONG_WIDTH (__SIZEOF_LONG_LONG__ * GHOST_CHAR_WIDTH)
        #define ghost_has_GHOST_LLONG_WIDTH 1
    #endif
#endif

/*
 * Many third-party implementations of <stdint.h>, <limits.h> and others
 * attempt to determine the width of standard types based on their max values
 * using the preprocessor. Such code will typically look like this:
 *
 *     #if UINT_MAX == 0xFFFFFFFFU
 *         #define UINT_WIDTH 32
 *     #elif UINT_MAX == 0xFFFFFFFFFFFFFFFFLLU
 *         #define UINT_WIDTH 64
 *     #endif
 *
 * This is wrong. Several real world implementations of <limits.h> define
 * UINT_MAX as (~0U) and ULONG_MAX as (~0LU). This breaks the above comparisons
 * because preprocessor arithmetic must be performed as (u)intmax_t. This means
 * the preprocessor for a compiler that has a 64-bit long long must ignore
 * suffixes and evaluate (~0U) as 0xFFFFFFFFFFFFFFFF, not 0xFFFFFFFF.
 *
 * Intrinsics defined by compilers are more well-behaved. For example on
 * x86_64, Clang and older GCC define __LONG_LONG_MAX__ to
 * 9223372036854775807LL while newer GCC defines it to 0x7fffffffffffffffLL.
 * GCC in particular defined this for several versions before it started
 * defining __SIZEOF_LONG_LONG__ so we could in theory usefully and safely
 * compare the max on older compilers.
 *
 * There is however another problem with comparing these: a compiler for a
 * platform that does not support a 64-bit type is not required to be able to
 * perform preprocessor arithmetic on 64-bit numbers. If we try to do such
 * checks, the preprocessor could fail due to trying to compare too large a
 * number. We could scope it to compilers we know support bignum or at least
 * 64-bit preprocessor arithmetic but this is getting too complicated for
 * little benefit.
 *
 * It's safer to avoid comparing values with the preprocessor and instead just
 * rely on direct platform detection.
 */

/* On virtually all modern machines, long long is 64 bits. */
#ifndef ghost_has_GHOST_LLONG_WIDTH
    #if defined(_WIN32) || \
            defined(__LP64__) || defined(_LP64) || \
            defined(__ILP32__) || defined(_ILP32) || \
            defined(__x86_64__) || defined(__i386__) || \
            defined(__arm__) || defined(__aarch64__) || \
            defined(__riscv) || defined(__riscv__) || \
            defined(__wasm) || defined(__wasm__)
        #define GHOST_LLONG_WIDTH 64
        #define ghost_has_GHOST_LLONG_WIDTH 1
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_LLONG_WIDTH
    #define ghost_has_GHOST_LLONG_WIDTH 0
#endif

/* Test width with sizeof, assuming no padding bits */
#if ghost_has(GHOST_LLONG_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(sizeof(ghost_llong) * GHOST_CHAR_WIDTH == GHOST_LLONG_WIDTH,
                "GHOST_LLONG_WIDTH is incorrect");
    #endif
#endif

#endif
