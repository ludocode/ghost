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

#ifndef GHOST_EXPAND_H_INCLUDED
#define GHOST_EXPAND_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_EXPAND(...) __VA_ARGS__
 *
 * Performs a preprocessor expansion pass on the arguments.
 *
 * If variadic macros are not available, GHOST_EXPAND() takes only one
 * argument.
 */

#ifndef ghost_has_GHOST_EXPAND
    #ifdef GHOST_EXPAND
        #define ghost_has_GHOST_EXPAND 1
    #endif
#endif

#ifndef ghost_has_GHOST_EXPAND
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if GHOST_PP_VA_ARGS
        #define GHOST_EXPAND(...) __VA_ARGS__
    #else
        #define GHOST_EXPAND(x) x
    #endif
    #define ghost_has_GHOST_EXPAND 1
#endif

#endif
