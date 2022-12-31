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

#ifndef GHOST_TSS_T_H_INCLUDED
#define GHOST_TSS_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A key for thread-specific storage.
 */
typedef /*unspecified*/ ghost_tss_t;
#endif

#include "ghost/thread/tss/ghost_tss_config.h"

/* Handle override */
#ifndef ghost_has_ghost_tss_t
    #ifdef ghost_tss_t
        #define ghost_has_ghost_tss_t 1
    #endif
#endif

/* Windows
 *     https://docs.microsoft.com/en-us/windows/win32/procthread/using-thread-local-storage */
#ifndef ghost_has_ghost_tss_t
    #if GHOST_TSS_WINDOWS
        typedef DWORD ghost_tss_t;
        #define ghost_has_ghost_tss_t 1
    #endif
#endif

/* pthreads
 *     https://man.archlinux.org/man/core/man-pages/pthread_key_create.3p.en */
#ifndef ghost_has_ghost_tss_t
    #if GHOST_TSS_PTHREADS
        typedef pthread_key_t ghost_tss_t;
        #define ghost_has_ghost_tss_t 1
    #endif
#endif

/* C11 threads
 *     https://en.cppreference.com/w/c/thread/tss_set */
#ifndef ghost_has_ghost_tss_t
    #if GHOST_TSS_C11
        typedef tss_t ghost_tss_t;
        #define ghost_has_ghost_tss_t 1
    #endif
#endif

#ifndef ghost_has_ghost_tss_t
    #define ghost_has_ghost_tss_t 0
#endif

#endif
