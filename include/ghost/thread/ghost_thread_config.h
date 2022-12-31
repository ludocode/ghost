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

#ifndef GHOST_THREAD_CONFIG_H_INCLUDED
#define GHOST_THREAD_CONFIG_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO move file to impl/, hide this documentation, document as separate macros instead. there is nothing in this file exported to users */
/**
 * @file
 *
 * Configures the backend for Ghost's thread functions.
 *
 * You can choose a thread backend by pre-defining one of the following macros
 * to 1:
 *
 * - GHOST_THREAD_WINDOWS: Windows CreateThread(), etc.
 * - GHOST_THREAD_PTHREADS: POSIX pthread_t, pthread_create(), etc.
 * - GHOST_THREAD_C11: C11 thrd_t, thrd_create(), etc.
 *
 * If none is set, Ghost will autodetect an appropriate backend.
 *
 * Ghost does not wrap C++ std::thread because it would make any code that uses
 * it incompatible with C.
 */

/* For now we enforce that only one backend is used. We won't mix-and-match
 * backends for different thread types. */
#ifdef GHOST_IMPL_THREAD_HAVE_BACKEND
    #error "GHOST_IMPL_THREAD_HAVE_BACKEND cannot be pre-defined."
#endif

/* See if the user has chosen a backend */
#ifdef GHOST_THREAD_WINDOWS
    #if GHOST_THREAD_WINDOWS
        #include "ghost/header/windows/ghost_windows_h.h"
        #if !ghost_has_ghost_windows_h
            #error "GHOST_THREAD_WINDOWS is set but we failed to include <Windows.h>."
        #endif
        #define GHOST_IMPL_THREAD_HAVE_BACKEND
    #endif
#endif
#ifdef GHOST_THREAD_PTHREADS
    #if GHOST_THREAD_PTHREADS
        #include "ghost/header/posix/ghost_pthread_h.h"
        #if !ghost_has_ghost_pthread_h
            #error "GHOST_THREAD_PTHREADS is set but we failed to include <pthread.h>."
        #endif
        #define GHOST_IMPL_THREAD_HAVE_BACKEND
    #endif
#endif
#ifdef GHOST_THREAD_C11
    #if GHOST_THREAD_C11
        #include "ghost/header/c/ghost_threads_h.h"
        #if !ghost_has_ghost_threads_h
            #error "GHOST_THREAD_C11 is set but we failed to include <threads.h>."
        #endif
        #define GHOST_IMPL_THREAD_HAVE_BACKEND
    #endif
#endif

/* If any backend is enabled by the user, turn off the others */
#ifdef GHOST_IMPL_THREAD_HAVE_BACKEND
    #ifndef GHOST_THREAD_WINDOWS
        #define GHOST_THREAD_WINDOWS 0
    #endif
    #ifndef GHOST_THREAD_PTHREADS
        #define GHOST_THREAD_PTHREADS 0
    #endif
    #ifndef GHOST_THREAD_C11
        #define GHOST_THREAD_C11 0
    #endif
#endif

/* Detect Windows. */
#ifndef GHOST_IMPL_THREAD_HAVE_BACKEND
    #ifdef _WIN32
        #include "ghost/header/windows/ghost_windows_h.h"
        #if ghost_has_ghost_windows_h
            #define GHOST_THREAD_WINDOWS 1
            #define GHOST_IMPL_THREAD_HAVE_BACKEND
        #endif
    #endif
#endif

/* Detect pthreads. */
#ifndef GHOST_IMPL_THREAD_HAVE_BACKEND
    #include "ghost/header/posix/ghost_pthread_h.h"
    #if ghost_has_ghost_pthread_h
        #define GHOST_THREAD_PTHREADS 1
        #define GHOST_IMPL_THREAD_HAVE_BACKEND
    #endif
#endif

/*
 * Detect C11 threads
 *
 * We prefer pthreads to C11 threads for several reasons:
 *
 * - C11 threads return int while pthreads return void*. On modern platforms an
 *   int can be stored in void* but not the other way around. Wrapping a C11
 *   thread to return void* requires auxiliary storage.
 *
 * - C11 threads have no customization options. You cannot configure stack
 *   size, scheduling parameters, CPU affinity, signal mask, etc.
 */
#ifndef GHOST_IMPL_THREAD_HAVE_BACKEND
    #include "ghost/header/c/ghost_threads_h.h"
    #if ghost_has_ghost_threads_h
        #define GHOST_THREAD_C11 1
        #define GHOST_IMPL_THREAD_HAVE_BACKEND
    #endif
#endif

/* Turn off anything not detected */
#ifndef GHOST_THREAD_WINDOWS
    #define GHOST_THREAD_WINDOWS 0
#endif
#ifndef GHOST_THREAD_PTHREADS
    #define GHOST_THREAD_PTHREADS 0
#endif
#ifndef GHOST_THREAD_C11
    #define GHOST_THREAD_C11 0
#endif

/* Make sure the user hasn't defined multiple backends */
#if GHOST_THREAD_WINDOWS + GHOST_THREAD_PTHREADS + GHOST_THREAD_C11 > 1
    #error "At most one Ghost thread backend can be enabled."
#endif

#undef GHOST_IMPL_THREAD_HAVE_BACKEND
#endif
