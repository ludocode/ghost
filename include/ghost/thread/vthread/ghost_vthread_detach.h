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

#ifndef GHOST_VTHREAD_DETACH_H_INCLUDED
#define GHOST_VTHREAD_DETACH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
void ghost_vthread_detach(ghost_vthread_t* thread);
#endif

/* Handle override */
#ifndef ghost_has_ghost_vthread_detach
    #ifdef ghost_vthread_detach
        #define ghost_has_ghost_vthread_detach 1
    #endif
#endif

/* A thread type is required */
#ifndef ghost_has_ghost_vthread_detach
    #include "ghost/thread/vthread/ghost_vthread_t.h"
    #if !ghost_has(ghost_vthread_t)
        #define ghost_has_ghost_vthread_detach 0
    #endif
#endif

/* Synthesize it from a thread returning int or void*. */
#ifndef ghost_has_ghost_vthread_detach
    #include "ghost/impl/thread/ghost_impl_ex_ithread_detach.h"
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_detach.h"
    #if ghost_has(ghost_impl_ex_ithread_detach) || ghost_has(ghost_impl_ex_vpthread_detach)
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_vthread_detach(ghost_vthread_t* ghost_v_thread) {
            #if ghost_has(ghost_impl_ex_ithread_detach)
                ghost_impl_ex_ithread_detach
            #elif ghost_has(ghost_impl_ex_vpthread_detach)
                ghost_impl_ex_vpthread_detach
            #endif
                (&ghost_v_thread->ghost_impl_platform_thread);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_vthread_detach 1
    #endif
#endif

#ifndef ghost_has_ghost_vthread_detach
    #define ghost_has_ghost_vthread_detach 0
#endif

#endif
