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

#ifndef GHOST_IMPL_EX_ITHREAD_T_H_INCLUDED
#define GHOST_IMPL_EX_ITHREAD_T_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

#if GHOST_DOCUMENTATION
/*
 * ghost_impl_ex_ithread_t
 *
 * A wrapper for a platform handle type representing a thread that returns an
 * int.
 *
 * Don't call or override this; override ghost_ithread_t instead.
 */
typedef /*unspecified*/ ghost_impl_ex_ithread_t;
#endif

#if defined(ghost_has_ghost_impl_ex_ithread_t) || defined(ghost_impl_ex_ithread_t)
    #error "ghost_impl_ex_ithread_t cannot be overridden. Override ghost_ithread_t instead."
#endif

/* Handle ghost_ithread_t override here */
#ifndef ghost_has_ghost_ithread_t
    #ifdef ghost_ithread_t
        #define ghost_has_ghost_ithread_t 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_ithread_t so it can be used to
 * implement other thread types */
#ifdef ghost_has_ghost_ithread_t
    #if ghost_has_ghost_ithread_t
        #define ghost_impl_ex_ithread_t ghost_ithread_t
        #define ghost_has_ghost_impl_ex_ithread_t 1
    #endif
#endif

/* Windows */
#ifndef ghost_has_ghost_impl_ex_ithread_t
    #if GHOST_THREAD_WINDOWS
        #ifdef _M_IX86
            /* On x86 we need to be able to allocate a thunk. (Not that Windows
             * would ever not have malloc, but it's possible for the user to
             * override or disable it and our unit tests have variants that
             * test just that.) */
            #include "ghost/malloc/ghost_alloc.h"
            #include "ghost/malloc/ghost_free.h"
            #if ghost_has(ghost_alloc) && ghost_has(ghost_free)
                typedef HANDLE ghost_impl_ex_ithread_t;
                #define ghost_has_ghost_impl_ex_ithread_t 1
            #endif
        #else
            typedef HANDLE ghost_impl_ex_ithread_t;
            #define ghost_has_ghost_impl_ex_ithread_t 1
        #endif
    #endif
#endif

/* C11 */
#ifndef ghost_has_ghost_impl_ex_ithread_t
    #if GHOST_THREAD_C11
        typedef thrd_t ghost_impl_ex_ithread_t;
        #define ghost_has_ghost_impl_ex_ithread_t 1
    #endif
#endif

#ifndef ghost_has_ghost_impl_ex_ithread_t
    #define ghost_has_ghost_impl_ex_ithread_t 0
#endif

#endif
