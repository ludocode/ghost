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

#ifndef GHOST_ONCE_INIT_S_H_INCLUDED
#define GHOST_ONCE_INIT_S_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_ONCE_INIT
 *
 * A static initializer for a once flag.
 *
 * Use it like this:
 *
 *     static ghost_once_t my_once = GHOST_ONCE_INIT;
 *
 * This can only be used as part of a variable definition. You cannot assign
 * GHOST_ONCE_INIT to an existing variable. (Even if it compiles on some
 * platforms it may not on others so avoid doing it for portability.) If you
 * need to dynamically initialize a once flag, use ghost_once_init() instead.
 */
#endif

#ifndef ghost_has_GHOST_ONCE_INIT
    #ifdef GHOST_ONCE_INIT
        #define ghost_has_GHOST_ONCE_INIT 1
    #endif
#endif

/* Windows */
#ifndef ghost_has_GHOST_ONCE_INIT
    #ifdef _WIN32
        #include "ghost/header/windows/ghost_windows_h.h"
        #if ghost_has_ghost_windows_h
            #define GHOST_ONCE_INIT INIT_ONCE_STATIC_INIT
            #define ghost_has_GHOST_ONCE_INIT 1
        #endif
    #endif
#endif

/* pthreads */
#ifndef ghost_has_GHOST_ONCE_INIT
    #include "ghost/header/posix/ghost_pthread_h.h"
    #if ghost_has_ghost_pthread_h
        #ifndef ghost_has_GHOST_ONCE_INIT
            #define GHOST_ONCE_INIT PTHREAD_ONCE_INIT
            #define ghost_has_GHOST_ONCE_INIT 1
        #endif
    #endif
#endif

/* C11 threads */
#ifndef ghost_has_GHOST_ONCE_INIT
    #include "ghost/header/c/ghost_threads_h.h"
    #if ghost_has_ghost_threads_h
        #ifndef ghost_has_GHOST_ONCE_INIT
            #define GHOST_ONCE_INIT ONCE_FLAG_INIT
            #define ghost_has_GHOST_ONCE_INIT 1
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_ONCE_INIT
    #define ghost_has_GHOST_ONCE_INIT 0
#endif

#endif
