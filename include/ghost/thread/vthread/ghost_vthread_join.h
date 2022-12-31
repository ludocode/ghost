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

#ifndef GHOST_VTHREAD_JOIN_H_INCLUDED
#define GHOST_VTHREAD_JOIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Joins a Ghost thread returning void, blocking until the thread exits.
 */
void ghost_vthread_join(ghost_vthread_t* thread);
#endif

/* Handle override */
#ifndef ghost_has_ghost_vthread_join
    #ifdef ghost_vthread_join
        #define ghost_has_ghost_vthread_join 1
    #endif
#endif

/* A thread type is required */
#ifndef ghost_has_ghost_vthread_join
    #include "ghost/thread/vthread/ghost_vthread_t.h"
    #if !ghost_has(ghost_vthread_t)
        #define ghost_has_ghost_vthread_join 0
    #endif
#endif

/* Synthesize it from a thread returning int or void*. */
#ifndef ghost_has_ghost_vthread_join
    #include "ghost/impl/thread/ghost_impl_ex_ithread_join.h"
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_join.h"
    #if ghost_has(ghost_impl_ex_ithread_join) || ghost_has(ghost_impl_ex_vpthread_join)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/language/ghost_discard.h"
        #if !ghost_has(ghost_impl_ex_ithread_join)
            #include "ghost/language/ghost_null.h"
        #endif
        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_inline
        void ghost_vthread_join(ghost_vthread_t* ghost_v_thread) {
            #if ghost_has(ghost_impl_ex_ithread_join)
                int ghost_v_ret = ghost_impl_ex_ithread_join(&ghost_v_thread->ghost_impl_platform_thread);
                ghost_assert(ghost_v_ret == 0, "thread returned unexpected value");
            #elif ghost_has(ghost_impl_ex_vpthread_join)
                void* ghost_v_ret = ghost_impl_ex_vpthread_join(&ghost_v_thread->ghost_impl_platform_thread);
                ghost_assert(ghost_v_ret == ghost_null, "thread returned unexpected value");
            #endif
            ghost_discard(ghost_v_ret);
        }

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_vthread_join 1
    #endif
#endif

#ifndef ghost_has_ghost_vthread_join
    #define ghost_has_ghost_vthread_join 0
#endif

#endif
