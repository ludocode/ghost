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

#ifndef GHOST_THREAD_OPTIONS_H_INCLUDED
#define GHOST_THREAD_OPTIONS_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/type/bool/ghost_bool.h"

#if GHOST_DOCUMENTATION
/**
 * A structure used to customize a new thread.
 *
 * You must initialize this structure by zeroing it (e.g. by assigning
 * GHOST_ZERO_INIT to it) before calling any setters.
 *
 * Use it like this:
 *
 *     ghost_thread_options_t my_options = GHOST_ZERO_INIT;
 *     ghost_thread_options_set_stack_size(&my_options, 1024*1024);
 *     ghost_ithread_create(&my_thread, &my_callback, my_context, &my_options);
 *
 * The call to ghost_*thread_create() cleans up any state stored in the
 * options structure. You must call a thread creation function exactly once
 * with an initialized options struct.
 */
typedef struct ghost_thread_options_t ghost_thread_options_t;

/*
 * Sets the stack size for a thread to be created.
 *
 * The default is 0. Pass 0 as the stack size to use the system default.
 *
 * Some platforms do not support setting the stack size. In this case
 * ghost_thread_options_set_stack_size() will not exist and the stack size will
 * be the system default. Use ghost_has(ghost_thread_options_set_stack_size) to
 * see if this is supported.
 *
 * The system default stack size varies by platform. Most modern systems use
 * relatively large stacks (around 8 MB) but some use smaller stacks (e.g. musl
 * defaults to 128 kB.) For maximum portability, use the default stack size and
 * use as little stack space as possible.
 */
void ghost_thread_options_set_stack_size(ghost_thread_options_t* options, size_t stack_size);

/**
 * Sets whether a failure to create the thread should be reported (i.e.
 * returned from the create function) instead of treated as a fatal error.
 *
 * If false, any error will result in a call to ghost_fatal() and the call to
 * ghost_thread_create_*() will not return.
 *
 * If true, you must call ghost_thread_options_is_error() on the options struct
 * after attempting to create the thread to see if an error occurred. For
 * example:
 *
 *     ghost_thread_options_t my_options = GHOST_ZERO_INIT;
 *     ghost_thread_options_set_report_error(&my_options, true);
 *     ghost_ithread_create(&my_thread, &my_callback, my_context, &my_options);
 *     if (ghost_thread_options_is_error(&my_options)) {
 *         // an error occurred creating the thread.
 *     }
 *
 * The default is false.
 */
void ghost_thread_options_set_report_error(ghost_thread_options_t* options, bool report_error);

/**
 * Sets whether the new thread should be detached.
 *
 * The default is false.
 *
 * If true, the thread handle passed to ghost_thread_create() may be null; if
 * not, it will be assigned to an invalid thread handle. You must not join or
 * detach the thread.
 *
 * If detaching the thread fails, Ghost may still call ghost_fatal() even if
 * ghost_thread_options_set_report_error() was set to true. Errors are only
 * reported if thread creation fails, not thread detachment. (There is no
 * reasonable way to recover from a thread that was successfully started but
 * failed to detach.)
 */
void ghost_thread_options_set_detached(ghost_thread_options_t* options, bool detached);
#endif

/* TODO need to break this up into separate files. Some will be more complicated
 * than just this, and we need to make them not exist if ghost_thread_t doesn't
 * exist */

#ifndef ghost_has_ghost_thread_options_t
    #ifndef ghost_thread_options_t
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/type/bool/ghost_bool.h"
        typedef struct ghost_thread_options_t {
            /* This structure is meant to be opaque. Don't access these fields directly. */
            ghost_size_t ghost_impl_stack_size;
            ghost_bool ghost_impl_report_error;
            ghost_bool ghost_impl_detached;
            ghost_bool ghost_impl_thread_error_occurred;

            /* TODO add debug leak check field, cleanup function */
        } ghost_thread_options_t;
        #define ghost_has_ghost_thread_options_t 1
    #endif
#endif

/* TODO this shouldn't exist under C11 threads. */
#ifndef ghost_has_ghost_thread_options_set_stack_size
    #ifndef ghost_thread_options_set_stack_size
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_thread_options_set_stack_size(
                ghost_thread_options_t* ghost_impl_options, ghost_size_t ghost_impl_stack_size)
        {
            ghost_impl_options->ghost_impl_stack_size = ghost_impl_stack_size;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_thread_options_set_stack_size 1
    #endif
#endif

#ifndef ghost_has_ghost_thread_options_set_report_error
    #ifndef ghost_thread_options_set_report_error
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_thread_options_set_report_error(
                ghost_thread_options_t* ghost_impl_options, ghost_bool ghost_impl_report_error)
        {
            ghost_impl_options->ghost_impl_report_error = ghost_impl_report_error;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_thread_options_set_report_error 1
    #endif
#endif

#ifndef ghost_has_ghost_thread_options_set_detached
    #ifndef ghost_thread_options_set_detached
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_thread_options_set_detached(
                ghost_thread_options_t* ghost_impl_options, ghost_bool ghost_impl_detached)
        {
            ghost_impl_options->ghost_impl_detached = ghost_impl_detached;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_thread_options_set_detached 1
    #endif
#endif

#ifndef ghost_has_ghost_thread_options_is_error
    #ifndef ghost_thread_options_is_error
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_bool ghost_thread_options_is_error(ghost_thread_options_t* ghost_impl_options) {
            return ghost_impl_options->ghost_impl_thread_error_occurred;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_thread_options_is_error 1
    #endif
#endif

#endif
