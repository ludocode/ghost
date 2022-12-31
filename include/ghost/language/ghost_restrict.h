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

#ifndef GHOST_RESTRICT_H_INCLUDED
#define GHOST_RESTRICT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_restrict restrict
 *
 * `restrict` or a compiler-specific equivalent if possible, or nothing
 * otherwise.
 *
 * A restrict-qualified pointer cannot be aliased to any other pointer during
 * its lifetime. For example, if a function takes two restrict pointers (like
 * memcpy()), the compiler can assume they don't overlap for the purpose of
 * optimization. The rules for restrict are much more complicated than this;
 * please find a good source for how to use restrict.
 *
 * This is useful as an optimization tool. Ghost's wrapper provides
 * compatibility between C and C++ because restrict is not available in C++;
 * only compiler-specific extensions are supported.
 */
#endif

/* Use the standard C99 keyword */
#ifndef ghost_has_ghost_restrict
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            /* https://en.cppreference.com/w/c/language/restrict */
            #define ghost_restrict restrict
            #define ghost_has_ghost_restrict 1
        #endif
    #endif
#endif

/* Use a compiler extension (in C++) */
#ifndef ghost_has_ghost_restrict
    #if defined(_MSC_VER)
        /* Microsoft
         *     https://docs.microsoft.com/en-us/cpp/cpp/extension-restrict
         * Note that this is different from C99 restrict: it doesn't propagate.
         * If you assign a __restrict variable to a non-__restrict variable,
         * the non-__restrict variable can be aliased. C99 restrict is stronger
         * but it isn't available in C++. */
        #define ghost_restrict __restrict
        #define ghost_has_ghost_restrict 1
    #elif defined(__GNUC__)
        /* GCC and friends
         *     https://gcc.gnu.org/onlinedocs/gcc/Restricted-Pointers.html */
        #define ghost_restrict __restrict__
        #define ghost_has_ghost_restrict 1
    #endif
#endif

/* Omitting restrict is harmless so we define it to nothing. */
#ifndef ghost_has_ghost_restrict
    #define ghost_restrict /*nothing*/
    #define ghost_has_ghost_restrict 1
#endif

#endif
