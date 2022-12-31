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

#ifndef GHOST_CONDITION_INIT_H_INCLUDED
#define GHOST_CONDITION_INIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Initializes a condition variable.
 *
 * You must destroy the condition with ghost_condition_destroy().
 */
void ghost_condition_init(ghost_condition_t* condition);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_condition_init
    #ifdef ghost_condition_init
        #define ghost_has_ghost_condition_init 1
    #endif
#endif

#ifndef ghost_has_ghost_condition_init
    #include "ghost/thread/condition/ghost_condition_t.h"
    #if !ghost_has_ghost_condition_t
        #define ghost_has_ghost_condition_init 0
    #endif
#endif

#ifndef ghost_has_ghost_condition_init

    #if GHOST_MUTEX_WINSLIM || GHOST_MUTEX_WINCS
        /* https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initializeconditionvariable */
        #define ghost_condition_init(condition) InitializeConditionVariable(condition)
        #define ghost_has_ghost_condition_init 1

    #elif GHOST_MUTEX_PTHREADS || GHOST_MUTEX_C11
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_condition_init(ghost_condition_t* condition) {
            #if GHOST_MUTEX_PTHREADS
                /* https://man.archlinux.org/man/core/man-pages/pthread_cond_destroy.3p.en */
                ghost_check(0 == pthread_cond_init(condition, ghost_null), "");
            #elif GHOST_MUTEX_C11
                /* https://en.cppreference.com/w/c/thread/cnd_init */
                ghost_check(thrd_success == cnd_init(condition), "");
            #else
                #error
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_condition_init 1

    #elif GHOST_MUTEX_FUTEX
        /* TODO */
        #error
        #define ghost_has_ghost_condition_init 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_ghost_condition_init
    #define ghost_has_ghost_condition_init 0
#endif

#endif
