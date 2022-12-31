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

#ifndef GHOST_ITHREAD_CREATE_H_INCLUDED
#define GHOST_ITHREAD_CREATE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Launch a new thread that returns an int.
 *
 * The out_thread parameter is set to the thread handle before the thread
 * starts. This guarantees that the thread can access its own handle upon
 * starting up.
 *
 * You must either join or detach the thread, otherwise the thread handle will
 * be leaked.
 *
 * The thread callback function must return an int. If joining the thread, you
 * must join with ghost_ithread_join() which will return the int. If the
 * thread is detached, the return value of the thread will be discarded. To use
 * a different return type, see ghost_vpthread_create() or
 * ghost_vthread_create().
 *
 * The options parameter can be used to customize the new thread. Pass null for
 * options if you want to use the defaults. See ghost_thread_options_t for
 * documentation on thread options.
 *
 * If thread creation fails, by default the program aborts. You can instead
 * enable error reporting in the thread options if you want to handle errors.
 * See ghost_thread_options_set_report_error().
 *
 * @see ghost_ithread_join()
 * @see ghost_vpthread_create()
 * @see ghost_vthread_create()
 * @see ghost_thread_options_t
 * @see ghost_thread_options_set_report_error()
 */
void ghost_ithread_create(
        ghost_ithread_t* out_thread,
        int (*callback)(void* context),
        void* context,
        ghost_thread_options_t* /*nullable*/ options);
#endif

/* Override is handled in the ex wrapper */
#include "ghost/impl/thread/ghost_impl_ex_ithread_create.h"

/* A thread type is required */
#ifndef ghost_has_ghost_ithread_create
    #include "ghost/thread/ithread/ghost_ithread_t.h"
    #if !ghost_has(ghost_ithread_t)
        #define ghost_has_ghost_ithread_create 0
    #endif
#endif

/* If we have a real thread type returning int, use it */
#ifndef ghost_has_ghost_ithread_create
    #if ghost_has_ghost_impl_ex_ithread_create
        #define ghost_ithread_create ghost_impl_ex_ithread_create
        #define ghost_has_ghost_ithread_create 1
    #endif
#endif

/* Synthesize it from a thread returning void*. Our thread type header above
 * has checked that int fits in void*. */
#ifndef ghost_has_ghost_ithread_create
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_create.h"
    #if ghost_has(ghost_impl_ex_vpthread_create)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/thread/thread_options/ghost_thread_options_t.h"
        #include "ghost/language/ghost_bit_cast.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/intptr_t/ghost_intptr_t.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN

        typedef struct {
            int (*ghost_impl_user_function)(void* ghost_impl_user_context);
            void* ghost_impl_user_context;
        } ghost_impl_ithread_wrapper_t;

        ghost_impl_function
        void* ghost_impl_ithread_wrapper(void* ghost_impl_vwrapper) GHOST_IMPL_DEF({
            int ghost_impl_v_ret;
            ghost_impl_ithread_wrapper_t ghost_impl_wrapper = *ghost_static_cast(
                    ghost_impl_ithread_wrapper_t*, ghost_impl_vwrapper);
            ghost_free(ghost_impl_vwrapper);
            ghost_impl_v_ret = ghost_impl_wrapper.ghost_impl_user_function(ghost_impl_wrapper.ghost_impl_user_context);
            return ghost_bit_cast(void*, ghost_intptr_t, ghost_static_cast(ghost_intptr_t, ghost_impl_v_ret));
        })

        ghost_impl_inline
        void ghost_ithread_create(ghost_ithread_t* ghost_impl_out_thread,
                int (*ghost_impl_user_function)(void* ghost_impl_user_context),
                void* ghost_impl_user_context,
                ghost_thread_options_t* options)
        {
            ghost_impl_ithread_wrapper_t* ghost_impl_wrapper = ghost_alloc(ghost_impl_ithread_wrapper_t);
            ghost_ensure(ghost_impl_wrapper != ghost_null, "Failed to allocate int thread wrapper");
            ghost_impl_wrapper->ghost_impl_user_function = ghost_impl_user_function;
            ghost_impl_wrapper->ghost_impl_user_context = ghost_impl_user_context;
            ghost_impl_ex_vpthread_create(&ghost_impl_out_thread->ghost_impl_platform_thread,
                    ghost_impl_ithread_wrapper, ghost_impl_wrapper, options);
        }

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_ithread_create 1
    #endif
#endif

#ifndef ghost_has_ghost_ithread_create
    #define ghost_has_ghost_ithread_create 0
#endif

#endif
