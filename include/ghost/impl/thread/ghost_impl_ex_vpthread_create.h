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

#ifndef GHOST_IMPL_EX_VPTHREAD_CREATE_H_INCLUDED
#define GHOST_IMPL_EX_VPTHREAD_CREATE_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

/*
 * ghost_impl_ex_vpthread_create()
 *
 * A wrapper for a platform function that creates a thread that returns an int.
 *
 * Don't call or override this; use ghost_vpthread_create() instead.
 */

#if defined(ghost_has_ghost_impl_ex_vpthread_create) || defined(ghost_impl_ex_vpthread_create)
    #error "ghost_impl_ex_vpthread_create cannot be overridden. Override ghost_vpthread_create instead."
#endif

/* Handle ghost_vpthread_create override here */
#ifndef ghost_has_ghost_vpthread_create
    #ifdef ghost_vpthread_create
        #define ghost_has_ghost_vpthread_create 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_vpthread_create so it can be used to
 * implement other thread types */
#ifdef ghost_has_ghost_vpthread_create
    #if ghost_has_ghost_vpthread_create
        #define ghost_impl_ex_vpthread_create ghost_vpthread_create
        #define ghost_has_ghost_impl_ex_vpthread_create 1
    #endif
#endif

/* We need a thread type */
#ifndef ghost_has_ghost_impl_ex_vpthread_create
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_t.h"
    #if !ghost_has(ghost_impl_ex_vpthread_t)
        #define ghost_has_ghost_impl_ex_vpthread_create 0
    #endif
#endif

/*
 * pthread_create()
 *     https://man.archlinux.org/man/pthread_create.3
 *     https://man.archlinux.org/man/pthread_attr_init.3.en
 *     https://man.archlinux.org/man/pthread_attr_setstacksize.3.en
 */
#ifndef ghost_has_ghost_impl_ex_vpthread_create
    #if GHOST_THREAD_PTHREADS
        #include "ghost/debug/ghost_fatal.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/intptr_t/ghost_intptr_t.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/type/bool/ghost_false.h"
        #include "ghost/language/ghost_bit_cast.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/string/ghost_memset.h"
        #include "ghost/thread/thread_options/ghost_thread_options_t.h"
        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_function
        void ghost_impl_ex_vpthread_create(ghost_impl_ex_vpthread_t* ghost_impl_out_thread,
                void* (*function)(void* context), void* context,
                ghost_thread_options_t* options)
        #if !GHOST_EMIT_DEFS
        ;
        #else
        {
            pthread_attr_t ghost_impl_attr_value;
            pthread_attr_t* ghost_impl_attr = ghost_null;
            ghost_bool detached = ghost_static_cast(ghost_bool,
                    (options == ghost_null) ? ghost_false : options->ghost_impl_detached);
            int ghost_impl_ret;

            /* stack size */
            ghost_size_t stack_size = (options == ghost_null) ? 0 : options->ghost_impl_stack_size;
            if (stack_size != 0) {
                if (ghost_impl_attr == ghost_null) {
                    ghost_impl_attr = &ghost_impl_attr_value;
                    pthread_attr_init(ghost_impl_attr);
                }

                /* Figure out minimum stack size */
                {
                    /*
                     * PTHREAD_STACK_MIN isn't defined by glibc unless __USE_MISC
                     * is defined which doesn't happen under -std=c89. When it is
                     * defined it's usually a dynamic value fetched with sysconf().
                     *
                     * Other platforms may also define it conditionally, or may
                     * not define it at all (e.g. NetBSD doesn't have this.)
                     * It's probably not required to be a macro but we'll check
                     * if it's defined anyway for safety.
                     */
                    #if defined(PTHREAD_STACK_MIN)
                        /* sysconf() returns long. In case this is coming from
                         * sysconf we need to cast it. */
                        ghost_size_t stack_min = ghost_static_cast(ghost_size_t, PTHREAD_STACK_MIN);
                        /* Make sure it's not negative which would imply some
                         * sort of error in sysconf. Note that this check only
                         * works if sizeof(size_t)==sizeof(long). */
                        if (stack_min > (ghost_static_cast(ghost_size_t, 0) - 1) / 2)
                            stack_min = 0;
                    #elif defined(__linux__)
                        /* A typical default for Linux. TODO use sysconf()
                         * ourselves. We may be able to do something similar on
                         * other platforms, e.g. NetBSD has _SC_THREAD_STACK_MIN. */
                        ghost_size_t stack_min = 16384;
                    #else
                        /* We don't know the platform minimum. This is just a
                         * safety check anyway so this effectively disables it. */
                        ghost_size_t stack_min = 1;
                    #endif
                    if (stack_size < stack_min)
                        stack_size = stack_min;
                }

                /* Old versions of glibc had a bug where the stack size could
                 * be incorrectly rounded down. Presumably this has been fixed
                 * long enough that we don't need to worry about it. */

                pthread_attr_setstacksize(ghost_impl_attr, stack_size);
            }

            /* detached */
            if (detached != 0) {
                if (ghost_impl_attr == ghost_null) {
                    ghost_impl_attr = &ghost_impl_attr_value;
                    pthread_attr_init(ghost_impl_attr);
                }
                pthread_attr_setdetachstate(ghost_impl_attr, PTHREAD_CREATE_DETACHED);
            }

            ghost_impl_ret = pthread_create(ghost_impl_out_thread, ghost_null, function, context);
            if (ghost_impl_attr != ghost_null) {
                pthread_attr_destroy(ghost_impl_attr);
            }

            /* report error */
            if (ghost_impl_ret != 0) {
                if (options != ghost_null && options->ghost_impl_report_error) {
                    options->ghost_impl_thread_error_occurred = true;
                    return;
                } else {
                    ghost_fatal("pthread_create() failed");
                }
            }

            if (detached) {
                ghost_memset(ghost_impl_out_thread, 0, sizeof(*ghost_impl_out_thread));
            }
        }
        #endif

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_impl_ex_vpthread_create 1
    #endif
#endif

#ifndef ghost_has_ghost_impl_ex_vpthread_create
    #define ghost_has_ghost_impl_ex_vpthread_create 0
#endif

#endif
