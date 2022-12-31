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

#ifndef GHOST_IMPL_EX_VPTHREAD_DETACH_H_INCLUDED
#define GHOST_IMPL_EX_VPTHREAD_DETACH_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

/*
 * ghost_impl_ex_vpthread_detach()
 *
 * A wrapper for a platform function that detachs a thread that returns an int.
 *
 * Don't call or override this; use ghost_vpthread_detach() instead.
 */

#if defined(ghost_has_ghost_impl_ex_vpthread_detach) || defined(ghost_impl_ex_vpthread_detach)
    #error "ghost_impl_ex_vpthread_detach cannot be overridden. Override ghost_vpthread_detach instead."
#endif

/* Handle ghost_vpthread_detach override here */
#ifndef ghost_has_ghost_vpthread_detach
    #ifdef ghost_vpthread_detach
        #define ghost_has_ghost_vpthread_detach 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_vpthread_detach so it can be used to
 * implement other thread types */
#ifdef ghost_has_ghost_vpthread_detach
    #if ghost_has_ghost_vpthread_detach
        #define ghost_impl_ex_vpthread_detach ghost_vpthread_detach
        #define ghost_has_ghost_impl_ex_vpthread_detach 1
    #endif
#endif

/* We need a thread type */
#ifndef ghost_has_ghost_impl_ex_vpthread_detach
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_t.h"
    #if !ghost_has(ghost_impl_ex_vpthread_t)
        #define ghost_has_ghost_impl_ex_vpthread_detach 0
    #endif
#endif

/*
 * pthreads
 *     https://man.archlinux.org/man/pthread_detach.3
 */
#ifndef ghost_has_ghost_impl_ex_vpthread_detach
    #if GHOST_THREAD_PTHREADS
        #include "ghost/debug/ghost_ensure.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_impl_ex_vpthread_detach(ghost_impl_ex_vpthread_t* ghost_impl_thread) {
            ghost_ensure(0 == pthread_detach(*ghost_impl_thread), "pthread_detach() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_impl_ex_vpthread_detach 1
    #endif
#endif

#ifndef ghost_has_ghost_impl_ex_vpthread_detach
    #define ghost_has_ghost_impl_ex_vpthread_detach 0
#endif

#endif
