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

#ifndef GHOST_FORMAT_PD_H_INCLUDED
#define GHOST_FORMAT_PD_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines printf()/scanf() format specifiers for ptrdiff_t.
 *
 * There is no standard format length modifier for printing ptrdiff_t so Ghost
 * provides this abstraction.
 *
 * In cases where size_t is the same width and "z" is supported, this will be
 * "z", otherwise it will try to find an appropriate length modifier. If you
 * don't care about any other platforms, you can always simply ignore this and
 * use "z".
 *
 * These are non-standard but they are in the style of C99 fixed-width format
 * specifiers like PRIi64, SCNx16, etc.
 *
 * For size_t, see ghost_format_z.h. For intptr_t and uintptr_t, see
 * ghost_format_ip.h.
 */

/**
 * @def GHOST_PRIdPD
 *
 * Prints a signed decimal integer of a type matching ssize_t.
 */

/**
 * @def GHOST_PRIiPD
 *
 * Prints a signed decimal integer of a type matching ssize_t.
 */

/**
 * @def GHOST_PRIuPD
 *
 * Prints an unsigned decimal integer of a type matching size_t.
 */

/**
 * @def GHOST_PRIoPD
 *
 * Prints an unsigned octal integer of a type matching size_t.
 */

/**
 * @def GHOST_PRIxPD
 *
 * Prints an unsigned lowercase hexadecimal integer of a type matching size_t.
 */

/**
 * @def GHOST_PRIXPD
 *
 * Prints an unsigned uppercase hexadecimal integer of a type matching size_t.
 */

/**
 * @def GHOST_SCNdPD
 *
 * Scans a signed decimal integer into a type matching ssize_t.
 */

/**
 * @def GHOST_SCNiPD
 *
 * Scans a signed integer into a type matching ssize_t, auto-detecting the base
 * from the prefix.
 *
 * If the value is prefixed by 0x, it is parsed as hexadecimal; otherwise, if
 * it is prefixed by 0, it is parsed as octal; otherwise it is parsed as
 * decimal.
 */

/**
 * @def GHOST_SCNuPD
 *
 * Scans an unsigned decimal integer into a type matching size_t.
 */

/**
 * @def GHOST_SCNoPD
 *
 * Scans an unsigned octal integer into a type matching size_t.
 */

/**
 * @def GHOST_SCNxPD
 *
 * Scans an unsigned hexadecimal integer into a type matching size_t.
 */
#endif

#ifdef GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER
    #error "GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER cannot be overridden."
#endif
#ifdef GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER
    #error "GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER cannot be overridden."
#endif

/* If ptrdiff_t is the same width as size_t, we can use the format modifier for
 * size_t. This might be "z" which is ideal for modern C. */
#include "ghost/type/ptrdiff_t/ghost_ptrdiff_width.h"
#include "ghost/type/size_t/ghost_size_width.h"
#if defined(GHOST_PTRDIFF_WIDTH) && defined(GHOST_SIZE_WIDTH)
    #if GHOST_PTRDIFF_WIDTH == GHOST_SIZE_WIDTH
        #include "ghost/format/ghost_format_z.h"
        #ifdef GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER
            #define GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER
        #endif
        #ifdef GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER
            #define GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER
        #endif
    #endif
#endif

/* Otherwise we need to detect a matching basic type of ptrdiff_t. */
#if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
    #ifdef GHOST_PTRDIFF_WIDTH
        #include "ghost/impl/format/ghost_impl_format_c99_specifiers.h"

        /* check from smallest to largest */

        #if (!defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/char/ghost_char_width.h"
            #ifdef GHOST_CHAR_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) && GHOST_CHAR_WIDTH >= GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "hh"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER) && GHOST_CHAR_WIDTH == GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "hh"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
            #include "ghost/type/short/ghost_short_width.h"
            #ifdef GHOST_SHORT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) && GHOST_SHORT_WIDTH >= GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "h"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER) && GHOST_SHORT_WIDTH == GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "h"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
            #include "ghost/type/int/ghost_int_width.h"
            #ifdef GHOST_INT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) && GHOST_INT_WIDTH >= GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER /*nothing*/
                #endif
                #if !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER) && GHOST_INT_WIDTH == GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER /*nothing*/
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
            #include "ghost/type/long/ghost_long_width.h"
            /* Make sure we also checked int because it won't be promoted to long */
            #if defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) && GHOST_LONG_WIDTH >= GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "l"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER) && GHOST_LONG_WIDTH == GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "l"
                #endif
            #endif
        #endif

        #if (!defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/llong/ghost_llong_width.h"
            /* Make sure we also checked int and long because they won't be promoted to long long */
            #if defined(GHOST_LLONG_WIDTH) && defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER) && GHOST_LLONG_WIDTH >= GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "ll"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER) && GHOST_LLONG_WIDTH == GHOST_PTRDIFF_WIDTH
                    #define GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "ll"
                #endif
            #endif
        #endif

        #undef GHOST_IMPL_FORMAT_PD_ALLOW_HH_LL
    #endif
#endif

/* Handle override, define with modifier if possible, otherwise we don't have
 * it. */

/* Print */
#ifndef ghost_has_GHOST_PRIdPD
    #ifdef GHOST_PRIdPD
        #define ghost_has_GHOST_PRIdPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER)
        #define GHOST_PRIdPD GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "d"
        #define ghost_has_GHOST_PRIdPD 1
    #else
        #define ghost_has_GHOST_PRIdPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIiPD
    #ifdef GHOST_PRIiPD
        #define ghost_has_GHOST_PRIiPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER)
        #define GHOST_PRIiPD GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "i"
        #define ghost_has_GHOST_PRIiPD 1
    #else
        #define ghost_has_GHOST_PRIiPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIuPD
    #ifdef GHOST_PRIuPD
        #define ghost_has_GHOST_PRIuPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER)
        #define GHOST_PRIuPD GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "u"
        #define ghost_has_GHOST_PRIuPD 1
    #else
        #define ghost_has_GHOST_PRIuPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIoPD
    #ifdef GHOST_PRIoPD
        #define ghost_has_GHOST_PRIoPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER)
        #define GHOST_PRIoPD GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "o"
        #define ghost_has_GHOST_PRIoPD 1
    #else
        #define ghost_has_GHOST_PRIoPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIxPD
    #ifdef GHOST_PRIxPD
        #define ghost_has_GHOST_PRIxPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER)
        #define GHOST_PRIxPD GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "x"
        #define ghost_has_GHOST_PRIxPD 1
    #else
        #define ghost_has_GHOST_PRIxPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIXPD
    #ifdef GHOST_PRIXPD
        #define ghost_has_GHOST_PRIXPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER)
        #define GHOST_PRIXPD GHOST_IMPL_FORMAT_PD_PRINT_MODIFIER "X"
        #define ghost_has_GHOST_PRIXPD 1
    #else
        #define ghost_has_GHOST_PRIXPD 0
    #endif
#endif

/* Scan */
#ifndef ghost_has_GHOST_SCNdPD
    #ifdef GHOST_SCNdPD
        #define ghost_has_GHOST_SCNdPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
        #define GHOST_SCNdPD GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "d"
        #define ghost_has_GHOST_SCNdPD 1
    #else
        #define ghost_has_GHOST_SCNdPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNiPD
    #ifdef GHOST_SCNiPD
        #define ghost_has_GHOST_SCNiPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
        #define GHOST_SCNiPD GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "i"
        #define ghost_has_GHOST_SCNiPD 1
    #else
        #define ghost_has_GHOST_SCNiPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNuPD
    #ifdef GHOST_SCNuPD
        #define ghost_has_GHOST_SCNuPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
        #define GHOST_SCNuPD GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "u"
        #define ghost_has_GHOST_SCNuPD 1
    #else
        #define ghost_has_GHOST_SCNuPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNoPD
    #ifdef GHOST_SCNoPD
        #define ghost_has_GHOST_SCNoPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
        #define GHOST_SCNoPD GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "o"
        #define ghost_has_GHOST_SCNoPD 1
    #else
        #define ghost_has_GHOST_SCNoPD 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNxPD
    #ifdef GHOST_SCNxPD
        #define ghost_has_GHOST_SCNxPD 1
    #elif defined(GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER)
        #define GHOST_SCNxPD GHOST_IMPL_FORMAT_PD_SCAN_MODIFIER "x"
        #define ghost_has_GHOST_SCNxPD 1
    #else
        #define ghost_has_GHOST_SCNxPD 0
    #endif
#endif

#endif
