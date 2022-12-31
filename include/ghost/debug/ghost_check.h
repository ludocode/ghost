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

#ifndef GHOST_CHECK_H_INCLUDED
#define GHOST_CHECK_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO come up with a better name for this, ghost_check() is bad because it doesn't actually check in release */

/**
 * @def ghost_check(condition, message) (condition ? (void)0 : fatal(message))
 *
 * In a debug build, aborts the program if the given condition is not true; in
 * a release build, evaluates the condition but ignores the result.
 *
 * The message is optional. If provided, it must be a string literal.
 *
 * This is a safer form of ghost_assert() that does not check its condition in
 * release builds but evaluates it anyway. This prevents code with side effects
 * from being stripped out. This can prevent mysterious differences in behavior
 * between debug and release builds.
 *
 * It can also make it easier to write code that only checks return values in
 * debug builds. For example:
 *
 *     ghost_check(0 == pthread_mutex_lock(&mutex));
 *
 * If the condition has no side effects, the compiler may be able to optimize
 * it away in release. This means in many cases this is just as fast as
 * ghost_assert().
 *
 * @see ghost_assert()
 * @see ghost_ensure()
 * @see GHOST_DEBUG
 */

#ifndef ghost_has_ghost_check
    #ifdef ghost_check
        #define ghost_has_ghost_check 1
    #endif
#endif

#ifndef ghost_has_ghost_check
    #include "ghost/debug/ghost_debug.h"
    #if GHOST_DEBUG
        #include "ghost/debug/ghost_ensure.h"
        #if ghost_has(ghost_ensure)
            #include "ghost/preprocessor/ghost_cparser_pp.h"
            #if GHOST_CPARSER_PP
                /* cparser macro forwarding bug: https://github.com/libfirm/cparser/issues/53 */
                #define ghost_check(...) ghost_ensure(__VA_ARGS__)
            #else
                /* forward without arguments so the expression can be
                 * stringified correctly */
                #define ghost_check ghost_ensure
            #endif
            #define ghost_has_ghost_check 1
        #endif
    #endif
#endif

/* Like ghost_assert(), we don't assert if we don't have an assertion handler
 * (for example if the platform doesn't have abort(). Unlike ghost_assert() we
 * always evaluate the expression.
 *
 * TODO we should probably also evaluate the message just in case. */
#ifndef ghost_has_ghost_check
    #include "ghost/language/ghost_discard.h"
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if GHOST_PP_VA_ARGS
        #include "ghost/preprocessor/ghost_omit_va_args.h"
        #if GHOST_OMIT_VA_ARGS
            #define ghost_check(x, ...) ghost_discard(x)
        #else
            #define ghost_check(...) GHOST_CHECK_IMPL(__VA_ARGS__, 0)
            #define GHOST_CHECK_IMPL(x, ...) ghost_discard(x)
        #endif
    #else
        /* Without variadic macros the message is not optional. */
        #define ghost_check(x, msg) ghost_discard(x)
    #endif
    #define ghost_has_ghost_check 1
#endif

#endif
