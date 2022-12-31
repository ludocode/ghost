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

#ifndef GHOST_ERRNO_H_INCLUDED
#define GHOST_ERRNO_H_INCLUDED

/**
 * @def ghost_errno errno
 *
 * A wrapper around errno.
 *
 * This can be used to implement your own errno (for example if building in a
 * freestanding environment) or to disable any interaction between Ghost and
 * errno.
 *
 * Ghost separates the different parts of errno handling so you can configure
 * it however you like. Ghost internally only uses ghost_errno_store() and
 * ghost_errno_is() which gives you maximum flexibility for how you want to
 * configure it:
 *
 * - Define ghost_errno to a custom value if you have your own global or
 *   thread-local errno variable in freestanding;
 *
 * - Define ghost_errno_load() and ghost_errno_store() if you have some special
 *   way of handling errno (perhaps you need to use thread-specific storage, or
 *   you want to log or debugbreak any time errno is set by Ghost);
 *
 * - Define ghost_has_ghost_errno to 0 to disable all Ghost handling of errno;
 *
 * - Define ghost_has_ghost_errno_h to 0 to prevent Ghost from including
 *   <errno.h>;
 *
 * - Define ghost_has_ghost_errno_store to 0 if you just want to prevent Ghost
 *   from setting errno in its synthetic libc wrappers while still allowing it
 *   to check errno values normally.
 */

#ifndef ghost_has_ghost_errno
    #ifdef ghost_errno
        #define ghost_has_ghost_errno 1
    #endif
#endif

#ifndef ghost_has_ghost_errno
    #include "ghost/header/c/ghost_errno_h.h"
    #if ghost_has(ghost_errno_h)
        #define ghost_errno errno
        #define ghost_has_ghost_errno 1
    #endif
#endif

#ifndef ghost_has_ghost_errno
    #define ghost_has_ghost_errno 0
#endif

#endif
