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

#ifndef GHOST_MAY_ALIAS_H_INCLUDED
#define GHOST_MAY_ALIAS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_may_alias [[may_alias]]
 *
 * Marks a pointer as possibly aliasing other pointers, possibly of different
 * types, so that the compiler doesn't assume strict aliasing on this pointer
 * for the purpose of optimization.
 */
#endif

#ifndef ghost_has_ghost_may_alias
    #if defined(__GNUC__)
        #define ghost_may_alias __attribute__((__may_alias__))
    #else
        /*
         * may_alias only matters for compilers that use strict aliasing
         * optimizations. GCC is by far the most aggressive which is why it
         * supports this. Most others don't. If we find it's too unsafe to
         * alias this to nothing we could get rid of it, but realistically,
         * compilers that do strict aliasing optimizations should provide a way
         * to allow aliasing.
         */
        #define ghost_may_alias /*nothing*/
    #endif
    #define ghost_has_ghost_may_alias 1
#endif

#endif
