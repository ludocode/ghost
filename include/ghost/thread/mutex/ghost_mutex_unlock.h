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

#ifndef GHOST_MUTEX_UNLOCK_H_INCLUDED
#define GHOST_MUTEX_UNLOCK_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Unlocks the given mutex that is locked by this thread.
 *
 * The mutex must have been previously locked on this thread by a call to
 * ghost_mutex_lock() or a successful call to ghost_mutex_trylock(). If not,
 * the behaviour is undefined.
 */
void ghost_mutex_unlock(ghost_mutex_t* mutex);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_mutex_unlock
    #ifdef ghost_mutex_unlock
        #define ghost_has_ghost_mutex_unlock 1
    #endif
#endif

#ifndef ghost_has_ghost_mutex_unlock
    #include "ghost/thread/mutex/ghost_mutex_t.h"
    #if !ghost_has_ghost_mutex_t
        #define ghost_has_ghost_mutex_unlock 0
    #endif
#endif

#ifndef ghost_has_ghost_mutex_unlock

    #if GHOST_MUTEX_WINSLIM
        /* https://docs.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--unlocks */
        #define ghost_mutex_unlock(mutex) ReleaseSRWLockExclusive(mutex)
        #define ghost_has_ghost_mutex_unlock 1

    #elif GHOST_MUTEX_WINCS
        /* https://docs.microsoft.com/en-us/windows/win32/sync/critical-section-objects */
        #define ghost_mutex_unlock(mutex) LeaveCriticalSection(mutex)
        #define ghost_has_ghost_mutex_unlock 1

    #elif GHOST_MUTEX_PTHREADS || GHOST_MUTEX_C11
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_mutex_unlock(ghost_mutex_t* mutex) {
            #if GHOST_MUTEX_PTHREADS
                /* https://man.archlinux.org/man/pthread_mutex_unlock.3p.en */
                ghost_check(0 == pthread_mutex_unlock(mutex), "");
            #elif GHOST_MUTEX_C11
                /* https://en.cppreference.com/w/c/thread */
                ghost_check(thrd_success == mtx_unlock(mutex), "");
            #else
                #error "Unimplemented!"
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_mutex_unlock 1

    #elif GHOST_MUTEX_FUTEX
        /* TODO */
        #error
        #define ghost_has_ghost_mutex_unlock 1

    #elif GHOST_MUTEX_NOOP
        #include "ghost/language/ghost_discard.h"
        #define ghost_mutex_unlock(mutex) ghost_discard(mutex)
        #define ghost_has_ghost_mutex_unlock 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_ghost_mutex_unlock
    #define ghost_has_ghost_mutex_unlock 0
#endif

#endif
