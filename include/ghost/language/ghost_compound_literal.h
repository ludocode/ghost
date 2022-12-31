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

#ifndef GHOST_COMPOUND_LITERAL_H_INCLUDED
#define GHOST_COMPOUND_LITERAL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_compound_literal(T, ...) ((T){...})
 *
 * Creates a literal struct (or other compound type) in an expression.
 *
 * C99 supports compound literals: a literal struct or other type can be
 * created as an expression. C++ does not support this syntax, but C++11
 * supports a similar syntax for value initialization of a struct or class.
 * This macro wraps both (plus some compiler-specific extensions), allowing you
 * to define literal structs in C99, C++11, gnu89 and gnu++98.
 *
 * There are some limitations. C++ does not support designated initializers
 * before C++20, and C++20 is still limited compared to C99 (for example you
 * cannot specify designated initializers in arbitrary order.) C++ also does
 * not support taking the address of a compound literal.
 *
 * TODO add support for no arguments, needs to be {0} in C, use GHOST_ZERO_INIT
 *
 * https://en.cppreference.com/w/c/language/compound_literal
 */
#endif

#ifndef ghost_has_ghost_compound_literal
    #ifdef ghost_compound_literal
        #define ghost_has_ghost_compound_literal 1
    #endif
#endif

/* Digital Mars C/C++ claims to support C99 but doesn't seem to support
 * compound literals. */
#ifndef ghost_has_ghost_compound_literal
    #ifdef __DMC__
        #define ghost_has_ghost_compound_literal 0
    #endif
#endif

/* C99 compound literal */
#ifndef ghost_has_ghost_compound_literal
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            /* https://en.cppreference.com/w/c/language/compound_literal */
            #define ghost_compound_literal(T, ...) ((T){__VA_ARGS__})
            #define ghost_has_ghost_compound_literal 1
        #endif
    #endif
#endif

/* C++ value initialization */
#ifndef ghost_has_ghost_compound_literal
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            /* https://en.cppreference.com/w/cpp/language/value_initialization */
            #define ghost_compound_literal(T, ...) (T{__VA_ARGS__})
            #define ghost_has_ghost_compound_literal 1
        #endif
    #endif
#endif

/* GNU C statement expression (for -std=gnu89 or equivalent) */
#ifndef ghost_has_ghost_compound_literal
    #ifdef __GNUC__
        #include "ghost/preprocessor/ghost_pp_va_args.h"
        #if GHOST_PP_VA_ARGS
            #define ghost_compound_literal(T, ...) \
                ( __extension__ ({ \
                    T ghost_compound_literal_impl_temp = {__VA_ARGS__}; \
                    ghost_compound_literal_impl_temp; \
                }))
            #define ghost_has_ghost_compound_literal 1
        #endif
    #endif
#endif

/* Otherwise it's not supported. */
#ifndef ghost_has_ghost_compound_literal
    #define ghost_has_ghost_compound_literal 0
#endif

#endif
