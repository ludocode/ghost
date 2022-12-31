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

#ifndef GHOST_IMPL_INTPTR_UINTPTR_H_INCLUDED
#define GHOST_IMPL_INTPTR_UINTPTR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * This internal implementation file defines the following macros:
 *
 * - ghost_has_ghost_intptr_t
 * - ghost_has_ghost_uintptr_t
 * - GHOST_INTPTR_WIDTH
 * - GHOST_UINTPTR_WIDTH
 * - GHOST_INTPTR_MAX
 * - GHOST_UINTPTR_MAX
 * - GHOST_INTPTR_MIN
 *
 * These macros are somewhat interdependent so we define them together here.
 * The macros are documented in their respective files.
 */
#endif

/* Always include standard headers so the user can use intptr_t, INTPTR_MAX and
 * friends where available.
 *     https://en.cppreference.com/w/c/types/limits */
#include "ghost/header/c/ghost_stdint_h.h"
#include "ghost/header/c/ghost_limits_h.h"

/*
 * Handle overriddes. If ghost_intptr_t is disabled, GHOST_INTPTR_WIDTH and
 * friends should be disabled as well.
 */

#ifndef ghost_has_ghost_intptr_t
    #ifdef ghost_intptr_t
        #define ghost_has_ghost_intptr_t 1
    #endif
#endif

#ifndef ghost_has_ghost_uintptr_t
    #ifdef ghost_uintptr_t
        #define ghost_has_ghost_uintptr_t 1
    #endif
#endif

#ifndef ghost_has_GHOST_INTPTR_WIDTH
    #ifdef GHOST_INTPTR_WIDTH
        #define ghost_has_GHOST_INTPTR_WIDTH 1
    #elif defined(ghost_has_ghost_intptr_t)
        #if !ghost_has_ghost_intptr_t
            #define ghost_has_GHOST_INTPTR_WIDTH 0
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_INTPTR_MAX
    #ifdef GHOST_INTPTR_MAX
        #define ghost_has_GHOST_INTPTR_MAX 1
    #elif defined(ghost_has_ghost_intptr_t)
        #if !ghost_has_ghost_intptr_t
            #define ghost_has_GHOST_INTPTR_MAX 0
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_INTPTR_MIN
    #ifdef GHOST_INTPTR_MIN
        #define ghost_has_GHOST_INTPTR_MIN 1
    #elif defined(ghost_has_ghost_intptr_t)
        #if !ghost_has_ghost_intptr_t
            #define ghost_has_GHOST_INTPTR_MIN 0
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_UINTPTR_WIDTH
    #ifdef GHOST_UINTPTR_WIDTH
        #define ghost_has_GHOST_UINTPTR_WIDTH 1
    #elif defined(ghost_has_ghost_uintptr_t)
        #if !ghost_has_ghost_uintptr_t
            #define ghost_has_GHOST_UINTPTR_WIDTH 0
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_UINTPTR_MAX
    #ifdef GHOST_UINTPTR_MAX
        #define ghost_has_GHOST_UINTPTR_MAX 1
    #elif defined(ghost_has_ghost_uintptr_t)
        #if !ghost_has_ghost_uintptr_t
            #define ghost_has_GHOST_UINTPTR_MAX 0
        #endif
    #endif
#endif

/* See if [u]intptr_t are defined. Technically they are optional in C99 so we
 * check whether [U]INTPTR_MAX is defined. */

#ifndef ghost_has_ghost_intptr_t
    #ifdef INTPTR_MAX
        typedef intptr_t ghost_intptr_t;
        #define ghost_has_ghost_intptr_t 1
    #endif
#endif
#ifndef ghost_has_ghost_uintptr_t
    #ifdef UINTPTR_MAX
        typedef uintptr_t ghost_uintptr_t;
        #define ghost_has_ghost_uintptr_t 1
    #endif
#endif

/* We also gather other constants from <stdint.h> here. [U]INTPTR_WIDTH and
 * friends might only be defined under C23. */

#ifndef ghost_has_GHOST_INTPTR_WIDTH
    #ifdef INTPTR_WIDTH
        #define GHOST_INTPTR_WIDTH INTPTR_WIDTH
        #define ghost_has_GHOST_INTPTR_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_INTPTR_MAX
    #ifdef INTPTR_MAX
        #define GHOST_INTPTR_MAX INTPTR_MAX
        #define ghost_has_GHOST_INTPTR_MAX 1
    #endif
#endif

#ifndef ghost_has_GHOST_INTPTR_MIN
    #ifdef INTPTR_MIN
        #define GHOST_INTPTR_MIN INTPTR_MIN
        #define ghost_has_GHOST_INTPTR_MIN 1
    #endif
#endif

#ifndef ghost_has_GHOST_UINTPTR_WIDTH
    #ifdef UINTPTR_WIDTH
        #define GHOST_UINTPTR_WIDTH UINTPTR_WIDTH
        #define ghost_has_GHOST_UINTPTR_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_UINTPTR_MAX
    #ifdef UINTPTR_MAX
        #define GHOST_UINTPTR_MAX UINTPTR_MAX
        #define ghost_has_GHOST_UINTPTR_MAX 1
    #endif
#endif

/* GCC has pre-defined constants for intptr_t. */

#ifndef ghost_has_ghost_intptr_t
    #ifdef __INTPTR_TYPE__
        typedef __INTPTR_TYPE__ ghost_intptr_t;
        #define ghost_has_ghost_intptr_t 1
    #endif
#endif

#ifndef ghost_has_ghost_uintptr_t
    #ifdef __UINTPTR_TYPE__
        typedef __UINTPTR_TYPE__ ghost_uintptr_t;
        #define ghost_has_ghost_uintptr_t 1
    #endif
#endif

#ifndef ghost_has_GHOST_INTPTR_WIDTH
    #ifdef __INTPTR_WIDTH__
        #define GHOST_INTPTR_WIDTH __INTPTR_WIDTH__
        #define ghost_has_GHOST_INTPTR_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_UINTPTR_WIDTH
    #ifdef __INTPTR_WIDTH__
        #define GHOST_UINTPTR_WIDTH __INTPTR_WIDTH__
        #define ghost_has_GHOST_UINTPTR_WIDTH 1
    #endif
#endif

#ifndef ghost_has_GHOST_INTPTR_MAX
    #ifdef __INTPTR_MAX__
        #define GHOST_INTPTR_MAX __INTPTR_MAX__
        #define ghost_has_GHOST_INTPTR_MAX 1
    #endif
#endif

#ifndef ghost_has_GHOST_UINTPTR_MAX
    #ifdef __UINTPTR_MAX__
        #define GHOST_UINTPTR_MAX __UINTPTR_MAX__
        #define ghost_has_GHOST_UINTPTR_MAX 1
    #endif
#endif

/* Calculate min from max (GCC doesn't tell us min) */
#ifndef ghost_has_GHOST_INTPTR_MIN
    #ifdef ghost_has_GHOST_INTPTR_MAX
        #if ghost_has_GHOST_INTPTR_MAX
            #include "ghost/impl/ghost_impl_assumptions.h"
            #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
                #define GHOST_INTPTR_MIN (-1 - GHOST_INTPTR_MAX)
                #define ghost_has_GHOST_INTPTR_MIN 1
            #endif
        #endif
    #endif
#endif

/* If we're still missing parts of intptr_t, we will have to figure it out
 * ourselves. */
#if \
        !defined(ghost_has_ghost_intptr_t) || \
        !defined(ghost_has_ghost_uintptr_t) || \
        !defined(ghost_has_GHOST_INTPTR_WIDTH) || \
        !defined(ghost_has_GHOST_UINTPTR_WIDTH) || \
        !defined(ghost_has_GHOST_INTPTR_MAX) || \
        !defined(ghost_has_GHOST_INTPTR_MIN) || \
        !defined(ghost_has_GHOST_UINTPTR_MAX) || \
        !defined(ghost_has_GHOST_INTPTR_C) || \
        !defined(ghost_has_GHOST_UINTPTR_C)

    /* We'll choose a basic type by defining one of the following macros based
     * on the platform, compiler, machine, etc. If ghost_intptr_t exists but
     * something is missing (e.g. usually GHOST_INTPTR_C), this type will have
     * to match. */
    #ifdef GHOST_IMPL_INTPTR_IS_INT
        #error
    #endif
    #ifdef GHOST_IMPL_INTPTR_IS_LONG
        #error
    #endif
    #ifdef GHOST_IMPL_INTPTR_IS_LLONG
        #error
    #endif

    /* First check platform or data model */
    #if defined(_WIN64)
        #define GHOST_IMPL_INTPTR_IS_LLONG
    #elif defined(__LP64__) || defined(_LP64) || \
            defined(__ILP32__) || defined(_ILP32) || \
            defined(_WIN32)
        #define GHOST_IMPL_INTPTR_IS_LONG
    #endif

    /* Otherwise try to detect the machine */
    #if !defined(GHOST_IMPL_INTPTR_IS_INT) && \
            !defined(GHOST_IMPL_INTPTR_IS_LONG) && \
            !defined(GHOST_IMPL_INTPTR_IS_LLONG)
        #include "ghost/detect/ghost_x86_32.h"
        #include "ghost/detect/ghost_x86_64.h"
        #if GHOST_X86_32 || GHOST_X86_64 || \
                defined(__arm__) || defined(__aarch64__) || \
                defined(__riscv) || defined(__riscv__)
            #define GHOST_IMPL_INTPTR_IS_LONG
        #endif
    #endif

    /* Otherwise we use the largest type. This is long long if we have it and long
     * otherwise. We'll statically assert that it's large enough at the bottom. */
    #if !defined(GHOST_IMPL_INTPTR_IS_INT) && \
            !defined(GHOST_IMPL_INTPTR_IS_LONG) && \
            !defined(GHOST_IMPL_INTPTR_IS_LLONG)
        #include "ghost/type/ghost_llong_all.h"
        #if ghost_has(ghost_llong)
            #define GHOST_IMPL_INTPTR_IS_LLONG
        #else
            #define GHOST_IMPL_INTPTR_IS_LONG
        #endif
    #endif

    /* Define whatever's missing using our basic type info. */

    /* int */
    #ifdef GHOST_IMPL_INTPTR_IS_INT
        #include "ghost/type/int/ghost_int_width.h"
        #include "ghost/type/ghost_uint_all.h"
        #ifndef ghost_has_ghost_intptr_t
            typedef int ghost_intptr_t;
            #define ghost_has_ghost_intptr_t 1
        #endif
        #ifndef ghost_has_ghost_uintptr_t
            typedef unsigned int ghost_uintptr_t;
            #define ghost_has_ghost_uintptr_t 1
        #endif
        #ifndef ghost_has_GHOST_INTPTR_WIDTH
            #ifdef GHOST_INT_WIDTH
                #define GHOST_INTPTR_WIDTH GHOST_INT_WIDTH
                #define ghost_has_GHOST_INTPTR_WIDTH 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_MAX
            #ifdef GHOST_INT_MAX
                #define GHOST_INTPTR_MAX GHOST_INT_MAX
                #define ghost_has_GHOST_INTPTR_MAX 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_MIN
            #ifdef GHOST_INT_MIN
                #define GHOST_INTPTR_MIN GHOST_INT_MIN
                #define ghost_has_GHOST_INTPTR_MIN 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_C
            #ifdef GHOST_INT_C
                #define GHOST_INTPTR_C GHOST_INT_C
                #define ghost_has_GHOST_INTPTR_C 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_WIDTH
            #ifdef GHOST_UINT_WIDTH
                #define GHOST_UINTPTR_WIDTH GHOST_UINT_WIDTH
                #define ghost_has_GHOST_UINTPTR_WIDTH 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_MAX
            #ifdef GHOST_UINT_MAX
                #define GHOST_UINTPTR_MAX GHOST_UINT_MAX
                #define ghost_has_GHOST_UINTPTR_MAX 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_C
            #ifdef GHOST_UINT_C
                #define GHOST_UINTPTR_C GHOST_UINT_C
                #define ghost_has_GHOST_UINTPTR_C 1
            #endif
        #endif
    #endif

    /* long */
    #ifdef GHOST_IMPL_INTPTR_IS_LONG
        #include "ghost/type/ghost_long_all.h"
        #include "ghost/type/ghost_ulong_all.h"
        #ifndef ghost_has_ghost_intptr_t
            typedef long ghost_intptr_t;
            #define ghost_has_ghost_intptr_t 1
        #endif
        #ifndef ghost_has_ghost_uintptr_t
            typedef unsigned long ghost_uintptr_t;
            #define ghost_has_ghost_uintptr_t 1
        #endif
        #ifndef ghost_has_GHOST_INTPTR_WIDTH
            #ifdef GHOST_LONG_WIDTH
                #define GHOST_INTPTR_WIDTH GHOST_LONG_WIDTH
                #define ghost_has_GHOST_INTPTR_WIDTH 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_MAX
            #ifdef GHOST_LONG_MAX
                #define GHOST_INTPTR_MAX GHOST_LONG_MAX
                #define ghost_has_GHOST_INTPTR_MAX 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_MIN
            #ifdef GHOST_LONG_MIN
                #define GHOST_INTPTR_MIN GHOST_LONG_MIN
                #define ghost_has_GHOST_INTPTR_MIN 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_C
            #ifdef GHOST_LONG_C
                #define GHOST_INTPTR_C GHOST_LONG_C
                #define ghost_has_GHOST_INTPTR_C 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_WIDTH
            #ifdef GHOST_ULONG_WIDTH
                #define GHOST_UINTPTR_WIDTH GHOST_ULONG_WIDTH
                #define ghost_has_GHOST_UINTPTR_WIDTH 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_MAX
            #ifdef GHOST_ULONG_MAX
                #define GHOST_UINTPTR_MAX GHOST_ULONG_MAX
                #define ghost_has_GHOST_UINTPTR_MAX 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_C
            #ifdef GHOST_ULONG_C
                #define GHOST_UINTPTR_C GHOST_ULONG_C
                #define ghost_has_GHOST_UINTPTR_C 1
            #endif
        #endif
    #endif

    /* long long */
    #ifdef GHOST_IMPL_INTPTR_IS_LLONG
        #include "ghost/type/ghost_llong_all.h"
        #include "ghost/type/ghost_ullong_all.h"
        #ifndef ghost_has_ghost_intptr_t
            typedef long long ghost_intptr_t;
            #define ghost_has_ghost_intptr_t 1
        #endif
        #ifndef ghost_has_ghost_uintptr_t
            typedef unsigned long long ghost_uintptr_t;
            #define ghost_has_ghost_uintptr_t 1
        #endif
        #ifndef ghost_has_GHOST_INTPTR_WIDTH
            #ifdef GHOST_LLONG_WIDTH
                #define GHOST_INTPTR_WIDTH GHOST_LLONG_WIDTH
                #define ghost_has_GHOST_INTPTR_WIDTH 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_MAX
            #ifdef GHOST_LLONG_MAX
                #define GHOST_INTPTR_MAX GHOST_LLONG_MAX
                #define ghost_has_GHOST_INTPTR_MAX 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_MIN
            #ifdef GHOST_LLONG_MIN
                #define GHOST_INTPTR_MIN GHOST_LLONG_MIN
                #define ghost_has_GHOST_INTPTR_MIN 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_INTPTR_C
            #ifdef GHOST_LLONG_C
                #define GHOST_INTPTR_C GHOST_LLONG_C
                #define ghost_has_GHOST_INTPTR_C 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_WIDTH
            #ifdef GHOST_ULLONG_WIDTH
                #define GHOST_UINTPTR_WIDTH GHOST_ULLONG_WIDTH
                #define ghost_has_GHOST_UINTPTR_WIDTH 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_MAX
            #ifdef GHOST_ULLONG_MAX
                #define GHOST_UINTPTR_MAX GHOST_ULLONG_MAX
                #define ghost_has_GHOST_UINTPTR_MAX 1
            #endif
        #endif
        #ifndef ghost_has_GHOST_UINTPTR_C
            #ifdef GHOST_ULLONG_C
                #define GHOST_UINTPTR_C GHOST_ULLONG_C
                #define ghost_has_GHOST_UINTPTR_C 1
            #endif
        #endif
    #endif
#endif

/*
 * Finally, turn off anything we haven't figured out.
 */

#ifndef ghost_has_ghost_intptr_t
    #define ghost_has_ghost_intptr_t 0
#endif
#ifndef ghost_has_GHOST_INTPTR_WIDTH
    #define ghost_has_GHOST_INTPTR_WIDTH 0
#endif
#ifndef ghost_has_GHOST_INTPTR_MAX
    #define ghost_has_GHOST_INTPTR_MAX 0
#endif
#ifndef ghost_has_GHOST_INTPTR_MIN
    #define ghost_has_GHOST_INTPTR_MIN 0
#endif
#ifndef ghost_has_GHOST_INTPTR_C
    #define ghost_has_GHOST_INTPTR_C 0
#endif
#ifndef ghost_has_ghost_uintptr_t
    #define ghost_has_ghost_uintptr_t 0
#endif
#ifndef ghost_has_GHOST_UINTPTR_WIDTH
    #define ghost_has_GHOST_UINTPTR_WIDTH 0
#endif
#ifndef ghost_has_GHOST_UINTPTR_MAX
    #define ghost_has_GHOST_UINTPTR_MAX 0
#endif
#ifndef ghost_has_GHOST_UINTPTR_C
    #define ghost_has_GHOST_UINTPTR_C 0
#endif

/*
 * Sanity checks
 */

#include "ghost/debug/ghost_static_assert.h"
#include "ghost/language/ghost_static_cast.h"
#include "ghost/type/char/ghost_char_width.h"

/* Test that it is at least as big as a pointer */
#if ghost_has_ghost_intptr_t
    ghost_static_assert(sizeof(ghost_intptr_t) >= sizeof(void*),
            "ghost_intptr_t is not large enough to store a void pointer");
    ghost_static_assert(sizeof(ghost_uintptr_t) >= sizeof(void*),
            "ghost_uintptr_t is not large enough to store a void pointer");
#endif

/*
 * Test width with sizeof
 *
 * (Technically integer types are allowed to have padding bits so this test is
 * not really correct. Still, this is more likely to catch cases of Ghost
 * incorrectly determining widths than it is to fail on platforms with
 * padding so I'd rather disable the test only on those platforms that have
 * padding.)
 */
#if ghost_has_GHOST_CHAR_WIDTH
    #if ghost_has_GHOST_INTPTR_WIDTH
        ghost_static_assert(sizeof(ghost_intptr_t) * GHOST_CHAR_WIDTH == GHOST_INTPTR_WIDTH,
                "GHOST_INTPTR_WIDTH is incorrect");
    #endif
    #if ghost_has_GHOST_UINTPTR_WIDTH
        ghost_static_assert(sizeof(ghost_uintptr_t) * GHOST_CHAR_WIDTH == GHOST_UINTPTR_WIDTH,
                "GHOST_UINTPTR_WIDTH is incorrect");
    #endif
#endif

/* Test ghost_uintptr_t max via unsigned overflow */
#if ghost_has_GHOST_UINTPTR_MAX
    #include "ghost/silence/ghost_silence_push_pop.h"
    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        #include "ghost/silence/ghost_silence_cast_truncates_constant.h"
        #include "ghost/silence/ghost_silence_constant_overflow.h"
        GHOST_SILENCE_PUSH
        GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
        GHOST_SILENCE_CONSTANT_OVERFLOW
    #endif

    ghost_static_assert(0 == ghost_static_cast(ghost_uintptr_t, GHOST_UINTPTR_MAX + 1U),
            "GHOST_UINTPTR_MAX is incorrect");

    /* Test ghost_intptr_t min/max from unsigned assuming two's complement */
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
        ghost_static_assert(GHOST_INTPTR_MAX == ghost_static_cast(ghost_intptr_t, GHOST_UINTPTR_MAX >> 1U),
                "GHOST_INTPTR_MAX is incorrect!");
        ghost_static_assert(GHOST_INTPTR_MIN == -ghost_static_cast(ghost_intptr_t, GHOST_UINTPTR_MAX >> 1U) - 1,
                "GHOST_INTPTR_MIN is incorrect!");
    #endif

    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        GHOST_SILENCE_POP
    #endif
#endif

#endif
