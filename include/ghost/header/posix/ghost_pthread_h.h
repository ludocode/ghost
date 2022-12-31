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

#ifndef GHOST_PTHREAD_H_H_INCLUDED
#define GHOST_PTHREAD_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes <pthread.h> if possible, which declares POSIX threads.
 *
 * Check `ghost_has(ghost_pthread_h)` to see whether it was actually included.
 *
 *     https://man.archlinux.org/man/pthread.h.0p
 *     https://man.archlinux.org/man/core/man-pages/pthreads.7.en
 *     https://en.wikipedia.org/wiki/Pthreads
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* Allow the user to override the include path */
#ifndef ghost_has_ghost_pthread_h
    #ifdef GHOST_PTHREAD_H
        #include GHOST_PTHREAD_H
        #define ghost_has_ghost_pthread_h 1
    #endif
#endif

/*
 * If we can detect that <pthread.h> exists, we enable this and include it
 * regardless of _POSIX_THREADS or other detection. This will detect
 * third-party implementations of pthreads (like pthreads-win32) that aren't
 * declared by <unistd.h>.
 */
#ifndef ghost_has_ghost_pthread_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<pthread.h>)
            #include <pthread.h>
            #define ghost_has_ghost_pthread_h 1
        #else
            #define ghost_has_ghost_pthread_h 0
        #endif
    #endif
#endif

/*
 * We otherwise defer most of the heavy lifting to ghost_unistd_h.h. It will do
 * the platform detection necessary to check whether <unistd.h> exists. After
 * that, _POSIX_THREADS tells us whether the system has <pthread.h>.
 */
#ifndef ghost_has_ghost_pthread_h
    #include "ghost/header/posix/ghost_unistd_h.h"
    #ifdef _POSIX_THREADS
        #include <pthread.h>
        #define ghost_has_ghost_pthread_h 1
    #endif
#endif

/* Otherwise assume we don't have pthreads. */
#ifndef ghost_has_ghost_pthread_h
    #define ghost_has_ghost_pthread_h 0
#endif

#endif
