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

#ifndef GHOST_THREAD_ID_CURRENT_H_INCLUDED
#define GHOST_THREAD_ID_CURRENT_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

#if GHOST_DOCUMENTATION
/*
 * Gets the thread id for the current thread.
 */
ghost_thread_id_t ghost_thread_id_current(void);
#endif

#ifndef ghost_has_ghost_thread_id_current
    #ifdef ghost_thread_id_current
        #define ghost_has_ghost_thread_id_current 1
    #endif
#endif

/* We need thread id */
#ifndef ghost_has_ghost_thread_id_current
    #include "ghost/thread/thread_id/ghost_thread_id_t.h"
    #if !ghost_has(ghost_thread_id_t)
        #define ghost_has_ghost_thread_id_current 0
    #endif
#endif

/*
 * Windows
 *     https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getcurrentthreadid
 */
#ifndef ghost_has_ghost_thread_id_current
    #if GHOST_THREAD_WINDOWS
        #define ghost_thread_id_current GetCurrentThreadId
        #define ghost_has_ghost_thread_id_current 1
    #endif
#endif

/*
 * pthreads
 *     https://man.archlinux.org/man/pthread_self.3.en
 */
#ifndef ghost_has_ghost_thread_id_current
    #if GHOST_THREAD_PTHREADS
        #define ghost_thread_id_current pthread_self
        #define ghost_has_ghost_thread_id_current 1
    #endif
#endif

/*
 * C11
 *     https://en.cppreference.com/w/c/thread/thrd_current
 */
#ifndef ghost_has_ghost_thread_id_current
    #if GHOST_THREAD_C11
        #define ghost_thread_id_current thrd_current
        #define ghost_has_ghost_thread_id_current 1
    #endif
#endif

#ifndef ghost_has_ghost_thread_id_current
    #define ghost_has_ghost_thread_id_current 0
#endif

#endif
