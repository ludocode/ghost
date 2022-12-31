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

#ifndef GHOST_CONDITION_T_H_INCLUDED
#define GHOST_CONDITION_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A condition variable.
 *
 * This wraps a particular condition implementation available on the platform.
 */
typedef /*unspecified*/ ghost_condition_t;
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_condition_t
    #ifdef ghost_condition_t
        #define ghost_has_ghost_condition_t 1
    #endif
#endif

#ifndef ghost_has_ghost_condition_t

    #if GHOST_MUTEX_WINSLIM || GHOST_MUTEX_WINCS
        /* A CONDITION_VARIABLE is used with both SRWLOCK and CRITICAL_SECTION.
         * There is no lighter-weight condition variable available in the
         * Windows API.
         *     https://docs.microsoft.com/en-us/windows/win32/sync/condition-variables */
        typedef CONDITION_VARIABLE ghost_condition_t;
        #define ghost_has_ghost_condition_t 1

    #elif GHOST_MUTEX_PTHREADS
        /* https://man.archlinux.org/man/core/man-pages/pthread.h.0p.en */
        typedef pthread_cond_t ghost_condition_t;
        #define ghost_has_ghost_condition_t 1

    #elif GHOST_MUTEX_C11
        /* https://en.cppreference.com/w/c/thread */
        typedef cnd_t ghost_condition_t;
        #define ghost_has_ghost_condition_t 1

    #elif GHOST_MUTEX_FUTEX
        /* TODO */
        #error
        #define ghost_has_ghost_condition_t 1

    #elif GHOST_MUTEX_NOOP
        /* Ghost does not define a condition variable under no-op threading
         * because there is no way to wait on it. */
        #define ghost_has_ghost_condition_t 0

    #endif
#endif

#ifndef ghost_has_ghost_condition_t
    #define ghost_has_ghost_condition_t 0
#endif

#endif
