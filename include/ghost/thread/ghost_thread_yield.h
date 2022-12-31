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

#ifndef GHOST_THREAD_YIELD_H_INCLUDED
#define GHOST_THREAD_YIELD_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Yields the current thread to the operating system.
 */
void ghost_thread_yield(void);
#endif

#ifndef ghost_has_ghost_thread_yield
    #ifdef ghost_thread_yield
        #define ghost_has_ghost_thread_yield 1
    #endif
#endif

/* Windows. SwitchToThread() appears to be some sort of wrapper to
 * YieldProcessor() which is a #define around some inline assembly or
 * intrinsics. We use SwitchToThread() for safety but ignore its result. */
#ifndef ghost_has_ghost_thread_yield
    #ifdef _WIN32
        /* Sadly we need to include all of <Windows.h> just for this. */
        #include "ghost/header/windows/ghost_windows_h.h"
        #include "ghost/language/ghost_discard.h"
        #define ghost_thread_yield() ghost_discard(SwitchToThread())
        #define ghost_has_ghost_thread_yield 1
    #endif
#endif

/* POSIX sched_yield() (which replaces pthread_yield() since POSIX 2001.) We
 * assume all UNIX systems support this. We ignore its result. */
#ifndef ghost_has_ghost_thread_yield
    #include "ghost/detect/ghost_unix.h"
    #if GHOST_UNIX
        /* TODO posix header wrapper for <sched.h>, move this unix test into it */
        #ifndef __COSMOPOLITAN__
            #include <sched.h>
        #endif
        #include "ghost/language/ghost_discard.h"
        #define ghost_thread_yield() ghost_discard(sched_yield())
        #define ghost_has_ghost_thread_yield 1
    #endif
#endif

/* C11 thrd_yield() */
#ifndef ghost_has_ghost_thread_yield
    #include "ghost/header/c/ghost_threads_h.h"
    #if ghost_has_ghost_threads_h
        #define ghost_thread_yield thrd_yield
        #define ghost_has_ghost_thread_yield 1
    #endif
#endif

/* Systems with <unistd.h> tend to have usleep(). This function was in POSIX
 * but was removed in 2008. We assume systems will keep it around for backwards
 * compatibility. (POSIX 2008 does have sleep() and nanosleep() but it also has
 * sched_yield() so wrapping more sleep functions is probably useless.) */
#ifndef ghost_has_ghost_thread_yield
    #include "ghost/header/posix/ghost_unistd_h.h"
    #if !ghost_has(ghost_unistd_h)
        #include "ghost/language/ghost_discard.h"
        #define ghost_thread_yield() ghost_discard(usleep(1))
        #define ghost_has_ghost_thread_yield 1
    #endif
#endif

/* Otherwise we don't have a way to yield. It's not necessarily safe to make
 * this a no-op. */
#ifndef ghost_has_ghost_thread_yield
    #define ghost_has_ghost_thread_yield 0
#endif

#endif
