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

#ifndef GHOST_STATIC_ASSERT_H_INCLUDED
#define GHOST_STATIC_ASSERT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_static_assert(expression, message) static_assert(expression, message)
 *
 * A declaration that causes a compile error if the given compile-time constant
 * expression is false.
 *
 * The message is optional (provided the compiler supports variadic macros.)
 * When this triggers a compile error, the message will be emitted by the
 * compiler if provided and supported.
 *
 * This can only be used as a declaration. It must be followed by a semicolon.
 * It can be used at file or block scope, but not in an expression. If you want
 * a static assertion in an expression (for example in a comma operator as part
 * of a macro), use ghost_static_assert_expr().
 *
 * On modern compilers, this will wrap a built-in static_assert(), making the
 * message optional if it isn't already.
 *
 * On compilers or in older language standards that don't support a built-in
 * static_assert() mechanism, a compiler error is generated using an invalid
 * function declaration. This cannot be used inside the definition of a struct,
 * union or enum so avoid doing that if you intend to support pre-C11 or
 * pre-C++11 compilers.
 *
 * Read more here:
 *
 *     https://en.cppreference.com/w/c/language/_Static_assert
 *     https://en.cppreference.com/w/cpp/language/static_assert
 *
 * ghost_static_assert() is a macro, and the C preprocessor only considers
 * parentheses when ignoring nested commas. This means the following code will
 * cause compiler errors:
 *
 *     ghost_static_assert((int[2]){1,2}[0]); // error
 *     ghost_static_assert(std::is_same<int,int>::value); // C++ error
 *
 * These are both considered to pass two arguments to ghost_static_assert().
 * The preprocessor splits arguments on the comma, ignoring the surrounding
 * braces and angle brackets. To work around this, add an extra set of
 * parentheses around the condition. (ghost_assert() has the same limitation;
 * see its documentation for details.)
 *
 * @see ghost_assert
 * @see ghost_static_assert_expr
 *
 * TODO move to ghost/debug
 */
#endif

#include "ghost/language/ghost_static_cast.h"

#ifndef ghost_has_ghost_static_assert
    #ifdef ghost_static_assert
        #define ghost_has_ghost_static_assert 1
    #endif
#endif

/* Note that a lot of libcs (e.g. glibc, FreeBSD) define their own
 * _Static_assert macro on older compiler versions. We avoid them all. We only
 * use _Static_assert or static_assert where it is required by the language
 * standard so it is more likely to be a compiler intrinsic. */

/* First handle cases where the real static assert allows the message to be
 * optional. */

#ifndef ghost_has_ghost_static_assert
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        /* In C23 the message to _Static_assert is optional. static_assert is
         * also a predefined macro but we don't use it because it could
         * technically be defined to something else. */
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            /* https://en.cppreference.com/w/c/language/_Static_assert */
            #define ghost_static_assert _Static_assert
            #define ghost_has_ghost_static_assert 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_static_assert
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201703L
            /* https://en.cppreference.com/w/cpp/language/static_assert */
            #define ghost_static_assert static_assert
            #define ghost_has_ghost_static_assert 1
        #endif
    #endif
#endif

/* Next handle cases where static assert requires a message. We add one if the
 * user didn't supply one. (We keep this separate in order to keep the above
 * macros for modern compilers as simple as possible.) */

#ifndef ghost_has_ghost_static_assert
    #ifdef ghost_impl_static_assert_with_msg
        #error "ghost_impl_static_assert_with_msg cannot be pre-defined."
    #endif

    /* C11 added _Static_assert with required message */
    #ifndef ghost_impl_static_assert_with_msg
        #ifdef __STDC_VERSION__
            /* chibicc declares C11 support but doesn't support _Static_assert(). */
            #if GHOST_STDC_VERSION >= 201112L && !defined(__chibicc__)
                #define ghost_impl_static_assert_with_msg(expr, msg, ...) _Static_assert(expr, msg)
            #endif
        #endif
    #endif

    /* C++11 added static_assert with required message */
    #ifndef ghost_impl_static_assert_with_msg
        #ifdef __cplusplus
            #if ghost_cplusplus >= 201103L
                #define ghost_impl_static_assert_with_msg(expr, msg, ...) static_assert(expr, msg)
            #endif
        #endif
    #endif

    /* Visual C++ 2010 (version 10.0) supports static_assert() with message
     * (but only in C++) */
    #ifndef ghost_impl_static_assert_with_msg
        #if defined(_MSC_VER) && defined(__cplusplus)
            #if _MSC_VER >= 1600
                #define ghost_impl_static_assert_with_msg(expr, msg, ...) static_assert(expr, msg)
            #endif
        #endif
    #endif

    /* TODO check if msvc supports this in C */

    #ifdef ghost_impl_static_assert_with_msg
        #include "ghost/preprocessor/ghost_msvc_traditional.h"
        #if GHOST_MSVC_TRADITIONAL
            #include "ghost/preprocessor/ghost_expand.h"
            #define ghost_static_assert(...) GHOST_EXPAND(ghost_impl_static_assert_with_msg(__VA_ARGS__, "(no message)", 0))
        #else
            #define ghost_static_assert(...) ghost_impl_static_assert_with_msg(__VA_ARGS__, "(no message)", 0)
        #endif
        #define ghost_has_ghost_static_assert 1
    #endif
#endif


/* Lastly, if we have no compiler support at all for static assertions, we
 * declare an extern function with an array parameter that will have negative
 * size if the given expression is false. */
#ifndef ghost_has_ghost_static_assert
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if GHOST_PP_VA_ARGS
        #include "ghost/preprocessor/ghost_msvc_traditional.h"
        #if GHOST_MSVC_TRADITIONAL
            /* More workarounds for MSVC's old preprocessor */
            #include "ghost/preprocessor/ghost_expand.h"
            #define ghost_static_assert(...) GHOST_EXPAND(ghost_static_assert_impl(__VA_ARGS__, 0))
        #else
            #define ghost_static_assert(...) ghost_static_assert_impl(__VA_ARGS__, 0)
        #endif
        #ifdef __CPARSER__
            /* cparser complains about redundant or unused extern declarations
             * in source files.
             * TODO figure out how to silence unused warning, ghost_maybe_unused doesn't work */
            #include "ghost/preprocessor/ghost_counter.h"
            #include "ghost/preprocessor/ghost_concat.h"
            /*#include "ghost/language/ghost_maybe_unused.h"*/
            #define ghost_static_assert_impl(expr, ...) \
                    extern void GHOST_CONCAT(GHOST_STATIC_ASSERT_FAILED_, GHOST_COUNTER)(char[1 - 2*!(expr)])
        #else
            #define ghost_static_assert_impl(expr, ...) \
                    extern void GHOST_STATIC_ASSERT_FAILED(char[1 - 2*!(expr)])
        #endif
    #else
        /* Without variadic macros the message is not optional. */
        #define ghost_static_assert(expr, message) \
                extern void GHOST_STATIC_ASSERT_FAILED(char[1 - 2*!(expr)])
    #endif
    #define ghost_has_ghost_static_assert 1

    /* We mark our static_assert as synthetic so that
     * ghost_static_assert_expr() doesn't use it. */
    #ifdef GHOST_IMPL_GHOST_STATIC_ASSERT_IS_SYNTHETIC
        #error "GHOST_IMPL_GHOST_STATIC_ASSERT_IS_SYNTHETIC cannot be pre-defined."
    #endif
    #define GHOST_IMPL_GHOST_STATIC_ASSERT_IS_SYNTHETIC
#endif

#endif
