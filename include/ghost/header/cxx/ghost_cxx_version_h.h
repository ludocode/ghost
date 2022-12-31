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

#ifndef GHOST_CXX_VERSION_H_H_INCLUDED
#define GHOST_CXX_VERSION_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Include C++ standard library feature-testing macros from a header like
 * <version>.
 *
 * This doesn't guarantee that any particular macros will be available. It just
 * tries to include them if possible.
 *
 *     https://en.cppreference.com/w/cpp/feature_test
 */

/* C++ only. */
#ifndef ghost_has_ghost_cxx_version_h
    #ifndef __cplusplus
        #define ghost_has_ghost_cxx_version_h 0
    #endif
#endif

/* Include C++20 <version> */
#ifndef ghost_has_ghost_cxx_version_h
    #ifdef __cplusplus
        /*
         * If we can check whether <version> exists, we check, which will
         * support backporting it from a new C++ standard library to an older
         * language standard. If we can't check, it only becomes required under
         * C++20 so that's what we require.
         *
         *     https://en.cppreference.com/w/cpp/header/version
         */
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<version>)
                #include <version>
                #define ghost_has_ghost_cxx_version_h 1
            #endif
        #else
            #include "ghost/language/ghost_cplusplus.h"
            #if ghost_cplusplus >= 202002L
                #include <version>
                #define ghost_has_ghost_cxx_version_h 1
            #endif
        #endif
    #endif
#endif

/* Include an older fallback */
#ifndef ghost_has_ghost_cxx_version_h
    #ifdef __cplusplus
        /*
         * <ciso646> is apparently commonly used to get feature-testing macros
         * in C++ because it otherwise does nothing. The declarations in the
         * corresponding C header <iso646.h> are all keywords in C++.
         *
         *     https://en.cppreference.com/w/cpp/header/ciso646
         *
         * If we can check whether it exists, we check; otherwise we include it
         * unconditionally.
         *
         * We do not ever include <iso646.h> in C because we don't want to
         * pollute non-C++ code with those disgusting macros.
         */
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<ciso646>)
                #include <ciso646>
                #define ghost_has_ghost_cxx_version_h 1
            #endif
        #else
            #include <ciso646>
            #define ghost_has_ghost_cxx_version_h 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_cxx_version_h
    #define ghost_has_ghost_cxx_version_h 0
#endif

#endif
