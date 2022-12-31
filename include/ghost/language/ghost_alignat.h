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

#ifndef GHOST_ALIGNAT_H_INCLUDED
#define GHOST_ALIGNAT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_alignat(n)
 *
 * Align a declaration at a multiple of the given numerical alignment or, on
 * modern compilers, as the given type.
 *
 * C11 and C++11 allow alignas to take either a numerical expression or a type.
 * Older compiler extensions for specifying alignment do not. Ghost separates
 * these two concepts for better portability.
 *
 * ghost_alignat(n) is for specifying a numerical alignment, not for aligning as
 * a type. Don't pass the result of sizeof() to this because this is not
 * supported on all compilers. To align as a type, prefer ghost_alignas(T).
 *
 * @see ghost_alignas
 */
#endif

#ifndef ghost_has_ghost_alignat
    #ifdef ghost_alignat
        #define ghost_has_ghost_alignat 1
    #endif
#endif

/* We don't use C23 alignas because it's a predefined macro to _Alignas so it
 * could technically be defined to something else. */

/* PCC has _Alignas but it doesn't seem to do anything. For now we just disable it. */
#ifndef ghost_has_ghost_alignat
    #ifdef __PCC__
        #define ghost_has_ghost_alignat 0
    #endif
#endif

/* C11 _Alignas
 * (TinyCC also supports this even though it sets __STDC_VERSION__ to C99.) */
#ifndef ghost_has_ghost_alignat
    #ifdef __STDC_VERSION__
        #if __STDC_VERSION__ >= 201112L || defined(__TINYC__)
            /* https://en.cppreference.com/w/c/language/_Alignas */
            #define ghost_alignat(n) _Alignas(n)
            #define ghost_has_ghost_alignat 1
        #endif
    #endif
#endif

/* C++11 alignof, alignas
 *     https://en.cppreference.com/w/cpp/language/alignas */
#ifndef ghost_has_ghost_alignat
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #include "ghost/detect/ghost_gcc.h"
            #if GHOST_GCC
                /* GCC 4.7 only supports types in alignas(), not values. It will
                 * fallback to the old-style __attribute__((__aligned__(n))) below. */
                #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 7)
                    #define ghost_alignat(n) alignas(n)
                    #define ghost_has_ghost_alignat 1
                #endif
            #else
                #define ghost_alignat(n) alignas(n)
                #define ghost_has_ghost_alignat 1
            #endif
        #endif
    #endif
#endif

/* GNU-style __attribute__((__aligned__(n)))
 * (TinyCC claims to support this as well but it doesn't appear to actually
 * work. Thankfully _Alignas above does in fact work.) */
#ifndef ghost_has_ghost_alignat
    #if defined(__GNUC__) || defined(__TINYC__)
        /* https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html */
        #define ghost_alignat(n) __attribute__((__aligned__(n)))
        #define ghost_has_ghost_alignat 1
    #endif
#endif

/* MSVC 2015 backports alignas() to C++98 */
#ifndef ghost_has_ghost_alignas
    #ifdef _MSC_VER
        #if _MSC_VER >= 1900
            #define ghost_alignas(T) alignas(T)
            #define ghost_has_ghost_alignas 1
        #endif
    #endif
#endif

/* MSVC __declspec(align(n)) */
#ifndef ghost_has_ghost_alignat
    #ifdef _MSC_VER
        /* https://docs.microsoft.com/en-us/cpp/cpp/align-cpp */
        #define ghost_alignat(n) __declspec(align(n))
        #define ghost_has_ghost_alignat 1
    #endif
#endif

/* Without any of the above, we don't have a definition of ghost_alignat. */
#ifndef ghost_has_ghost_alignat
    #define ghost_has_ghost_alignat 0
#endif

#endif
