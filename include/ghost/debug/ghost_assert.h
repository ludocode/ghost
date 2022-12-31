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

#ifndef GHOST_ASSERT_H_INCLUDED
#define GHOST_ASSERT_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def ghost_assert(condition, message) (condition ? (void)0 : fatal(message))
 *
 * In a debug build (on platforms where assertion handling is possible), prints
 * the given message and aborts the program if the given condition is not true;
 * otherwise this expands to nothing: the arguments are not evaluated or
 * compiled.
 *
 * This works like the traditional assert() macro, except that it also takes an
 * optional message as an extra argument like static_assert(). The message must
 * be a string literal.
 *
 * This can be dangerous if the code in the condition has side effects because
 * the behaviour of the code will be different between debug and release
 * builds. Avoid putting code with side effects inside an assert.
 *
 * If you want a safer assert, use ghost_check(). If you want the check to be
 * done even in release builds, use ghost_ensure(). If you want a stronger form
 * that tells the compiler to assume the condition is true in release, use
 * ghost_assume() (but beware its caveats.)
 *
 * ghost_assert() is a macro, and the C preprocessor only considers parentheses
 * to ignore nested commas. This means the following code will cause compiler
 * errors:
 *
 *     ghost_assert((int[2]){1,2}[0]); // error
 *     ghost_assert(std::is_same<int,int>::value); // C++ error
 *
 * These are both considered to pass two arguments to ghost_assert(). The
 * preprocessor splits arguments on the comma, ignoring the surrounding braces
 * and angle brackets.
 *
 * C23 is considering a change to `assert()` to work around this. The macro
 * will take variadic arguments that are expanded as-is, and some hacks are
 * used to ensure that they do not inadvertently expand to a comma operator.
 * See the C23 proposal here:
 *
 *     https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2829.htm
 *
 * We prefer to keep ghost_assert() the same as ghost_static_assert() where the
 * optional second parameter is a message. (In fact ghost_static_assert() has
 * the same comma limitations as ghost_assert().) To work around the comma
 * limitation, add an extra set of parentheses around the condition.
 *
 * @see ghost_check()
 * @see ghost_assume()
 * @see ghost_ensure()
 * @see GHOST_DEBUG
 * @see ghost_static_assert()
 */

#ifndef ghost_has_ghost_assert
    #ifdef ghost_assert
        #define ghost_has_ghost_assert 1
    #endif
#endif

#ifndef ghost_has_ghost_assert
    #include "ghost/debug/ghost_debug.h"
    #if GHOST_DEBUG
        #include "ghost/debug/ghost_ensure.h"
        #if ghost_has(ghost_ensure)
            #include "ghost/preprocessor/ghost_cparser_pp.h"
            #if GHOST_CPARSER_PP
                /* cparser macro forwarding bug: https://github.com/libfirm/cparser/issues/53 */
                #define ghost_assert(...) ghost_ensure(__VA_ARGS__)
            #else
                /* forward without arguments so the expression can be
                 * stringified correctly */
                #define ghost_assert ghost_ensure
            #endif
            #define ghost_has_ghost_assert 1
        #endif
    #endif
#endif

/*
 * In release builds we define it to a void expression. We also do this in
 * debug builds where we don't have support for ghost_assert_fail() (for
 * example if the platform doesn't support abort().)
 *
 * This means ghost_assert() always exists (which makes it a lot easier to use)
 * but it doesn't actually assert unless there is an assertion handler.
 *
 * If you are on some embedded platform and want to make sure ghost_assert()
 * works, make sure you have a definition for ghost_assert_fail().
 */
#ifndef ghost_has_ghost_assert
    #include "ghost/language/ghost_discard.h"
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if GHOST_PP_VA_ARGS
        #define ghost_assert(...) ghost_discard(0)
    #else
        /* Without variadic macros the message is not optional. */
        #define ghost_assert(x, msg) ghost_discard(0)
    #endif
    #define ghost_has_ghost_assert 1
#endif

#endif
