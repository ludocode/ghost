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

#ifndef GHOST_CONDITION_DESTROY_H_INCLUDED
#define GHOST_CONDITION_DESTROY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Destroys a condition variable.
 *
 * If any threads are waiting on the condition, the behaviour is undefined.
 *
 * On some platforms ghost_condition_destroy() does nothing. Make sure you call it
 * anyway to maintain portability with other platforms.
 */
void ghost_condition_destroy(ghost_condition_t* condition);
#endif

#include "ghost/thread/mutex/ghost_mutex_config.h"

#ifndef ghost_has_ghost_condition_destroy
    #ifdef ghost_condition_destroy
        #define ghost_has_ghost_condition_destroy 1
    #endif
#endif

#ifndef ghost_has_ghost_condition_destroy
    #include "ghost/thread/condition/ghost_condition_t.h"
    #if !ghost_has_ghost_condition_t
        #define ghost_has_ghost_condition_destroy 0
    #endif
#endif

#ifndef ghost_has_ghost_condition_destroy

    #if GHOST_MUTEX_WINSLIM || GHOST_MUTEX_WINCS || GHOST_MUTEX_FUTEX
        /* Nothing to do! */
        #include "ghost/language/ghost_discard.h"
        #define ghost_condition_destroy(condition) ghost_discard(condition)
        #define ghost_has_ghost_condition_destroy 1

    #elif GHOST_MUTEX_PTHREADS
        /* https://man.archlinux.org/man/pthread_cond_destroy.3p */
        #include "ghost/debug/ghost_check.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_condition_destroy(ghost_condition_t* condition) {
            ghost_check(0 == pthread_cond_destroy(condition), "");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_condition_destroy 1

    #elif GHOST_MUTEX_C11
        /* https://en.cppreference.com/w/c/thread/mtx_destroy */
        #define ghost_condition_destroy(condition) mtx_destroy(condition)
        #define ghost_has_ghost_condition_destroy 1

    #else
        #error "Unimplemented!"
    #endif
#endif

#ifndef ghost_has_ghost_condition_destroy
    #define ghost_has_ghost_condition_destroy 0
#endif

#endif
