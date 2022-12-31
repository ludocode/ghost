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

#ifndef GHOST_ERRNO_LOAD_H_INCLUDED
#define GHOST_ERRNO_LOAD_H_INCLUDED

/**
 * @def ghost_errno_load() errno
 *
 * A wrapper around reading from errno that supports errno being disabled.
 *
 * If Ghost's errno support is disabled, this returns 0.
 *
 * Override this and ghost_errno_store() if you want an alternate means of
 * implementing errno that isn't just reading and writing an l-value. See
 * ghost_errno for many more errno configuration options.
 *
 * @see ghost_errno
 */

#ifndef ghost_has_ghost_errno_load
    #ifdef ghost_errno_load
        #define ghost_has_ghost_errno_load 1
    #endif
#endif

#ifndef ghost_has_ghost_errno_load
    #include "ghost/error/ghost_errno.h"
    #if ghost_has(ghost_errno)
        #include "ghost/language/ghost_static_cast.h"
        /* We cast it down to convert lvalue to rvalue preventing writing to
         * it, and also to make sure it's an int because you could in theory
         * store it as some other type if you wanted. */
        #define ghost_errno_load() ghost_static_cast(int, ghost_errno)
    #else
        #define ghost_errno_load() 0
    #endif
    #define ghost_has_ghost_errno_load 1
#endif

#endif
