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

#ifndef GHOST_CONDITION_SIGNAL_H_INCLUDED
#define GHOST_CONDITION_SIGNAL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Wakes one thread waiting on the given condition.
 *
 * Though it is not technically required, you generally want to hold a lock on
 * the same mutex that waiting threads passed to ghost_condition_wait() when
 * calling this. In this case a thread will wake after you release the lock.
 */
void ghost_condition_signal(ghost_condition_t* condition);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_condition_signal
    #ifdef ghost_condition_signal
        #define ghost_has_ghost_condition_signal 1
    #endif
#endif

#ifndef ghost_has_ghost_condition_signal
    #include "ghost/thread/condition/ghost_condition_t.h"
    #if !ghost_has_ghost_condition_t
        #define ghost_has_ghost_condition_signal 0
    #endif
#endif

#ifndef ghost_has_ghost_condition_signal

    #if GHOST_MUTEX_WINSLIM || GHOST_MUTEX_WINCS
        /* https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-wakeconditionvariable */
        #define ghost_condition_signal(condition) WakeConditionVariable(condition)
        #define ghost_has_ghost_condition_signal 1

    #elif GHOST_MUTEX_PTHREADS || GHOST_MUTEX_C11
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_condition_signal(ghost_condition_t* condition) {
            #if GHOST_MUTEX_PTHREADS
                /* https://man.archlinux.org/man/core/man-pages/pthread_cond_signal.3p.en */
                ghost_check(0 == pthread_cond_signal(condition), "");
            #elif GHOST_MUTEX_C11
                /* https://en.cppreference.com/w/c/thread/cnd_signal */
                ghost_check(thrd_success == cnd_signal(condition), "");
            #else
                #error "Unimplemented!"
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_condition_signal 1

    #elif GHOST_MUTEX_FUTEX
        /* TODO */
        #error
        #define ghost_has_ghost_condition_signal 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_ghost_condition_signal
    #define ghost_has_ghost_condition_signal 0
#endif

#endif
