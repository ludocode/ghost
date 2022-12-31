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

#ifndef GHOST_THREAD_LOCAL_H_INCLUDED
#define GHOST_THREAD_LOCAL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Declares a variable thread-local.
 *
 * This can only be used on variables in static storage duration. It must
 * appear on all declarations (those with "extern") and the definition.
 *
 * This does not exist on all platforms. Use ghost_has(ghost_thread_local) to
 * see if thread-local storage is available.
 *
 * If you want to fallback to thread-specific storage when thread-local storage
 * is unavailable, see the experimental ghost_tlss.
 */
#endif

/* Allow override */
#ifndef ghost_has_ghost_thread_local
    #ifdef ghost_thread_local
        #define ghost_has_ghost_thread_local 1
    #endif
#endif

/* C11 has _Thread_local. We don't want this to apply to C++ for the reasons
 * below. */
#ifndef ghost_has_ghost_thread_local
    #if defined(__STDC_VERSION__) && !defined(__cplusplus)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 201112L
            #define ghost_thread_local _Thread_local
            #define ghost_has_ghost_thread_local 1
        #endif
    #endif
#endif

/*
 * In C++ with GNU C compilers, we prefer __thread to thread_local. __thread
 * can be more efficient than thread_local but it requires that the type be
 * trivially constructible/destructible. Since Ghost is a C library, we prefer
 * the more efficient version that works best on C types. If you need a
 * thread-local non-trivially-constructible variable in C++, just use the C++11
 * keyword thread_local directly.
 *
 * See a discussion here:
 *     https://reviews.llvm.org/D72399
 */

/* GNU C compilers have __thread. */
#ifndef ghost_has_ghost_thread_local
    #ifdef __GNUC__
        #define ghost_thread_local __thread
        #define ghost_has_ghost_thread_local 1
    #endif
#endif

/* C++11 has thread_local */
#ifndef ghost_has_ghost_thread_local
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define ghost_thread_local thread_local
            #define ghost_has_ghost_thread_local 1
        #endif
    #endif
#endif

/* MSVC has __declspec(thread). */
#ifndef ghost_has_ghost_thread_local
    #ifdef _MSC_VER
        #define ghost_thread_local __declspec(thread)
        #define ghost_has_ghost_thread_local 1
    #endif
#endif

/* Otherwise we don't support it. */
#ifndef ghost_has_ghost_thread_local
    #define ghost_has_ghost_thread_local 0
#endif

#endif
