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

#ifndef GHOST_IS_PARENS_H_INCLUDED
#define GHOST_IS_PARENS_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_IS_PARENS(x)
 *
 * Expands to 1 if the argument is parenthesized and 0 otherwise.
 */

#ifndef ghost_has_GHOST_IS_PARENS
    #ifdef GHOST_IS_PARENS
        #define ghost_has_GHOST_IS_PARENS 1
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_IS_PARENS
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_IS_PARENS 0
    #endif
#endif

/* This is implemented similar to GHOST_NOT(). The argument is tacked on to
 * GHOST_IS_PARENS_IMPL_PROBE which is a function-like macro so it requires
 * parentheses to expand. If the argument has parentheses, it causes the probe
 * to expand which causes GHOST_IS_PARENS() to expand to 1. */

#ifndef ghost_has_GHOST_IS_PARENS
    #include "ghost/preprocessor/ghost_first.h"
    #include "ghost/preprocessor/ghost_not.h"
    #include "ghost/preprocessor/ghost_expand.h"

    #define GHOST_IS_PARENS_IMPL_PROBE(...) ~, 1

    #define GHOST_IS_PARENS_IMPL_IS_PROBE(...) GHOST_IS_PARENS_IMPL_IS_PROBE_IMPL(__VA_ARGS__, 0, )
    #define GHOST_IS_PARENS_IMPL_IS_PROBE_IMPL(a, b, ...) b

    #define GHOST_IS_PARENS(x) GHOST_IS_PARENS_IMPL_IS_PROBE(GHOST_IS_PARENS_IMPL_PROBE x)

    #define ghost_has_GHOST_IS_PARENS 1
#endif

#endif
