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

#ifndef GHOST_SILENCE_PEDANTIC_H_INCLUDED
#define GHOST_SILENCE_PEDANTIC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_PEDANTIC
 *
 * Silences -Wpedantic in GCC and Clang.
 *
 * This was called -pedantic in older versions of GCC.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_PEDANTIC
    #ifdef GHOST_SILENCE_PEDANTIC
        #define ghost_has_GHOST_SILENCE_PEDANTIC 1
    #endif
#endif

/* In Clang 3.1 and earlier, this was called -pedantic. */
#ifndef ghost_has_GHOST_SILENCE_PEDANTIC
    /* This version check won't work on Clang variants. For now we only check
     * that we're not Apple Clang. */
    #if defined(__clang__) && !defined(__APPLE__)
        #if __clang_major__ < 3 || (__clang_major__ == 3 && __clang_minor__ <= 1)
            #define GHOST_SILENCE_PEDANTIC _Pragma("GCC diagnostic ignored \"-pedantic\"")
            #define ghost_has_GHOST_SILENCE_PEDANTIC 1
        #endif
    #endif
#endif

/* In GCC 4.7 and earlier, this was called -pedantic. */
#ifndef ghost_has_GHOST_SILENCE_PEDANTIC
    #ifdef __GNUC__
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* _Pragma() wasn't supported until GCC 4.2 */
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
                #define GHOST_SILENCE_PEDANTIC _Pragma("GCC diagnostic ignored \"-pedantic\"")
                #define ghost_has_GHOST_SILENCE_PEDANTIC 1
            #endif
        #endif
    #endif
#endif

/* Otherwise, GCC and Clang call this -Wpedantic. */
#ifndef ghost_has_GHOST_SILENCE_PEDANTIC
    /* We assume all C compilers that define __GNUC__ support -Wpedantic unless
     * we know otherwise. */
    #if defined(__GNUC__)
        #define GHOST_SILENCE_PEDANTIC _Pragma("GCC diagnostic ignored \"-Wpedantic\"")
        #define ghost_has_GHOST_SILENCE_PEDANTIC 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_PEDANTIC
    #define GHOST_SILENCE_PEDANTIC /*nothing*/
    #define ghost_has_GHOST_SILENCE_PEDANTIC 1
#endif

#endif
