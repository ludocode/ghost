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

#ifndef GHOST_FORMAT_I32_H_INCLUDED
#define GHOST_FORMAT_I32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines printf()/scanf() format specifiers for int32_t and uint32_t.
 */

/**
 * @def GHOST_PRId32
 *
 * Prints a signed decimal integer of width int32_t.
 */

/**
 * @def GHOST_PRIi32
 *
 * Prints a signed decimal integer of width int32_t.
 */

/**
 * @def GHOST_PRIu32
 *
 * Prints an unsigned decimal integer of width uint32_t.
 */

/**
 * @def GHOST_PRIo32
 *
 * Prints an unsigned octal decimal integer of width uint32_t.
 */

/**
 * @def GHOST_PRIx32
 *
 * Prints an unsigned lowercase hexadecimal decimal integer of width uint32_t.
 */

/**
 * @def GHOST_PRIX32
 *
 * Prints an unsigned uppercase hexadecimal decimal integer of width uint32_t.
 */

/**
 * @def GHOST_SCNd32
 *
 * Scans a signed decimal integer of width int32_t.
 */

/**
 * @def GHOST_SCNi32
 *
 * Scans a signed integer of width int32_t, auto-detecting the base from the
 * prefix.
 *
 * If the value is prefixed by 0x, it is parsed as hexadecimal; otherwise, if
 * it is prefixed by 0, it is parsed as octal; otherwise it is parsed as
 * decimal.
 */

/**
 * @def GHOST_SCNu32
 *
 * Scans an unsigned decimal integer of width uint32_t.
 */

/**
 * @def GHOST_SCNo32
 *
 * Scans an unsigned octal integer of width uint32_t.
 */

/**
 * @def GHOST_SCNx32
 *
 * Scans an unsigned hexadecimal integer of width uint32_t.
 */
#endif

/* We always try to include <inttypes.h>. */
#include "ghost/header/c/ghost_inttypes_h.h"

/* Handle overrides and standard specifiers together first. */
#ifndef ghost_has_GHOST_PRId32
    #ifdef GHOST_PRId32
        #define ghost_has_GHOST_PRId32 1
    #elif defined PRId32
        #define GHOST_PRId32 PRId32
        #define ghost_has_GHOST_PRId32 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIi32
    #ifdef GHOST_PRIi32
        #define ghost_has_GHOST_PRIi32 1
    #elif defined PRId32
        #define GHOST_PRIi32 PRIi32
        #define ghost_has_GHOST_PRIi32 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIu32
    #ifdef GHOST_PRIu32
        #define ghost_has_GHOST_PRIu32 1
    #elif defined PRId32
        #define GHOST_PRIu32 PRIu32
        #define ghost_has_GHOST_PRIu32 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIo32
    #ifdef GHOST_PRIo32
        #define ghost_has_GHOST_PRIo32 1
    #elif defined PRId32
        #define GHOST_PRIo32 PRIo32
        #define ghost_has_GHOST_PRIo32 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIx32
    #ifdef GHOST_PRIx32
        #define ghost_has_GHOST_PRIx32 1
    #elif defined PRIx32
        #define GHOST_PRIx32 PRIx32
        #define ghost_has_GHOST_PRIx32 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIX32
    #ifdef GHOST_PRIX32
        #define ghost_has_GHOST_PRIX32 1
    #elif defined PRIX32
        #define GHOST_PRIX32 PRIX32
        #define ghost_has_GHOST_PRIX32 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNd32
    #ifdef GHOST_SCNd32
        #define ghost_has_GHOST_SCNd32 1
    #elif defined SCNd32
        #define GHOST_SCNd32 SCNd32
        #define ghost_has_GHOST_SCNd32 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNi32
    #ifdef GHOST_SCNi32
        #define ghost_has_GHOST_SCNi32 1
    #elif defined SCNi32
        #define GHOST_SCNi32 SCNi32
        #define ghost_has_GHOST_SCNi32 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNu32
    #ifdef GHOST_SCNu32
        #define ghost_has_GHOST_SCNu32 1
    #elif defined SCNu32
        #define GHOST_SCNu32 SCNu32
        #define ghost_has_GHOST_SCNu32 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNo32
    #ifdef GHOST_SCNo32
        #define ghost_has_GHOST_SCNo32 1
    #elif defined SCNo32
        #define GHOST_SCNo32 SCNo32
        #define ghost_has_GHOST_SCNo32 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNx32
    #ifdef GHOST_SCNx32
        #define ghost_has_GHOST_SCNx32 1
    #elif defined SCNx32
        #define GHOST_SCNx32 SCNx32
        #define ghost_has_GHOST_SCNx32 1
    #endif
#endif

/* Figure out modifier (if needed) */
#ifdef GHOST_IMPL_FORMAT_32_PRINT_MODIFIER
    #error "GHOST_IMPL_FORMAT_32_PRINT_MODIFIER cannot be overridden."
#endif
#ifdef GHOST_IMPL_FORMAT_32_SCAN_MODIFIER
    #error "GHOST_IMPL_FORMAT_32_SCAN_MODIFIER cannot be overridden."
#endif
#if \
        !defined(ghost_has_GHOST_PRId32) || \
        !defined(ghost_has_GHOST_PRIi32) || \
        !defined(ghost_has_GHOST_PRIu32) || \
        !defined(ghost_has_GHOST_PRIo32) || \
        !defined(ghost_has_GHOST_PRIx32) || \
        !defined(ghost_has_GHOST_PRIX32) || \
        !defined(ghost_has_GHOST_SCNd32) || \
        !defined(ghost_has_GHOST_SCNi32) || \
        !defined(ghost_has_GHOST_SCNu32) || \
        !defined(ghost_has_GHOST_SCNo32) || \
        !defined(ghost_has_GHOST_SCNx32)

    /* We need int32_t */
    #include "ghost/type/int32_t/ghost_int32_t.h"
    #if ghost_has(ghost_int32_t)
        #include "ghost/impl/format/ghost_impl_format_c99_specifiers.h"

        /* check from smallest to largest */

        #if (!defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/char/ghost_char_width.h"
            #ifdef GHOST_CHAR_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) && GHOST_CHAR_WIDTH >= 32
                    #define GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "hh"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER) && GHOST_CHAR_WIDTH == 32
                    #define GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "hh"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER)
            #include "ghost/type/short/ghost_short_width.h"
            #ifdef GHOST_SHORT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) && GHOST_SHORT_WIDTH >= 32
                    #define GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "h"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER) && GHOST_SHORT_WIDTH == 32
                    #define GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "h"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER)
            #include "ghost/type/int/ghost_int_width.h"
            #ifdef GHOST_INT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) && GHOST_INT_WIDTH >= 32
                    #define GHOST_IMPL_FORMAT_32_PRINT_MODIFIER /*nothing*/
                #endif
                #if !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER) && GHOST_INT_WIDTH == 32
                    #define GHOST_IMPL_FORMAT_32_SCAN_MODIFIER /*nothing*/
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER)
            #include "ghost/type/long/ghost_long_width.h"
            /* Make sure we also checked int because it won't be promoted to long */
            #if defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) && GHOST_LONG_WIDTH >= 32
                    #define GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "l"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER) && GHOST_LONG_WIDTH == 32
                    #define GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "l"
                #endif
            #endif
        #endif

        #if (!defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/llong/ghost_llong_width.h"
            /* Make sure we also checked int and long because they won't be promoted to long long */
            #if defined(GHOST_LLONG_WIDTH) && defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_32_PRINT_MODIFIER) && GHOST_LLONG_WIDTH >= 32
                    #define GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "ll"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_32_SCAN_MODIFIER) && GHOST_LLONG_WIDTH == 32
                    #define GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "ll"
                #endif
            #endif
        #endif

        #undef GHOST_IMPL_FORMAT_32_ALLOW_HH_LL
    #endif
#endif

/* Define with modifier if possible, otherwise we don't have it. */

/* Print */
#ifndef ghost_has_GHOST_PRId32
    #ifdef GHOST_IMPL_FORMAT_32_PRINT_MODIFIER
        #define GHOST_PRId32 GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "d"
        #define ghost_has_GHOST_PRId32 1
    #else
        #define ghost_has_GHOST_PRId32 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIi32
    #ifdef GHOST_IMPL_FORMAT_32_PRINT_MODIFIER
        #define GHOST_PRIi32 GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "i"
        #define ghost_has_GHOST_PRIi32 1
    #else
        #define ghost_has_GHOST_PRIi32 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIu32
    #ifdef GHOST_IMPL_FORMAT_32_PRINT_MODIFIER
        #define GHOST_PRIu32 GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "u"
        #define ghost_has_GHOST_PRIu32 1
    #else
        #define ghost_has_GHOST_PRIu32 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIo32
    #ifdef GHOST_IMPL_FORMAT_32_PRINT_MODIFIER
        #define GHOST_PRIo32 GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "o"
        #define ghost_has_GHOST_PRIo32 1
    #else
        #define ghost_has_GHOST_PRIo32 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIx32
    #ifdef GHOST_IMPL_FORMAT_32_PRINT_MODIFIER
        #define GHOST_PRIx32 GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "x"
        #define ghost_has_GHOST_PRIx32 1
    #else
        #define ghost_has_GHOST_PRIx32 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIX32
    #ifdef GHOST_IMPL_FORMAT_32_PRINT_MODIFIER
        #define GHOST_PRIX32 GHOST_IMPL_FORMAT_32_PRINT_MODIFIER "X"
        #define ghost_has_GHOST_PRIX32 1
    #else
        #define ghost_has_GHOST_PRIX32 0
    #endif
#endif

/* Scan */
#ifndef ghost_has_GHOST_SCNd32
    #ifdef GHOST_IMPL_FORMAT_32_SCAN_MODIFIER
        #define GHOST_SCNd32 GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "d"
        #define ghost_has_GHOST_SCNd32 1
    #else
        #define ghost_has_GHOST_SCNd32 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNi32
    #ifdef GHOST_IMPL_FORMAT_32_SCAN_MODIFIER
        #define GHOST_SCNi32 GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "i"
        #define ghost_has_GHOST_SCNi32 1
    #else
        #define ghost_has_GHOST_SCNi32 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNu32
    #ifdef GHOST_IMPL_FORMAT_32_SCAN_MODIFIER
        #define GHOST_SCNu32 GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "u"
        #define ghost_has_GHOST_SCNu32 1
    #else
        #define ghost_has_GHOST_SCNu32 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNo32
    #ifdef GHOST_IMPL_FORMAT_32_SCAN_MODIFIER
        #define GHOST_SCNo32 GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "o"
        #define ghost_has_GHOST_SCNo32 1
    #else
        #define ghost_has_GHOST_SCNo32 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNx32
    #ifdef GHOST_IMPL_FORMAT_32_SCAN_MODIFIER
        #define GHOST_SCNx32 GHOST_IMPL_FORMAT_32_SCAN_MODIFIER "x"
        #define ghost_has_GHOST_SCNx32 1
    #else
        #define ghost_has_GHOST_SCNx32 0
    #endif
#endif

#endif
