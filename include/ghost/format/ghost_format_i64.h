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

#ifndef GHOST_FORMAT_I64_H_INCLUDED
#define GHOST_FORMAT_I64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines printf()/scanf() format specifiers for int64_t and uint64_t.
 */

/**
 * @def GHOST_PRId64
 *
 * Prints a signed decimal integer of width int64_t.
 */

/**
 * @def GHOST_PRIi64
 *
 * Prints a signed decimal integer of width int64_t.
 */

/**
 * @def GHOST_PRIu64
 *
 * Prints an unsigned decimal integer of width uint64_t.
 */

/**
 * @def GHOST_PRIo64
 *
 * Prints an unsigned octal decimal integer of width uint64_t.
 */

/**
 * @def GHOST_PRIx64
 *
 * Prints an unsigned lowercase hexadecimal decimal integer of width uint64_t.
 */

/**
 * @def GHOST_PRIX64
 *
 * Prints an unsigned uppercase hexadecimal decimal integer of width uint64_t.
 */

/**
 * @def GHOST_SCNd64
 *
 * Scans a signed decimal integer of width int64_t.
 */

/**
 * @def GHOST_SCNi64
 *
 * Scans a signed integer of width int64_t, auto-detecting the base from the
 * prefix.
 *
 * If the value is prefixed by 0x, it is parsed as hexadecimal; otherwise, if
 * it is prefixed by 0, it is parsed as octal; otherwise it is parsed as
 * decimal.
 */

/**
 * @def GHOST_SCNu64
 *
 * Scans an unsigned decimal integer of width uint64_t.
 */

/**
 * @def GHOST_SCNo64
 *
 * Scans an unsigned octal integer of width uint64_t.
 */

/**
 * @def GHOST_SCNx64
 *
 * Scans an unsigned hexadecimal integer of width uint64_t.
 */
#endif

/* We always try to include <inttypes.h>. */
#include "ghost/header/c/ghost_inttypes_h.h"

/* Handle overrides and standard specifiers together first. */
#ifndef ghost_has_GHOST_PRId64
    #ifdef GHOST_PRId64
        #define ghost_has_GHOST_PRId64 1
    #elif defined PRId64
        #define GHOST_PRId64 PRId64
        #define ghost_has_GHOST_PRId64 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIi64
    #ifdef GHOST_PRIi64
        #define ghost_has_GHOST_PRIi64 1
    #elif defined PRId64
        #define GHOST_PRIi64 PRIi64
        #define ghost_has_GHOST_PRIi64 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIu64
    #ifdef GHOST_PRIu64
        #define ghost_has_GHOST_PRIu64 1
    #elif defined PRId64
        #define GHOST_PRIu64 PRIu64
        #define ghost_has_GHOST_PRIu64 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIo64
    #ifdef GHOST_PRIo64
        #define ghost_has_GHOST_PRIo64 1
    #elif defined PRId64
        #define GHOST_PRIo64 PRIo64
        #define ghost_has_GHOST_PRIo64 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIx64
    #ifdef GHOST_PRIx64
        #define ghost_has_GHOST_PRIx64 1
    #elif defined PRIx64
        #define GHOST_PRIx64 PRIx64
        #define ghost_has_GHOST_PRIx64 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIX64
    #ifdef GHOST_PRIX64
        #define ghost_has_GHOST_PRIX64 1
    #elif defined PRIX64
        #define GHOST_PRIX64 PRIX64
        #define ghost_has_GHOST_PRIX64 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNd64
    #ifdef GHOST_SCNd64
        #define ghost_has_GHOST_SCNd64 1
    #elif defined SCNd64
        #define GHOST_SCNd64 SCNd64
        #define ghost_has_GHOST_SCNd64 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNi64
    #ifdef GHOST_SCNi64
        #define ghost_has_GHOST_SCNi64 1
    #elif defined SCNi64
        #define GHOST_SCNi64 SCNi64
        #define ghost_has_GHOST_SCNi64 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNu64
    #ifdef GHOST_SCNu64
        #define ghost_has_GHOST_SCNu64 1
    #elif defined SCNu64
        #define GHOST_SCNu64 SCNu64
        #define ghost_has_GHOST_SCNu64 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNo64
    #ifdef GHOST_SCNo64
        #define ghost_has_GHOST_SCNo64 1
    #elif defined SCNo64
        #define GHOST_SCNo64 SCNo64
        #define ghost_has_GHOST_SCNo64 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNx64
    #ifdef GHOST_SCNx64
        #define ghost_has_GHOST_SCNx64 1
    #elif defined SCNx64
        #define GHOST_SCNx64 SCNx64
        #define ghost_has_GHOST_SCNx64 1
    #endif
#endif

/* Figure out modifier (if needed) */
#ifdef GHOST_IMPL_FORMAT_64_PRINT_MODIFIER
    #error "GHOST_IMPL_FORMAT_64_PRINT_MODIFIER cannot be overridden."
#endif
#ifdef GHOST_IMPL_FORMAT_64_SCAN_MODIFIER
    #error "GHOST_IMPL_FORMAT_64_SCAN_MODIFIER cannot be overridden."
#endif
#if \
        !defined(ghost_has_GHOST_PRId64) || \
        !defined(ghost_has_GHOST_PRIi64) || \
        !defined(ghost_has_GHOST_PRIu64) || \
        !defined(ghost_has_GHOST_PRIo64) || \
        !defined(ghost_has_GHOST_PRIx64) || \
        !defined(ghost_has_GHOST_PRIX64) || \
        !defined(ghost_has_GHOST_SCNd64) || \
        !defined(ghost_has_GHOST_SCNi64) || \
        !defined(ghost_has_GHOST_SCNu64) || \
        !defined(ghost_has_GHOST_SCNo64) || \
        !defined(ghost_has_GHOST_SCNx64)

    /* We need int64_t */
    #include "ghost/type/int64_t/ghost_int64_t.h"
    #if ghost_has(ghost_int64_t)
        #include "ghost/impl/format/ghost_impl_format_c99_specifiers.h"

        /* check from smallest to largest */

        #if (!defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/char/ghost_char_width.h"
            #ifdef GHOST_CHAR_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) && GHOST_CHAR_WIDTH >= 64
                    #define GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "hh"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER) && GHOST_CHAR_WIDTH == 64
                    #define GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "hh"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER)
            #include "ghost/type/short/ghost_short_width.h"
            #ifdef GHOST_SHORT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) && GHOST_SHORT_WIDTH >= 64
                    #define GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "h"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER) && GHOST_SHORT_WIDTH == 64
                    #define GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "h"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER)
            #include "ghost/type/int/ghost_int_width.h"
            #ifdef GHOST_INT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) && GHOST_INT_WIDTH >= 64
                    #define GHOST_IMPL_FORMAT_64_PRINT_MODIFIER /*nothing*/
                #endif
                #if !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER) && GHOST_INT_WIDTH == 64
                    #define GHOST_IMPL_FORMAT_64_SCAN_MODIFIER /*nothing*/
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER)
            #include "ghost/type/long/ghost_long_width.h"
            /* Make sure we also checked int because it won't be promoted to long */
            #if defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) && GHOST_LONG_WIDTH >= 64
                    #define GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "l"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER) && GHOST_LONG_WIDTH == 64
                    #define GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "l"
                #endif
            #endif
        #endif

        #if (!defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER)) \
                && (GHOST_IMPL_FORMAT_C99_SPECIFIERS || defined(_MSC_VER))
            #include "ghost/type/llong/ghost_llong_width.h"
            /* Make sure we also checked int and long because they won't be promoted to long long */
            #if defined(GHOST_LLONG_WIDTH) && defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_64_PRINT_MODIFIER) && GHOST_LLONG_WIDTH >= 64
                    #define GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "ll"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_64_SCAN_MODIFIER) && GHOST_LLONG_WIDTH == 64
                    #define GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "ll"
                #endif
            #endif
        #endif

        #undef GHOST_IMPL_FORMAT_64_ALLOW_HH_LL
    #endif
#endif

/* Define with modifier if possible, otherwise we don't have it. */

/* Print */
#ifndef ghost_has_GHOST_PRId64
    #ifdef GHOST_IMPL_FORMAT_64_PRINT_MODIFIER
        #define GHOST_PRId64 GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "d"
        #define ghost_has_GHOST_PRId64 1
    #else
        #define ghost_has_GHOST_PRId64 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIi64
    #ifdef GHOST_IMPL_FORMAT_64_PRINT_MODIFIER
        #define GHOST_PRIi64 GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "i"
        #define ghost_has_GHOST_PRIi64 1
    #else
        #define ghost_has_GHOST_PRIi64 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIu64
    #ifdef GHOST_IMPL_FORMAT_64_PRINT_MODIFIER
        #define GHOST_PRIu64 GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "u"
        #define ghost_has_GHOST_PRIu64 1
    #else
        #define ghost_has_GHOST_PRIu64 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIo64
    #ifdef GHOST_IMPL_FORMAT_64_PRINT_MODIFIER
        #define GHOST_PRIo64 GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "o"
        #define ghost_has_GHOST_PRIo64 1
    #else
        #define ghost_has_GHOST_PRIo64 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIx64
    #ifdef GHOST_IMPL_FORMAT_64_PRINT_MODIFIER
        #define GHOST_PRIx64 GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "x"
        #define ghost_has_GHOST_PRIx64 1
    #else
        #define ghost_has_GHOST_PRIx64 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIX64
    #ifdef GHOST_IMPL_FORMAT_64_PRINT_MODIFIER
        #define GHOST_PRIX64 GHOST_IMPL_FORMAT_64_PRINT_MODIFIER "X"
        #define ghost_has_GHOST_PRIX64 1
    #else
        #define ghost_has_GHOST_PRIX64 0
    #endif
#endif

/* Scan */
#ifndef ghost_has_GHOST_SCNd64
    #ifdef GHOST_IMPL_FORMAT_64_SCAN_MODIFIER
        #define GHOST_SCNd64 GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "d"
        #define ghost_has_GHOST_SCNd64 1
    #else
        #define ghost_has_GHOST_SCNd64 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNi64
    #ifdef GHOST_IMPL_FORMAT_64_SCAN_MODIFIER
        #define GHOST_SCNi64 GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "i"
        #define ghost_has_GHOST_SCNi64 1
    #else
        #define ghost_has_GHOST_SCNi64 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNu64
    #ifdef GHOST_IMPL_FORMAT_64_SCAN_MODIFIER
        #define GHOST_SCNu64 GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "u"
        #define ghost_has_GHOST_SCNu64 1
    #else
        #define ghost_has_GHOST_SCNu64 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNo64
    #ifdef GHOST_IMPL_FORMAT_64_SCAN_MODIFIER
        #define GHOST_SCNo64 GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "o"
        #define ghost_has_GHOST_SCNo64 1
    #else
        #define ghost_has_GHOST_SCNo64 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNx64
    #ifdef GHOST_IMPL_FORMAT_64_SCAN_MODIFIER
        #define GHOST_SCNx64 GHOST_IMPL_FORMAT_64_SCAN_MODIFIER "x"
        #define ghost_has_GHOST_SCNx64 1
    #else
        #define ghost_has_GHOST_SCNx64 0
    #endif
#endif

#endif
