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

#ifndef GHOST_AUTO_H_INCLUDED
#define GHOST_AUTO_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_auto __auto_type
 *
 * Declares a variable whose type is deduced from its initialization
 * expression.
 *
 * This is a wrapper for C++11 auto or GNU C __auto_type.
 *
 * Use it like this:
 *
 *     ghost_auto x = <some expression...>;
 *
 * x will have the type (and value) of the expression.
 *
 * This requires compiler extensions in C and C++98. Check
 * `#if ghost_has(ghost_auto)` to see whether it exists.
 */
#endif

#ifndef ghost_has_ghost_auto
    #ifdef ghost_auto
        #define ghost_has_ghost_auto 1
    #endif
#endif

/* C++11 added auto */
#ifndef ghost_has_ghost_auto
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define ghost_auto auto
            #define ghost_has_ghost_auto 1
        #endif
    #endif
#endif

/* GCC and friends support __auto_type in C
 *     https://gcc.gnu.org/onlinedocs/gcc/Typeof.html */
#ifndef ghost_has_ghost_auto
    #if !defined(__cplusplus)

        /* Clang added it in 3.8 */
        #if defined(__clang__)
            /* TODO this version check won't work on e.g. Apple Clang and other variants */
            #if __clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 8) || defined(__APPLE__)
                /* Use __extension__ to silence Clang -Wgnu-auto-type */
                #define ghost_auto __extension__ __auto_type
                #define ghost_has_ghost_auto 1
            #endif

        /* GCC added it in 4.9 */
        #else
            #include "ghost/detect/ghost_gcc.h"
            #if GHOST_GCC
                #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)
                    #define ghost_auto __auto_type
                    #define ghost_has_ghost_auto 1
                #endif
            #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_auto
    #define ghost_has_ghost_auto 0
#endif

#endif
