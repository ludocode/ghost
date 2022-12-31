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

#ifndef GHOST_CHAR_IS_SIGNED_H_INCLUDED
#define GHOST_CHAR_IS_SIGNED_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR_IS_SIGNED
 *
 * Expands to 1 if char is signed and 0 if char is unsigned.
 */
#endif

#ifndef ghost_has_GHOST_CHAR_IS_SIGNED
    #ifdef GHOST_CHAR_IS_SIGNED
        #define ghost_has_GHOST_CHAR_IS_SIGNED 1
    #endif
#endif

/* GNU C compilers define __CHAR_UNSIGNED__ to 1 if char is unsigned. */
#ifndef ghost_has_GHOST_CHAR_IS_SIGNED
    #ifdef __GNUC__
        #ifdef __CHAR_UNSIGNED__
            #if __CHAR_UNSIGNED__
                #define GHOST_CHAR_IS_SIGNED 0
            #else
                #define GHOST_CHAR_IS_SIGNED 1
            #endif
        #else
            #define GHOST_CHAR_IS_SIGNED 1
        #endif
        #define ghost_has_GHOST_CHAR_IS_SIGNED 1
    #endif
#endif

/* MSVC defines _CHAR_UNSIGNED to 1 if char is unsigned.
 *     https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros */
#ifndef ghost_has_GHOST_CHAR_IS_SIGNED
    #ifdef _MSC_VER
        #ifdef _CHAR_UNSIGNED
            #if _CHAR_UNSIGNED
                #define GHOST_CHAR_IS_SIGNED 0
            #else
                #define GHOST_CHAR_IS_SIGNED 1
            #endif
        #else
            #define GHOST_CHAR_IS_SIGNED 1
        #endif
        #define ghost_has_GHOST_CHAR_IS_SIGNED 1
    #endif
#endif

/* <limits.h> has CHAR_MIN. Check whether it's zero. (We don't check
 * GHOST_CHAR_MIN because that file depends on this one.) */
#ifndef ghost_has_GHOST_CHAR_IS_SIGNED
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef CHAR_MIN
        #if CHAR_MIN == 0
            #define GHOST_CHAR_IS_SIGNED 0
        #else
            #define GHOST_CHAR_IS_SIGNED 1
        #endif
        #define ghost_has_GHOST_CHAR_IS_SIGNED 1
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_CHAR_IS_SIGNED
    #define ghost_has_GHOST_CHAR_IS_SIGNED 0
#endif

/* Test signedness */
#if ghost_has(GHOST_CHAR_IS_SIGNED)
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/language/ghost_static_cast.h"
    #if GHOST_CHAR_IS_SIGNED
        ghost_static_assert(ghost_static_cast(char, -1) == -1,
                "GHOST_CHAR_IS_SIGNED is 1 but char appears to be unsigned.");
    #else
        ghost_static_assert(ghost_static_cast(char, -1) != -1,
                "GHOST_CHAR_IS_SIGNED is 0 but char appears to be signed.");
    #endif
#endif

#endif
