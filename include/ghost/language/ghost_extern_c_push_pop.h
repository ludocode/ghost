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

#ifndef GHOST_EXTERN_C_PUSH_POP_H_INCLUDED
#define GHOST_EXTERN_C_PUSH_POP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_EXTERN_C_PUSH
 *
 * In C, this expands to nothing. In C++, this opens an `extern "C"` block:
 *
 *     extern "C" {
 *
 * Use it to wrap a group of function declarations (perhaps the contents of an
 * entire header). This allows functions implemented in C to be used in C++.
 *
 * Ghost defines all its inline functions wrapped in this (unless they are
 * specifically for C++.) We need to prevent name mangling so that the linker
 * will collapse non-static inlines into a single definition (otherwise we'd
 * have two, one unmangled for C and one mangled for C++.) We also want to
 * prevent name mangling even for static functions because unmangled names are
 * better for debugging and we don't want our functions overridden or put in
 * namespaces.
 *
 * Even when defining only one function, Ghost still uses this rather than
 * putting `extern "C"` directly on the function because it works on static
 * and/or inline functions. Specifying `extern "C"` directly on the function
 * interferes with `extern inline` (see ghost_inline_emit.h).
 *
 * @see GHOST_EXTERN_C_POP
 */
#endif

#ifndef ghost_has_GHOST_EXTERN_C_PUSH
    #ifdef GHOST_EXTERN_C_PUSH
        #define ghost_has_GHOST_EXTERN_C_PUSH 1
    #endif
#endif

#ifndef ghost_has_GHOST_EXTERN_C_PUSH
    #ifdef __cplusplus
        #define GHOST_EXTERN_C_PUSH extern "C" {
    #else
        #define GHOST_EXTERN_C_PUSH /*nothing*/
    #endif
    #define ghost_has_GHOST_EXTERN_C_PUSH 1
#endif

/**
 * @def GHOST_EXTERN_C_POP
 *
 * In C, this expands to nothing. In C++, this closes an `extern "C"` block via
 * a single closing brace:
 *
 *     }
 *
 * @see GHOST_EXTERN_C_PUSH
 */

#ifndef ghost_has_GHOST_EXTERN_C_POP
    #ifdef GHOST_EXTERN_C_POP
        #define ghost_has_GHOST_EXTERN_C_POP 1
    #endif
#endif

#ifndef ghost_has_GHOST_EXTERN_C_POP
    #ifdef __cplusplus
        #define GHOST_EXTERN_C_POP }
    #else
        #define GHOST_EXTERN_C_POP /*nothing*/
    #endif
    #define ghost_has_GHOST_EXTERN_C_POP 1
#endif

#endif
