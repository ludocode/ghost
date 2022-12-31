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

#ifndef GHOST_ALIGNAS_H_INCLUDED
#define GHOST_ALIGNAS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_alignas(T)
 *
 * Align a declaration as the given type or, on modern compilers, at a multiple
 * of the given power-of-two numerical alignment.
 *
 * C11 and C++11 allow alignas to take either a numerical expression or a type.
 * Older compiler extensions for specifying alignment do not. Ghost separates
 * these two concepts for better portability.
 *
 * On modern compilers this will take a numerical alignment as well as a type.
 * If you want your code to support old or non-standard compilers, prefer
 * ghost_alignat(n) for numerical alignment.
 *
 * ghost_alignat(n) is more likely to be supported than ghost_alignas(T) on
 * older compilers.
 *
 * @see ghost_alignat
 */
#endif

#ifndef ghost_has_ghost_alignas
    #ifdef ghost_alignas
        #define ghost_has_ghost_alignas 1
    #endif
#endif

/* We don't use C23 alignas because it's a predefined macro to _Alignas so it
 * could technically be defined to something else. */

/* PCC has _Alignas but it doesn't seem to do anything. For now we just disable it. */
#ifndef ghost_has_ghost_alignas
    #ifdef __PCC__
        #define ghost_has_ghost_alignas 0
    #endif
#endif

/* C11 _Alignas
 * (TinyCC also supports this even though it sets __STDC_VERSION__ to C99.) */
#ifndef ghost_has_ghost_alignas
    #ifdef __STDC_VERSION__
        #if (__STDC_VERSION__ >= 201112L) || defined(__TINYC__)
            #define ghost_alignas(T) _Alignas(T)
            #define ghost_has_ghost_alignas 1
        #endif
    #endif
#endif

/* C++11 alignas */
#ifndef ghost_has_ghost_alignas
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define ghost_alignas(T) alignas(T)
            #define ghost_has_ghost_alignas 1
        #endif
    #endif
#endif

/* GNU-style combining attribute aligned with alignof */
#ifndef ghost_has_ghost_alignas
    #if defined(__GNUC__)
        #define ghost_alignas(T) __attribute__((__aligned__(__alignof__(T))))
        #define ghost_has_ghost_alignas 1
    #endif
#endif

/* MSVC 2015 backports alignas() to C++98 in C++ mode */
#ifndef ghost_has_ghost_alignas
    #if defined(_MSC_VER) && defined(__cplusplus)
        #if _MSC_VER >= 1900
            #define ghost_alignas(T) alignas(T)
            #define ghost_has_ghost_alignas 1
        #endif
    #endif
#endif

/*
 * MSVC does not allow the equivalent of the GNU construction above.
 *
 *     __declspec(align(__alignof(T)))  // doesn't work!
 *
 * This is one reason why Ghost separates ghost_alignas() from ghost_alignat().
 *
 * It looks like this bug/limitation has been around forever:
 *
 *     https://godbolt.org/z/1f7oWj
 *     https://stackoverflow.com/questions/5134217/aligning-data-on-the-stack-c
 *
 * MSVC 2019 and later support _Alignas in C11 mode. Outside of that, aligning
 * as a type doesn't appear to be possible in C under any previous version of
 * MSVC. If you desperately need it, you'll have to compile your code as C++.
 */

/* Without any of the above, we don't have a definition of ghost_alignas. */
#ifndef ghost_has_ghost_alignas
    #define ghost_has_ghost_alignas 0
#endif

#endif
