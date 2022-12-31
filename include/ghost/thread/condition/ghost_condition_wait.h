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

#ifndef GHOST_CONDITION_WAIT_H_INCLUDED
#define GHOST_CONDITION_WAIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Waits on the given condition, releasing the given mutex atomically before
 * sleeping and re-acquiring it upon awakening.
 *
 * The mutex must have been locked by this thread. (In the case of a recursive
 * mutex, it must have been locked exactly once).
 *
 * The thread will wake when the condition is signalled or broadcast and may
 * wake spuriously. Ghost does not report why the thread woke up. You should
 * generally loop on a predicate like this:
 *
 *     while (!data_ready)
 *         ghost_condition_wait(condition, mutex);
 */
void ghost_condition_wait(ghost_condition_t* condition, ghost_mutex_t* mutex);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_condition_wait
    #ifdef ghost_condition_wait
        #define ghost_has_ghost_condition_wait 1
    #endif
#endif

#ifndef ghost_has_ghost_condition_wait
    #include "ghost/thread/condition/ghost_condition_t.h"
    #include "ghost/thread/mutex/ghost_mutex_t.h"
    #if !ghost_has_ghost_condition_t || !ghost_has_ghost_mutex_t
        #define ghost_has_ghost_condition_wait 0
    #endif
#endif

#ifndef ghost_has_ghost_condition_wait
    #include "ghost/debug/ghost_check.h"
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    void ghost_condition_wait(ghost_condition_t* condition, ghost_mutex_t* mutex) {
        #if GHOST_MUTEX_WINSLIM
            /* https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-sleepconditionvariablesrw */
            ghost_check(SleepConditionVariableSRW(condition, mutex, INFINITE, 0), "");
        #elif GHOST_MUTEX_WINCS
            /* https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-sleepconditionvariablecs */
            ghost_check(SleepConditionVariableCS(condition, mutex, INFINITE), "");
        #elif GHOST_MUTEX_PTHREADS
            /* https://man.archlinux.org/man/core/man-pages/pthread_cond_timedwait.3p.en */
            ghost_check(0 == pthread_cond_wait(condition, mutex), "");
        #elif GHOST_MUTEX_C11
            /* https://en.cppreference.com/w/c/thread */
            ghost_check(thrd_success == cnd_wait(condition, mutex), "");
        #elif GHOST_MUTEX_FUTEX
            /* TODO */
            #error
        #else
            #error "Unimplemented!"
        #endif
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_condition_wait 1
#endif

#ifndef ghost_has_ghost_condition_wait
    #define ghost_has_ghost_condition_wait 0
#endif

#endif
