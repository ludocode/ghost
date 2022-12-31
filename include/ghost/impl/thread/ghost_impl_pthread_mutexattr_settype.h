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

#ifndef GHOST_IMPL_PTHREAD_MUTEXATTR_SETTYPE_H_INCLUDED
#define GHOST_IMPL_PTHREAD_MUTEXATTR_SETTYPE_H_INCLUDED

/* This file figures out how to call pthread_mutexattr_settype(). */

#include "ghost/thread/mutex/ghost_mutex_config.h"

#if defined(ghost_has_ghost_impl_pthread_mutexattr_settype) || defined(ghost_impl_pthread_mutexattr_settype)
    #error "ghost_impl_pthread_mutexattr_settype cannot be pre-defined."
#endif

/* If we're not using pthreads we don't want this. */
#ifndef ghost_has_ghost_impl_pthread_mutexattr_settype
    #if !GHOST_MUTEX_PTHREADS
        #define ghost_has_ghost_impl_pthread_mutexattr_settype 0
    #endif
#endif

/* glibc and uClibc only declare this under certain conditions. We need to
 * declare it ourselves. */
#ifndef ghost_has_ghost_impl_pthread_mutexattr_settype
    #if defined(__GLIBC__) || defined(__UCLIBC__)
        #include "ghost/language/ghost_extern_c.h"
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/impl/ghost_impl_libc_noexcept.h"
        #if GHOST_IMPL_LIBC_ASM
            ghost_extern_c
            ghost_dllimport
            int ghost_impl_pthread_mutexattr_settype(pthread_mutexattr_t*, int)
                ghost_impl_libc_noexcept(ghost_impl_libc_asm("pthread_mutexattr_settype"));
        #else
            #include "ghost/preprocessor/ghost_nothing.h"
            ghost_extern_c
            ghost_dllimport
            int pthread_mutexattr_settype(pthread_mutexattr_t*, int)
                ghost_impl_libc_noexcept(GHOST_NOTHING);
            #define ghost_impl_pthread_mutexattr_settype pthread_mutexattr_settype
        #endif
        #define ghost_has_ghost_impl_pthread_mutexattr_settype 1
    #endif
#endif

/* We otherwise assume it is declared by the pthread header we've already
 * included. Older platforms won't have this; we could detect them and disable
 * this here. */
#ifndef ghost_has_ghost_impl_pthread_mutexattr_settype
    #define ghost_impl_pthread_mutexattr_settype pthread_mutexattr_settype
    #define ghost_has_ghost_impl_pthread_mutexattr_settype 1
#endif

#endif
