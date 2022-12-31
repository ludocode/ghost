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

#ifndef GHOST_THREADS_H_H_INCLUDED
#define GHOST_THREADS_H_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Includes C11 <threads.h> if possible.
 *
 * Check ghost_has(ghost_threads_h) to see if it's been included.
 */
#endif

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* If we're freestanding, we don't have <threads.h>. */
#ifndef ghost_has_ghost_threads_h
    #include "ghost/language/ghost_hosted.h"
    #if !GHOST_HOSTED
        #define ghost_has_ghost_threads_h 0
    #endif
#endif

/* If we're in glibc compat mode, for now we just turn this off entirely. */
#ifndef ghost_has_ghost_threads_h
    #include "ghost/detect/ghost_libc.h"
    #include "ghost/impl/ghost_impl_glibc_compat.h"
    #if GHOST_GLIBC_COMPAT > 0
        #define ghost_has_ghost_threads_h 0
    #endif
#endif

/* See if __STDC_NO_THREADS__ is on. This will tell us if we have a C11 libc
 * without thread support. It won't tell us if we have an older libc without it
 * though because this macro didn't exist before C11 threads. */
#ifndef ghost_has_ghost_threads_h
    /* Include <string.h> to get libc feature macros first */
    #include "ghost/header/c/ghost_string_h.h"
    #ifdef __STDC_NO_THREADS__
        #if __STDC_NO_THREADS__ != 0
            #define ghost_has_ghost_threads_h 0
        #endif
    #endif
#endif

/* See if we can test whether it exists. */
#ifndef ghost_has_ghost_threads_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<threads.h>)
            #include <threads.h>
            #define ghost_has_ghost_threads_h 1
        #else
            #define ghost_has_ghost_threads_h 0
        #endif
    #endif
#endif

/* Try to detect the libc. */
#ifndef ghost_has_ghost_threads_h
    #ifdef __linux__
        #include "ghost/detect/ghost_libc.h"

        /* Check glibc */
        #if defined(__GLIBC__) && !defined(__UCLIBC__)
            /* glibc 2.28 added C11 threads. Support for specific architectures
             * may have only come in later versions though; if so we need to
             * add detection for them here. */
            #if __GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 28)
                #include <threads.h>
                #define ghost_has_ghost_threads_h 1
            #else
                #define ghost_has_ghost_threads_h 0
            #endif

        /* Check musl */
        #else
            #include "ghost/detect/ghost_musl.h"
            #if GHOST_MUSL
                #include "ghost/detect/ghost_musl_version.h"
                #if GHOST_MUSL_VERSION >= 1001005
                    #include <threads.h>
                    #define ghost_has_ghost_threads_h 1
                #else
                    #define ghost_has_ghost_threads_h 0
                #endif
            #endif
        #endif
    #endif
#endif

/* A lot more platform detection is necessary. */

#ifndef ghost_has_ghost_threads_h
    #define ghost_has_ghost_threads_h 0
#endif

#endif
