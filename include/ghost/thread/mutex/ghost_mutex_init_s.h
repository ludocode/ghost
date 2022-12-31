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

#ifndef GHOST_MUTEX_INIT_S_H_INCLUDED
#define GHOST_MUTEX_INIT_S_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_MUTEX_INIT
 *
 * A constant value you can use to statically initialize a Ghost mutex.
 *
 * This is equivalent to calling pthread_mutex_init(). You can only use it in a
 * declaration, like this:
 *
 *     ghost_mutex_t mutex = GHOST_MUTEX_INIT;
 *
 * This may not be available on all platforms. Use ghost_has(GHOST_MUTEX_INIT)
 * to see if it's available.
 */
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_GHOST_MUTEX_INIT
    #ifdef GHOST_MUTEX_INIT
        #define ghost_has_GHOST_MUTEX_INIT 1
    #endif
#endif

#ifndef ghost_has_GHOST_MUTEX_INIT
    #include "ghost/thread/mutex/ghost_mutex_t.h"
    #if !ghost_has_ghost_mutex_t
        #define ghost_has_GHOST_MUTEX_INIT 0
    #endif
#endif

#ifndef ghost_has_GHOST_MUTEX_INIT

    #if GHOST_MUTEX_WINSLIM
        /* https://docs.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--inits */
        #define GHOST_MUTEX_INIT SRWLOCK_INIT
        #define ghost_has_GHOST_MUTEX_INIT 1

    #elif GHOST_MUTEX_WINCS || GHOST_MUTEX_C11
        /*
         * These cannot be initialized statically.
         *     https://docs.microsoft.com/en-us/windows/win32/sync/critical-section-objects
         *     https://en.cppreference.com/w/c/thread/mtx_init
         */
        #define ghost_has_GHOST_MUTEX_INIT 0

    #elif GHOST_MUTEX_PTHREADS
        /*
         * The only standard value is PTHREAD_MUTEX_INITIALIZER. This is a
         * default mutex which is (or "may be") mapped to one of the other
         * types. On some platforms it's normal, on some it's recursive, and on
         * some it's error checking. We want normal.
         *
         * glibc defines some extensions to define specific types but only
         * enables them under _GNU_SOURCE. We could try to replicate their
         * behaviour but (at least for now) it's safer to just ignore them.
         *
         * FreeBSD also provides an extension but only to initialize what it
         * calls an "adaptive" mutex, not a normal one.
         *
         * Until we find some extensions we can use, for now we just use the
         * standard PTHREAD_MUTEX_INITIALIZER. It's possible some platforms do
         * not support this and it's required to be a macro so we check for it.
         */
        #ifdef PTHREAD_MUTEX_INITIALIZER
            #define GHOST_MUTEX_INIT PTHREAD_MUTEX_INITIALIZER
            #define ghost_has_GHOST_MUTEX_INIT 1
        #else
            #define ghost_has_GHOST_MUTEX_INIT 0
        #endif

    #elif GHOST_MUTEX_FUTEX || GHOST_MUTEX_NOOP
        #include "ghost/language/ghost_zero_init.h"
        #define GHOST_MUTEX_INITIALIZER GHOST_ZERO_INIT
        #define ghost_has_GHOST_MUTEX_INIT 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_GHOST_MUTEX_INIT
    #define ghost_has_GHOST_MUTEX_INIT 0
#endif

#endif
