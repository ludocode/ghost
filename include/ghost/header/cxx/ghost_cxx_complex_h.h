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

#ifndef GHOST_CXX_COMPLEX_H_H_INCLUDED
#define GHOST_CXX_COMPLEX_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes C++ <complex> if possible.
 *
 * https://en.cppreference.com/w/cpp/numeric/complex
 * https://docs.microsoft.com/en-us/cpp/standard-library/complex
 */

/* C++ only. */
#ifndef ghost_has_ghost_cxx_complex_h
    #ifndef __cplusplus
        #define ghost_has_ghost_cxx_complex_h 0
    #endif
#endif

/* Any platforms that fail the below test should be disabled explicitly here. */

/* Complex numbers in C++ can be implemented purely as templates without
 * special compiler support so they should be available as part of any STL
 * library. */
#ifndef ghost_has_ghost_cxx_complex_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        /* If we can check, we check. */
        #if __has_include(<complex>)
            #include <complex>
            #define ghost_has_ghost_cxx_complex_h 1
        #else
            #define ghost_has_ghost_cxx_complex_h 0
        #endif
    #else
        /* Otherwise we assume it exists if we're hosted. A freestanding
         * implementation might not have the STL, and even if they do they're
         * highly unlikely to need complex numbers. */
        #include "ghost/language/ghost_hosted.h"
        #if GHOST_HOSTED
            #include <complex>
            #define ghost_has_ghost_cxx_complex_h 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_cxx_complex_h
    #define ghost_has_ghost_cxx_complex_h 0
#endif

#endif
