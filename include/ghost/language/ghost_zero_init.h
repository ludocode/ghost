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

#ifndef GHOST_ZERO_INIT_H_INCLUDED
#define GHOST_ZERO_INIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_ZERO_INIT
 *
 * Zero-initializes a struct, union, or array of scalars in C and C++.
 *
 * Suppose you have a struct with typedef `foo_t`. Traditionally, you would
 * zero-initialize it in C like this:
 *
 *     foo_t foo = {0};
 *
 * or in C++ like this:
 *
 *     foo_t foo = {};
 *
 * Neither syntax works in all versions of both languages so Ghost provides
 * this abstraction. To make your code portable to both C and C++, do this
 * instead:
 *
 *     foo_t foo = GHOST_ZERO_INIT;
 *
 * Note that C23 will support the C++ syntax. This is also properly supported
 * in C++ on modern compilers (e.g. GCC 5+, Clang 4+.) If you are only
 * supporting these language standards, just use {}.
 */
#endif

#ifndef ghost_has_GHOST_ZERO_INIT
    #ifdef GHOST_ZERO_INIT
        #define ghost_has_GHOST_ZERO_INIT 1
    #endif
#endif

/* C23 will support the C++ {} syntax. */
#ifndef ghost_has_GHOST_ZERO_INIT
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 202000L && GHOST_IMPL_ENABLE_C23
            #define GHOST_ZERO_INIT {}
            #define ghost_has_GHOST_ZERO_INIT 1
        #endif
    #endif
#endif

/*
 * The C++11 standard explicitly supports {} as zero-initialization for POD
 * types and default-initialization otherwise. This was considered a defect
 * resolution in C++, not a new feature; this behaviour is well supported by
 * compilers on older language standards so we enable it in all versions of
 * C++.
 *
 * Versions of GCC before 5 warn with -Wmissing-field-initializers if a POD
 * struct is initialized in C++ with {}. There are many bug reports about this,
 * for example:
 *
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=55805
 *
 * Unfortunately there is no way to work around it. (The trick with Clang below
 * does not work because these old versions of GCC don't support _Pragma within
 * expressions.) You should probably disable this warning on such old
 * compilers.
 */
#ifndef ghost_has_GHOST_ZERO_INIT
    #ifdef __cplusplus
        #define GHOST_ZERO_INIT {}
        #define ghost_has_GHOST_ZERO_INIT 1
    #endif
#endif

/*
 * Old versions of Clang warn with -Wmissing-field-initializers when compiling
 * C code if the C-style initialization syntax is nested within another struct
 * (TODO add a unit test for this and example here.)
 *
 * Instead we use the C++-style syntax and disable the GCC extension warning.
 * (Unfortunately __extension__ doesn't work here.)
 */
#ifndef ghost_has_GHOST_ZERO_INIT
    #ifdef __clang__
        /* TODO nail down the exact version */
        /* TODO this version check won't work on Clang forks like Apple Clang
         * which have their own versioning. We'll need a better way to detect
         * this bug. */
        #if __clang_major__ <= 3 && !defined(__APPLE__)
            #define GHOST_ZERO_INIT \
                _Pragma("GCC diagnostic push") \
                _Pragma("GCC diagnostic ignored \"-Wgnu-empty-initializer\"") \
                {} \
                _Pragma("GCC diagnostic pop")
            #define ghost_has_GHOST_ZERO_INIT 1
        #endif
    #endif
#endif

/* C-style syntax pre-C23 is {0}. */
#ifndef ghost_has_GHOST_ZERO_INIT
    #define GHOST_ZERO_INIT {0}
    #define ghost_has_GHOST_ZERO_INIT 1
#endif

#endif
