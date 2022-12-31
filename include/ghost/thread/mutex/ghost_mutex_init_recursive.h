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

#ifndef GHOST_MUTEX_INIT_RECURSIVE_H_INCLUDED
#define GHOST_MUTEX_INIT_RECURSIVE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Initializes a recursive mutex.
 */
void ghost_mutex_init_recursive(ghost_mutex_t* mutex);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_mutex_init_recursive
    #ifdef ghost_mutex_init_recursive
        #define ghost_has_ghost_mutex_init_recursive 1
    #endif
#endif

#ifndef ghost_has_ghost_mutex_init_recursive
    #include "ghost/thread/mutex/ghost_mutex_t.h"
    #if !ghost_has_ghost_mutex_t
        #define ghost_has_ghost_mutex_init_recursive 0
    #endif
#endif

#ifndef ghost_has_ghost_mutex_init_recursive

    #if GHOST_MUTEX_WINSLIM
        /*
         * There is no way to make a recursive SRWLOCK. If you need a recursive
         * mutex, use CRITICAL_SECTION instead by pre-defining GHOST_MUTEX_WINCS
         * to 1.
         *     https://docs.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--init_recursives
         */
        #define ghost_has_ghost_mutex_init_recursive 0

    #elif GHOST_MUTEX_WINCS
        /*
         * Critical sections are always recursive.
         *     https://docs.microsoft.com/en-us/windows/win32/sync/critical-section-objects
         */
        #define ghost_mutex_init_recursive(mutex) InitializeCriticalSection(mutex)
        #define ghost_has_ghost_mutex_init_recursive 1

    #elif GHOST_MUTEX_PTHREADS || GHOST_MUTEX_C11
        #include "ghost/impl/thread/ghost_impl_pthread_mutexattr_settype.h"
        #if ghost_has_ghost_impl_pthread_mutexattr_settype

            #include "ghost/debug/ghost_check.h"
            #include "ghost/impl/ghost_impl_inline.h"
            #ifdef __linux__
                /* We'll need to detect the libc. */
                #include "ghost/header/c/ghost_string_h.h"
            #endif

            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_inline
            void ghost_mutex_init_recursive(ghost_mutex_t* mutex) {
                pthread_mutexattr_t attr;
                ghost_check(0 == pthread_mutexattr_init(&attr), "");

                /* Figure out if we should use the _NP suffix. Some libcs define these
                 * as macros (e.g. newlib, musl) so we try to detect them first. Other
                 * libcs (e.g. glibc, uClibc, BSDs) define them as enum values and
                 * some only under certain conditions. */
                #if !defined(PTHREAD_MUTEX_RECURSIVE) && \
                        (defined(PTHREAD_MUTEX_RECURSIVE_NP) || defined(__GLIBC__) || defined(__UCLIBC__))
                    ghost_check(0 == ghost_impl_pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP), "");
                #else
                    ghost_check(0 == ghost_impl_pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE), "");
                #endif

                ghost_check(0 == pthread_mutex_init(mutex, &attr), "");
                ghost_check(0 == pthread_mutexattr_destroy(&attr), "");
            }
            GHOST_IMPL_FUNCTION_CLOSE
            #define ghost_has_ghost_mutex_init_recursive 1
        #else
            /* We don't have pthread_mutex_setattr. We have no way to
             * initialize a recursive mutex. (We could detect platforms here
             * where the default mutex is recursive and enable this. For now we
             * don't bother to do this.) */
            #define ghost_has_ghost_mutex_init_recursive 0
        #endif

    #elif GHOST_MUTEX_C11
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_mutex_init(ghost_mutex_t* mutex) {
            /*
             * We have to pass both plain and recursive apparently
             *     https://en.cppreference.com/w/c/thread/mtx_init
             */
            ghost_check(thrd_success == mtx_init(mutex, mtx_plain | mtx_recursive), "");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_mutex_init 1

    #elif GHOST_MUTEX_FUTEX
        /* TODO */
        #error
        /* We probably won't define this... */
        #define ghost_has_ghost_mutex_init_recursive 0

    #elif GHOST_MUTEX_NOOP
        #include "ghost/language/ghost_discard.h"
        #define ghost_mutex_init_recursive(mutex) ghost_discard(mutex)
        #define ghost_has_ghost_mutex_init_recursive 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_ghost_mutex_init_recursive
    #define ghost_has_ghost_mutex_init_recursive 0
#endif

#endif
