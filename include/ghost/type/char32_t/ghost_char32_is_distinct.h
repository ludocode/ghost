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

#ifndef GHOST_CHAR32_IS_DISTINCT_H_INCLUDED
#define GHOST_CHAR32_IS_DISTINCT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR32_IS_DISTINCT
 *
 * 1 if ghost_char32_t is a distinct type, or 0 if it is a typedef to some other
 * type.
 *
 * This is necessary to use char32_t properly in _Generic selections, C++
 * overloads, etc. If char32_t is a typedef of another type, you cannot put both
 * in a _Generic.
 */
#endif

#ifndef ghost_has_GHOST_CHAR32_IS_DISTINCT
    #ifdef GHOST_CHAR32_IS_DISTINCT
        #define ghost_has_GHOST_CHAR32_IS_DISTINCT 1
    #endif
#endif

/* char32_t is a distinct type in C++ as of its introduction in C++11. */
#ifndef ghost_has_GHOST_CHAR32_IS_DISTINCT
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define GHOST_CHAR32_IS_DISTINCT 1
            #define ghost_has_GHOST_CHAR32_IS_DISTINCT 1
        #endif
    #endif
#endif

/* Otherwise it's not distinct.
 * (This assumes compiler extensions in <uchar.h> haven't made it distinct.) */
#ifndef ghost_has_GHOST_CHAR32_IS_DISTINCT
    #define GHOST_CHAR32_IS_DISTINCT 0
    #define ghost_has_GHOST_CHAR32_IS_DISTINCT 1
#endif

#endif
