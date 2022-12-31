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

#ifndef GHOST_SILENCE_UNUSED_PARAMETER_H_INCLUDED
#define GHOST_SILENCE_UNUSED_PARAMETER_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_UNUSED_PARAMETER
 *
 * Silences warnings about unused function parameters.
 *
 * Some compilers (like GCC) let you silence these warnings for individual
 * parameters by putting ghost_maybe_unused on them. Other compilers (like
 * MSVC) don't support this (before C++17) so you can use this instead.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_UNUSED_PARAMETER
    #ifdef GHOST_SILENCE_UNUSED_PARAMETER
        #define ghost_has_GHOST_SILENCE_UNUSED_PARAMETER 1
    #endif
#endif

/* GCC/Clang -Wunused-parameter */
#ifndef ghost_has_GHOST_SILENCE_UNUSED_PARAMETER
    #if defined(__GNUC__) && !defined(__CPARSER__)
        /* _Pragma GCC diagnostic is supported since GCC 4.2 */
        #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
            #define GHOST_SILENCE_UNUSED_PARAMETER \
                    _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
            #define ghost_has_GHOST_SILENCE_UNUSED_PARAMETER 1
        #endif
    #endif
#endif

/* MSVC C4100 in /W4
 * https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4100 */
#ifndef ghost_has_GHOST_SILENCE_UNUSED_PARAMETER
    #ifdef _MSC_VER
        /* C4100: unreferenced formal parameter */
        #define GHOST_SILENCE_UNUSED_PARAMETER __pragma(warning(disable:4100))
        #define ghost_has_GHOST_SILENCE_UNUSED_PARAMETER 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_UNUSED_PARAMETER
    #define GHOST_SILENCE_UNUSED_PARAMETER /*nothing*/
    #define ghost_has_GHOST_SILENCE_UNUSED_PARAMETER 1
#endif

#endif
