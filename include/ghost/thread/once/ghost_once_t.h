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

#ifndef GHOST_ONCE_T_H_INCLUDED
#define GHOST_ONCE_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A once flag.
 *
 * Declare it like this:
 *
 *     static ghost_once_t my_once = GHOST_ONCE_INIT;
 *
 * Then call ghost_once() on it from any number threads concurrently.
 */
typedef /*unspecified*/ ghost_once_t;
#endif

#ifndef ghost_has_ghost_once_t
    #ifdef ghost_once_t
        #define ghost_has_ghost_once_t 1
    #endif
#endif

/* Windows
 * One-Time Initialization is available from Windows Vista onward. Ghost
 * doesn't support anything older.
 *     https://docs.microsoft.com/en-us/windows/win32/sync/one-time-initialization */
#ifndef ghost_has_ghost_once_t
    #ifdef _WIN32
        #include "ghost/header/windows/ghost_windows_h.h"
        #ifndef ghost_has_ghost_once_t
            typedef INIT_ONCE ghost_once_t;
            #define ghost_has_ghost_once_t 1
        #endif
    #endif
#endif

/* pthreads */
#ifndef ghost_has_ghost_once_t
    #include "ghost/header/posix/ghost_pthread_h.h"
    #if ghost_has_ghost_pthread_h
        typedef pthread_once_t ghost_once_t;
        #define ghost_has_ghost_once_t 1
    #endif
#endif

/* C11 threads
 * We prefer pthreads to this for the same reasons as mutex and condition; see
 * the comment in ghost_mutex_config.h. */
#ifndef ghost_has_ghost_once_t
    #include "ghost/header/c/ghost_threads_h.h"
    #if ghost_has_ghost_threads_h
        #ifndef ghost_has_ghost_once_t
            typedef once_flag ghost_once_t;
            #define ghost_has_ghost_once_t 1
        #endif
    #endif
#endif

/*
 * We could implement our own with futex. There is probably no point in doing
 * this because any platform that supports futexes will support some kind of
 * once flag and a custom implementation is unlikely to be better.
 *
 * We could also implement something with atomics for freestanding or embedded
 * environments. This would require that waiting threads spin during
 * initialization (or at best yield if we're on some RTOS that supports it.)
 * We don't bother doing this yet either.
 */

#ifndef ghost_has_ghost_once_t
    #define ghost_has_ghost_once_t 0
#endif

#endif
