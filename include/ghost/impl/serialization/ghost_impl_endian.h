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

#ifndef GHOST_IMPL_ENDIAN_H_INCLUDED
#define GHOST_IMPL_ENDIAN_H_INCLUDED

#include "ghost/ghost_core.h"

/*
 * This header tries to detect endianness. Ghost defines the
 * following macros for endianness:
 *
 * - GHOST_LITTLE_ENDIAN
 * - GHOST_BIG_ENDIAN
 *
 * For each macro: If the macro is 1, the machine definitely has that
 * endianness; if the macro is 0, the machine may or may not have that
 * endianness, but we could not determine for certain that it does. At most one
 * of these macros will be 1 and the others will be 0.
 *
 * As usual you can define any of these macros to 0 or 1 before including this
 * to override detection.
 *
 * Ghost doesn't currently detect older word-swapped endian modes; only
 * byte-swapped endian modes are detect. Ghost also doesn't support changing
 * the CPU endianness at runtime.
 *
 * If Ghost can't determine the endianness or the endian mode is unsupported,
 * Ghost falls back to endian-independent code. You can pre-define both
 * GHOST_LITTLE_ENDIAN and GHOST_BIG_ENDIAN to 0 if you want to force Ghost to
 * use endian-independent code.
 */

/* GHOST_BIG_ENDIAN and GHOST_LITTLE_ENDIAN must be preprocessor constants. We
 * don't allow predefining ghost_has for them. */
#ifdef ghost_has_GHOST_BIG_ENDIAN
    #error "Don't define ghost_has_GHOST_BIG_ENDIAN; only define GHOST_BIG_ENDIAN."
#endif
#ifdef ghost_has_GHOST_LITTLE_ENDIAN
    #error "Don't define ghost_has_GHOST_LITTLE_ENDIAN; only define GHOST_LITTLE_ENDIAN."
#endif

/* We allow either GHOST_BIG_ENDIAN or GHOST_LITTLE_ENDIAN to be pre-defined to
 * 1 to override Ghost's detection. If either is on, turn the other off to
 * inhibit further detection. */
#if defined(GHOST_LITTLE_ENDIAN) && !defined(GHOST_BIG_ENDIAN)
    #if GHOST_LITTLE_ENDIAN
        #define GHOST_BIG_ENDIAN 0
    #endif
#endif
#if defined(GHOST_BIG_ENDIAN) && !defined(GHOST_LITTLE_ENDIAN)
    #if GHOST_BIG_ENDIAN
        #define GHOST_LITTLE_ENDIAN 0
    #endif
#endif

/* Windows */
#ifdef _WIN32
    /*
     * MSVC documentation says Windows is always little-endian even on ARM.
     *
     *     https://docs.microsoft.com/en-us/cpp/build/overview-of-arm-abi-conventions
     *
     * We check for the current supported architectures of Windows so as not to
     * make assumptions about future CPUs.
     */
    #if defined(_M_IX86) || defined(_M_X64) || defined(_M_AMD64)
        #ifndef GHOST_LITTLE_ENDIAN
            #define GHOST_LITTLE_ENDIAN 1
        #endif
        #ifndef GHOST_BIG_ENDIAN
            #define GHOST_BIG_ENDIAN 0
        #endif
    #endif
#endif

/* GCC-style byte ordering macros */
#ifdef __BYTE_ORDER__
    #ifdef __ORDER_LITTLE_ENDIAN__
        #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            #ifndef GHOST_LITTLE_ENDIAN
                #define GHOST_LITTLE_ENDIAN 1
            #endif
            #ifndef GHOST_BIG_ENDIAN
                #define GHOST_BIG_ENDIAN 0
            #endif
        #endif
    #endif
    #ifdef __ORDER_BIG_ENDIAN__
        #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
            #ifndef GHOST_BIG_ENDIAN
                #define GHOST_BIG_ENDIAN 1
            #endif
            #ifndef GHOST_LITTLE_ENDIAN
                #define GHOST_LITTLE_ENDIAN 0
            #endif
        #endif
    #endif
#endif

/*
 * glibc-style byte ordering macros
 *
 * We wrap these under __GLIBC__ because some other platform might choose to
 * define __BIG_ENDIAN to blank for example. Without knowing the platform we
 * can't rely on it. (The same is technically true for the GCC macros above but
 * those are a bit more widely supported so it's less likely that they will be
 * defined differently than we expect.)
 */
#include "ghost/header/linux/ghost_features_h.h"
#if defined(__GLIBC__) && defined(__BYTE_ORDER)
    #ifdef __LITTLE_ENDIAN
        #if __BYTE_ORDER == __LITTLE_ENDIAN
            #ifndef GHOST_LITTLE_ENDIAN
                #define GHOST_LITTLE_ENDIAN 1
            #endif
            #ifndef GHOST_BIG_ENDIAN
                #define GHOST_BIG_ENDIAN 0
            #endif
        #endif
    #endif
    #ifdef __BIG_ENDIAN
        #if __BYTE_ORDER == __BIG_ENDIAN
            #ifndef GHOST_BIG_ENDIAN
                #define GHOST_BIG_ENDIAN 1
            #endif
            #ifndef GHOST_LITTLE_ENDIAN
                #define GHOST_LITTLE_ENDIAN 0
            #endif
        #endif
    #endif
#endif

/* Generic macros. We check that only one of little or big is defined. If both
 * are defined it's probably because it uses some scheme like GCC and glibc
 * above. */
#if (defined(__LITTLE_ENDIAN__) || defined(__LITTLEENDIAN__)) && \
        !defined(__BIG_ENDIAN__) && !defined(__BIGENDIAN__)
    #ifndef GHOST_LITTLE_ENDIAN
        #define GHOST_LITTLE_ENDIAN 1
    #endif
    #ifndef GHOST_BIG_ENDIAN
        #define GHOST_BIG_ENDIAN 0
    #endif
#endif
#if (defined(__BIG_ENDIAN__) || defined(__BIGENDIAN__)) && \
        !defined(__LITTLE_ENDIAN__) && !defined(__LITTLEENDIAN__)
    #ifndef GHOST_BIG_ENDIAN
        #define GHOST_BIG_ENDIAN 1
    #endif
    #ifndef GHOST_LITTLE_ENDIAN
        #define GHOST_LITTLE_ENDIAN 0
    #endif
#endif

/* Machine-specific macros */
#include "ghost/detect/ghost_x86_32.h"
#include "ghost/detect/ghost_x86_64.h"
#if GHOST_X86_32 || GHOST_X86_64 || \
        defined(__ARMEL__) || defined(__THUMBEL__) || defined(__AARCH64EL__) || \
        defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
    #ifndef GHOST_LITTLE_ENDIAN
        #define GHOST_LITTLE_ENDIAN 1
    #endif
    #ifndef GHOST_BIG_ENDIAN
        #define GHOST_BIG_ENDIAN 0
    #endif
#endif
#if defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || \
        defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__)
    #ifndef GHOST_BIG_ENDIAN
        #define GHOST_BIG_ENDIAN 1
    #endif
    #ifndef GHOST_LITTLE_ENDIAN
        #define GHOST_LITTLE_ENDIAN 0
    #endif
#endif

/* Turn off anything we haven't detected */
#ifndef GHOST_LITTLE_ENDIAN
    #define GHOST_LITTLE_ENDIAN 0
#endif
#ifndef GHOST_BIG_ENDIAN
    #define GHOST_BIG_ENDIAN 0
#endif

/* Make sure at most one is on */
#if GHOST_BIG_ENDIAN && GHOST_LITTLE_ENDIAN
    #error "Only one of GHOST_LITTLE_ENDIAN and GHOST_BIG_ENDIAN can be 1."
#endif

#define ghost_has_GHOST_BIG_ENDIAN 1
#define ghost_has_GHOST_LITTLE_ENDIAN 1

#endif
