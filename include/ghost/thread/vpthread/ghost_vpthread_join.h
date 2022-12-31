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

#ifndef GHOST_VPTHREAD_JOIN_H_INCLUDED
#define GHOST_VPTHREAD_JOIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Joins a Ghost thread returning void*, blocking until the thread exits and
 * returning the thread function's return value.
 */
void* ghost_vpthread_join(ghost_vpthread_t* thread);
#endif

/* Override is handled in the ex wrapper */
#include "ghost/impl/thread/ghost_impl_ex_vpthread_join.h"

/* A thread type is required */
#ifndef ghost_has_ghost_vpthread_join
    #include "ghost/thread/vpthread/ghost_vpthread_t.h"
    #if !ghost_has(ghost_vpthread_t)
        #define ghost_has_ghost_vpthread_join 0
    #endif
#endif

/* If we have a real thread type returning int, use it */
#ifndef ghost_has_ghost_vpthread_join
    #if ghost_has_ghost_impl_ex_vpthread_join
        #define ghost_vpthread_join ghost_impl_ex_vpthread_join
        #define ghost_has_ghost_vpthread_join 1
    #endif
#endif

/* Synthesize it from a thread returning int. */
#ifndef ghost_has_ghost_vpthread_join
    #include "ghost/impl/thread/ghost_impl_ex_ithread_join.h"
    #if ghost_has_ghost_impl_ex_ithread_join
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_bit_cast.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/language/ghost_discard.h"
        #include "ghost/debug/ghost_check.h"
        #include "ghost/type/intptr_t/ghost_intptr_t.h"
        #include "ghost/type/int/ghost_int_width.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void* ghost_vpthread_join(ghost_vpthread_t* ghost_v_thread) {
            int ghost_v_ret = ghost_impl_ex_ithread_join(&ghost_v_thread->ghost_impl_platform_thread);
            #if GHOST_INT_WIDTH >= GHOST_INTPTR_WIDTH
                /* We're not using auxiliary storage. The return value can be
                 * cast directly. */
                return ghost_bit_cast(void*, ghost_intptr_t, ghost_static_cast(ghost_intptr_t, ghost_v_ret));
            #else
                /* We need to fetch the return value from auxiliary storage. */
                ghost_check(ghost_v_ret == 0, "return value should have been zero");
                return ghost_impl_thread_aux_join(ghost_v_thread->ghost_v_aux_index);
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_vpthread_join 1
    #endif
#endif

#ifndef ghost_has_ghost_vpthread_join
    #define ghost_has_ghost_vpthread_join 0
#endif

#endif
