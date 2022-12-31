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

#ifndef GHOST_COMPLEX_H_H_INCLUDED
#define GHOST_COMPLEX_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes <complex.h> if possible.
 *
 * https://en.cppreference.com/w/c/numeric/complex
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* This requires complex number support. */
#ifndef ghost_has_ghost_complex_h
    #include "ghost/language/ghost_complex.h"
    #if !ghost_has(ghost_complex)
        #define ghost_has_ghost_complex_h 0
    #endif
#endif

/*
 * In C++, complex number support is provided by <complex>. As of C++11,
 * <complex.h> was added for compatibility in C, but it only needs to be an
 * alias of <complex>. We backport this behaviour to C++98 by including
 * <complex>.
 */
#ifndef ghost_has_ghost_complex_h
    #ifdef __cplusplus
        #include "ghost/header/cxx/ghost_cxx_complex_h.h"
        #if !ghost_has(ghost_cxx_complex_h)
            #define ghost_has_ghost_complex_h 0
        #endif
    #endif
#endif
/*
 * Even if we included <complex>, we still try to include <complex.h> in C++
 * because it's possible it defines functions that work on a _Complex extension
 * and not just std::complex<>. Even if those checks fail though, we'll still
 * say <complex.h> has been included as long as <complex> has been included.
 */

/*
 * The header <ccomplex> was added in C++11 as a blank alias of <complex.h>. It
 * was deprecated in C++17 and removed in C++20 but <complex.h> was never
 * deprecated or removed. Nevertheless, some compilers (e.g. MSVC) give us an
 * incorrect deprecation warning against <complex.h>, not <ccomplex>. We
 * silence these warnings and include <complex.h> anyway, and we don't bother
 * with <ccomplex>.
 */
#ifdef _MSC_VER
    #include "ghost/silence/ghost_silence_push_pop.h"
    #include "ghost/silence/ghost_silence_deprecated.h"
    GHOST_SILENCE_PUSH
    GHOST_SILENCE_DEPRECATED
#endif

/* Try to test whether it exists if possible. */
#ifndef ghost_has_ghost_complex_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<complex.h>)
            #include <complex.h>
            #define ghost_has_ghost_complex_h 1
        #else
            #define ghost_has_ghost_complex_h 0
        #endif
    #endif
#endif

/*
 * Otherwise:
 * - In C we believe it exists since we have tested for complex number support
 *   above so we include it;
 * - In C++ we declare that it has been included already since we've included
 *   <complex> above.
 */
#ifndef ghost_has_ghost_complex_h
    #ifndef __cplusplus
        #include <complex.h>
    #endif
    #define ghost_has_ghost_complex_h 1
#endif

#ifdef _MSC_VER
    GHOST_SILENCE_POP
#endif

#endif
