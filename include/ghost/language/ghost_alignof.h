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

#ifndef GHOST_ALIGNOF_H_INCLUDED
#define GHOST_ALIGNOF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_alignof(T)
 *
 * Get the power-of-two alignment requirement of a type.
 */
#endif

#ifndef ghost_has_ghost_alignof
    #ifdef ghost_alignof
        #define ghost_has_ghost_alignof 1
    #endif
#endif

/* We don't use C23 alignof because it's a predefined macro to _Alignof so it
 * could technically be defined to something else. */

/* C11 _Alignof */
#ifndef ghost_has_ghost_alignof
    #ifdef __STDC_VERSION__
        #if __STDC_VERSION__ >= 201112L
            /* https://en.cppreference.com/w/c/language/_Alignof */
            #define ghost_alignof(T) _Alignof(T)
            #define ghost_has_ghost_alignof 1
        #endif
    #endif
#endif

/* C++11 alignof */
#ifndef ghost_has_ghost_alignof
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            /* https://en.cppreference.com/w/cpp/language/alignof */
            #define ghost_alignof(T) alignof(T)
            #define ghost_has_ghost_alignof 1
        #endif
    #endif
#endif

/* GNU-style __alignof__ */
#ifndef ghost_has_ghost_alignof
    #if defined(__GNUC__) || defined(__TINYC__)
        /* This actually returns preferred alignment rather than minimum as of
         * GCC 8, but without a standard alignof it's the best we've got:
         *     https://www.gnu.org/software/gcc/gcc-8/porting_to.html */
        #define ghost_alignof(T) __alignof__(T)
        #define ghost_has_ghost_alignof 1
    #endif
#endif

/* MSVC __alignof */
#ifndef ghost_has_ghost_alignof
    #ifdef _MSC_VER
        /* https://docs.microsoft.com/en-us/cpp/cpp/alignof-operator#microsoft-specific */
        #define ghost_alignof(T) __alignof(T)
        #define ghost_has_ghost_alignof 1
    #endif
#endif

/* Without any of the above, we don't have a definition of ghost_alignof. */
#ifndef ghost_has_ghost_alignof
    #define ghost_has_ghost_alignof 0
#endif

#endif
