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

#ifndef GHOST_VTHREAD_CREATE_H_INCLUDED
#define GHOST_VTHREAD_CREATE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Launch a new thread that returns void.
 *
 * The out_thread parameter is set to the thread handle before the thread
 * starts. This guarantees that the thread can access its own handle upon
 * starting up.
 *
 * You must either join or detach the thread, otherwise the thread handle will
 * be leaked.
 *
 * The thread callback function must return void. If joining the thread, you
 * must join with ghost_vthread_join(). To use a different return type, see
 * ghost_ithread_create() or ghost_vpthread_create().
 *
 * The options parameter can be used to customize the new thread. Pass null for
 * options if you want to use the defaults. See ghost_thread_options_t for
 * documentation on thread options.
 *
 * @see ghost_vthread_join
 * @see ghost_ithread_create
 * @see ghost_vpthread_create
 * @see ghost_thread_options_t
 */
void ghost_vthread_create(
        ghost_vthread_t* out_thread,
        int (*callback)(void* context),
        void* context,
        ghost_thread_options_t* /*nullable*/ options);
#endif

/* Handle override */
#ifndef ghost_has_ghost_vthread_create
    #ifdef ghost_vthread_create
        #define ghost_has_ghost_vthread_create 1
    #endif
#endif

/* A thread type is required */
#ifndef ghost_has_ghost_vthread_create
    #include "ghost/thread/vthread/ghost_vthread_t.h"
    #if !ghost_has(ghost_vthread_t)
        #define ghost_has_ghost_vthread_create 0
    #endif
#endif

/* Synthesize from a thread returning int or void*. */
#ifndef ghost_has_ghost_vthread_create
    #include "ghost/impl/thread/ghost_impl_ex_ithread_create.h"
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_create.h"
    #if ghost_has(ghost_impl_ex_ithread_create) || ghost_has(ghost_impl_ex_vpthread_create)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/thread/thread_options/ghost_thread_options_t.h"
        #include "ghost/debug/ghost_ensure.h"
        #include "ghost/malloc/ghost_free.h"
        #include "ghost/malloc/ghost_alloc.h"
        #if !ghost_has(ghost_impl_ex_ithread_create)
            #include "ghost/language/ghost_null.h"
        #endif

        GHOST_IMPL_FUNCTION_OPEN

        typedef struct {
            void (*ghost_impl_user_function)(void* ghost_impl_user_context);
            void* ghost_impl_user_context;
        } ghost_impl_vthread_wrapper_t;

        ghost_impl_function
        #if ghost_has(ghost_impl_ex_ithread_create)
            int
        #elif ghost_has(ghost_impl_ex_vpthread_create)
            void*
        #endif
        ghost_impl_thread_wrapper_i_or_vp(void* ghost_impl_vwrapper)
        #if !GHOST_EMIT_DEFS
            ;
        #else
            {
                ghost_impl_vthread_wrapper_t ghost_impl_wrapper = *ghost_static_cast(
                        ghost_impl_vthread_wrapper_t*, ghost_impl_vwrapper);
                ghost_free(ghost_impl_vwrapper);
                ghost_impl_wrapper.ghost_impl_user_function(ghost_impl_wrapper.ghost_impl_user_context);

                return
                #if ghost_has(ghost_impl_ex_ithread_create)
                    0
                #elif ghost_has(ghost_impl_ex_vpthread_create)
                    ghost_null
                #endif
                    ;
            }
        #endif

        ghost_impl_inline
        void ghost_vthread_create(ghost_vthread_t* ghost_impl_out_thread,
                void (*ghost_impl_user_function)(void* ghost_impl_user_context),
                void* ghost_impl_user_context,
                ghost_thread_options_t* options)
        {
            ghost_impl_vthread_wrapper_t* ghost_impl_wrapper = ghost_alloc(ghost_impl_vthread_wrapper_t);
            ghost_ensure(ghost_impl_wrapper != ghost_null, "Failed to allocate int thread wrapper");
            ghost_impl_wrapper->ghost_impl_user_function = ghost_impl_user_function;
            ghost_impl_wrapper->ghost_impl_user_context = ghost_impl_user_context;

            #if ghost_has(ghost_impl_ex_ithread_create)
                ghost_impl_ex_ithread_create
            #elif ghost_has(ghost_impl_ex_vpthread_create)
                ghost_impl_ex_vpthread_create
            #endif
                (&ghost_impl_out_thread->ghost_impl_platform_thread,
                    ghost_impl_thread_wrapper_i_or_vp, ghost_impl_wrapper, options);
        }

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_vthread_create 1
    #endif
#endif

#ifndef ghost_has_ghost_vthread_create
    #define ghost_has_ghost_vthread_create 0
#endif

#endif
