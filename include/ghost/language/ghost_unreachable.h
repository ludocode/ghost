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

#ifndef GHOST_UNREACHABLE_H_INCLUDED
#define GHOST_UNREACHABLE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_unreachable(dummy_return_value) __builtin_unreachable()
 *
 * Indicates to the compiler that control flow cannot reach this point. If the
 * statement is actually reached, the behaviour is undefined.
 *
 * The compiler may perform any optimizations based on this assumption such as
 * eliminating code leading to and following the statement. This has similar
 * optimization implications as ghost_assume() and they are implemented
 * similarly.
 *
 * In a debug build, or if the compiler does not perform such optimizations,
 * Ghost may instead attempt to abort the program (via ghost_fatal().) This
 * is not possible on all compilers (even popular ones like MSVC) so if you
 * want to be portable you must not rely on this behaviour. Even in a debug
 * build, reaching ghost_unreachable() is undefined behaviour.
 *
 * Most modern compilers, those that support unreachable directives or that
 * understand noreturn functions, will allow you to omit a `return` statement
 * from a ghost_unreachable() branch in functions that return non-void.
 * However, if you want to support older or less featureful compilers, you need
 * to pass a dummy value that matches the return value of the function. Ghost
 * will insert a return statement with this value if necessary to appease the
 * compiler. If you don't care about supporting such compilers you can omit the
 * dummy value.
 *
 * @see ghost_assume()
 */
#endif

/*
 * There are two very different cases where ghost_unreachable() may be useful:
 *
 * - Where a good compiler can prove that a code path is unreachable but a
 *   lesser compiler may not, e.g.:
 *
 *     int foo() {
 *         for (;;) {
 *             ... // unconditional loop, no break or goto (but possibly return)
 *         }
 *         ghost_unreachable(0); // not possible, we do not want a useless return statement
 *     }
 *
 * - Where a compiler cannot possibly prove that a code path is unreachable but
 *   we want to assert that it is for optimization purposes, e.g.:
 *
 *     int bar() {
 *         switch (...) {
 *             case ...:
 *                 ...
 *             ...
 *             default:
 *                 break; // some cases unhandled
 *         }
 *         ghost_unreachable(0); // we promise that unhandled cases are impossible
 *     }
 *
 * Unfortunately, compiler behaviour differs significantly in handling of
 * unreachable code:
 *
 * - Some compilers will forbid any code in a path that it can prove is
 *   unreachable;
 *
 * - Some compilers will silently ignore code in an unreachable path, but will
 *   allow omitting a return statement from such paths without warning;
 *
 * - Some compilers won't detect that the code path is unreachable and, if the
 *   path exits the function, will warn about a missing return statement.
 *
 * There is some overlap between these cases. For example some compilers may
 * detect that an infinite loop doesn't exit while others will only detect
 * whether every branch in an if/else chain return. Some will perform
 * optimizations such as function inlining and constant propagation before
 * detecting reachability so the behaviour can differ even with the same
 * compiler. It can even depend on compiler flags like whether link-time
 * optimization is enabled. We therefore can't separate these cases into
 * different macros.
 *
 * For all these reasons we want the single macro ghost_unreachable() to be
 * usable in all situations. This has the unfortunate downside that we can't
 * put in debug code on compilers that forbid unreachable code.
 */

/* MSVC supports __assume(0) and NVIDIA/PGI supports __builtin_unreachable.
 * These compilers don't allow us to put anything else in a provably
 * unreachable path so we can't use anything else in debug mode. */
/* TODO can we not use GHOST_SILENCE_UNREACHABLE? */
#ifndef ghost_has_ghost_unreachable
    #ifdef _MSC_VER
        /* https://docs.microsoft.com/en-us/cpp/intrinsics/assume */
        /* Take variadic arguments to avoid "not enough arguments" warning from
         * traditional preprocessor */
        #define ghost_unreachable(...) __assume(0)
        #define ghost_has_ghost_unreachable 1
    #elif defined(__PGI)
        #define ghost_unreachable(dummy) __builtin_unreachable()
        #define ghost_has_ghost_unreachable 1
    #endif
#endif

/*
 * cparser also warns about unreachable code with no way to silence the
 * warning. It also has no unreachable intrinsic for code paths that are not
 * provably unreachable. We'd need two different macros, one for provably
 * unreachable paths and one for not, but as we've discussed above, compilers
 * differ in what they can prove so it's not possible to make two different
 * macros portable. There is no way to make this work without warnings on
 * cparser. Instead we fallback to the default ghost_fatal() implementations
 * below. You will have to build with -Wno-unreachable-code to silence the
 * warning.
 */

/* TinyCC has no unreachable intrinsic and it warns about a missing return
 * statement even after calling a noreturn function. We return the dummy value
 * after calling abort. */
#ifndef ghost_has_ghost_unreachable
    #ifdef __TINYC__
        #include "ghost/debug/ghost_fatal.h"
        #define ghost_unreachable(dummy) \
            do { \
                ghost_fatal("unreachable code path reached"); \
                /* No parens around dummy in case it's blank */ \
                return dummy; \
            } while (0)
        #define ghost_has_ghost_unreachable 1
    #endif
#endif

/*
 * LCC also has no unreachable intrinsic, and also warns about a missing return
 * statement after calling a noreturn function... but it also warns about a
 * missing return statement if the return is inside the `do {} while (0)` loop
 * as above. It expects a return statement outside of the loop. We have no
 * choice but to simply return the dummy value.
 */
#ifndef ghost_has_ghost_unreachable
    #ifdef __LCC__
        #include "ghost/debug/ghost_fatal.h"
        #define ghost_unreachable(dummy) return dummy
        #define ghost_has_ghost_unreachable 1
    #endif
#endif

/* In debug builds, we want to flag a fatal error instead of optimizing the
 * code path away. Unfortunately, this can't be used on compilers that complain
 * about unreachable code. */
#ifndef ghost_has_ghost_unreachable
    #include "ghost/debug/ghost_debug.h"
    #ifdef GHOST_DEBUG
        #include "ghost/debug/ghost_fatal.h"
        #if ghost_has(ghost_fatal)
            #define ghost_unreachable(dummy) ghost_fatal("unreachable code path reached")
            #define ghost_has_ghost_unreachable 1
        #endif
    #endif
#endif

/* C23 will have unreachable(). It's supposed to be a macro so we can test for
 * it. */
#ifndef ghost_has_ghost_unreachable
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            #include "ghost/header/c/ghost_stddef_h.h"
            #ifdef unreachable
                #define ghost_unreachable(dummy) unreachable()
                #define ghost_has_ghost_unreachable 1
            #endif
        #endif
    #endif
#endif

/* C++23 will also have std::unreachable().
 *     https://en.cppreference.com/w/cpp/utility/unreachable */
/* TODO */

/* Use __builtin_unreachable if supported. */
#ifndef ghost_has_ghost_unreachable
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_unreachable)
            #define ghost_unreachable(dummy) __builtin_unreachable()
            #define ghost_has_ghost_unreachable 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* GCC has supported __builtin_unreachable since 4.5. */
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
                #define ghost_unreachable(dummy) __builtin_unreachable()
                #define ghost_has_ghost_unreachable 1
            #endif
        #endif
    #endif
#endif

/* If we have no support for any of the above, we just abort(). We assume any
 * remaining compilers won't warn about a missing return statement after
 * calling a noreturn function. */
#ifndef ghost_has_ghost_unreachable
    #include "ghost/debug/ghost_fatal.h"
    #if ghost_has(ghost_fatal)
        #define ghost_unreachable(dummy) ghost_fatal("unreachable code path reached")
        #define ghost_has_ghost_unreachable 1
    #endif
#endif

/* If we can't abort(), we return the dummy value. */
#ifndef ghost_has_ghost_unreachable
    /* No parens around dummy in case it's blank */
    #define ghost_unreachable(dummy) return dummy;
    #define ghost_has_ghost_unreachable 1
#endif

#endif
