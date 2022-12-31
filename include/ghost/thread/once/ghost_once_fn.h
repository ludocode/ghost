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

#ifndef GHOST_ONCE_FN_H_INCLUDED
#define GHOST_ONCE_FN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Call a function once.
 *
 * The given once flag must have been initialized by GHOST_ONCE_INIT or
 * ghost_once_init().
 *
 * This can be called from any number of threads concurrently. For a given once flag:
 *
 * - The first call to ghost_once() will call the given function.
 * - Other calls to ghost_once() before the function returns will ignore their
 *   function parameter and block.
 * - Once the function returns, all waiting threads will unblock return from
 *   ghost_once().
 * - Subsequent calls to ghost_once() will ignore their function parameter and
 *   return immediately.
 *
 * The most common way to use this is:
 *
 *     static ghost_once_t my_once = GHOST_ONCE_INIT;
 *
 *     static void my_initialization(void) {
 *         // perform your initialization
 *     }
 *
 *     static void my_thread(void) {
 *         // in several threads simultaneously
 *         ghost_once(&my_once, &my_initialization);
 *     }
 */
void ghost_once(ghost_once_t* once, void (*function)(void));
#endif

/* Overrides */
#ifndef ghost_has_ghost_once
    #ifdef ghost_once
        #define ghost_has_ghost_once 1
    #endif
#endif

#ifndef ghost_has_ghost_once_init
    #include "ghost/thread/once/ghost_once_t.h"
    #if !ghost_has_ghost_once_t
        #define ghost_has_ghost_once_init 0
    #endif
#endif

/* TODO the below don't need to include headers or do header checks, it's done
 * in ghost_once_t */

#ifndef ghost_has_ghost_once
    #ifdef _WIN32
        #include "ghost/header/windows/ghost_windows_h.h"
        #if ghost_has_ghost_windows_h
            #include "ghost/impl/ghost_impl_inline.h"
            #include "ghost/debug/ghost_check.h"
            #include "ghost/language/ghost_null.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_inline
            void ghost_once(ghost_once_t* once, void (*function)(void)) {
                /* Abort on errors in debug mode, ignore them otherwise. */
                BOOL pending;
                ghost_check(InitOnceBeginInitialize(once, 0, &pending, ghost_null), "");

                /* We don't use ghost_expect_true() here. Even though this will
                 * usually be true, it's not generally a good idea to put
                 * expect on something that isn't an unusual error condition
                 * because it might put the initialization code in a weird cold
                 * place. */
                if (!pending)
                    return;

                function();
                ghost_check(InitOnceComplete(once, 0, ghost_null), "");
            }
            GHOST_IMPL_FUNCTION_CLOSE
            #define ghost_has_ghost_once 1
        #endif
    #endif
#endif

/* pthreads */
#ifndef ghost_has_ghost_once
    #include "ghost/header/posix/ghost_pthread_h.h"
    #if ghost_has_ghost_pthread_h
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/debug/ghost_check.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        void ghost_once(ghost_once_t* once, void (*function)(void)) {
            /* Abort on error in debug mode, otherwise ignore it. The only
             * real reason this can fail is if the once flag was improperly
             * initialized which isn't something that can be reasonably
             * guarded against. */
            ghost_check(pthread_once(once, function), "");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_once 1
    #endif
#endif

/* C11 threads */
#ifndef ghost_has_ghost_once
    #include "ghost/header/c/ghost_threads_h.h"
    #if ghost_has_ghost_threads_h
        /* call_once cannot return an error. */
        #define ghost_once call_once
        #define ghost_has_ghost_once 1
    #endif
#endif

#ifndef ghost_has_ghost_once
    #define ghost_has_ghost_once 0
#endif

#endif
