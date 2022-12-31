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

#ifndef GHOST_CPLUSPLUS_H_INCLUDED
#define GHOST_CPLUSPLUS_H_INCLUDED

/* TODO move to ghost/preprocessor/? same with ghost_stdc_version? */

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_cplusplus __cplusplus
 *
 * A macro that specifies the C++ version in the style of __cplusplus, working
 * around compiler lies.
 *
 * Under Microsoft's compiler, this macro prefers the value of _MSVC_LANG
 * rather than __cplusplus, so it will report the correct version even if
 * /Zc:__cplusplus is not specified.
 *
 * Here's a table of known C++ versions:
 *
 * C++98: 199711L
 * C++03: 199711L (same as C++98)
 * C++11: 201103L
 * C++14: 201402L
 * C++17: 201703L
 * C++20: 202002L
 * C++23: TBD
 *
 * Note that C++03 primarily fixes defects in C++98, although it did introduce
 * the TR1 library which was eventually added to C++11 proper.
 *
 * And here's a lot more information: https://stackoverflow.com/a/56483887
 */
#endif

/* Allow override */
#ifndef ghost_has_ghost_cplusplus
    #ifdef ghost_cplusplus
        #define ghost_has_ghost_cplusplus 1
    #endif
#endif

/* See whether we're actually C++ */
#ifndef ghost_has_ghost_cplusplus
    #ifndef __cplusplus
        #define ghost_has_ghost_cplusplus 0
    #endif
#endif

/*
 * Microsoft lies!
 *     https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
 */
#ifndef ghost_has_ghost_cplusplus
    #ifdef _MSVC_LANG
        #define ghost_cplusplus _MSVC_LANG
        #define ghost_has_ghost_cplusplus 1
    #endif
#endif

/*
 * GCC 4.7 also lies.
 *
 * GCC 4.8 was the first version to support all C++11 language features.
 * Unfortunately, GCC 4.7 under -std=c++11 defines __cplusplus to the official
 * value 201103L despite not supporting several features like modern [[..]]
 * attributes, the "z" format length modifier, alignas(int), etc.
 *
 *     https://gcc.gnu.org/gcc-4.7/cxx0x_status.html
 *
 * There's an argument to be made here to define this to 199711L under GCC 4.7.
 * The problem with that is that it does support most C++11 features and some
 * of those cannot be safely disabled. For example r-value references were
 * added in GCC 4.3, and move constructors are probably one of the major
 * features protected by lines like `#if __cplusplus > 200000L`. Disabling
 * these would drastically alter the semantics of code.
 *
 * For now we let GCC 4.7 define it as it wants. If you care about C++11
 * support you probably aren't still supporting GCC 4.7 anyway. As for Ghost,
 * we manually check for the broken features internally (see e.g.
 * GHOST_IMPL_STANDARD_ATTRIBUTE, GHOST_IMPL_FORMAT_C99_SPECIFIERS, etc.)
 */

#ifndef ghost_has_ghost_cplusplus
    #define ghost_cplusplus __cplusplus
    #define ghost_has_ghost_cplusplus 1
#endif

#endif
