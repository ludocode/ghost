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

#ifndef GHOST_NOINLINE_H_INCLUDED
#define GHOST_NOINLINE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_noinline
 *
 * Suggests to the compiler that it should not inline this function.
 *
 * When a static function is only used once, compilers often inline it into its
 * call site even if not declared inline. This can cause poor instruction cache
 * usage because a function that should rarely be called may get inlined into
 * the middle of a hot code path. Profile-guided optimization can help but you
 * may want a more explicit way of preventing this. You may also want to
 * prevent inlining to allow identical code folding to merge duplicate
 * definitions of functions across different translation units. For all these
 * reasons, Ghost provides ghost_noinline.
 *
 * In C++, noinline has no effect on linkage, so it is valid and meaningful
 * to declare a function both inline and noinline. In C, declaring an inline
 * function noinline is diagnosed as an error by some compilers. Unfortunately
 * this makes it more complicated to use for header-only libraries in C.
 *
 * Since noinline is just an optimization hint, we define this to nothing if
 * it's not supported. This means ghost_has(ghost_noinline) is always 1.
 */
#endif

#ifndef ghost_has_ghost_noinline
    #ifdef ghost_noinline
        #define ghost_has_ghost_noinline 1
    #endif
#endif

/* MSVC supports __declspec(noinline).
 *     https://docs.microsoft.com/en-us/cpp/cpp/noinline
 * In VS 2013 and earlier, this is not supported in C mode. */
#ifndef ghost_has_ghost_noinline
    #if defined(_MSC_VER)
        #if defined(__cplusplus) || _MSC_VER >= 1900
            #define ghost_noinline __declspec(noinline)
            #define ghost_has_ghost_noinline 1
        #endif
    #endif
#endif

/* GNU C compilers support __attribute__((noinline))
 *     https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html */
#ifndef ghost_has_ghost_noinline
    #if defined(__GNUC__)
        #define ghost_noinline __attribute__((__noinline__))
        #define ghost_has_ghost_noinline 1
    #endif
#endif

#ifndef ghost_has_ghost_noinline
    #define ghost_noinline /*nothing*/
    #define ghost_has_ghost_noinline 1
#endif

#endif
