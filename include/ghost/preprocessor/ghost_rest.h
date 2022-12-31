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

#ifndef GHOST_REST_H_INCLUDED
#define GHOST_REST_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_REST(x, ...) __VA_ARGS__
 *
 * Expands to all but the first argument, or nothing if only one argument is
 * provided.
 *
 * Note that no arguments is really one blank argument. In other words, this
 * expands to nothing if there are no commas in the argument list.
 */

#ifndef ghost_has_GHOST_REST
    #ifdef GHOST_REST
        #define ghost_has_GHOST_REST 1
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_REST
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_REST 0
    #endif
#endif

/* Implement it in the obvious way if the compiler will let us */
#ifndef ghost_has_GHOST_REST
    #include "ghost/preprocessor/ghost_omit_va_args.h"
    #if GHOST_OMIT_VA_ARGS
        #define GHOST_REST(x, ...) __VA_ARGS__
        #define ghost_has_GHOST_REST 1
    #endif
#endif

/* Our fallback uses GHOST_CONTAINS_COMMA() which is limited to 63 arguments.
 * See the comments in ghost_contains_comma.h. */
#ifndef ghost_has_GHOST_REST
    #include "ghost/preprocessor/ghost_concat.h"
    #include "ghost/preprocessor/ghost_contains_comma.h"

    #define GHOST_REST(...) \
            GHOST_CONCAT( \
                GHOST_REST_IMPL_, \
                GHOST_CONTAINS_COMMA(__VA_ARGS__) \
            )(__VA_ARGS__)

    #define GHOST_REST_IMPL_0(...) /*nothing*/
    #define GHOST_REST_IMPL_1(first, ...) __VA_ARGS__

    #define ghost_has_GHOST_REST 1
#endif

#endif
