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

#ifndef GHOST_PP_VA_ARGS_H_INCLUDED
#define GHOST_PP_VA_ARGS_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_PP_VA_ARGS
 *
 * Expands to 1 if the preprocessor supports variadic macros (i.e. `...` and
 * `__VA_ARGS__`) or 0 otherwise.
 *
 * Variadic macros are required as of the C99 and C++98 standards. They are not
 * supported in ANSI C89/C90 but they are implemented as an extension in many
 * compilers.
 */

/*
 * TODO explain the situation with newer C standards requiring lax macro
 * parsing in disabled sections but older C not necessarily supporting this,
 * there is other docs somewhere in Ghost that also discusses it
 */

#ifndef ghost_has_GHOST_PP_VA_ARGS
    #ifdef GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_PP_VA_ARGS 1
    #endif
#endif

/* C has it since C99. */
#ifndef ghost_has_GHOST_PP_VA_ARGS
    #ifdef __STDC_VERSION__
        #if __STDC_VERSION__ >= 199901L
            #define GHOST_PP_VA_ARGS 1
            #define ghost_has_GHOST_PP_VA_ARGS 1
        #endif
    #endif
#endif

/* C++ has it since C++11. */
#ifndef ghost_has_GHOST_PP_VA_ARGS
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define GHOST_PP_VA_ARGS 1
            #define ghost_has_GHOST_PP_VA_ARGS 1
        #endif
    #endif
#endif

/* ANSI C89/C90 does not have it but several compilers support it as an
 * extension. */

/*
 * GCC supports this without warning in C89 or C++98 since GCC 5 as long as we
 * aren't compiling under __STRICT_ANSI__ (i.e. -std=gnu90 or -std=gnu++98, not
 * -std=c90 or -std=c++98 or -ansi.)
 *
 * (Under strict ANSI it still technically supports the extension but will warn
 * about it. We disable it to avoid these warnings.)
 */
#ifndef ghost_has_GHOST_PP_VA_ARGS
    #ifdef __GNUC__
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #if __GNUC__ >= 5
                #ifdef __STRICT_ANSI__
                    #if __STRICT_ANSI__
                        #define GHOST_PP_VA_ARGS 0
                    #else
                        #define GHOST_PP_VA_ARGS 1
                    #endif
                #else
                    #define GHOST_PP_VA_ARGS 1
                #endif
                #define ghost_has_GHOST_PP_VA_ARGS 1
            #endif
        #endif
    #endif
#endif

/* TODO clang? other GNU C compilers? Not using GHOST_GCC above */

/*
 * MSVC supports this since 2015. Ghost doesn't support any older versions.
 *
 * Note that old versions of MSVC do not have a conforming preprocessor. The
 * traditional MSVC preprocessor has lots of bugs especially around variadic
 * macros. Ghost tries to work around these where possible.
 *
 * See ghost_msvc_traditional.h for details.
 */
#ifndef ghost_has_GHOST_PP_VA_ARGS
    #if defined(_MSC_VER)
        #define GHOST_PP_VA_ARGS 1
    #else
        #define GHOST_PP_VA_ARGS 0
    #endif
    #define ghost_has_GHOST_PP_VA_ARGS 1
#endif

#endif
