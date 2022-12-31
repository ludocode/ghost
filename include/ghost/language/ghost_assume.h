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

#ifndef GHOST_ASSUME_H_INCLUDED
#define GHOST_ASSUME_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_assume(condition[, message]) __assume(condition)
 *
 * Allows the compiler to assume for optimization purposes that the given
 * condition is true. If the condition is false, the behaviour is undefined.
 *
 * Example:
 *
 *     ghost_assume(i > 0);
 *
 * The compiler may perform any optimizations based on this assumption such as
 * eliminating code that it determines cannot be reached. This has similar
 * optimization implications as ghost_unreachable() and they are implemented
 * similarly.
 *
 * This may or may not evaluate its condition, and the compiler may not be able
 * to optimize the evaluation away (if you call a function for example.) This
 * means it's possible to make code slower by adding this. If you do not want
 * the condition to be evaluated in release builds, use ghost_assert() instead.
 *
 * In a debug build, instead of a compiler hint this is converted to an
 * assertion with the given message. The message is optional (as long as
 * variadic macros are supported.)
 *
 * @see GHOST_DEBUG
 * @see ghost_assert()
 * @see ghost_unreachable()
 */
#endif

#ifndef ghost_has_ghost_assume
    #ifdef ghost_assume
        #define ghost_has_ghost_assume 1
    #endif
#endif

/* In a debug build, this is the same as an assert. ghost_assert() will at
 * least hint to the compiler that it is likely to be true. */
#ifndef ghost_has_ghost_assume
    #include "ghost/debug/ghost_debug.h"
    #if GHOST_DEBUG
        #include "ghost/debug/ghost_assert.h"
        #if ghost_has(ghost_assert)
            #include "ghost/preprocessor/ghost_cparser_pp.h"
            #if GHOST_CPARSER_PP
                /* workaround for cparser's busted preprocessor */
                #define ghost_assume(...) ghost_assert(__VA_ARGS__)
            #else
                /* forward without arguments so the expression can be
                 * stringified correctly */
                #define ghost_assume ghost_assert
            #endif
            #define ghost_has_ghost_assume 1
        #endif
    #endif
#endif

/* MSVC supports __assume(). */
#ifndef ghost_has_ghost_assume
    #ifdef _MSC_VER
        /* https://docs.microsoft.com/en-us/cpp/intrinsics/assume */
        #include "ghost/preprocessor/ghost_pp_va_args.h"
        #if GHOST_PP_VA_ARGS
            #define ghost_assume(...) ghost_assume_impl(__VA_ARGS__, 0)
            #define ghost_assume_impl(x, ...) __assume(x)
        #else
            #define ghost_assume(x, msg) __assume(x)
        #endif
        #define ghost_has_ghost_assume 1
    #endif
#endif

/* In compilers that support an unreachable annotation we can provide the hint
 * by calling it if the condition is false. The optimizer can assume the
 * condition is true and propagate it outward. */

/* C23 will have unreachable(). It's supposed to be a macro so we can test for
 * it. */
#ifndef ghost_has_ghost_assume
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            #include "ghost/header/c/ghost_stddef_h.h"
            #ifdef unreachable
                #include "ghost/language/ghost_discard.h"
                #include "ghost/preprocessor/ghost_pp_va_args.h"
                #if GHOST_PP_VA_ARGS
                    #define ghost_assume(...) ghost_assume_impl(__VA_ARGS__, 0)
                    #define ghost_assume_impl(x, ...) ((x) ? ghost_discard(0) : unreachable())
                #else
                    #define ghost_assume(x, msg) ((x) ? ghost_discard(0) : unreachable())
                #endif
                #define ghost_has_ghost_assume 1
            #endif
        #endif
    #endif
#endif

/* Use __builtin_unreachable if supported. */
#ifndef ghost_has_ghost_assume
    #ifdef GHOST_IMPL_UNREACHABLE_BUILTIN
        #error
    #endif

    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_unreachable)
            #define GHOST_IMPL_UNREACHABLE_BUILTIN
        #endif
    #elif defined(__PGI)
        #define GHOST_IMPL_UNREACHABLE_BUILTIN
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* GCC has supported __builtin_unreachable since 4.5. */
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
                #define GHOST_IMPL_UNREACHABLE_BUILTIN
            #endif
        #endif
    #endif

    #ifdef GHOST_IMPL_UNREACHABLE_BUILTIN
        #undef GHOST_IMPL_UNREACHABLE_BUILTIN
        #include "ghost/language/ghost_discard.h"
        #include "ghost/preprocessor/ghost_pp_va_args.h"
        #if GHOST_PP_VA_ARGS
            #define ghost_assume(...) ghost_assume_impl(__VA_ARGS__, 0)
            #define ghost_assume_impl(x, ...) ((x) ? ghost_discard(0) : __builtin_unreachable())
        #else
            #define ghost_assume(x, msg) ((x) ? ghost_discard(0) : __builtin_unreachable())
        #endif
        #define ghost_has_ghost_assume 1
    #endif
#endif

/* If none of the above are supported, since this is just a compiler hint, we
 * ignore all arguments and expand to an empty expression. */
#ifndef ghost_has_ghost_assume
    #include "ghost/language/ghost_discard.h"
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if GHOST_PP_VA_ARGS
        #define ghost_assume(...) ghost_discard(0)
    #else
        #define ghost_assume(x, msg) ghost_discard(0)
    #endif
    #define ghost_has_ghost_assume 1
#endif

#endif
