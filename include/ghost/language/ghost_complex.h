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

#ifndef GHOST_COMPLEX_H_INCLUDED
#define GHOST_COMPLEX_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO move this and header ghost_complex_h.h and ghost_cxx_complex_h.h to experimental */

#if GHOST_DOCUMENTATION
/**
 * @def ghost_complex(Type) Type _Complex or std::complex<Type>
 *
 * A complex number type.
 *
 * This wraps either C99 _Complex or C++ std::complex<> under the assumption
 * that they are bridged between language standards. Check `#if
 * ghost_has(ghost_complex)` to see if complex numbers are supported.
 *
 * In C++, std::complex<> is preferred but if it is unavailable, _Complex may
 * be used as a compiler extension.
 *
 * This does not include `<complex.h>`. (It is in theory possible for a
 * compiler to support _Complex without supporting any complex library
 * functions, for example in a freestanding environment.) To see if complex
 * functions are available:
 *
 * - In C, include `ghost/header/c/ghost_complex_h.h` and check `#if ghost_has(ghost_complex_h)`;
 * - In C++, include `ghost/header/cxx/ghost_cxx_complex_h.h` and check `#if ghost_has(ghost_cxx_complex_h)`.
 */
#endif

#ifndef ghost_has_ghost_complex
    #ifdef ghost_complex
        #define ghost_has_ghost_complex
    #endif
#endif

/* C++ supports std::complex<> if <complex> exists. */
#ifndef ghost_has_ghost_complex
    #ifdef __cplusplus
        #include "ghost/header/cxx/ghost_cxx_complex_h.h"
        #if ghost_has(ghost_cxx_complex_h)
            #define ghost_complex(T) ::std::complex<T>
            #define ghost_has_ghost_complex 1
        #endif
    #endif
#endif

/*
 * C11 implementations can define __STDC_NO_COMPLEX__ to disable complex number
 * support. We allow this macro to also be used by implementations to disable
 * complex numbers in other versions of C.
 *
 * MSVC in C mode and chibicc currently define this.
 *
 * We don't check this in C++ (as long as <complex> exists) because a C++
 * compiler could in theory define this to indicate that it does not support
 * _Complex while still supporting std::complex<>.
 */
#ifndef ghost_has_ghost_complex
    #ifdef __STDC_NO_COMPLEX__
        #define ghost_has_ghost_complex 0
    #endif
#endif

/* TinyCC and lacc claim to support C11 and do not define __STDC_NO_COMPLEX__
 * but they nevertheless do not support complex numbers. */
#ifndef ghost_has_ghost_complex
    #if defined(__TINYC__) || defined(__lacc__)
        #define ghost_has_ghost_complex 0
    #endif
#endif

/* GCC and Clang support _Complex as an extension in all language standards,
 * even C++.
 *
 * Some other __GNUC__ compilers probably do as well. (NVidia? Intel?) If so we
 * can add them here.  */
#ifndef ghost_has_ghost_complex
    #ifdef __clang__
        #define ghost_complex(T) T _Complex
        #define ghost_has_ghost_complex 1
    #elif defined __GNUC__
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define ghost_complex(T) T _Complex
            #define ghost_has_ghost_complex 1
        #endif
    #endif
#endif

/* _Complex is only supported as of C99 and is not officially supported in any
 * C++ language standard. */
#ifndef ghost_has_ghost_complex
    #ifndef __cplusplus
        #ifdef __STDC_VERSION__
            #include "ghost/language/ghost_stdc_version.h"
            #if GHOST_STDC_VERSION >= 199901L
                #define ghost_complex(T) T _Complex
                #define ghost_has_ghost_complex 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we don't have it. */
#ifndef ghost_has_ghost_complex
    #define ghost_has_ghost_complex 0
#endif

#endif
