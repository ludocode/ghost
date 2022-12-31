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

#ifndef GHOST_FATAL_H_INCLUDED
#define GHOST_FATAL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_fatal(message) ghost_assert_fail(..., __FILE__, __LINE__, message)
 *
 * Reports a fatal error with the given message (if provided) and aborts the
 * program.
 *
 * The message is optional. If provided, it must be a literal string.
 *
 * If you want to override the abort behaviour you should override
 * ghost_assert_fail().
 *
 * @see ghost_fatal_msg()
 */
#endif

#ifndef ghost_has_ghost_fatal
    #ifdef ghost_fatal
        #define ghost_has_ghost_fatal 1
    #endif
#endif

#ifndef ghost_has_ghost_fatal
    #include "ghost/debug/ghost_assert_fail.h"
    #if ghost_has(ghost_assert_fail)
        #include "ghost/debug/ghost_pretty_function.h"
        #include "ghost/preprocessor/ghost_pp_va_args.h"

        #ifdef GHOST_IMPL_FATAL_PRETTY_FUNCTION
            #error "Cannot pre-define GHOST_IMPL_FATAL_PRETTY_FUNCTION."
        #endif
        #if ghost_has(GHOST_PRETTY_FUNCTION)
            #define GHOST_IMPL_FATAL_PRETTY_FUNCTION GHOST_PRETTY_FUNCTION
        #else
            #include "ghost/language/ghost_null.h"
            #define GHOST_IMPL_FATAL_PRETTY_FUNCTION ghost_null
        #endif

        #if GHOST_PP_VA_ARGS
            #include "ghost/language/ghost_null.h"
            /* Concatenate the message with a blank string literal. This ensures
             * that the message is a string literal and allows it to be omitted. */
            #define ghost_fatal(...) ghost_fatal_impl(__VA_ARGS__, "", 0)
            #define ghost_fatal_impl(msg, ...) \
                ghost_assert_fail(ghost_null, "" msg, __FILE__, __LINE__, GHOST_IMPL_FATAL_PRETTY_FUNCTION)
        #else
            /* Without variadic macros the message is not optional. */
            #define ghost_fatal(msg) \
                ghost_assert_fail(ghost_null, "" msg, __FILE__, __LINE__, GHOST_IMPL_FATAL_PRETTY_FUNCTION)
        #endif

        #define ghost_has_ghost_fatal 1
    #endif
#endif

#ifndef ghost_has_ghost_fatal
    #define ghost_has_ghost_fatal 0
#endif

#endif
