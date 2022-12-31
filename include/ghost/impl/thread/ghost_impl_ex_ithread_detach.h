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

#ifndef GHOST_IMPL_EX_ITHREAD_DETACH_H_INCLUDED
#define GHOST_IMPL_EX_ITHREAD_DETACH_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

/*
 * ghost_impl_ex_ithread_detach()
 *
 * A wrapper for a platform function that detachs a thread that returns an int.
 *
 * Don't call or override this; use ghost_ithread_detach() instead.
 */

#if defined(ghost_has_ghost_impl_ex_ithread_detach) || defined(ghost_impl_ex_ithread_detach)
    #error "ghost_impl_ex_ithread_detach cannot be overridden. Override ghost_ithread_detach instead."
#endif

/* Handle ghost_ithread_detach override here */
#ifndef ghost_has_ghost_ithread_detach
    #ifdef ghost_ithread_detach
        #define ghost_has_ghost_ithread_detach 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_ithread_detach so it can be used to
 * implement other thread types */
#ifdef ghost_has_ghost_ithread_detach
    #if ghost_has_ghost_ithread_detach
        #define ghost_impl_ex_ithread_detach ghost_ithread_detach
        #define ghost_has_ghost_impl_ex_ithread_detach 1
    #endif
#endif

/* We need a thread type */
#ifndef ghost_has_ghost_impl_ex_ithread_detach
    #include "ghost/impl/thread/ghost_impl_ex_ithread_t.h"
    #if !ghost_has(ghost_impl_ex_ithread_t)
        #define ghost_has_ghost_impl_ex_ithread_detach 0
    #endif
#endif

/*
 * Windows
 *     https://docs.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
 */
#ifndef ghost_has_ghost_impl_ex_ithread_detach
    #if GHOST_THREAD_WINDOWS
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_impl_ex_ithread_detach(ghost_impl_ex_ithread_t* ghost_impl_thread) {
            ghost_ensure(CloseHandle(*ghost_impl_thread), "Failed to CloseHandle() thread");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_impl_ex_ithread_detach 1
    #endif
#endif

/*
 * C11
 *     https://en.cppreference.com/w/c/thread/thrd_detach
 */
#ifndef ghost_has_ghost_impl_ex_ithread_detach
    #if GHOST_THREAD_C11
        #include "ghost/debug/ghost_ensure.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_impl_ex_ithread_detach(ghost_impl_ex_ithread_t* ghost_impl_thread) {
            ghost_ensure(thrd_success == thrd_detach(*ghost_impl_thread), "thrd_detach() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_impl_ex_ithread_detach 1
    #endif
#endif

#ifndef ghost_has_ghost_impl_ex_ithread_detach
    #define ghost_has_ghost_impl_ex_ithread_detach 0
#endif

#endif
