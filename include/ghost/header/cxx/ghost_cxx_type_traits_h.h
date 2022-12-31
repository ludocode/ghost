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

#ifndef GHOST_CXX_TYPE_TRAITS_H_H_INCLUDED
#define GHOST_CXX_TYPE_TRAITS_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes C++ <type_traits> if possible.
 *
 * https://en.cppreference.com/w/cpp/header/type_traits
 */

/* C++ only. */
#ifndef ghost_has_ghost_cxx_type_traits_h
    #ifndef __cplusplus
        #define ghost_has_ghost_cxx_type_traits_h 0
    #endif
#endif

/* If we can check whether it exists, we check. */
#ifndef ghost_has_ghost_cxx_type_traits_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<type_traits>)
            #include <type_traits>
            #define ghost_has_ghost_cxx_type_traits_h 1
        #else
            #define ghost_has_ghost_cxx_type_traits_h 0
        #endif
    #endif
#endif

/* <type_traits> is available as of C++11 and it's required even in
 * freestanding. */
#ifndef ghost_has_ghost_cxx_type_traits_h
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #include <type_traits>
            #define ghost_has_ghost_cxx_type_traits_h 1
        #endif
    #endif
#endif

/* Otherwise we don't have it. */
#ifndef ghost_has_ghost_cxx_type_traits_h
    #define ghost_has_ghost_cxx_type_traits_h 0
#endif

#endif
