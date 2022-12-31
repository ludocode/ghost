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

#ifndef GHOST_FORMAT_Z_H_INCLUDED
#define GHOST_FORMAT_Z_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines printf()/scanf() format specifiers for size_t and its signed
 * counterpart (which may match ssize_t, rsize_t, etc.)
 *
 * The C99 standard character for printing size_t is "z". This is supported on
 * modern platforms but wasn't historically supported by ANSI C
 * implementations. Ghost provides wrappers here. You of course don't have to
 * use them if you don't care about platforms that don't support "z".
 *
 * These are non-standard but they are in the style of C99 fixed-width format
 * specifiers like PRIi64, SCNx16, etc.
 *
 * @note While ssize_t matches the width of size_t on almost all modern
 *       systems, this isn't technically required by POSIX. You can use the
 *       signed format specifiers below with ssize_t (or ghost_ssize_t) if you
 *       are comfortable limiting yourself to systems where it matches.
 *
 * For intptr_t and uintptr_t, see ghost_format_ip.h. For ptrdiff_t, see
 * ghost_format_pd.h.
 *
 * @see ghost_size_t
 * @see ghost_ssize_t
 */

/**
 * @def GHOST_PRIdZ
 *
 * Prints a signed decimal integer of a type matching a signed counterpart to
 * size_t.
 */

/**
 * @def GHOST_PRIiZ
 *
 * Prints a signed decimal integer of a type matching a signed counterpart to
 * size_t.
 */

/**
 * @def GHOST_PRIuZ
 *
 * Prints an unsigned decimal integer of a type matching size_t.
 */

/**
 * @def GHOST_PRIoZ
 *
 * Prints an unsigned octal integer of a type matching size_t.
 */

/**
 * @def GHOST_PRIxZ
 *
 * Prints an unsigned lowercase hexadecimal integer of a type matching size_t.
 */

/**
 * @def GHOST_PRIXZ
 *
 * Prints an unsigned uppercase hexadecimal integer of a type matching size_t.
 */

/**
 * @def GHOST_SCNdZ
 *
 * Scans a signed decimal integer into a type matching a signed counterpart to
 * size_t.
 */

/**
 * @def GHOST_SCNiZ
 *
 * Scans a signed integer into a type matching a signed counterpart to size_t,
 * auto-detecting the base from the prefix.
 *
 * If the value is prefixed by 0x, it is parsed as hexadecimal; otherwise, if
 * it is prefixed by 0, it is parsed as octal; otherwise it is parsed as
 * decimal.
 */

/**
 * @def GHOST_SCNuZ
 *
 * Scans an unsigned decimal integer into a type matching size_t.
 */

/**
 * @def GHOST_SCNoZ
 *
 * Scans an unsigned octal integer into a type matching size_t.
 */

/**
 * @def GHOST_SCNxZ
 *
 * Scans an unsigned hexadecimal integer into a type matching size_t.
 */
#endif

#ifdef GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER
    #error "GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER cannot be overridden."
#endif
#ifdef GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER
    #error "GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER cannot be overridden."
#endif

/*
 * Older Windows uses 'I' for pointer-size values. Newer Windows supports C99
 * 'z'. We need to check this first because before VS 2015, Microsoft
 * apparently didn't support 'z' even under C++11.
 *
 *     https://docs.microsoft.com/en-us/previous-versions/tcxf1dw6(v=vs.140)
 *     https://stackoverflow.com/questions/2524611/how-can-one-print-a-size-t-variable-portably-using-the-printf-family
 *
 * This is apparently tied to the Microsoft compiler version, not the version
 * of the runtime. It's not clear to me how this is supposed to work for MinGW
 * compilers targeting old Windows SDKs. Do they rely on the newer runtime?
 * Should we use 'I' for MinGW? For now we just check for VS 2015.
 */
#if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
    #ifdef _MSC_VER
        #if _MSC_VER < 1900 /* VS 2015 */
            #ifndef GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER
                #define GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "I"
            #endif
            #ifndef GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER
                #define GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "I"
            #endif
        #endif
    #endif
#endif

/*
 * Use "z" if supported.
 */
#if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
    #include "ghost/impl/format/ghost_impl_format_c99_specifiers.h"
    #if GHOST_IMPL_FORMAT_C99_SPECIFIERS
        #ifndef GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER
            #define GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "z"
        #endif
        #ifndef GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER
            #define GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "z"
        #endif
    #endif
#endif

/* Otherwise we need to detect a matching basic type of size_t. */
/* TODO should probably change this, >= is probably not a good idea, and some
 * platforms use long instead of int when they are the same size which also
 * gives warnings... */
#if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
    #ifdef GHOST_SIZE_WIDTH

        /* Note that we don't check for "hh" and "ll" support because they are
         * only supported as recently as "z" which we would use instead. */

        /* check from smallest to largest */

        #if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
            #include "ghost/type/short/ghost_short_width.h"
            #ifdef GHOST_SHORT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) && GHOST_SHORT_WIDTH >= GHOST_SIZE_WIDTH
                    #define GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "h"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER) && GHOST_SHORT_WIDTH == GHOST_SIZE_WIDTH
                    #define GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "h"
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
            #include "ghost/type/int/ghost_int_width.h"
            #ifdef GHOST_INT_WIDTH
                #if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) && GHOST_INT_WIDTH >= GHOST_SIZE_WIDTH
                    #define GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER /*nothing*/
                #endif
                #if !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER) && GHOST_INT_WIDTH == GHOST_SIZE_WIDTH
                    #define GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER /*nothing*/
                #endif
            #endif
        #endif

        #if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) || !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
            #include "ghost/type/long/ghost_long_width.h"
            /* Make sure we also checked int because it won't be promoted to long */
            #if defined(GHOST_LONG_WIDTH) && defined(GHOST_INT_WIDTH)
                #if !defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER) && GHOST_LONG_WIDTH >= GHOST_SIZE_WIDTH
                    #define GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "l"
                #endif
                #if !defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER) && GHOST_LONG_WIDTH == GHOST_SIZE_WIDTH
                    #define GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "l"
                #endif
            #endif
        #endif

        #undef GHOST_IMPL_FORMAT_Z_ALLOW_HH_LL
    #endif
#endif

/* Handle override, define with modifier if possible, otherwise we don't have
 * it. */

/* Print */
#ifndef ghost_has_GHOST_PRIdZ
    #ifdef GHOST_PRIdZ
        #define ghost_has_GHOST_PRIdZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER)
        #define GHOST_PRIdZ GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "d"
        #define ghost_has_GHOST_PRIdZ 1
    #else
        #define ghost_has_GHOST_PRIdZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIiZ
    #ifdef GHOST_PRIiZ
        #define ghost_has_GHOST_PRIiZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER)
        #define GHOST_PRIiZ GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "i"
        #define ghost_has_GHOST_PRIiZ 1
    #else
        #define ghost_has_GHOST_PRIiZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIuZ
    #ifdef GHOST_PRIuZ
        #define ghost_has_GHOST_PRIuZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER)
        #define GHOST_PRIuZ GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "u"
        #define ghost_has_GHOST_PRIuZ 1
    #else
        #define ghost_has_GHOST_PRIuZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIoZ
    #ifdef GHOST_PRIoZ
        #define ghost_has_GHOST_PRIoZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER)
        #define GHOST_PRIoZ GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "o"
        #define ghost_has_GHOST_PRIoZ 1
    #else
        #define ghost_has_GHOST_PRIoZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIxZ
    #ifdef GHOST_PRIxZ
        #define ghost_has_GHOST_PRIxZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER)
        #define GHOST_PRIxZ GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "x"
        #define ghost_has_GHOST_PRIxZ 1
    #else
        #define ghost_has_GHOST_PRIxZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_PRIXZ
    #ifdef GHOST_PRIXZ
        #define ghost_has_GHOST_PRIXZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER)
        #define GHOST_PRIXZ GHOST_IMPL_FORMAT_Z_PRINT_MODIFIER "X"
        #define ghost_has_GHOST_PRIXZ 1
    #else
        #define ghost_has_GHOST_PRIXZ 0
    #endif
#endif

/* Scan */
#ifndef ghost_has_GHOST_SCNdZ
    #ifdef GHOST_SCNdZ
        #define ghost_has_GHOST_SCNdZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
        #define GHOST_SCNdZ GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "d"
        #define ghost_has_GHOST_SCNdZ 1
    #else
        #define ghost_has_GHOST_SCNdZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNiZ
    #ifdef GHOST_SCNiZ
        #define ghost_has_GHOST_SCNiZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
        #define GHOST_SCNiZ GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "i"
        #define ghost_has_GHOST_SCNiZ 1
    #else
        #define ghost_has_GHOST_SCNiZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNuZ
    #ifdef GHOST_SCNuZ
        #define ghost_has_GHOST_SCNuZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
        #define GHOST_SCNuZ GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "u"
        #define ghost_has_GHOST_SCNuZ 1
    #else
        #define ghost_has_GHOST_SCNuZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNoZ
    #ifdef GHOST_SCNoZ
        #define ghost_has_GHOST_SCNoZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
        #define GHOST_SCNoZ GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "o"
        #define ghost_has_GHOST_SCNoZ 1
    #else
        #define ghost_has_GHOST_SCNoZ 0
    #endif
#endif
#ifndef ghost_has_GHOST_SCNxZ
    #ifdef GHOST_SCNxZ
        #define ghost_has_GHOST_SCNxZ 1
    #elif defined(GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER)
        #define GHOST_SCNxZ GHOST_IMPL_FORMAT_Z_SCAN_MODIFIER "x"
        #define ghost_has_GHOST_SCNxZ 1
    #else
        #define ghost_has_GHOST_SCNxZ 0
    #endif
#endif

#endif
