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

#ifndef GHOST_SILENCE_LONG_LONG_H_INCLUDED
#define GHOST_SILENCE_LONG_LONG_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_LONG_LONG
 *
 * Silences compiler warnings about the use of a `long long` extension in older
 * language standards.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_LONG_LONG
    #ifdef GHOST_SILENCE_LONG_LONG
        #define ghost_has_GHOST_SILENCE_LONG_LONG 1
    #endif
#endif

/* GCC/Clang -Wlong-long */
#ifndef ghost_has_GHOST_SILENCE_LONG_LONG
    #if defined(__GNUC__) && !defined(__CPARSER__)
        /* _Pragma GCC diagnostic is supported since GCC 4.2 */
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
                #define GHOST_SILENCE_LONG_LONG _Pragma("GCC diagnostic ignored \"-Wlong-long\"")
                #define ghost_has_GHOST_SILENCE_LONG_LONG 1
            #endif
        #else
            #define GHOST_SILENCE_LONG_LONG _Pragma("GCC diagnostic ignored \"-Wlong-long\"")
            #define ghost_has_GHOST_SILENCE_LONG_LONG 1
        #endif
    #endif
#endif

/* MSVC doesn't appear to warn when `long long` is used in ANSI C. */

#ifndef ghost_has_GHOST_SILENCE_LONG_LONG
    #define GHOST_SILENCE_LONG_LONG /*nothing*/
    #define ghost_has_GHOST_SILENCE_LONG_LONG 1
#endif

#endif
