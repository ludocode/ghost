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

#ifndef GHOST_STATIC_ASSERT_EXPR_H_INCLUDED
#define GHOST_STATIC_ASSERT_EXPR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_static_assert_expr(expression, message) ({static_assert(expression, message);})
 *
 * An expression of type void that causes a compile error if the given
 * compile-time constant expression is false.
 *
 * The message is optional (provided the compiler supports variadic macros.)
 * When this triggers a compile error, the message will be emitted by the
 * compiler if provided and supported.
 *
 * This can only be used as an expression. It will not work outside of a
 * function. This is useful for example in implementing macros where it can be
 * used in left side of a comma expression.
 *
 * The standard static_assert() can only be used as a declaration. On modern
 * compilers, static_assert() will be used if it can be wrapped in a construct
 * that converts it from a declaration to an expression (such as a statement
 * expression or a C++ lambda.) Otherwise this is implemented by taking the
 * size of a struct with an invalid bitfield.
 *
 * @see ghost_static_assert
 */
#endif

#ifndef ghost_has_ghost_static_assert_expr
    #ifdef ghost_static_assert_expr
        #define ghost_has_ghost_static_assert_expr 1
    #endif
#endif

/* Try to convert ghost_static_assert() to an expression. */

/* In GNU C/C++, use a statement expression */
#ifndef ghost_has_ghost_static_assert_expr
    #include "ghost/debug/ghost_static_assert.h"
    #ifndef GHOST_IMPL_GHOST_STATIC_ASSERT_IS_SYNTHETIC
        #ifdef __GNUC__
            #include "ghost/language/ghost_discard.h"
            #define ghost_static_assert_expr(...) ( __extension__ ({ \
                        ghost_static_assert(__VA_ARGS__); \
                        ghost_discard(0); \
                    }))
            #define ghost_has_ghost_static_assert_expr 1
        #endif
    #endif
#endif

/* In C++11, use a lambda */
#ifndef ghost_has_ghost_static_assert_expr
    #ifndef GHOST_IMPL_GHOST_STATIC_ASSERT_IS_SYNTHETIC
        #ifdef __cplusplus
            #include "ghost/language/ghost_cplusplus.h"
            #if ghost_cplusplus >= 201103L
                #define ghost_static_assert_expr(...) ([&]->void{ghost_static_assert(__VA_ARGS__);}())
                #define ghost_has_ghost_static_assert_expr 1
            #endif
        #endif
    #endif
#endif

/* If we have no real static_assert() or no way to wrap it in an expression, we
 * can't use it. Fallback to an invalid expression. */
#ifndef ghost_has_ghost_static_assert_expr
    /* We declare a struct containing a bitfield with a member that will have
     * negative width if the condition is false. A bitfield member with
     * negative width (or a width that can't be resolved at compile-time) will
     * cause a compiler error. */
    #include "ghost/language/ghost_discard.h"
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if GHOST_PP_VA_ARGS
        #define ghost_static_assert_expr_impl(expr, ...) \
            ghost_discard(sizeof(struct { int ghost_impl_unused: 1; int: -!(expr); }))
        #define ghost_static_assert_expr(...) ghost_static_assert_expr_impl(__VA_ARGS__, 0)
    #else
        /* Without variadic macros the message is not optional. */
        #define ghost_static_assert_expr(expr, message) \
            ghost_discard(sizeof(struct { int ghost_impl_unused: 1; int: -!(expr); }))
    #endif
    #define ghost_has_ghost_static_assert_expr 1
#endif

#endif
