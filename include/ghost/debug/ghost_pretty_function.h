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

#ifndef GHOST_PRETTY_FUNCTION_H_INCLUDED
#define GHOST_PRETTY_FUNCTION_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_PRETTY_FUNCTION
 *
 * Evaluates to a `const char*` string containing the name of the containing
 * function, ideally human-readable.
 *
 * The format of the string differs based on the platform. This is mainly for
 * C++ to indicate template parameters and differentiate between overloads but
 * the parameters may still be given even when compiling as C. Don't try to
 * parse this string.
 *
 * Note that this is not a string literal. You cannot use string concatenation
 * on it nor use sizeof to get its length.
 */
#endif

/* We cast all cases to `const char*` (unless they are already.) This ensures
 * that the user won't do something that works only on one compiler and not
 * another (like string concatenation or sizeof). */

#ifndef ghost_has_GHOST_PRETTY_FUNCTION
    #ifdef GHOST_PRETTY_FUNCTION
        #define ghost_has_GHOST_PRETTY_FUNCTION 1
    #endif
#endif

/* Try to use the non-standard GNU __PRETTY_FUNCTION__ or MSVC __FUNCSIG__. */
#ifndef ghost_has_GHOST_PRETTY_FUNCTION
    #ifdef __GNUC__
        /* GCC and Clang support __PRETTY_FUNCTION__ in both C and C++ but the
         * behaviour is different: in C it's the same as __func__ while in C++
         * it's the full signature even if the function is extern "C". In any
         * case in C it causes -Wpedantic warnings from GCC so we avoid it. */
        #ifdef __cplusplus
            #include "ghost/language/ghost_static_cast.h"
            #define GHOST_PRETTY_FUNCTION ghost_static_cast(const char*, __PRETTY_FUNCTION__)
            #define ghost_has_GHOST_PRETTY_FUNCTION 1
        #endif
    #elif defined(_MSC_VER)
        /* MSVC __FUNCSIG__ is a full signature in both C and C++. */
        #include "ghost/language/ghost_static_cast.h"
        #define GHOST_PRETTY_FUNCTION ghost_static_cast(const char*, __FUNCSIG__)
        #define ghost_has_GHOST_PRETTY_FUNCTION 1
    #endif
#endif

/* In C++20 we use source_location. This isn't necessarily a pretty name so we
 * prefer our compiler-specific symbols above. (In GCC/Clang this returns the
 * same as __PRETTY_FUNCTION__ but in MSVC this returns the same as __func__.) */
#ifndef ghost_has_GHOST_PRETTY_FUNCTION
    #include "ghost/header/cxx/ghost_cxx_version_h.h"
    #ifdef __cpp_lib_source_location
        #if __cpp_lib_source_location >= 201907L
            /* https://en.cppreference.com/w/cpp/utility/source_location
             * https://en.cppreference.com/w/cpp/utility/source_location/function_name
             * TODO make header ghost_cxx_source_location.h */
            #include <source_location>
            #define GHOST_PRETTY_FUNCTION (::std::source_location::current().function_name())
            #define ghost_has_GHOST_PRETTY_FUNCTION 1
        #endif
    #endif
#endif

/* In C99 or C++11 we can use the standard __func__. */
#ifndef ghost_has_GHOST_PRETTY_FUNCTION
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            /* https://en.cppreference.com/w/cpp/language/function */
            #include "ghost/language/ghost_static_cast.h"
            #define GHOST_PRETTY_FUNCTION ghost_static_cast(const char*, __func__)
            #define ghost_has_GHOST_PRETTY_FUNCTION 1
        #endif
    #elif defined(__STDC_VERSION__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            /* https://en.cppreference.com/w/c/language/function_definition */
            #include "ghost/language/ghost_static_cast.h"
            #define GHOST_PRETTY_FUNCTION ghost_static_cast(const char*, __func__)
            #define ghost_has_GHOST_PRETTY_FUNCTION 1
        #endif
    #endif
#endif

/* cparser uses __FUNCTION__, not __func__. Some old versions of GCC (<4) did
 * as well; we can add support for them here if needed. */
#ifndef ghost_has_GHOST_PRETTY_FUNCTION
    #ifdef __CPARSER__
        #include "ghost/language/ghost_static_cast.h"
        #define GHOST_PRETTY_FUNCTION ghost_static_cast(const char*, __FUNCTION__)
        #define ghost_has_GHOST_PRETTY_FUNCTION 1
    #endif
#endif

/* In other GNU C compilers we can use __func__ even in C89 or C++98. */
#ifndef ghost_has_GHOST_PRETTY_FUNCTION
    #ifdef __GNUC__
        #include "ghost/language/ghost_static_cast.h"
        #define GHOST_PRETTY_FUNCTION ghost_static_cast(const char*, __extension__ __func__)
        #define ghost_has_GHOST_PRETTY_FUNCTION 1
    #endif
#endif

/* Otherwise we don't have this. */
#ifndef ghost_has_GHOST_PRETTY_FUNCTION
    #define ghost_has_GHOST_PRETTY_FUNCTION 0
#endif

#endif
