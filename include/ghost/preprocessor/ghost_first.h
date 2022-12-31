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

#ifndef GHOST_FIRST_H_INCLUDED
#define GHOST_FIRST_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_FIRST(a, ...) a
 *
 * Expands to the first argument in a variable list of arguments.
 *
 * The argument list may contain only one argument (which can be blank.)
 */

#ifndef ghost_has_GHOST_FIRST
    #ifdef GHOST_FIRST
        #define ghost_has_GHOST_FIRST 1
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_FIRST
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_FIRST 0
    #endif
#endif

#ifndef ghost_has_GHOST_FIRST
    #include "ghost/preprocessor/ghost_omit_va_args.h"
    #if GHOST_OMIT_VA_ARGS
        #define GHOST_FIRST(a, ...) a
    #else
        #define GHOST_FIRST(...) GHOST_FIRST_IMPL(__VA_ARGS__, 0)
        #define GHOST_FIRST_IMPL(a, ...) a
    #endif
    #define ghost_has_GHOST_FIRST 1
#endif

#endif
