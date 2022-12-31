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

#ifndef GHOST_TSS_INIT_DTOR_H_INCLUDED
#define GHOST_TSS_INIT_DTOR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Creates a key for thread-specific storage with a destructor callback that
 * will be run automatically on non-null values when a thread exits.
 *
 * If you want to create a key without a destructor callback, use
 * ghost_tss_init() instead.
 *
 * If any error occurs initializing the key, ghost_fatal() is called, which by
 * default aborts.
 *
 * When a thread exits, if the value of this key for the exiting thread is not
 * null, the value is set to null and then the destructor is run, passing in
 * the former value. After destructors for all keys have been run, if any are
 * still not null (i.e. the values have been set again), the process repeats.
 * This continues for an implementation-defined number of passes, or until all
 * keys with destructors are null.
 *
 * @see ghost_tss_init
 */
void ghost_tss_init_dtor(ghost_tss_t* key, void (*dtor)(void*));
#endif

/* Handle override */
#ifndef ghost_has_ghost_tss_init_dtor
    #ifdef ghost_tss_init_dtor
        #define ghost_has_ghost_tss_init_dtor 1
    #endif
#endif

/* We need a thread-specific storage type */
#ifndef ghost_has_ghost_tss_init_dtor
    #include "ghost/thread/tss/ghost_tss_t.h"
    #if !ghost_has(ghost_tss_t)
        #define ghost_has_ghost_tss_init_dtor 0
    #endif
#endif

/* Windows
 *     https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-tlsalloc */
#ifndef ghost_has_ghost_tss_init_dtor
    #if GHOST_TSS_WINDOWS
        /* Windows doesn't support destructors for its dynamic thread-local
         * storage.
         *
         * We could implement this manually for Ghost threads by tracking keys
         * ourselves and cleaning them up in our thread wrappers. We could also
         * use such an implementation on all platforms to remove any limit on
         * the maximum number of tss keys.
         *
         * This is certainly something I want to do but it can only work on
         * threads created through Ghost and it will add some overhead (so it
         * will probably be opt-in with a configuration option.) For these
         * reasons I haven't implemented it yet. In the meantime this is not
         * available. */
        #define ghost_has_ghost_tss_init_dtor 0
    #endif
#endif

/* pthreads
 *     https://man.archlinux.org/man/pthread_key_create.3p.en */
#ifndef ghost_has_ghost_tss_init_dtor
    #if GHOST_TSS_PTHREADS
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_init_dtor(ghost_tss_t* ghost_impl_v_tss, void (*ghost_impl_v_dtor)(void*)) {
            ghost_ensure(pthread_key_create(ghost_impl_v_tss, ghost_impl_v_dtor) == 0,
                    "pthread_key_create() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_init_dtor 1
    #endif
#endif

/* C11 threads
 *     https://en.cppreference.com/w/c/thread/tss_create */
#ifndef ghost_has_ghost_tss_init_dtor
    #if GHOST_TSS_C11
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_tss_init_dtor(ghost_tss_t* ghost_impl_v_tss, void (*ghost_impl_v_dtor)(void*)) {
            ghost_ensure(tss_create(ghost_impl_v_tss, ghost_impl_v_dtor) == thrd_success,
                    "tss_create() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_tss_init_dtor 1
    #endif
#endif

#ifndef ghost_has_ghost_tss_init_dtor
    #define ghost_has_ghost_tss_init_dtor 0
#endif

#endif
