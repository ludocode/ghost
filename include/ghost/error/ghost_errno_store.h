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

#ifndef GHOST_ERRNO_STORE_H_INCLUDED
#define GHOST_ERRNO_STORE_H_INCLUDED

/**
 * @def ghost_errno_store(x) errno = x
 *
 * A wrapper around setting errno that supports errno being disabled.
 *
 * If Ghost's errno support is disabled, this does nothing and its argument is
 * not evaluated. This means you can pass an error name to ghost_errno_store()
 * even if that error name will not be defined when errno is disabled.
 *
 * @see ghost_errno
 */

#ifndef ghost_has_ghost_errno_store
    #ifdef ghost_errno_store
        #define ghost_has_ghost_errno_store 1
    #endif
#endif

#ifndef ghost_has_ghost_errno_store
    #include "ghost/error/ghost_errno.h"
    #if ghost_has(ghost_errno)
        #include "ghost/language/ghost_discard.h"
        /* Discard the result so that it can't be used as an l-value. */
        #define ghost_errno_store(x) ghost_discard(ghost_errno = (x))
    #else
        #define ghost_errno_store(x) ghost_discard(0)
    #endif
    #define ghost_has_ghost_errno_store 1
#endif

#endif
