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

#ifndef GHOST_BOOL_PP_H_INCLUDED
#define GHOST_BOOL_PP_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_BOOL(condition)
 *
 * Expands to 0 if the condition is 0, otherwise expands to 1.
 *
 * This macro coerces the given preprocessor expression into a preprocessor
 * boolean, that is 0 or 1. Only an explicit 0 is considered false; any other
 * text, including blank or an undefined macro, is coerced to 1.
 *
 * Note that this cannot take a string.
 *
 * This requires variadic macros. Check `#if ghost_has(GHOST_BOOL)` to see
 * whether it's supported.
 */

#ifndef ghost_has_GHOST_BOOL
    #ifdef GHOST_BOOL
        #define ghost_has_GHOST_BOOL 1
    #endif
#endif

#ifndef ghost_has_GHOST_BOOL
    #include "ghost/preprocessor/ghost_not.h"
    #if ghost_has(GHOST_NOT)
        #define GHOST_BOOL(x) GHOST_NOT(GHOST_NOT(x))
        #define ghost_has_GHOST_BOOL 1
    #else
        #define ghost_has_GHOST_BOOL 0
    #endif
#endif

#endif
