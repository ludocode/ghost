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

#ifndef GHOST_TSS_SET_H_INCLUDED
#define GHOST_TSS_SET_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Sets the value of a thread-specific storage key for the current thread.
 *
 * If any error occurs, ghost_fatal() is called, which by default aborts.
 */
void ghost_tss_set(ghost_tss_t* key, void* value);
#endif

/* Handle override */
#ifndef ghost_has_ghost_tss_set
    #ifdef ghost_tss_set
        #define ghost_has_ghost_tss_set 1
    #endif
#endif

/* We need a thread-specific storage type */
#ifndef ghost_has_ghost_tss_set
    #include "ghost/thread/tss/ghost_tss_t.h"
    #if !ghost_has(ghost_tss_t)
        #define ghost_has_ghost_tss_set 0
    #endif
#endif

/* Windows
 *     https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-tlssetvalue */
#ifndef ghost_has_ghost_tss_set
    #if GHOST_TSS_WINDOWS
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void* ghost_tss_set(ghost_tss_t* ghost_impl_v_tss, void* ghost_impl_v_value) {
            ghost_ensure(TlsSetValue(*ghost_impl_v_tss, ghost_impl_v_value),
                    "TlsSetValue() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_set 1
    #endif
#endif

/* pthreads
 *     https://man.archlinux.org/man/pthread_setspecific.3p */
#ifndef ghost_has_ghost_tss_set
    #if GHOST_TSS_PTHREADS
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_set(ghost_tss_t* ghost_impl_v_tss, void* ghost_impl_v_value) {
            ghost_ensure(pthread_setspecific(*ghost_impl_v_tss, ghost_impl_v_value) == 0,
                    "pthread_setspecific() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_set 1
    #endif
#endif

/* C11 threads
 *     https://en.cppreference.com/w/c/thread/tss_set */
#ifndef ghost_has_ghost_tss_set
    #if GHOST_TSS_C11
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_set(ghost_tss_t* ghost_impl_v_tss, void* ghost_impl_v_value) {
            ghost_ensure(tss_set(*ghost_impl_v_tss, ghost_impl_v_value) == thrd_success,
                    "tss_set() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_set 1
    #endif
#endif

#ifndef ghost_has_ghost_tss_set
    #define ghost_has_ghost_tss_set 0
#endif

#endif
