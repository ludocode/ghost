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

#ifndef GHOST_MUTEX_CONFIG_H_INCLUDED
#define GHOST_MUTEX_CONFIG_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/* TODO move file to impl/, hide this documentation, document as separate macros instead. there is nothing in this file exported to users */
/**
 * @file
 *
 * Configures the backend for Ghost's mutex and condition.
 *
 * You can choose a mutex and condition backend by pre-defining one of the
 * following macros to 1:
 *
 * - GHOST_MUTEX_WINSLIM: Windows Slim Reader/Writer (SRW) locks and CONDITION_VARIABLE
 * - GHOST_MUTEX_WINCS: Windows CRITICAL_SECTION and CONDITION_VARIABLE
 * - GHOST_MUTEX_PTHREADS: POSIX pthread_mutex_t and pthread_cond_t
 * - GHOST_MUTEX_C11: C11 threads library, mtx_t and cnd_t
 * - GHOST_MUTEX_FUTEX: An internal implementation using Linux futex or Windows WaitOnAddress()
 * - GHOST_MUTEX_NOOP: Disables locks, compiling them to nothing. Other features do not exist.
 *
 * If none is set, Ghost will autodetect an appropriate backend. It will prefer
 * SRWLOCKs on Windows-compatible platforms and pthreads otherwise.
 *
 * Ghost will never enable NOOP mutexes on its own. You can only enable this
 * manually. Beware that this may disable threading in whatever source
 * libraries you are including that use your configuration of Ghost threads.
 *
 * Ghost does not wrap C++ std::mutex or std::condition because it would make
 * any code that uses it incompatible with C.
 */
#endif

#ifdef GHOST_IMPL_MUTEX_HAVE_BACKEND
    #error "GHOST_IMPL_MUTEX_HAVE_BACKEND cannot be pre-defined."
#endif

/* See if the user has chosen a backend */
#ifdef GHOST_MUTEX_WINSLIM
    #if GHOST_MUTEX_WINSLIM
        #include "ghost/header/windows/ghost_windows_h.h"
        #if !ghost_has_ghost_windows_h
            #error "GHOST_MUTEX_WINSLIM is set but we failed to include <Windows.h>."
        #endif
        #define GHOST_IMPL_MUTEX_HAVE_BACKEND
    #endif
#endif
#ifdef GHOST_MUTEX_WINCS
    #if GHOST_MUTEX_WINCS
        #include "ghost/header/windows/ghost_windows_h.h"
        #if !ghost_has_ghost_windows_h
            #error "GHOST_MUTEX_WINCS is set but we failed to include <Windows.h>."
        #endif
        #define GHOST_IMPL_MUTEX_HAVE_BACKEND
    #endif
#endif
#ifdef GHOST_MUTEX_PTHREADS
    #if GHOST_MUTEX_PTHREADS
        #include "ghost/header/posix/ghost_pthread_h.h"
        #if !ghost_has_ghost_pthread_h
            #error "GHOST_MUTEX_PTHREADS is set but we failed to include <pthread.h>."
        #endif
        #define GHOST_IMPL_MUTEX_HAVE_BACKEND
    #endif
#endif
#ifdef GHOST_MUTEX_C11
    #if GHOST_MUTEX_C11
        #include "ghost/header/c/ghost_threads_h.h"
        #if !ghost_has_ghost_threads_h
            #error "GHOST_MUTEX_C11 is set but we failed to include <threads.h>."
        #endif
        #define GHOST_IMPL_MUTEX_HAVE_BACKEND
    #endif
#endif
#ifdef GHOST_MUTEX_FUTEX
    #if GHOST_MUTEX_FUTEX
        /* TODO include ghost_futex */
        #define GHOST_IMPL_MUTEX_HAVE_BACKEND
    #endif
#endif
#ifdef GHOST_MUTEX_NOOP
    #if GHOST_MUTEX_NOOP
        #define GHOST_IMPL_MUTEX_HAVE_BACKEND
    #endif
#endif

/* If any backend is enabled by the user, turn off the others */
#ifdef GHOST_IMPL_MUTEX_HAVE_BACKEND
    #ifndef GHOST_MUTEX_WINSLIM
        #define GHOST_MUTEX_WINSLIM 0
    #endif
    #ifndef GHOST_MUTEX_WINCS
        #define GHOST_MUTEX_WINCS 0
    #endif
    #ifndef GHOST_MUTEX_PTHREADS
        #define GHOST_MUTEX_PTHREADS 0
    #endif
    #ifndef GHOST_MUTEX_C11
        #define GHOST_MUTEX_C11 0
    #endif
    #ifndef GHOST_MUTEX_FUTEX
        #define GHOST_MUTEX_FUTEX 0
    #endif
    #ifndef GHOST_MUTEX_NOOP
        #define GHOST_MUTEX_NOOP 0
    #endif
#endif

/* Detect Windows. The slim reader/writer locks have been around since Windows
 * Vista which is really old now so we don't do any version detection; we just
 * use them. */
#ifndef GHOST_IMPL_MUTEX_HAVE_BACKEND
    #ifdef _WIN32
        #include "ghost/header/windows/ghost_windows_h.h"
        #if ghost_has_ghost_windows_h
            #define GHOST_MUTEX_WINSLIM 1
            #define GHOST_IMPL_MUTEX_HAVE_BACKEND
        #endif
    #endif
#endif

/*
 * The alternate Windows CRITICAL_SECTION implementation can only be enabled
 * manually. We prefer SRWLOCK.
 *     https://johantorp.com/tidbits/index.php/2016/10/14/prefer-srw-locks-over-critical-section/
 */

/* Detect pthreads. */
#ifndef GHOST_IMPL_MUTEX_HAVE_BACKEND
    #include "ghost/header/posix/ghost_pthread_h.h"
    #if ghost_has_ghost_pthread_h
        #define GHOST_MUTEX_PTHREADS 1
        #define GHOST_IMPL_MUTEX_HAVE_BACKEND
    #endif
#endif

/*
 * Detect C11 threads
 *
 * We prefer pthreads to C11 threads for several reasons:
 *
 * - C11 threads are missing some pretty important functionality (in particular
 *   a static initializer for mutex and condition and monotonic or relative
 *   timed waits);
 *
 * - Many libcs require linking against pthreads to use C11 threads. Since we
 *   need pthreads anyway, we might as well use it. (This is becoming less
 *   common now since implementations have been merging libpthread into libc,
 *   in particular musl and glibc.)
 *
 * There's no real reason to stop using pthreads so we prefer pthreads.
 */
#ifndef GHOST_IMPL_MUTEX_HAVE_BACKEND
    #include "ghost/header/c/ghost_threads_h.h"
    #if ghost_has_ghost_threads_h
        #define GHOST_MUTEX_C11 1
        #define GHOST_IMPL_MUTEX_HAVE_BACKEND
    #endif
#endif

/* The futex backend is experimental. It can only be enabled manually. */

/* We never turn on the noop backend ourselves. It can only be enabled
 * manually. */

/* Turn off anything not detected */
#ifndef GHOST_MUTEX_WINSLIM
    #define GHOST_MUTEX_WINSLIM 0
#endif
#ifndef GHOST_MUTEX_WINCS
    #define GHOST_MUTEX_WINCS 0
#endif
#ifndef GHOST_MUTEX_PTHREADS
    #define GHOST_MUTEX_PTHREADS 0
#endif
#ifndef GHOST_MUTEX_C11
    #define GHOST_MUTEX_C11 0
#endif
#ifndef GHOST_MUTEX_FUTEX
    #define GHOST_MUTEX_FUTEX 0
#endif
#ifndef GHOST_MUTEX_NOOP
    #define GHOST_MUTEX_NOOP 0
#endif

/* Make sure the user hasn't defined multiple backends */
#if GHOST_MUTEX_WINSLIM + GHOST_MUTEX_WINCS + GHOST_MUTEX_PTHREADS + \
        GHOST_MUTEX_C11 + GHOST_MUTEX_FUTEX + GHOST_MUTEX_NOOP > 1
    #error "At most one Ghost mutex backend can be enabled."
#endif

#undef GHOST_IMPL_MUTEX_HAVE_BACKEND
#endif
