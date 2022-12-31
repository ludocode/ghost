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

#ifndef GHOST_FORMAT_I8_H_INCLUDED
#define GHOST_FORMAT_I8_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines printf()/scanf() format specifiers for int8_t and uint8_t.
 *
 * Note that 8-bit scan modifiers most likely won't exist in ANSI C.
 */

/**
 * @def GHOST_PRId8
 *
 * Prints a signed decimal integer of width int8_t.
 */

/**
 * @def GHOST_PRIi8
 *
 * Prints a signed decimal integer of width int8_t.
 */

/**
 * @def GHOST_PRIu8
 *
 * Prints an unsigned decimal integer of width uint8_t.
 */

/**
 * @def GHOST_PRIo8
 *
 * Prints an unsigned octal decimal integer of width uint8_t.
 */

/**
 * @def GHOST_PRIx8
 *
 * Prints an unsigned lowercase hexadecimal decimal integer of width uint8_t.
 */

/**
 * @def GHOST_PRIX8
 *
 * Prints an unsigned uppercase hexadecimal decimal integer of width uint8_t.
 */

/**
 * @def GHOST_SCNd8
 *
 * Scans a signed decimal integer of width int8_t.
 *
 * Note that 8-bit scan modifiers most likely won't exist in ANSI C (even if
 * the C99 modifiers are backported) since "hh" is not supported in ANSI C.
 */

/**
 * @def GHOST_SCNi8
 *
 * Scans a signed integer of width int8_t, auto-detecting the base from the
 * prefix.
 *
 * If the value is prefixed by 0x, it is parsed as hexadecimal; otherwise, if
 * it is prefixed by 0, it is parsed as octal; otherwise it is parsed as
 * decimal.
 *
 * Note that 8-bit scan modifiers most likely won't exist in ANSI C (even if
 * the C99 modifiers are backported) since "hh" is not supported in ANSI C.
 */

/**
 * @def GHOST_SCNu8
 *
 * Scans an unsigned decimal integer of width uint8_t.
 *
 * Note that 8-bit scan modifiers most likely won't exist in ANSI C (even if
 * the C99 modifiers are backported) since "hh" is not supported in ANSI C.
 */

/**
 * @def GHOST_SCNo8
 *
 * Scans an unsigned octal integer of width uint8_t.
 *
 * Note that 8-bit scan modifiers most likely won't exist in ANSI C (even if
 * the C99 modifiers are backported) since "hh" is not supported in ANSI C.
 */

/**
 * @def GHOST_SCNx8
 *
 * Scans an unsigned hexadecimal integer of width uint8_t.
 *
 * Note that 8-bit scan modifiers most likely won't exist in ANSI C (even if
 * the C99 modifiers are backported) since "hh" is not supported in ANSI C.
 */
#endif

/* We always try to include <inttypes.h>. */
#include "ghost/header/c/ghost_inttypes_h.h"

/* Handle overrides */
#ifndef ghost_has_GHOST_PRId8
    #ifdef GHOST_PRId8
        #define ghost_has_GHOST_PRId8 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIi8
    #ifdef GHOST_PRIi8
        #define ghost_has_GHOST_PRIi8 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIu8
    #ifdef GHOST_PRIu8
        #define ghost_has_GHOST_PRIu8 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIo8
    #ifdef GHOST_PRIo8
        #define ghost_has_GHOST_PRIo8 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIx8
    #ifdef GHOST_PRIx8
        #define ghost_has_GHOST_PRIx8 1
    #endif
#endif
#ifndef ghost_has_GHOST_PRIX8
    #ifdef GHOST_PRIX8
        #define ghost_has_GHOST_PRIX8 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNd8
    #ifdef GHOST_SCNd8
        #define ghost_has_GHOST_SCNd8 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNi8
    #ifdef GHOST_SCNi8
        #define ghost_has_GHOST_SCNi8 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNu8
    #ifdef GHOST_SCNu8
        #define ghost_has_GHOST_SCNu8 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNo8
    #ifdef GHOST_SCNo8
        #define ghost_has_GHOST_SCNo8 1
    #endif
#endif
#ifndef ghost_has_GHOST_SCNx8
    #ifdef GHOST_SCNx8
        #define ghost_has_GHOST_SCNx8 1
    #endif
#endif

/* The C99 standard PRId8 and friends may be exposed by <stdint.h> even when
 * compiling as ANSI C. On most platforms they will be "hh" but this causes
 * warnings when compiling as ANSI C. We therefore avoid using these even if
 * they are defined if we don't believe "hh" is supported. */
#include "ghost/impl/format/ghost_impl_format_c99_specifiers.h"
#if GHOST_IMPL_FORMAT_C99_SPECIFIERS
    #ifndef ghost_has_GHOST_PRId8
        #ifdef PRId8
            #define GHOST_PRId8 PRId8
            #define ghost_has_GHOST_PRId8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_PRIi8
        #ifdef PRId8
            #define GHOST_PRIi8 PRIi8
            #define ghost_has_GHOST_PRIi8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_PRIu8
        #ifdef PRId8
            #define GHOST_PRIu8 PRIu8
            #define ghost_has_GHOST_PRIu8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_PRIo8
        #ifdef PRId8
            #define GHOST_PRIo8 PRIo8
            #define ghost_has_GHOST_PRIo8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_PRIx8
        #ifdef PRIx8
            #define GHOST_PRIx8 PRIx8
            #define ghost_has_GHOST_PRIx8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_PRIX8
        #ifdef PRIX8
            #define GHOST_PRIX8 PRIX8
            #define ghost_has_GHOST_PRIX8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_SCNd8
        #ifdef SCNd8
            #define GHOST_SCNd8 SCNd8
            #define ghost_has_GHOST_SCNd8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_SCNi8
        #ifdef SCNi8
            #define GHOST_SCNi8 SCNi8
            #define ghost_has_GHOST_SCNi8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_SCNu8
        #ifdef SCNu8
            #define GHOST_SCNu8 SCNu8
            #define ghost_has_GHOST_SCNu8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_SCNo8
        #ifdef SCNo8
            #define GHOST_SCNo8 SCNo8
            #define ghost_has_GHOST_SCNo8 1
        #endif
    #endif
    #ifndef ghost_has_GHOST_SCNx8
        #ifdef SCNx8
            #define GHOST_SCNx8 SCNx8
            #define ghost_has_GHOST_SCNx8 1
        #endif
    #endif
#endif

/* Figure out modifier (if needed) */
#ifdef GHOST_IMPL_FORMAT_8_PRINT_MODIFIER
    #error "GHOST_IMPL_FORMAT_8_PRINT_MODIFIER cannot be overridden."
#endif
#ifdef GHOST_IMPL_FORMAT_8_SCAN_MODIFIER
    #error "GHOST_IMPL_FORMAT_8_SCAN_MODIFIER cannot be overridden."
#endif
#if \
        !defined(ghost_has_GHOST_PRId8) || \
        !defined(ghost_has_GHOST_PRIi8) || \
        !defined(ghost_has_GHOST_PRIu8) || \
        !defined(ghost_has_GHOST_PRIo8) || \
        !defined(ghost_has_GHOST_PRIx8) || \
        !defined(ghost_has_GHOST_PRIX8) || \
        !defined(ghost_has_GHOST_SCNd8) || \
        !defined(ghost_has_GHOST_SCNi8) || \
        !defined(ghost_has_GHOST_SCNu8) || \
        !defined(ghost_has_GHOST_SCNo8) || \
        !defined(ghost_has_GHOST_SCNx8)

    /* We need int8_t */
    #include "ghost/type/int8_t/ghost_int8_t.h"
    #if ghost_has(ghost_int8_t)
        #include "ghost/impl/format/ghost_impl_format_c99_specifiers.h"

        /* check from smallest to largest */

        /* TODO other sizes use >= for PRINT, we use == here because compilers
         * raise warnings if types don't match exactly. probably all of them
         * should use == ? */

        #if (!defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/char/ghost_char_width.h"
            #ifdef GHOST_CHAR_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) && GHOST_CHAR_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "hh"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER) && GHOST_CHAR_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "hh"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER)
            #include "ghost/type/short/ghost_short_width.h"
            #ifdef GHOST_SHORT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) && GHOST_SHORT_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "h"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER) && GHOST_SHORT_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "h"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER)
            #include "ghost/type/int/ghost_int_width.h"
            #ifdef GHOST_INT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) && GHOST_INT_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_PRINT_MODIFIER /*nothing*/
                #endif
                #if !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER) && GHOST_INT_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_SCAN_MODIFIER /*nothing*/
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER)
            #include "ghost/type/long/ghost_long_width.h"
            /* Make sure we also checked int because it won't be promoted to long */
            #if defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) && GHOST_LONG_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "l"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER) && GHOST_LONG_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "l"
                #endif
            #endif
        #endif

        #if (!defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/llong/ghost_llong_width.h"
            /* Make sure we also checked int and long because they won't be promoted to long long */
            #if defined(GHOST_LLONG_WIDTH) && defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_8_PRINT_MODIFIER) && GHOST_LLONG_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "ll"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_8_SCAN_MODIFIER) && GHOST_LLONG_WIDTH == 8
                    #define GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "ll"
                #endif
            #endif
        #endif
    #endif
#endif

/* Define with modifier if possible, otherwise we don't have it. */

/* Print */
#ifndef ghost_has_GHOST_PRId8
    #ifdef GHOST_IMPL_FORMAT_8_PRINT_MODIFIER
        #define GHOST_PRId8 GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "d"
        #define ghost_has_GHOST_PRId8 1
    #else
        #define ghost_has_GHOST_PRId8 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIi8
    #ifdef GHOST_IMPL_FORMAT_8_PRINT_MODIFIER
        #define GHOST_PRIi8 GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "i"
        #define ghost_has_GHOST_PRIi8 1
    #else
        #define ghost_has_GHOST_PRIi8 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIu8
    #ifdef GHOST_IMPL_FORMAT_8_PRINT_MODIFIER
        #define GHOST_PRIu8 GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "u"
        #define ghost_has_GHOST_PRIu8 1
    #else
        #define ghost_has_GHOST_PRIu8 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIo8
    #ifdef GHOST_IMPL_FORMAT_8_PRINT_MODIFIER
        #define GHOST_PRIo8 GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "o"
        #define ghost_has_GHOST_PRIo8 1
    #else
        #define ghost_has_GHOST_PRIo8 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIx8
    #ifdef GHOST_IMPL_FORMAT_8_PRINT_MODIFIER
        #define GHOST_PRIx8 GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "x"
        #define ghost_has_GHOST_PRIx8 1
    #else
        #define ghost_has_GHOST_PRIx8 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIX8
    #ifdef GHOST_IMPL_FORMAT_8_PRINT_MODIFIER
        #define GHOST_PRIX8 GHOST_IMPL_FORMAT_8_PRINT_MODIFIER "X"
        #define ghost_has_GHOST_PRIX8 1
    #else
        #define ghost_has_GHOST_PRIX8 0
    #endif
#endif

/* Scan */
#ifndef ghost_has_GHOST_SCNd8
    #ifdef GHOST_IMPL_FORMAT_8_SCAN_MODIFIER
        #define GHOST_SCNd8 GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "d"
        #define ghost_has_GHOST_SCNd8 1
    #else
        #define ghost_has_GHOST_SCNd8 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNi8
    #ifdef GHOST_IMPL_FORMAT_8_SCAN_MODIFIER
        #define GHOST_SCNi8 GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "i"
        #define ghost_has_GHOST_SCNi8 1
    #else
        #define ghost_has_GHOST_SCNi8 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNu8
    #ifdef GHOST_IMPL_FORMAT_8_SCAN_MODIFIER
        #define GHOST_SCNu8 GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "u"
        #define ghost_has_GHOST_SCNu8 1
    #else
        #define ghost_has_GHOST_SCNu8 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNo8
    #ifdef GHOST_IMPL_FORMAT_8_SCAN_MODIFIER
        #define GHOST_SCNo8 GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "o"
        #define ghost_has_GHOST_SCNo8 1
    #else
        #define ghost_has_GHOST_SCNo8 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNx8
    #ifdef GHOST_IMPL_FORMAT_8_SCAN_MODIFIER
        #define GHOST_SCNx8 GHOST_IMPL_FORMAT_8_SCAN_MODIFIER "x"
        #define ghost_has_GHOST_SCNx8 1
    #else
        #define ghost_has_GHOST_SCNx8 0
    #endif
#endif

#endif
