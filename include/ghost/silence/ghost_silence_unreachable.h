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

#ifndef GHOST_SILENCE_UNREACHABLE_H_INCLUDED
#define GHOST_SILENCE_UNREACHABLE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_UNREACHABLE
 *
 * Silences unreachable code warnings.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_UNREACHABLE
    #ifdef GHOST_SILENCE_UNREACHABLE
        #define ghost_has_GHOST_SILENCE_UNREACHABLE 1
    #endif
#endif

/* GCC/Clang -Wunreachable-code
 * GCC supports this warning but doesn't seem to warn about obvious cases (like
 * code after a return.) Clang seems better at warning about it. */
#ifndef ghost_has_GHOST_SILENCE_UNREACHABLE
    #if defined(__GNUC__) && !defined(__CPARSER__)
        /* _Pragma GCC diagnostic is supported since GCC 4.2 */
        #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
            #define GHOST_SILENCE_UNREACHABLE _Pragma("GCC diagnostic ignored \"-Wunreachable-code\"")
            #define ghost_has_GHOST_SILENCE_UNREACHABLE 1
        #endif
    #endif
#endif

/* MSVC C4702 in /W4 */
#ifndef ghost_has_GHOST_SILENCE_UNREACHABLE
    #ifdef _MSC_VER
        /* C4702: unreachable code */
        #define GHOST_SILENCE_UNREACHABLE __pragma(warning(disable:4702))
        #define ghost_has_GHOST_SILENCE_UNREACHABLE 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_UNREACHABLE
    #define GHOST_SILENCE_UNREACHABLE /*nothing*/
    #define ghost_has_GHOST_SILENCE_UNREACHABLE 1
#endif

#endif
