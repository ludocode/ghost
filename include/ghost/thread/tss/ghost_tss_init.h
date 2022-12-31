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

#ifndef GHOST_TSS_INIT_H_INCLUDED
#define GHOST_TSS_INIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Creates a key for thread-specific storage.
 *
 * If you want to create a key with a destructor callback that will be run
 * automatically on non-null values upon thread exit, use ghost_tss_init_dtor()
 * instead.
 *
 * If any error occurs, ghost_fatal() is called, which by default aborts.
 *
 * @see ghost_tss_init_dtor
 */
void ghost_tss_init(ghost_tss_t* key);
#endif

/* Handle override */
#ifndef ghost_has_ghost_tss_init
    #ifdef ghost_tss_init
        #define ghost_has_ghost_tss_init 1
    #endif
#endif

/* We need a thread-specific storage type */
#ifndef ghost_has_ghost_tss_init
    #include "ghost/thread/tss/ghost_tss_t.h"
    #if !ghost_has(ghost_tss_t)
        #define ghost_has_ghost_tss_init 0
    #endif
#endif

/* Windows
 *     https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-tlsalloc */
#ifndef ghost_has_ghost_tss_init
    #if GHOST_TSS_WINDOWS
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_init(ghost_tss_t* ghost_impl_v_tss) {
            *ghost_impl_v_tss = TlsAlloc();
            ghost_ensure(*ghost_impl_v_tss != TLS_OUT_OF_INDEXES,
                    "TlsAlloc() failed with TLS_OUT_OF_INDEXES");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_init 1
    #endif
#endif

/* pthreads
 *     https://man.archlinux.org/man/pthread_key_create.3p.en */
#ifndef ghost_has_ghost_tss_init
    #if GHOST_TSS_PTHREADS
        #include "ghost/language/ghost_null.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_init(ghost_tss_t* ghost_impl_v_tss) {
            ghost_ensure(pthread_key_create(ghost_impl_v_tss, ghost_null) == 0,
                    "pthread_key_create() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_init 1
    #endif
#endif

/* C11 threads
 *     https://en.cppreference.com/w/c/thread/tss_create */
#ifndef ghost_has_ghost_tss_init
    #if GHOST_TSS_C11
        #include "ghost/language/ghost_null.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_init(ghost_tss_t* ghost_impl_v_tss) {
            ghost_ensure(tss_create(ghost_impl_v_tss, ghost_null) == thrd_success,
                    "tss_create() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_init 1
    #endif
#endif

#ifndef ghost_has_ghost_tss_init
    #define ghost_has_ghost_tss_init 0
#endif

#endif
