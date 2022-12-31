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

#ifndef GHOST_CAST_H_INCLUDED
#define GHOST_CAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_cast(Type, value) (Type)(value)
 *
 * This is an alias for `ghost_static_cast()` because a static cast is almost
 * always what you want.
 *
 * @see ghost_static_cast
 */
#endif

#ifndef ghost_has_ghost_cast
    #ifdef ghost_cast
        #define ghost_has_ghost_cast 1
    #endif
#endif

#ifndef ghost_has_ghost_cast
    #include "ghost/language/ghost_static_cast.h"
    #ifdef __CPARSER__
        /* cparser macro forwarding bug: https://github.com/libfirm/cparser/issues/53 */
        #define ghost_cast(...) ghost_static_cast(__VA_ARGS__)
    #else
        #define ghost_cast ghost_static_cast
    #endif
    #define ghost_has_ghost_cast 1
#endif

#endif
