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

#ifndef GHOST_MUTEX_INIT_H_INCLUDED
#define GHOST_MUTEX_INIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Initializes a non-recursive mutex.
 *
 * You must destroy the mutex with ghost_mutex_destroy().
 *
 * On some platforms, this mutex may be recursive. You must not rely on this
 * behaviour if you want to ensure portability. Use
 * ghost_mutex_init_recursive() if you want a recursive mutex instead.
 *
 * @see ghost_mutex_t
 * @see ghost_mutex_lock
 * @see ghost_mutex_unlock
 * @see ghost_mutex_destroy
 */
void ghost_mutex_init(ghost_mutex_t* mutex);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_mutex_init
    #ifdef ghost_mutex_init
        #define ghost_has_ghost_mutex_init 1
    #endif
#endif

#ifndef ghost_has_ghost_mutex_init
    #include "ghost/thread/mutex/ghost_mutex_t.h"
    #if !ghost_has_ghost_mutex_t
        #define ghost_has_ghost_mutex_init 0
    #endif
#endif

#ifndef ghost_has_ghost_mutex_init

    #if GHOST_MUTEX_WINSLIM
        /* https://docs.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--inits */
        #define ghost_mutex_init(mutex) InitializeSRWLock(mutex)
        #define ghost_has_ghost_mutex_init 1

    #elif GHOST_MUTEX_WINCS
        /*
         * Note: Critical Sections are always recursive. There is no way to
         * make one non-recursive.
         *     https://docs.microsoft.com/en-us/windows/win32/sync/critical-section-objects
         */
        #define ghost_mutex_init(mutex) InitializeCriticalSection(mutex)
        #define ghost_has_ghost_mutex_init 1

    #elif GHOST_MUTEX_PTHREADS
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/impl/thread/ghost_impl_pthread_mutexattr_settype.h"
        #include "ghost/language/ghost_null.h"
        #ifdef __linux__
            /* We'll need to detect the libc. */
            #include "ghost/header/c/ghost_string_h.h"
        #endif

        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_mutex_init(ghost_mutex_t* mutex) {

            #if ghost_has_ghost_impl_pthread_mutexattr_settype
                /* To match the behaviour of our other platforms and to improve performance,
                 * we want a normal mutex without error checking (but we'll enable error
                 * checking in debug builds.) */

                pthread_mutexattr_t attr;
                ghost_check(0 == pthread_mutexattr_init(&attr), "");

                /* Figure out if we should use the _NP suffix. Some libcs define these
                 * as macros (e.g. newlib, musl) so we try to detect them first. Other
                 * libcs (e.g. glibc, uClibc, BSDs) define them as enum values and
                 * some only under certain conditions. */
                #if GHOST_DEBUG
                    #if !defined(PTHREAD_MUTEX_ERRORCHECK) && \
                            (defined(PTHREAD_MUTEX_ERRORCHECK_NP) || defined(__GLIBC__) || defined(__UCLIBC__))
                        ghost_check(0 == ghost_impl_pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP), "");
                    #else
                        ghost_check(0 == ghost_impl_pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK), "");
                    #endif
                #else
                    #if defined(__GLIBC__) || defined(__UCLIBC__)
                        ghost_check(0 == ghost_impl_pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_TIMED_NP), "");
                    #elif !defined(PTHREAD_MUTEX_NORMAL) && defined(PTHREAD_MUTEX_NORMAL_NP)
                        ghost_check(0 == ghost_impl_pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL_NP), "");
                    #else
                        ghost_check(0 == ghost_impl_pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL), "");
                    #endif
                #endif

                ghost_check(0 == pthread_mutex_init(mutex, &attr), "");
                ghost_check(0 == pthread_mutexattr_destroy(&attr), "");

            #else
                /* We can't set the mutex type. Just make a default mutex. */
                ghost_check(0 == pthread_mutex_init(mutex, &attr), "");
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_mutex_init 1

    #elif GHOST_MUTEX_C11
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_mutex_init(ghost_mutex_t* mutex) {
            /* https://en.cppreference.com/w/c/thread/mtx_init */
            ghost_check(thrd_success == mtx_init(mutex, mtx_plain), "");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_mutex_init 1

    #elif GHOST_MUTEX_FUTEX
        #include "ghost/language/ghost_discard.h"
        #define ghost_mutex_init(condition) ghost_discard((condition)->futex = 0)
        #define ghost_has_ghost_mutex_init 1

    #elif GHOST_MUTEX_NOOP
        #include "ghost/language/ghost_discard.h"
        #define ghost_mutex_init(mutex) ghost_discard(mutex)
        #define ghost_has_ghost_mutex_init 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_ghost_mutex_init
    #define ghost_has_ghost_mutex_init 0
#endif

#endif
