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

#ifndef GHOST_INSERT_COMMA_H_INCLUDED
#define GHOST_INSERT_COMMA_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_INSERT_COMMA(...) , ## __VA_ARGS__
 *
 * Expands to the arguments, inserting a leading comma if the argument list is
 * not blank.
 *
 * This is used for the same purpose as the GNU extension of deleting a comma
 * before a variable argument list if the token paste operator is inserted, as
 * well as the new `__VA_OPT__(,)` in C++20. This implementation is standard
 * C99 and works on all conforming compilers.
 *
 * Note that Ghost also has GHOST_VA_OPT() if you want to insert more than just
 * a comma.
 *
 * @see GHOST_VA_OPT()
 */

#ifndef ghost_has_GHOST_INSERT_COMMA
    #ifdef GHOST_INSERT_COMMA
        #define ghost_has_GHOST_INSERT_COMMA 1
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_INSERT_COMMA
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_INSERT_COMMA 0
    #endif
#endif

/* C++20 supports __VA_OPT__ */
#ifndef ghost_has_GHOST_INSERT_COMMA
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 202002L
            #define GHOST_INSERT_COMMA(...) __VA_OPT__(,) __VA_ARGS__
            #define ghost_has_GHOST_INSERT_COMMA 1
        #endif
    #endif
#endif

/* MSVC's traditional preprocessor always removes commas before empty
 * __VA_ARGS__. (This probably can't be used as is because MSVC's traditional
 * preprocessor doesn't forward __VA_ARGS__ correctly so you'll most likely
 * need some other special behaviour if you care about supporting it.) */
#ifndef ghost_has_GHOST_INSERT_COMMA
    #ifdef _MSC_VER
        #include "ghost/preprocessor/ghost_msvc_traditional.h"
        #if GHOST_MSVC_TRADITIONAL
            #define GHOST_INSERT_COMMA(...) , __VA_ARGS__
            #define ghost_has_GHOST_INSERT_COMMA 1
        #endif
    #endif
#endif

/* TODO test this, might need to wrap in GHOST_EXPAND, might not be available in pedantic
 * GNU C compilers and MSVC (with the new preprocessor) support token pasting
 * with a comma as an extension. */
#ifndef ghost_has_GHOST_INSERT_COMMA
    #if defined(__GNUC__) || defined(_MSC_VER)
        #define GHOST_INSERT_COMMA(...) , ## __VA_ARGS__
        #define ghost_has_GHOST_INSERT_COMMA 1
    #endif
#endif

/* Standard C */
#ifndef ghost_has_GHOST_INSERT_COMMA
    #include "ghost/preprocessor/ghost_if_else_block.h"
    #include "ghost/preprocessor/ghost_is_blank.h"
    #define GHOST_INSERT_COMMA(...) \
                GHOST_IF_ELSE_BLOCK(GHOST_IS_BLANK(__VA_ARGS__))()(,) \
                __VA_ARGS__
    #define ghost_has_GHOST_INSERT_COMMA 1
#endif

#endif
