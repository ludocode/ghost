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

#ifndef GHOST_MUTEX_TRYLOCK_H_INCLUDED
#define GHOST_MUTEX_TRYLOCK_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Tries to lock the given mutex without blocking, returning true if successful
 * or false if it could not be locked.
 *
 * This returns immediately without blocking. If the mutex was already locked,
 * false is returned. If an error occurs the behaviour is undefined.
 *
 * If the mutex is non-recursive, the mutex must not already be locked by this
 * thread (otherwise deadlock occurs.)
 *
 * If successful, you must unlock the mutex with ghost_mutex_unlock().
 */
bool ghost_mutex_trylock(ghost_mutex_t* mutex);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_mutex_trylock
    #ifdef ghost_mutex_trylock
        #define ghost_has_ghost_mutex_trylock 1
    #endif
#endif

#ifndef ghost_has_ghost_mutex_trylock
    #include "ghost/thread/mutex/ghost_mutex_t.h"
    #if !ghost_has_ghost_mutex_t
        #define ghost_has_ghost_mutex_trylock 0
    #endif
#endif

#ifndef ghost_has_ghost_mutex_trylock

    #if GHOST_MUTEX_WINSLIM
        /* https://docs.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--locks */
        #define ghost_mutex_trylock(mutex) TryAcquireSRWLockExclusive(mutex)
        #define ghost_has_ghost_mutex_trylock 1

    #elif GHOST_MUTEX_WINCS
        /* https://docs.microsoft.com/en-us/windows/win32/sync/critical-section-objects */
        #define ghost_mutex_trylock(mutex) TryEnterCriticalSection(mutex)
        #define ghost_has_ghost_mutex_trylock 1

    #elif GHOST_MUTEX_PTHREADS || GHOST_MUTEX_C11
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/type/bool/ghost_true.h"
        #include "ghost/type/bool/ghost_false.h"
        #include "ghost/header/c/ghost_errno_h.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_bool ghost_mutex_trylock(ghost_mutex_t* mutex) {
            #if GHOST_MUTEX_PTHREADS
                /* https://man.archlinux.org/man/pthread_mutex_trylock.3p.en */
                int ret = pthread_mutex_trylock(mutex);
                if (ret == 0)
                    return ghost_true;
                ghost_check(ret == EBUSY, "");
                return ghost_false;

            #elif GHOST_MUTEX_C11
                /* https://en.cppreference.com/w/c/thread/mtx_trylock */
                int ret = mtx_trylock(mutex);
                if (ret == thrd_success)
                    return ghost_true;
                ghost_check(ret == thrd_busy, "");
                return ghost_false;

            #else
                #error "Unimplemented!"
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_mutex_trylock 1

    #elif GHOST_MUTEX_FUTEX
        /* TODO */
        #error
        #define ghost_has_ghost_mutex_trylock 1

    #elif GHOST_MUTEX_NOOP
        #include "ghost/language/ghost_discard.h"
        #define ghost_mutex_trylock(mutex) ghost_discard(mutex)
        #define ghost_has_ghost_mutex_trylock 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_ghost_mutex_trylock
    #define ghost_has_ghost_mutex_trylock 0
#endif

#endif
