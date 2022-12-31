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

#ifndef GHOST_ENSURE_H_INCLUDED
#define GHOST_ENSURE_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def ghost_ensure(condition[, message]) (condition ? (void)0 : fatal(message))
 *
 * Aborts the program if the given condition is not true.
 *
 * This is an assert() that works in both debug and release builds. It
 * "ensures" that the condition is true after it runs because it will not allow
 * execution to continue if it isn't.
 *
 * The message is optional. If provided, it must be a string literal.
 *
 * The assertion handler is ghost_assert_fail(), which by default wraps
 * ghost_abort(). This is required in order for ghost_ensure() to exist. Use
 * ghost_has(ghost_ensure) to check whether this exists. If you want to
 * customize the assertion handler (for this and other assert macros), override
 * ghost_assert_fail().
 *
 * The assertion handler is required in order for ghost_ensure() to exist. (By
 * default the assertion handler wraps abort() or equivalent.)
 *
 * If you want the check to be disabled in release builds, use one of the other
 * assertion macros instead.
 *
 * The message is optional.
 *
 * @see ghost_assert()
 * @see ghost_check()
 * @see ghost_assume()
 */

#ifndef ghost_has_ghost_ensure
    #ifdef ghost_ensure
        #define ghost_has_ghost_ensure 1
    #endif
#endif

#ifndef ghost_has_ghost_ensure
    #include "ghost/debug/ghost_assert_fail.h"
    #if ghost_has(ghost_assert_fail)
        #include "ghost/language/ghost_expect_true.h"
        #include "ghost/debug/ghost_pretty_function.h"
        #include "ghost/preprocessor/ghost_pp_va_args.h"

        #ifdef GHOST_IMPL_ENSURE_PRETTY_FUNCTION
            #error "Cannot pre-define GHOST_IMPL_ENSURE_PRETTY_FUNCTION."
        #endif
        #if ghost_has(GHOST_PRETTY_FUNCTION)
            #define GHOST_IMPL_ENSURE_PRETTY_FUNCTION GHOST_PRETTY_FUNCTION
        #else
            #include "ghost/language/ghost_null.h"
            #define GHOST_IMPL_ENSURE_PRETTY_FUNCTION ghost_null
        #endif

        #if !GHOST_PP_VA_ARGS
            /* If we can't have variadic macros, the message is required. */
            #define ghost_ensure(x, msg) ((ghost_expect_true(x)) ? ((void)0) : \
                ghost_assert_fail(#x, "" msg, __FILE__, __LINE__, GHOST_IMPL_ENSURE_PRETTY_FUNCTION))
        #else
            /*
             * If we're allowed to have an optional vararg, use it. This eliminates
             * a macro indirection and allows us to inhibit macro expansion in
             * stringifying the expression.
             *
             * In both cases we concatenate the message with a blank string
             * literal. This ensures that the message is a string literal and
             * allows it to be omitted.
             */
            #include "ghost/preprocessor/ghost_omit_va_args.h"
            #if GHOST_OMIT_VA_ARGS
                #define ghost_ensure(x, ...) ((ghost_expect_true(x)) ? ((void)0) : \
                    ghost_assert_fail(#x, "" __VA_ARGS__, __FILE__, __LINE__, GHOST_IMPL_ENSURE_PRETTY_FUNCTION))
            #else
                #define ghost_ensure(...) ghost_ensure_impl(__VA_ARGS__, "", 0)
                #define ghost_ensure_impl(x, msg, ...) ((ghost_expect_true(x)) ? ((void)0) : \
                        ghost_assert_fail(#x, "" msg, __FILE__, __LINE__, GHOST_IMPL_ENSURE_PRETTY_FUNCTION))
            #endif
        #endif

        #define ghost_has_ghost_ensure 1
    #endif
#endif

#ifndef ghost_has_ghost_ensure
    #define ghost_has_ghost_ensure 0
#endif

#endif
