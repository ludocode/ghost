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

#ifndef GHOST_TSS_DESTROY_H_INCLUDED
#define GHOST_TSS_DESTROY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Destroys a key for thread-specific storage.
 *
 * No destructors are run for any existing values of the key (for keys created
 * with ghost_tss_init_dtor().)
 *
 * If any error occurs, ghost_fatal() is called, which by default aborts.
 *
 * @see ghost_tss_init
 * @see ghost_tss_init_dtor
 */
void ghost_tss_destroy(ghost_tss_t* key);
#endif

/* Handle override */
#ifndef ghost_has_ghost_tss_destroy
    #ifdef ghost_tss_destroy
        #define ghost_has_ghost_tss_destroy 1
    #endif
#endif

/* We need a thread-specific storage type */
#ifndef ghost_has_ghost_tss_destroy
    #include "ghost/thread/tss/ghost_tss_t.h"
    #if !ghost_has(ghost_tss_t)
        #define ghost_has_ghost_tss_destroy 0
    #endif
#endif

/* Windows
 *     https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-tlsfree */
#ifndef ghost_has_ghost_tss_destroy
    #if GHOST_TSS_WINDOWS
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_destroy(ghost_tss_t* ghost_impl_v_tss) {
            ghost_ensure(TlsFree(*ghost_impl_v_tss), "TlsFree() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_destroy 1
    #endif
#endif

/* pthreads
 *     https://man.archlinux.org/man/pthread_key_delete.3p */
#ifndef ghost_has_ghost_tss_destroy
    #if GHOST_TSS_PTHREADS
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_destroy(ghost_tss_t* ghost_impl_v_tss) {
            ghost_ensure(pthread_key_delete(*ghost_impl_v_tss) == 0,
                    "pthread_key_delete() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_destroy 1
    #endif
#endif

/* C11 threads
 *     https://en.cppreference.com/w/c/thread/tss_delete */
#ifndef ghost_has_ghost_tss_destroy
    #if GHOST_TSS_C11
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_destroy(ghost_tss_t* ghost_impl_v_tss) {
            tss_delete(*ghost_impl_v_tss);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_destroy 1
    #endif
#endif

#ifndef ghost_has_ghost_tss_destroy
    #define ghost_has_ghost_tss_destroy 0
#endif

#endif
