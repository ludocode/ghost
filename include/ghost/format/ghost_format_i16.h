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

#ifndef GHOST_FORMAT_I16_H_INCLUDED
#define GHOST_FORMAT_I16_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines printf()/scanf() format specifiers for int16_t and uint16_t.
 */

/**
 * @def GHOST_PRId16
 *
 * Prints a signed decimal integer of width int16_t.
 */

/**
 * @def GHOST_PRIi16
 *
 * Prints a signed decimal integer of width int16_t.
 */

/**
 * @def GHOST_PRIu16
 *
 * Prints an unsigned decimal integer of width uint16_t.
 */

/**
 * @def GHOST_PRIo16
 *
 * Prints an unsigned octal decimal integer of width uint16_t.
 */

/**
 * @def GHOST_PRIx16
 *
 * Prints an unsigned lowercase hexadecimal decimal integer of width uint16_t.
 */

/**
 * @def GHOST_PRIX16
 *
 * Prints an unsigned uppercase hexadecimal decimal integer of width uint16_t.
 */

/**
 * @def GHOST_SCNd16
 *
 * Scans a signed decimal integer of width int16_t.
 */

/**
 * @def GHOST_SCNi16
 *
 * Scans a signed integer of width int16_t, auto-detecting the base from the
 * prefix.
 *
 * If the value is prefixed by 0x, it is parsed as hexadecimal; otherwise, if
 * it is prefixed by 0, it is parsed as octal; otherwise it is parsed as
 * decimal.
 */

/**
 * @def GHOST_SCNu16
 *
 * Scans an unsigned decimal integer of width uint16_t.
 */

/**
 * @def GHOST_SCNo16
 *
 * Scans an unsigned octal integer of width uint16_t.
 */

/**
 * @def GHOST_SCNx16
 *
 * Scans an unsigned hexadecimal integer of width uint16_t.
 */
#endif

/* We always try to include <inttypes.h>. */
#include "ghost/header/c/ghost_inttypes_h.h"

/* Handle overrides and standard specifiers together first. */
#ifndef ghost_has_GHOST_PRId16
    #ifdef GHOST_PRId16
        #define ghost_has_GHOST_PRId16 1
    #elif defined PRId16
        #define GHOST_PRId16 PRId16
        #define ghost_has_GHOST_PRId16 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIi16
    #ifdef GHOST_PRIi16
        #define ghost_has_GHOST_PRIi16 1
    #elif defined PRId16
        #define GHOST_PRIi16 PRIi16
        #define ghost_has_GHOST_PRIi16 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIu16
    #ifdef GHOST_PRIu16
        #define ghost_has_GHOST_PRIu16 1
    #elif defined PRId16
        #define GHOST_PRIu16 PRIu16
        #define ghost_has_GHOST_PRIu16 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIo16
    #ifdef GHOST_PRIo16
        #define ghost_has_GHOST_PRIo16 1
    #elif defined PRId16
        #define GHOST_PRIo16 PRIo16
        #define ghost_has_GHOST_PRIo16 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIx16
    #ifdef GHOST_PRIx16
        #define ghost_has_GHOST_PRIx16 1
    #elif defined PRIx16
        #define GHOST_PRIx16 PRIx16
        #define ghost_has_GHOST_PRIx16 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIX16
    #ifdef GHOST_PRIX16
        #define ghost_has_GHOST_PRIX16 1
    #elif defined PRIX16
        #define GHOST_PRIX16 PRIX16
        #define ghost_has_GHOST_PRIX16 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNd16
    #ifdef GHOST_SCNd16
        #define ghost_has_GHOST_SCNd16 1
    #elif defined SCNd16
        #define GHOST_SCNd16 SCNd16
        #define ghost_has_GHOST_SCNd16 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNi16
    #ifdef GHOST_SCNi16
        #define ghost_has_GHOST_SCNi16 1
    #elif defined SCNi16
        #define GHOST_SCNi16 SCNi16
        #define ghost_has_GHOST_SCNi16 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNu16
    #ifdef GHOST_SCNu16
        #define ghost_has_GHOST_SCNu16 1
    #elif defined SCNu16
        #define GHOST_SCNu16 SCNu16
        #define ghost_has_GHOST_SCNu16 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNo16
    #ifdef GHOST_SCNo16
        #define ghost_has_GHOST_SCNo16 1
    #elif defined SCNo16
        #define GHOST_SCNo16 SCNo16
        #define ghost_has_GHOST_SCNo16 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNx16
    #ifdef GHOST_SCNx16
        #define ghost_has_GHOST_SCNx16 1
    #elif defined SCNx16
        #define GHOST_SCNx16 SCNx16
        #define ghost_has_GHOST_SCNx16 1
    #endif
#endif

/* Figure out modifier (if needed) */
#ifdef GHOST_IMPL_FORMAT_16_PRINT_MODIFIER
    #error "GHOST_IMPL_FORMAT_16_PRINT_MODIFIER cannot be overridden."
#endif
#ifdef GHOST_IMPL_FORMAT_16_SCAN_MODIFIER
    #error "GHOST_IMPL_FORMAT_16_SCAN_MODIFIER cannot be overridden."
#endif
#if \
        !defined(ghost_has_GHOST_PRId16) || \
        !defined(ghost_has_GHOST_PRIi16) || \
        !defined(ghost_has_GHOST_PRIu16) || \
        !defined(ghost_has_GHOST_PRIo16) || \
        !defined(ghost_has_GHOST_PRIx16) || \
        !defined(ghost_has_GHOST_PRIX16) || \
        !defined(ghost_has_GHOST_SCNd16) || \
        !defined(ghost_has_GHOST_SCNi16) || \
        !defined(ghost_has_GHOST_SCNu16) || \
        !defined(ghost_has_GHOST_SCNo16) || \
        !defined(ghost_has_GHOST_SCNx16)

    /* We need int16_t */
    #include "ghost/type/int16_t/ghost_int16_t.h"
    #if ghost_has(ghost_int16_t)
        #include "ghost/impl/format/ghost_impl_format_c99_specifiers.h"

        /* check from smallest to largest */

        #if (!defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/char/ghost_char_width.h"
            #ifdef GHOST_CHAR_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) && GHOST_CHAR_WIDTH >= 16
                    #define GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "hh"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER) && GHOST_CHAR_WIDTH == 16
                    #define GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "hh"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER)
            #include "ghost/type/short/ghost_short_width.h"
            #ifdef GHOST_SHORT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) && GHOST_SHORT_WIDTH >= 16
                    #define GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "h"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER) && GHOST_SHORT_WIDTH == 16
                    #define GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "h"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER)
            #include "ghost/type/int/ghost_int_width.h"
            #ifdef GHOST_INT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) && GHOST_INT_WIDTH >= 16
                    #define GHOST_IMPL_FORMAT_16_PRINT_MODIFIER /*nothing*/
                #endif
                #if !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER) && GHOST_INT_WIDTH == 16
                    #define GHOST_IMPL_FORMAT_16_SCAN_MODIFIER /*nothing*/
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER)
            #include "ghost/type/long/ghost_long_width.h"
            /* Make sure we also checked int because it won't be promoted to long */
            #if defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) && GHOST_LONG_WIDTH >= 16
                    #define GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "l"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER) && GHOST_LONG_WIDTH == 16
                    #define GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "l"
                #endif
            #endif
        #endif

        #if (!defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/llong/ghost_llong_width.h"
            /* Make sure we also checked int and long because they won't be promoted to long long */
            #if defined(GHOST_LLONG_WIDTH) && defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_16_PRINT_MODIFIER) && GHOST_LLONG_WIDTH >= 16
                    #define GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "ll"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_16_SCAN_MODIFIER) && GHOST_LLONG_WIDTH == 16
                    #define GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "ll"
                #endif
            #endif
        #endif

        #undef GHOST_IMPL_FORMAT_16_ALLOW_HH_LL
    #endif
#endif

/* Define with modifier if possible, otherwise we don't have it. */

/* Print */
#ifndef ghost_has_GHOST_PRId16
    #ifdef GHOST_IMPL_FORMAT_16_PRINT_MODIFIER
        #define GHOST_PRId16 GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "d"
        #define ghost_has_GHOST_PRId16 1
    #else
        #define ghost_has_GHOST_PRId16 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIi16
    #ifdef GHOST_IMPL_FORMAT_16_PRINT_MODIFIER
        #define GHOST_PRIi16 GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "i"
        #define ghost_has_GHOST_PRIi16 1
    #else
        #define ghost_has_GHOST_PRIi16 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIu16
    #ifdef GHOST_IMPL_FORMAT_16_PRINT_MODIFIER
        #define GHOST_PRIu16 GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "u"
        #define ghost_has_GHOST_PRIu16 1
    #else
        #define ghost_has_GHOST_PRIu16 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIo16
    #ifdef GHOST_IMPL_FORMAT_16_PRINT_MODIFIER
        #define GHOST_PRIo16 GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "o"
        #define ghost_has_GHOST_PRIo16 1
    #else
        #define ghost_has_GHOST_PRIo16 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIx16
    #ifdef GHOST_IMPL_FORMAT_16_PRINT_MODIFIER
        #define GHOST_PRIx16 GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "x"
        #define ghost_has_GHOST_PRIx16 1
    #else
        #define ghost_has_GHOST_PRIx16 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIX16
    #ifdef GHOST_IMPL_FORMAT_16_PRINT_MODIFIER
        #define GHOST_PRIX16 GHOST_IMPL_FORMAT_16_PRINT_MODIFIER "X"
        #define ghost_has_GHOST_PRIX16 1
    #else
        #define ghost_has_GHOST_PRIX16 0
    #endif
#endif

/* Scan */
#ifndef ghost_has_GHOST_SCNd16
    #ifdef GHOST_IMPL_FORMAT_16_SCAN_MODIFIER
        #define GHOST_SCNd16 GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "d"
        #define ghost_has_GHOST_SCNd16 1
    #else
        #define ghost_has_GHOST_SCNd16 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNi16
    #ifdef GHOST_IMPL_FORMAT_16_SCAN_MODIFIER
        #define GHOST_SCNi16 GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "i"
        #define ghost_has_GHOST_SCNi16 1
    #else
        #define ghost_has_GHOST_SCNi16 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNu16
    #ifdef GHOST_IMPL_FORMAT_16_SCAN_MODIFIER
        #define GHOST_SCNu16 GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "u"
        #define ghost_has_GHOST_SCNu16 1
    #else
        #define ghost_has_GHOST_SCNu16 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNo16
    #ifdef GHOST_IMPL_FORMAT_16_SCAN_MODIFIER
        #define GHOST_SCNo16 GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "o"
        #define ghost_has_GHOST_SCNo16 1
    #else
        #define ghost_has_GHOST_SCNo16 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNx16
    #ifdef GHOST_IMPL_FORMAT_16_SCAN_MODIFIER
        #define GHOST_SCNx16 GHOST_IMPL_FORMAT_16_SCAN_MODIFIER "x"
        #define ghost_has_GHOST_SCNx16 1
    #else
        #define ghost_has_GHOST_SCNx16 0
    #endif
#endif

#endif
