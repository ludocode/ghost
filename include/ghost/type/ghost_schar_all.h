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

#ifndef GHOST_SCHAR_ALL_H_INCLUDED
#define GHOST_SCHAR_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines macros related to signed char:
 *
 * - GHOST_SCHAR_WIDTH
 * - GHOST_SCHAR_MAX
 * - GHOST_SCHAR_MIN
 * - GHOST_SCHAR_C()
 */

/**
 * @def GHOST_SCHAR_WIDTH SCHAR_WIDTH
 *
 * The number of bits in signed char.
 */

/**
 * @def GHOST_SCHAR_MAX SCHAR_MAX
 *
 * The maximum value of signed char.
 */

/**
 * @def GHOST_SCHAR_MAX SCHAR_MIN
 *
 * The minimum value of signed char.
 */

/**
 * @def GHOST_SCHAR_C(x) x
 *
 * Defines a preprocessor constant convertible to signed char.
 */
#endif

/* Always include <limits.h> so the user can use SCHAR_MAX and friends where
 * available.
 *     https://en.cppreference.com/w/c/types/limits */
#include "ghost/header/c/ghost_limits_h.h"

/* signed char always exists. */
#ifndef ghost_has_ghost_schar
    #define ghost_has_ghost_schar 1
#endif



/*
 * GHOST_SCHAR_WIDTH
 */

/* Allow override */
#ifndef ghost_has_GHOST_SCHAR_WIDTH
    #ifdef GHOST_SCHAR_WIDTH
        #define ghost_has_GHOST_SCHAR_WIDTH 1
    #endif
#endif

/* C23 defines SCHAR_WIDTH. It might be backported. */
#ifndef ghost_has_GHOST_SCHAR_WIDTH
    #if defined(SCHAR_WIDTH)
        #define GHOST_SCHAR_WIDTH SCHAR_WIDTH
        #define ghost_has_GHOST_SCHAR_WIDTH 1
    #endif
#endif

/* GNU C compilers define __SCHAR_WIDTH__. */
#ifndef ghost_has_GHOST_SCHAR_WIDTH
    #if defined(__SCHAR_WIDTH__)
        #define GHOST_SCHAR_WIDTH __SCHAR_WIDTH__
        #define ghost_has_GHOST_SCHAR_WIDTH 1
    #endif
#endif

/* Match the width of char. (We're assuming signed and unsigned are the
 * same width.) */
#ifndef ghost_has_GHOST_SCHAR_WIDTH
    #include "ghost/type/char/ghost_char_width.h"
    #if ghost_has_GHOST_CHAR_WIDTH
        #include "ghost/impl/ghost_impl_assumptions.h"
        #if GHOST_IMPL_ASSUME_SIGNED_UNSIGNED_SAME_WIDTH
            #define GHOST_SCHAR_WIDTH GHOST_CHAR_WIDTH
            #define ghost_has_GHOST_SCHAR_WIDTH 1
        #endif
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_SCHAR_WIDTH
    #define ghost_has_GHOST_SCHAR_WIDTH 0
#endif



/*
 * GHOST_SCHAR_C()
 */

/* signed char constants have no suffix */
#ifndef ghost_has_GHOST_SCHAR_C
    #ifndef GHOST_SCHAR_C
        #define GHOST_SCHAR_C(x) x
    #endif
    #define ghost_has_GHOST_SCHAR_C 1
#endif



/**
 * GHOST_SCHAR_MAX
 */

/* Allow override */
#ifndef ghost_has_GHOST_SCHAR_MAX
    #ifdef GHOST_SCHAR_MAX
        #define ghost_has_GHOST_SCHAR_MAX 1
    #endif
#endif

/* SCHAR_MAX is in ANSI C. */
#ifndef ghost_has_GHOST_SCHAR_MAX
    #ifdef SCHAR_MAX
        #define GHOST_SCHAR_MAX SCHAR_MAX
        #define ghost_has_GHOST_SCHAR_MAX 1
    #endif
#endif

/* GNU C compilers define __SCHAR_MAX__. */
#ifndef ghost_has_GHOST_SCHAR_MAX
    #ifdef __SCHAR_MAX__
        #define GHOST_SCHAR_MAX __SCHAR_MAX__
        #define ghost_has_GHOST_SCHAR_MAX 1
    #endif
#endif

/* If char is signed we can use GHOST_CHAR_MAX. */
#ifndef ghost_has_GHOST_SCHAR_MAX
    #include "ghost/type/char/ghost_char_is_signed.h"
    #if ghost_has_GHOST_CHAR_IS_SIGNED
        #if GHOST_CHAR_IS_SIGNED
            #include "ghost/type/char/ghost_char_max.h"
            #if ghost_has(GHOST_CHAR_MAX)
                #define GHOST_SCHAR_MAX GHOST_CHAR_MAX
                #define ghost_has_GHOST_SCHAR_MAX 1
            #endif
        #endif
    #endif
#endif

/* If we have the width we can calculate it.
 * (Technically a type may have padding bits. If we intend to support any such
 * platforms we can handle that here.) */
#ifndef ghost_has_GHOST_SCHAR_MAX
    #if ghost_has_GHOST_SCHAR_WIDTH
        #if GHOST_UCHAR_WIDTH == 8
            #define GHOST_UCHAR_MAX 255
        #else
            #define GHOST_SCHAR_MAX ((((1 << (GHOST_SCHAR_WIDTH - 2)) - 1) << 1) + 1)
        #endif
        #define ghost_has_GHOST_SCHAR_MAX 1
    #endif
#endif

/* Otherwise we don't know the max. */
#ifndef ghost_has_GHOST_SCHAR_MAX
    #define ghost_has_GHOST_SCHAR_MAX 0
#endif



/**
 * GHOST_SCHAR_MIN
 */

/* Allow override */
#ifndef ghost_has_GHOST_SCHAR_MIN
    #ifdef GHOST_SCHAR_MIN
        #define ghost_has_GHOST_SCHAR_MIN 1
    #endif
#endif

/* SCHAR_MIN is in ANSI C. */
#ifndef ghost_has_GHOST_SCHAR_MIN
    #ifdef SCHAR_MIN
        #define GHOST_SCHAR_MIN SCHAR_MIN
        #define ghost_has_GHOST_SCHAR_MIN 1
    #endif
#endif

/* If char is signed we can use GHOST_CHAR_MIN. */
#ifndef ghost_has_GHOST_SCHAR_MIN
    #include "ghost/type/char/ghost_char_is_signed.h"
    #if ghost_has_GHOST_CHAR_IS_SIGNED
        #if GHOST_CHAR_IS_SIGNED
            #include "ghost/type/char/ghost_char_min.h"
            #if ghost_has(GHOST_CHAR_MIN)
                #define GHOST_SCHAR_MIN GHOST_CHAR_MIN
                #define ghost_has_GHOST_SCHAR_MIN 1
            #endif
        #endif
    #endif
#endif

/* If we have the max we can calculate it */
#ifndef ghost_has_GHOST_SCHAR_MIN
    #if ghost_has_GHOST_SCHAR_MAX
        #include "ghost/impl/ghost_impl_assumptions.h"
        #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
            #define GHOST_SCHAR_MIN (-1 - GHOST_SCHAR_MAX)
            #define ghost_has_GHOST_SCHAR_MIN 1
        #endif
    #endif
#endif

/* Otherwise we don't have min. */
#ifndef ghost_has_GHOST_SCHAR_MIN
    #define ghost_has_GHOST_SCHAR_MIN 0
#endif



#endif
