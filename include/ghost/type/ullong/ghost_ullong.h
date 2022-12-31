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

#ifndef GHOST_ULLONG_H_INCLUDED
#define GHOST_ULLONG_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_has_ghost_ullong 1
 *
 * Defined to 1 if `unsigned long long` exists and 0 otherwise.
 *
 * Test `#if ghost_has(ghost_ullong)` to check whether `unsigned long long`
 * exists.
 */

/**
 * A typedef for `unsigned long long`.
 *
 * This may silence pedantic warnings about using a `long long` extension in
 * older language standards.
 *
 * Note that other uses of extensions related to `long long` will still cause
 * warnings, for example the LL suffix on integers, the __LONG_LONG_MAX__
 * constant, etc. You probably want to disable the -Wlong-long warning on GNU C
 * compilers if you want to use `long long` on older language standards.
 *
 * @see GHOST_SILENCE_LONG_LONG
 */
typedef long long ghost_ullong;
#define ghost_has_ghost_ullong 1
#endif

#ifndef ghost_has_ghost_ullong
    #ifdef ghost_ullong
        #define ghost_has_ghost_ullong 1
    #endif
#endif

/* C99 has long long */
#ifndef ghost_has_ghost_ullong
    #if defined(__STDC_VERSION__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            typedef unsigned long long ghost_ullong;
            #define ghost_has_ghost_ullong 1
        #endif
    #endif
#endif

/* C++11 has long long */
#ifndef ghost_has_ghost_ullong
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            typedef unsigned long long ghost_ullong;
            #define ghost_has_ghost_ullong 1
        #endif
    #endif
#endif

/* MSVC has long long as an extension in older language standards */
#ifndef ghost_has_ghost_ullong
    #ifdef _MSC_VER
        typedef unsigned long long ghost_ullong;
        #define ghost_has_ghost_ullong 1
    #endif
#endif

/*
 * In some GNU C compilers `long long` is supported as an extension even in
 * ANSI C.
 *
 * When compiling as ANSI C, use of `long long` throws a pedantic warning in
 * both GCC and Clang. We can use __extension__ to silence it for our typedef
 * which can then be used without warning. If you want to use `long long`
 * normaully with -Wpedantic, you should probably silence -Wlong-long.
 *
 * We're going to assume that any compiler that defines __GNUC__ also supports
 * both __extension__ and `long long` unless we know otherwise.
 */
#ifndef ghost_has_ghost_ullong
    #ifdef __GNUC__
        __extension__ typedef unsigned long long ghost_ullong;
        #define ghost_has_ghost_ullong 1
    #endif
#endif

/* Otherwise we don't have unsigned long long. */
#ifndef ghost_has_ghost_ullong
    #define ghost_has_ghost_ullong 0
#endif

#endif
