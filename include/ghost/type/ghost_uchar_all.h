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

#ifndef GHOST_UCHAR_ALL_H_INCLUDED
#define GHOST_UCHAR_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines macros related to unsigned char:
 *
 * - GHOST_UCHAR_WIDTH
 * - GHOST_UCHAR_MAX
 * - GHOST_UCHAR_C()
 */

/**
 * @def GHOST_UCHAR_WIDTH UCHAR_WIDTH
 *
 * The number of bits in unsigned char.
 */

/**
 * @def GHOST_UCHAR_MAX UCHAR_MAX
 *
 * The maximum value of unsigned char.
 */

/**
 * @def GHOST_UCHAR_C(x) x
 *
 * Defines a preprocessor constant convertible to unsigned char.
 */
#endif

/* Always include <limits.h> so the user can use UCHAR_MAX and friends where
 * available.
 *     https://en.cppreference.com/w/c/types/limits */
#include "ghost/header/c/ghost_limits_h.h"

/* unsigned char always exists. */
#ifndef ghost_has_ghost_uchar
    #define ghost_has_ghost_uchar 1
#endif



/*
 * GHOST_UCHAR_WIDTH
 */

/* Allow override */
#ifndef ghost_has_GHOST_UCHAR_WIDTH
    #ifdef GHOST_UCHAR_WIDTH
        #define ghost_has_GHOST_UCHAR_WIDTH 1
    #endif
#endif

/* C23 defines UCHAR_WIDTH. It might be backported. */
#ifndef ghost_has_GHOST_UCHAR_WIDTH
    #if defined(UCHAR_WIDTH)
        #define GHOST_UCHAR_WIDTH UCHAR_WIDTH
        #define ghost_has_GHOST_UCHAR_WIDTH 1
    #endif
#endif

/* Match the width of char. */
#ifndef ghost_has_GHOST_UCHAR_WIDTH
    #include "ghost/type/char/ghost_char_width.h"
    #if ghost_has_GHOST_CHAR_WIDTH
        #include "ghost/impl/ghost_impl_assumptions.h"
        #if GHOST_IMPL_ASSUME_SIGNED_UNSIGNED_SAME_WIDTH
            #define GHOST_UCHAR_WIDTH GHOST_CHAR_WIDTH
            #define ghost_has_GHOST_UCHAR_WIDTH 1
        #endif
    #endif
#endif

/* Otherwise we don't know the width. */
#ifndef ghost_has_GHOST_UCHAR_WIDTH
    #define ghost_has_GHOST_UCHAR_WIDTH 0
#endif



/*
 * GHOST_UCHAR_C()
 */

/* unsigned char constants just have U suffix */
#ifndef ghost_has_GHOST_UCHAR_C
    #ifndef GHOST_UCHAR_C
        #define GHOST_UCHAR_C(x) x ## U
    #endif
    #define ghost_has_GHOST_UCHAR_C 1
#endif



/**
 * GHOST_UCHAR_MAX
 */

/* Allow override */
#ifndef ghost_has_GHOST_UCHAR_MAX
    #ifdef GHOST_UCHAR_MAX
        #define ghost_has_GHOST_UCHAR_MAX 1
    #endif
#endif

/* UCHAR_MAX is in ANSI C. */
#ifndef ghost_has_GHOST_UCHAR_MAX
    #ifdef UCHAR_MAX
        #define GHOST_UCHAR_MAX UCHAR_MAX
        #define ghost_has_GHOST_UCHAR_MAX 1
    #endif
#endif

/* If char is unsigned we can use GHOST_CHAR_MAX. */
#ifndef ghost_has_GHOST_UCHAR_MAX
    #include "ghost/type/char/ghost_char_width.h"
    #if ghost_has_GHOST_CHAR_IS_SIGNED
        #if !GHOST_CHAR_IS_SIGNED && ghost_has_GHOST_CHAR_MAX
            #define GHOST_UCHAR_MAX GHOST_CHAR_MAX
            #define ghost_has_GHOST_UCHAR_MAX 1
        #endif
    #endif
#endif

/* If we have the width we can calculate it.
 * (Technically a type may have padding bits. If we intend to support any such
 * platforms we can handle that here.) */
#ifndef ghost_has_GHOST_UCHAR_MAX
    #if ghost_has_GHOST_UCHAR_WIDTH
        #if GHOST_UCHAR_WIDTH == 8
            #define GHOST_UCHAR_MAX 255
        #else
            #define GHOST_UCHAR_MAX ((((1U << (GHOST_UCHAR_WIDTH - 1U)) - 1U) << 1U) + 1U)
        #endif
        #define ghost_has_GHOST_UCHAR_MAX 1
    #endif
#endif

/* Otherwise we don't know the max. */
#ifndef ghost_has_GHOST_UCHAR_MAX
    #define ghost_has_GHOST_UCHAR_MAX 0
#endif



#endif
