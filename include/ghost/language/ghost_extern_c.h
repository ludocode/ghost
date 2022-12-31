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

#ifndef GHOST_EXTERN_C_H_INCLUDED
#define GHOST_EXTERN_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_extern_c extern
 *
 * Declares a function prototype as `extern` in C and `extern "C"` in C++.
 *
 * This cannot be used to declare a block of functions as `extern "C"`, nor
 * should it be used as part of a function definition. It should be used in the
 * prototype for a function with external linkage.
 *
 * Ghost uses this for local declarations of function that are otherwise only
 * declared by the platform under certain conditions (e.g. _GNU_SOURCE, etc.)
 * See ghost_strdup for an example.
 *
 * TODO no we don't use this anymore, get rid of this whole file. we exclusively use extern "C" blocks now, this doesn't work
 *
 * @see GHOST_IMPL_FUNCTION_OPEN
 * @see GHOST_IMPL_FUNCTION_CLOSE
 */
#endif

/* TODO move this file out */

#ifndef ghost_has_ghost_extern_c
    #ifdef ghost_extern_c
        #define ghost_has_ghost_extern_c 1
    #endif
#endif

#ifndef ghost_has_ghost_extern_c
    #ifdef __cplusplus
        #define ghost_extern_c extern "C"
    #else
        #define ghost_extern_c extern
    #endif
    #define ghost_has_ghost_extern_c 1
#endif

#endif
