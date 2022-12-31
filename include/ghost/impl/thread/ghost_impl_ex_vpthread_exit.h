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

#ifndef GHOST_IMPL_EX_VPTHREAD_EXIT_H_INCLUDED
#define GHOST_IMPL_EX_VPTHREAD_EXIT_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

/*
 * ghost_impl_ex_vpthread_exit()
 *
 * A wrapper for a platform function that exits a thread that returns void*.
 *
 * Don't call or override this; use ghost_vpthread_exit() instead.
 */

#if defined(ghost_has_ghost_impl_ex_vpthread_exit) || defined(ghost_impl_ex_vpthread_exit)
    #error "ghost_impl_ex_vpthread_exit cannot be overridden. Override ghost_vpthread_exit instead."
#endif

/* Handle ghost_vpthread_exit override here */
#ifndef ghost_has_ghost_vpthread_exit
    #ifdef ghost_vpthread_exit
        #define ghost_has_ghost_vpthread_exit 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_vpthread_exit so it can be used to
 * implement other thread types */
#ifdef ghost_has_ghost_vpthread_exit
    #if ghost_has_ghost_vpthread_exit
        #define ghost_impl_ex_vpthread_exit ghost_vpthread_exit
        #define ghost_has_ghost_impl_ex_vpthread_exit 1
    #endif
#endif

/* We need a thread type */
#ifndef ghost_has_ghost_impl_ex_vpthread_exit
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_t.h"
    #if !ghost_has(ghost_impl_ex_vpthread_t)
        #define ghost_has_ghost_impl_ex_vpthread_exit 0
    #endif
#endif

/*
 * pthreads
 *     https://man.archlinux.org/man/pthread_exit.3.en
 */
#ifndef ghost_has_ghost_impl_ex_vpthread_exit
    #if GHOST_THREAD_PTHREADS
        #define ghost_impl_ex_vpthread_exit pthread_exit
        #define ghost_has_ghost_impl_ex_vpthread_exit 1
    #endif
#endif

#ifndef ghost_has_ghost_impl_ex_vpthread_exit
    #define ghost_has_ghost_impl_ex_vpthread_exit 0
#endif

#endif
