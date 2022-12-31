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

#ifndef GHOST_SIZE_WIDTH_H_INCLUDED
#define GHOST_SIZE_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SIZE_WIDTH SIZE_WIDTH
 *
 * The width of ghost_size_t in bits.
 */
#define ghost_has_GHOST_SIZE_WIDTH 1
#endif

/* SIZE_WIDTH is in <stdint.h>. Always include it unconditionally.
 *     https://en.cppreference.com/w/c/types/limits */
#include "ghost/header/c/ghost_stdint_h.h"

#ifndef ghost_has_GHOST_SIZE_WIDTH
    #ifdef GHOST_SIZE_WIDTH
        #define ghost_has_GHOST_SIZE_WIDTH 1
    #endif
#endif

/* C23 defines SIZE_WIDTH. It might be backported. */
#ifndef ghost_has_GHOST_SIZE_WIDTH
    #ifdef SIZE_WIDTH
        #define GHOST_SIZE_WIDTH SIZE_WIDTH
        #define ghost_has_GHOST_SIZE_WIDTH 1
    #endif
#endif

/* Newer GNU C compilers tell us __SIZE_WIDTH__. Older GNU C compilers tell us
 * __SIZEOF_SIZE_T__. */
#ifndef ghost_has_GHOST_SIZE_WIDTH
    #ifdef __SIZE_WIDTH__
        #define GHOST_SIZE_WIDTH __SIZE_WIDTH__
        #define ghost_has_GHOST_SIZE_WIDTH 1
    #elif defined(__SIZEOF_SIZE_T__) && defined(__CHAR_BIT__)
        #include "ghost/impl/ghost_impl_assumptions.h"
        #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
            #define GHOST_SIZE_WIDTH (__SIZEOF_SIZE_T__ * __CHAR_BIT__)
            #define ghost_has_GHOST_SIZE_WIDTH 1
        #endif
    #endif
#endif

/*
 * Without a real width, try to figure it out based on the CPU architecture.
 * This page has a lot of good info, although some of it is out of date (e.g.
 * as of this writing it doesn't have RISC-V)
 *     https://sourceforge.net/p/predef/wiki/Architectures/
 */
#ifndef ghost_has_GHOST_SIZE_WIDTH
    #include "ghost/detect/ghost_x86_32.h"
    #include "ghost/detect/ghost_x86_64.h"

    /* x86-64 (a.k.a. amd64) */
    #if GHOST_X86_64
        #define GHOST_SIZE_WIDTH 64
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* x86 32-bit (a.k.a. IA-32, a.k.a. i386) */
    #elif GHOST_X86_32
        #define GHOST_SIZE_WIDTH 32
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* x86 16-bit (a.k.a. 8086, a.k.a. i286) */
    #elif defined(_M_I86)
        #define GHOST_SIZE_WIDTH 16
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* ARM64 */
    #elif defined(__aarch64__) || defined(_M_ARM64)
        #define GHOST_SIZE_WIDTH 64
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* Itanium */
    #elif defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
        #define GHOST_SIZE_WIDTH 64
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* ARM (v7 and earlier) */
    #elif defined(__arm__) || defined(__arm) || defined(_ARM) || \
            defined(__thumb__) || defined(_M_ARM)
        #define GHOST_SIZE_WIDTH 32
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* RISC V */
    #elif defined(__riscv_xlen)
        #if __riscv_xlen == 32
            #define GHOST_SIZE_WIDTH 32
            #define ghost_has_GHOST_SIZE_WIDTH 1
        #elif __riscv_xlen == 64
            #define GHOST_SIZE_WIDTH 64
            #define ghost_has_GHOST_SIZE_WIDTH 1
        #endif
    #endif
#endif

/* Otherwise we guess based on the pointer width. Technically this can differ
 * from size width. If you have a platform where this matters, file a bug!
 *     https://sourceforge.net/p/predef/wiki/DataModels/ */
#ifndef ghost_has_GHOST_SIZE_WIDTH

    /* LP64 */
    #if defined(__LP64__) || defined(_LP64)
        #define GHOST_SIZE_WIDTH 64
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* ILP32 */
    #elif defined(__ILP32__) || defined(_ILP32)
        #define GHOST_SIZE_WIDTH 32
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* __POINTER_WIDTH__ */
    #elif defined(__POINTER_WIDTH__)
        #define GHOST_SIZE_WIDTH __POINTER_WIDTH__
        #define ghost_has_GHOST_SIZE_WIDTH 1

    /* __SIZEOF_POINTER__ */
    #elif defined(__SIZEOF_POINTER__) && defined(__CHAR_BIT__)
        #include "ghost/impl/ghost_impl_assumptions.h"
        #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
            #define GHOST_SIZE_WIDTH (__SIZEOF_POINTER__ * __CHAR_BIT__)
            #define ghost_has_GHOST_SIZE_WIDTH 1
        #endif
    #endif
#endif

/* If we don't have any of the above, we can't figure out the width. */
#ifndef ghost_has_GHOST_SIZE_WIDTH
    #define ghost_has_GHOST_SIZE_WIDTH 0
#endif

/* Ensure width is correct */
#if ghost_has(GHOST_SIZE_WIDTH)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/type/char/ghost_char_width.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        ghost_static_assert(sizeof(ghost_size_t) * GHOST_CHAR_WIDTH == GHOST_SIZE_WIDTH,
                "GHOST_SIZE_WIDTH is incorrect");
    #endif
#endif

#endif
