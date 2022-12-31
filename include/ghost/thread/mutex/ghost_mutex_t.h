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

#ifndef GHOST_MUTEX_T_H_INCLUDED
#define GHOST_MUTEX_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A mutex.
 *
 * This wraps a particular mutex implementation available on the platform.
 *
 * Ghost's mutex does not support any means of reporting errors because many of
 * the implementations used do not support error handling. If the underlying
 * implementation supports error detection, errors are asserted in debug builds
 * and ignored in release.
 *
 * Ghost's mutex can only be used by a single process. Do not use it with
 * multiple processes in shared memory.
 */
typedef /*unspecified*/ ghost_mutex_t;
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_mutex_t
    #ifdef ghost_mutex_t
        #define ghost_has_ghost_mutex_t 1
    #endif
#endif

#ifndef ghost_has_ghost_mutex_t

    #if GHOST_MUTEX_WINSLIM
        /* https://docs.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--locks */
        typedef SRWLOCK ghost_mutex_t;
        #define ghost_has_ghost_mutex_t 1

    #elif GHOST_MUTEX_WINCS
        /* https://docs.microsoft.com/en-us/windows/win32/sync/critical-section-objects */
        typedef CRITICAL_SECTION ghost_mutex_t;
        #define ghost_has_ghost_mutex_t 1

    #elif GHOST_MUTEX_PTHREADS
        /* https://man.archlinux.org/man/pthread_mutex_lock.3p.en */
        typedef pthread_mutex_t ghost_mutex_t;
        #define ghost_has_ghost_mutex_t 1

    #elif GHOST_MUTEX_C11
        /* https://en.cppreference.com/w/c/thread */
        typedef mtx_t ghost_mutex_t;
        #define ghost_has_ghost_mutex_t 1

    #elif GHOST_MUTEX_FUTEX
        /* TODO */
        typedef struct {ghost_atomic_i32_t futex} ghost_mutex_t;
        #define ghost_has_ghost_mutex_t 1

    #elif GHOST_MUTEX_NOOP
        /* wrap in a struct to prevent implicit conversions */
        typedef struct {char ghost_impl_v_unused;} ghost_mutex_t;
        #define ghost_has_ghost_mutex_t 1

    #endif
#endif

#ifndef ghost_has_ghost_mutex_t
    #define ghost_has_ghost_mutex_t 0
#endif

#endif
