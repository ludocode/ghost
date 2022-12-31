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

#ifndef GHOST_IMPL_EX_ITHREAD_CREATE_H_INCLUDED
#define GHOST_IMPL_EX_ITHREAD_CREATE_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

/*
 * ghost_impl_ex_ithread_create()
 *
 * A wrapper for a platform function that creates a thread that returns an int.
 *
 * Don't call or override this; use ghost_ithread_create() instead.
 */

#if defined(ghost_has_ghost_impl_ex_ithread_create) || defined(ghost_impl_ex_ithread_create)
    #error "ghost_impl_ex_ithread_create cannot be overridden. Override ghost_ithread_create instead."
#endif

/* Handle ghost_ithread_create override here */
#ifndef ghost_has_ghost_ithread_create
    #ifdef ghost_ithread_create
        #define ghost_has_ghost_ithread_create 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_ithread_create so it can be used to
 * implement other thread types */
#ifdef ghost_has_ghost_ithread_create
    #if ghost_has_ghost_ithread_create
        #define ghost_impl_ex_ithread_create ghost_ithread_create
        #define ghost_has_ghost_impl_ex_ithread_create 1
    #endif
#endif

/* We need a thread type */
#ifndef ghost_has_ghost_impl_ex_ithread_create
    #include "ghost/impl/thread/ghost_impl_ex_ithread_t.h"
    #if !ghost_has(ghost_impl_ex_ithread_t)
        #define ghost_has_ghost_impl_ex_ithread_create 0
    #endif
#endif

/*
 * Windows
 *     https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
 *     https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-resumethread
 */
#ifndef ghost_has_ghost_impl_ex_ithread_create
    #if GHOST_THREAD_WINDOWS
        #include "ghost/header/windows/ghost_windows_h.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/debug/ghost_fatal.h"
        #include "ghost/debug/ghost_ensure.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/language/ghost_reinterpret_cast.h"
        #include "ghost/malloc/ghost_alloc.h"
        #include "ghost/malloc/ghost_free.h"
        #include "ghost/string/ghost_memset.h"
        #include "ghost/type/bool/ghost_true.h"
        #include "ghost/thread/thread_options/ghost_thread_options_t.h"
        GHOST_IMPL_FUNCTION_OPEN

        /* On Windows the default calling convention is __cdecl but the thread
         * callback must be __stdcall. We need a thunk to do the conversion. */
        #if defined(_M_IX86) && GHOST_EMIT_DEFS
            typedef struct {
                int (*ghost_impl_user_function)(void* ghost_impl_user_context);
                void* ghost_impl_user_context;
            } ghost_impl_ex_ithread_thunk_t;

            ghost_impl_function
            DWORD WINAPI ghost_impl_ex_ithread_thunk(LPVOID ghost_impl_vthunk) {
                ghost_impl_ex_ithread_thunk_t ghost_impl_thunk = *ghost_static_cast(
                        ghost_impl_ex_ithread_thunk_t*, ghost_impl_vthunk);
                ghost_free(ghost_impl_vthunk);
                return ghost_impl_thunk.ghost_impl_user_function(ghost_impl_thunk.ghost_impl_user_context);
            }
        #endif

        ghost_impl_function
        void ghost_impl_ex_ithread_create(ghost_impl_ex_ithread_t* ghost_impl_out_thread,
                int (*function)(void* context), void* context,
                ghost_thread_options_t* options)
        #if !GHOST_EMIT_DEFS
        ;
        #else
        {
            ghost_size_t stack_size = (options == ghost_null) ? 0 : options->ghost_impl_stack_size;

            #ifdef _M_IX86
                /* Allocate our thunk above */
                LPTHREAD_START_ROUTINE ghost_impl_v_threadproc = ghost_impl_ex_ithread_thunk;
                ghost_impl_ex_ithread_thunk_t* ghost_impl_v_parameter = ghost_alloc(ghost_impl_ex_ithread_thunk_t);
                ghost_ensure(ghost_impl_v_parameter != ghost_null, "Failed to allocate thunk");
                ghost_impl_v_parameter->ghost_impl_user_function = function;
                ghost_impl_v_parameter->ghost_impl_user_context = context;
            #else
                /* On other architectures, __cdecl and __stdcall are the same.
                 * The signature doesn't exactly match because DWORD is long,
                 * not int, but they're the same size on Windows so it's safe
                 * to cast it. We cast to our own type without __stdcall to
                 * ensure that we don't get a compiler error in the conversion. */
                typedef DWORD (*ghost_impl_v_threadproc_t)(LPVOID);
                LPTHREAD_START_ROUTINE ghost_impl_v_threadproc = ghost_reinterpret_cast(ghost_impl_v_threadproc_t, function);
                void* ghost_impl_v_parameter = context;
            #endif

            /* Create suspended so that the thread handle is assigned first. */
            *ghost_impl_out_thread = CreateThread(
                    NULL, stack_size, ghost_impl_v_threadproc, ghost_impl_v_parameter,
                    /* We assume committing the entire stack is not necessary.
                     * This lets you use a large safety margin on stack space
                     * without wasting memory.
                     * (This could be made into an option.) */
                    CREATE_SUSPENDED | STACK_SIZE_PARAM_IS_A_RESERVATION, ghost_null);

            if (*ghost_impl_out_thread == ghost_null) {
                if (options != ghost_null && options->ghost_impl_report_error) {
                    options->ghost_impl_thread_error_occurred = ghost_true;
                    return;
                } else {
                    ghost_fatal("CreateThread() failed");
                }
            }

            ghost_ensure(ResumeThread(*ghost_impl_out_thread) != -1, "ResumeThread() failed");

            if (options != ghost_null && options->ghost_impl_detached) {
                ghost_ensure(CloseHandle(*ghost_impl_out_thread), "Failed to CloseHandle() to detach new thread");
                ghost_memset(ghost_impl_out_thread, 0, sizeof(*ghost_impl_out_thread));
            }
        }
        #endif

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_impl_ex_ithread_create 1
    #endif
#endif

/*
 * C11
 *     https://en.cppreference.com/w/c/thread/thrd_create
 */
#ifndef ghost_has_ghost_impl_ex_ithread_create
    #if GHOST_THREAD_C11
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/debug/ghost_fatal.h"
        #include "ghost/debug/ghost_ensure.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/string/ghost_memset.h"
        #include "ghost/thread/thread_options/ghost_thread_options_t.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        void ghost_impl_ex_ithread_create(ghost_impl_ex_ithread_t* ghost_impl_out_thread,
                int (*function)(void* context), void* context,
                ghost_thread_options_t* options) GHOST_IMPL_DEF(
        {
            ghost_assert(options == ghost_null || options->ghost_impl_stack_size == 0,
                    "stack size option is not supported by C11 threads.");

            if (thrd_success != thrd_create(ghost_impl_out_thread, function, context)) {
                if (options != ghost_null && options->ghost_impl_report_error) {
                    options->ghost_impl_thread_error_occurred = true;
                    return;
                } else {
                    ghost_fatal("thrd_create() failed");
                }
            }

            if (options != ghost_null && options->ghost_impl_detached) {
                ghost_ensure(thrd_success == thrd_detach(*ghost_impl_out_thread), "thrd_detach() failed");
                ghost_memset(ghost_impl_out_thread, 0, sizeof(*ghost_impl_out_thread));
            }
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_impl_ex_ithread_create 1
    #endif
#endif

#ifndef ghost_has_ghost_impl_ex_ithread_create
    #define ghost_has_ghost_impl_ex_ithread_create 0
#endif

#endif
