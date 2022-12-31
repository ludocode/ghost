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

#ifndef GHOST_FORMAT_IP_H_INCLUDED
#define GHOST_FORMAT_IP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines printf()/scanf() format specifiers for intptr_t and uintptr_t.
 *
 * There is no standard format length modifier for printing integers of pointer
 * width. (There is the "p" specifier for printing pointers but that's not what
 * this is for.) Ghost therefore provides this abstraction.
 *
 * In cases where size_t is the same width and "z" is supported, this will use
 * "z". Otherwise it will try to find an appropriate length modifier. If you
 * don't care about any other platforms, you can always simply ignore this and
 * use "z".
 *
 * These are non-standard but they are in the style of C99 fixed-width format
 * specifiers like PRIi64, SCNx16, etc.
 *
 * For size_t, see ghost_format_z.h. For ptrdiff_t, see ghost_format_pd.h.
 */

/**
 * @def GHOST_PRIdP
 *
 * Prints a signed decimal integer of a type matching intptr_t.
 */

/**
 * @def GHOST_PRIiP
 *
 * Prints a signed decimal integer of a type matching intptr_t.
 */

/**
 * @def GHOST_PRIuP
 *
 * Prints an unsigned decimal integer of a type matching uintptr_t.
 */

/**
 * @def GHOST_PRIoP
 *
 * Prints an unsigned octal integer of a type matching uintptr_t.
 */

/**
 * @def GHOST_PRIxP
 *
 * Prints an unsigned lowercase hexadecimal integer of a type matching
 * uintptr_t.
 */

/**
 * @def GHOST_PRIXP
 *
 * Prints an unsigned uppercase hexadecimal integer of a type matching
 * uintptr_t.
 */

/**
 * @def GHOST_SCNdP
 *
 * Scans a signed decimal integer into a type matching intptr_t.
 */

/**
 * @def GHOST_SCNiP
 *
 * Scans a signed integer into a type matching intptr_t, auto-detecting the
 * base from the prefix.
 *
 * If the value is prefixed by 0x, it is parsed as hexadecimal; otherwise, if
 * it is prefixed by 0, it is parsed as octal; otherwise it is parsed as
 * decimal.
 */

/**
 * @def GHOST_SCNuP
 *
 * Scans an unsigned decimal integer into a type matching uintptr_t.
 */

/**
 * @def GHOST_SCNoP
 *
 * Scans an unsigned octal integer into a type matching uintptr_t.
 */

/**
 * @def GHOST_SCNxP
 *
 * Scans an unsigned hexadecimal integer into a type matching uintptr_t.
 */
#endif

#ifdef GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER
    #error "GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER cannot be overridden."
#endif
#ifdef GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER
    #error "GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER cannot be overridden."
#endif

/* If [u]intptr_t is the same width as size_t, we can use the format modifier
 * for size_t. This might be "z" which is ideal for modern C. */
#include "ghost/type/intptr_t/ghost_intptr_width.h"
#include "ghost/type/uintptr_t/ghost_uintptr_width.h"
#include "ghost/type/size_t/ghost_size_width.h"
#if defined(GHOST_INTPTR_WIDTH) && \
        defined(GHOST_UINTPTR_WIDTH) && \
        defined(GHOST_SIZE_WIDTH)
    #if GHOST_INTPTR_WIDTH == GHOST_SIZE_WIDTH && GHOST_UINTPTR_WIDTH == GHOST_SIZE_WIDTH
        #include "ghost/format/ghost_format_z.h"
        #ifdef GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER
            #define GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER
        #endif
        #ifdef GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER
            #define GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER
        #endif
    #endif
#endif

/* Otherwise we need to detect a matching basic type of [u]intptr_t. */
#if (!defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)) \
        && defined(GHOST_UINTPTR_WIDTH) && defined(GHOST_INTPTR_WIDTH)
    #if GHOST_INTPTR_WIDTH == GHOST_UINTPTR_WIDTH
        #include "ghost/impl/format/ghost_impl_format_c99_specifiers.h"

        /* check from smallest to largest */

        #if (!defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/char/ghost_char_width.h"
            #ifdef GHOST_CHAR_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) && GHOST_CHAR_WIDTH >= GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "hh"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER) && GHOST_CHAR_WIDTH == GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "hh"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)
            #include "ghost/type/short/ghost_short_width.h"
            #ifdef GHOST_SHORT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) && GHOST_SHORT_WIDTH >= GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "h"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER) && GHOST_SHORT_WIDTH == GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "h"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)
            #include "ghost/type/int/ghost_int_width.h"
            #ifdef GHOST_INT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) && GHOST_INT_WIDTH >= GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER /*nothing*/
                #endif
                #if !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER) && GHOST_INT_WIDTH == GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER /*nothing*/
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)
            #include "ghost/type/long/ghost_long_width.h"
            /* Make sure we also checked int because it won't be promoted to long */
            #if defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) && GHOST_LONG_WIDTH >= GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "l"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER) && GHOST_LONG_WIDTH == GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "l"
                #endif
            #endif
        #endif

        #if (!defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)) \
                && GHOST_IMPL_FORMAT_C99_SPECIFIERS
            #include "ghost/type/llong/ghost_llong_width.h"
            /* Make sure we also checked int and long because they won't be promoted to long long */
            #if defined(GHOST_LLONG_WIDTH) && defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER) && GHOST_LLONG_WIDTH >= GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "ll"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER) && GHOST_LLONG_WIDTH == GHOST_UINTPTR_WIDTH
                    #define GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "ll"
                #endif
            #endif
        #endif

        #undef GHOST_IMPL_FORMAT_IP_ALLOW_HH_LL
    #endif
#endif

/* Handle override, define with modifier if possible, otherwise we don't have
 * it. */

/* Print */
#ifndef ghost_has_GHOST_PRIdP
    #ifdef GHOST_PRIdP
        #define ghost_has_GHOST_PRIdP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER)
        #define GHOST_PRIdP GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "d"
        #define ghost_has_GHOST_PRIdP 1
    #else
        #define ghost_has_GHOST_PRIdP 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIiP
    #ifdef GHOST_PRIiP
        #define ghost_has_GHOST_PRIiP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER)
        #define GHOST_PRIiP GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "i"
        #define ghost_has_GHOST_PRIiP 1
    #else
        #define ghost_has_GHOST_PRIiP 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIuP
    #ifdef GHOST_PRIuP
        #define ghost_has_GHOST_PRIuP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER)
        #define GHOST_PRIuP GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "u"
        #define ghost_has_GHOST_PRIuP 1
    #else
        #define ghost_has_GHOST_PRIuP 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIoP
    #ifdef GHOST_PRIoP
        #define ghost_has_GHOST_PRIoP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER)
        #define GHOST_PRIoP GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "o"
        #define ghost_has_GHOST_PRIoP 1
    #else
        #define ghost_has_GHOST_PRIoP 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIxP
    #ifdef GHOST_PRIxP
        #define ghost_has_GHOST_PRIxP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER)
        #define GHOST_PRIxP GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "x"
        #define ghost_has_GHOST_PRIxP 1
    #else
        #define ghost_has_GHOST_PRIxP 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIXP
    #ifdef GHOST_PRIXP
        #define ghost_has_GHOST_PRIXP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER)
        #define GHOST_PRIXP GHOST_IMPL_FORMAT_IP_PRINT_MODIFIER "X"
        #define ghost_has_GHOST_PRIXP 1
    #else
        #define ghost_has_GHOST_PRIXP 0
    #endif
#endif

/* Scan */
#ifndef ghost_has_GHOST_SCNdP
    #ifdef GHOST_SCNdP
        #define ghost_has_GHOST_SCNdP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)
        #define GHOST_SCNdP GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "d"
        #define ghost_has_GHOST_SCNdP 1
    #else
        #define ghost_has_GHOST_SCNdP 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNiP
    #ifdef GHOST_SCNiP
        #define ghost_has_GHOST_SCNiP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)
        #define GHOST_SCNiP GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "i"
        #define ghost_has_GHOST_SCNiP 1
    #else
        #define ghost_has_GHOST_SCNiP 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNuP
    #ifdef GHOST_SCNuP
        #define ghost_has_GHOST_SCNuP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)
        #define GHOST_SCNuP GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "u"
        #define ghost_has_GHOST_SCNuP 1
    #else
        #define ghost_has_GHOST_SCNuP 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNoP
    #ifdef GHOST_SCNoP
        #define ghost_has_GHOST_SCNoP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)
        #define GHOST_SCNoP GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "o"
        #define ghost_has_GHOST_SCNoP 1
    #else
        #define ghost_has_GHOST_SCNoP 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNxP
    #ifdef GHOST_SCNxP
        #define ghost_has_GHOST_SCNxP 1
    #elif defined(GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER)
        #define GHOST_SCNxP GHOST_IMPL_FORMAT_IP_SCAN_MODIFIER "x"
        #define ghost_has_GHOST_SCNxP 1
    #else
        #define ghost_has_GHOST_SCNxP 0
    #endif
#endif

#endif
