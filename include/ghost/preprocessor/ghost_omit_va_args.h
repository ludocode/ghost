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

#ifndef GHOST_OMIT_VA_ARGS_H_INCLUDED
#define GHOST_OMIT_VA_ARGS_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO fix name, make it match ghost_pp_va_args somehow (make them both the same) */

/**
 * @def GHOST_OMIT_VA_ARGS
 *
 * Expands to 1 if the preprocessor allows omitting a variadic argument to a
 * function-like macro without warning, or 0 if it might not.
 *
 * Example:
 *
 *     #define FIRST(x, ...) x
 *     FIRST(0)
 *
 * The above is not legal C11 or C++17. At least one argument must be provided
 * for `...`. It has become legal in C++20 but not in C (yet.) Several
 * compilers support it as an extension, though they may still warn about it.
 *
 * Ghost detects such compilers here. This only expands to 1 if the compiler
 * supports it without warning.
 *
 * You can pre-define this to 1 or 0 if you want to override Ghost's compiler
 * detection.
 *
 * GHOST_FIRST() and GHOST_REST() are among the macros that use this. Turning
 * this on (if it isn't already) can give much nicer error messages from macro
 * usage. It can also increase or remove limits on the number of parameters
 * allowed for some macros.
 *
 * This is mostly an implementation detail of Ghost but you may find it useful
 * for your own code.
 *
 * Note that this is unrelated to the traditional MSVC preprocessor requirement
 * that when passing a single argument to a macro, that argument cannot be
 * blank. See GHOST_NOTHING, GHOST_MSVC_TRADITIONAL, etc.
 */

#ifndef ghost_has_GHOST_OMIT_VA_ARGS
    #ifdef GHOST_OMIT_VA_ARGS
        #define ghost_has_GHOST_OMIT_VA_ARGS 1
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_OMIT_VA_ARGS
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define GHOST_OMIT_VA_ARGS 0
        #define ghost_has_GHOST_OMIT_VA_ARGS 1
    #endif
#endif

/* In C++20, variadic macros are allowed to be called without a variadic
 * argument. */
#ifndef ghost_has_GHOST_OMIT_VA_ARGS
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 202002L
            #define GHOST_OMIT_VA_ARGS 1
            #define ghost_has_GHOST_OMIT_VA_ARGS 1
        #endif
    #endif
#endif

/*
 * MSVC 2019 16.5 has backported the C++20 behaviour to C++14 and C++17
 * under the new conforming preprocessor.
 *
 * TODO test what the old preprocessor does, maybe it works there too?
 *     https://docs.microsoft.com/en-us/cpp/preprocessor/preprocessor-experimental-overview
 */
#ifndef ghost_has_GHOST_OMIT_VA_ARGS
    /* TODO testing where in MSVC this is legal */
    #ifdef _MSC_VER
        #define GHOST_OMIT_VA_ARGS 1
        #define ghost_has_GHOST_OMIT_VA_ARGS 1
    #endif

/*
    #if defined(__cplusplus) && defined(_MSC_VER) && defined(_MSVC_TRADITIONAL)
        #if _MSC_VER >= 1925 && _MSVC_TRADITIONAL == 0 && ghost_cplusplus >= 201402L
            #define GHOST_OMIT_VA_ARGS 1
            #define ghost_has_GHOST_OMIT_VA_ARGS 1
        #endif
    #endif
    */
#endif

/*
 * GCC also supports the above as an extension but warns about in under certain
 * conditions.
 *
 * As of GCC 8, if a -std=gnu* option is enabled (the default), the use of this
 * extension emits no pedantic warnings. However, if compiling under -std=c*
 * and -Wpedantic, GCC emits:
 *
 *     warning: ISO C99 requires at least one argument for the "..." in a variadic macro
 *
 * In versions of GCC <=7, GCC always reported the above warning under any
 * language standard.
 *
 * We cannot detect whether -Wpedantic is on, and if it is, there is no
 * reasonable way to silence this warning. We therefore detect whether -std=c*
 * is being used based on the value of __STRICT_ANSI__. If defined and
 * non-zero, or we are GCC <=7, we avoid the extension to prevent pedantic
 * warnings.
 */
#ifndef ghost_has_GHOST_OMIT_VA_ARGS
    #include "ghost/detect/ghost_gcc.h"
    #if GHOST_GCC
        #if __GNUC__ <= 7
            #define GHOST_OMIT_VA_ARGS 0
        #elif defined __STRICT_ANSI__
            #if __STRICT_ANSI__ != 0
                #define GHOST_OMIT_VA_ARGS 0
            #else
                #define GHOST_OMIT_VA_ARGS 1
            #endif
        #else
            #define GHOST_OMIT_VA_ARGS 1
        #endif
        #define ghost_has_GHOST_OMIT_VA_ARGS 1
    #endif
#endif

/*
 * Clang also supports this extension but in language standards where it isn't
 * officially supported (e.g. C++20) -Wpedantic enables
 * -Wgnu-zero-variadic-macro-arguments which triggers the warning:
 *
 *     warning: must specify at least one argument for ‘…’ parameter of variadic macro
 *
 * This occurs under both -std=c* and -std=gnu* options. Since we don't know
 * whether this warning is on (and warnings can be turned off and on later
 * anyway) we can't rely on the extension under any circumstances. We can work
 * around it anyway so we don't need it.
 */

/* TinyCC supports the extension. */
#ifndef ghost_has_GHOST_OMIT_VA_ARGS
    #ifdef __TINYC__
        #define GHOST_OMIT_VA_ARGS 1
        #define ghost_has_GHOST_OMIT_VA_ARGS 1
    #endif
#endif

/* Otherwise we assume it's not supported. */
#ifndef ghost_has_GHOST_OMIT_VA_ARGS
    #define GHOST_OMIT_VA_ARGS 0
    #define ghost_has_GHOST_OMIT_VA_ARGS 1
#endif

#endif
