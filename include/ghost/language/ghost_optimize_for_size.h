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

#ifndef GHOST_OPTIMIZE_FOR_SIZE_H_INCLUDED
#define GHOST_OPTIMIZE_FOR_SIZE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_OPTIMIZE_FOR_SIZE
 *
 * Expands to 1 if the compiler is optimizing for size (e.g. with a `-Os`
 * command-line option) or 0 if it isn't.
 *
 * If Ghost can't tell whether the compiler is optimizing for size, this macro
 * doesn't exist. Check ghost_has(GHOST_OPTIMIZE_FOR_SIZE) (or simply #ifdef
 * GHOST_OPTIMIZE_FOR_SIZE) to see if this is available.
 *
 * This detects -Os with GCC/Clang. Unfortunately there doesn't seem to be a
 * macro defined for /Os under MSVC.
 *
 * @see GHOST_OPTIMIZE_FOR_SIZE_OPT
 */
#endif

#ifndef ghost_has_GHOST_OPTIMIZE_FOR_SIZE
    #ifdef GHOST_OPTIMIZE_FOR_SIZE
        #define ghost_has_GHOST_OPTIMIZE_FOR_SIZE 1
    #endif
#endif

/* GCC and Clang define __OPTIMIZE_SIZE__ to 1 under -Os. They don't define it
 * otherwise, but we check that it's not 0 anyway in case some other compiler
 * does. */
#ifndef ghost_has_GHOST_OPTIMIZE_FOR_SIZE
    #ifdef __OPTIMIZE_SIZE__
        #if __OPTIMIZE_SIZE__
            #define GHOST_OPTIMIZE_FOR_SIZE 1
        #else
            #define GHOST_OPTIMIZE_FOR_SIZE 0
        #endif
        #define ghost_has_GHOST_OPTIMIZE_FOR_SIZE 1
    #endif
#endif

/* Since we expect GCC and Clang to define __OPTIMIZE_SIZE__, we can trust that
 * if it isn't defined on these specific compilers, we're not optimizing for
 * size. We can add additional compilers that behave similarly as we discover
 * them. */
#ifndef ghost_has_GHOST_OPTIMIZE_FOR_SIZE
    #ifdef __clang__
        #define GHOST_OPTIMIZE_FOR_SIZE 0
        #define ghost_has_GHOST_OPTIMIZE_FOR_SIZE 1
    #elif defined(__GNUC__)
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define GHOST_OPTIMIZE_FOR_SIZE 0
            #define ghost_has_GHOST_OPTIMIZE_FOR_SIZE 1
        #endif
    #endif
#endif

/* Otherwise we don't know whether we are optimizing for size. */
#ifndef ghost_has_GHOST_OPTIMIZE_FOR_SIZE
    #define ghost_has_GHOST_OPTIMIZE_FOR_SIZE 0
#endif

#endif
