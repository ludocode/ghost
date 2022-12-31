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

#ifndef GHOST_SILENCE_CONSTANT_OVERFLOW_H_INCLUDED
#define GHOST_SILENCE_CONSTANT_OVERFLOW_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_CONSTANT_OVERFLOW
 *
 * Silences warnings about constant arithmetic that overflows.
 *
 * Older versions of MSVC (e.g. 2015) warn about this in various situations.
 * Newer MSVC (e.g. 2022) seems more lax about it.
 *
 * For example:
 *
 *     unsigned x = UINT_MAX + 1; // warning C4307: '+': integral constant overflow
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW
    #ifdef GHOST_SILENCE_CONSTANT_OVERFLOW
        #define ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW 1
    #endif
#endif

/* C4307: '+': integral constant overflow
 * https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4307 */
#ifndef ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW
    #ifdef _MSC_VER
        #define GHOST_SILENCE_CONSTANT_OVERFLOW __pragma(warning(disable:4307))
        #define ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW 1
    #endif
#endif

/* GNU C compilers warn about this but only for signed arithmetic (and possibly
 * only pre-C23 or C++20 which require two's complement behaviour.) Ghost
 * doesn't currently have separate silencers for signed vs. unsigned.  */
#ifndef ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW
    #if defined(__GNUC__) && !defined(__CPARSER__)
        #include "ghost/detect/ghost_gcc.h"

        /* _Pragma GCC diagnostic is supported since GCC 4.2 */
        #if GHOST_GCC
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
                #define GHOST_SILENCE_CONSTANT_OVERFLOW _Pragma("GCC diagnostic ignored \"-Woverflow\"")
                #define ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW 1
            #endif
        #else
            #define GHOST_SILENCE_CONSTANT_OVERFLOW _Pragma("GCC diagnostic ignored \"-Woverflow\"")
            #define ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW 1
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW
    #define GHOST_SILENCE_CONSTANT_OVERFLOW /*nothing*/
    #define ghost_has_GHOST_SILENCE_CONSTANT_OVERFLOW 1
#endif

#endif
