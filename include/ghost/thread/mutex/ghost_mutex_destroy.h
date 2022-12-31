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

#ifndef GHOST_MUTEX_DESTROY_H_INCLUDED
#define GHOST_MUTEX_DESTROY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Destroys a mutex.
 *
 * If any threads have the mutex locked or are waiting on a condition with this
 * mutex, the behaviour is undefined.
 *
 * On some platforms ghost_mutex_destroy() does nothing. Make sure you call it
 * anyway to maintain portability with other platforms.
 */
void ghost_mutex_destroy(ghost_mutex_t* mutex);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_mutex_destroy
    #ifdef ghost_mutex_destroy
        #define ghost_has_ghost_mutex_destroy 1
    #endif
#endif

#ifndef ghost_has_ghost_mutex_destroy
    #include "ghost/thread/mutex/ghost_mutex_t.h"
    #if !ghost_has_ghost_mutex_t
        #define ghost_has_ghost_mutex_destroy 0
    #endif
#endif

#ifndef ghost_has_ghost_mutex_destroy

    #if GHOST_MUTEX_WINSLIM || GHOST_MUTEX_FUTEX || GHOST_MUTEX_NOOP
        /* Nothing to do!
         *     https://docs.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--destroys */
        #include "ghost/language/ghost_discard.h"
        #define ghost_mutex_destroy(mutex) ghost_discard(mutex)
        #define ghost_has_ghost_mutex_destroy 1

    #elif GHOST_MUTEX_WINCS
        /* https://docs.microsoft.com/en-us/windows/win32/sync/critical-section-objects */
        #define ghost_mutex_destroy(mutex) DeleteCriticalSection(mutex)
        #define ghost_has_ghost_mutex_destroy 1

    #elif GHOST_MUTEX_PTHREADS
        /* https://man.archlinux.org/man/pthread_mutex_destroy.3p */
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_mutex_destroy(ghost_mutex_t* mutex) {
            ghost_check(0 == pthread_mutex_destroy(mutex), "");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_mutex_destroy 1

    #elif GHOST_MUTEX_C11
        /* https://en.cppreference.com/w/c/thread/mtx_destroy */
        #define ghost_mutex_destroy(mutex) mtx_destroy(mutex)
        #define ghost_has_ghost_mutex_destroy 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_ghost_mutex_destroy
    #define ghost_has_ghost_mutex_destroy 0
#endif

#endif
