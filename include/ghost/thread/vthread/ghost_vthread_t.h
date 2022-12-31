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

#ifndef GHOST_VTHREAD_T_H_INCLUDED
#define GHOST_VTHREAD_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A handle for a thread that returns void*.
 */
typedef /*unspecified*/ ghost_vthread_t;
#endif

#ifndef ghost_has_ghost_vthread_t
    #ifdef ghost_vthread_t
        #define ghost_has_ghost_vthread_t 1
    #endif
#endif

/* We'll need a memory allocator to allocate our wrapper struct. */
#ifndef ghost_has_ghost_vthread_t
    #include "ghost/malloc/ghost_alloc.h"
    #include "ghost/malloc/ghost_free.h"
    #if !ghost_has(ghost_alloc) || !ghost_has(ghost_free)
        #define ghost_has_ghost_vthread_t 0
    #endif
#endif

/* Synthesize it from a thread returning int */
#ifndef ghost_has_ghost_vthread_t
    #include "ghost/impl/thread/ghost_impl_ex_ithread_t.h"
    #if ghost_has_ghost_impl_ex_ithread_t
        /* Wrap it in a struct to prevent implicit conversions */
        typedef struct ghost_vthread_t {
            ghost_impl_ex_ithread_t ghost_impl_platform_thread;
        } ghost_vthread_t;
        #define ghost_has_ghost_vthread_t 1
    #endif
#endif

/* Synthesize it from a thread returning void* */
#ifndef ghost_has_ghost_vthread_t
    #include "ghost/impl/thread/ghost_impl_ex_vpthread_t.h"
    #if ghost_has_ghost_impl_ex_vpthread_t
        /* Wrap it in a struct to prevent implicit conversions */
        typedef struct ghost_vthread_t {
            ghost_impl_ex_vpthread_t ghost_impl_platform_thread;
        } ghost_vthread_t;
        #define ghost_has_ghost_vthread_t 1
    #endif
#endif

#ifndef ghost_has_ghost_vthread_t
    #define ghost_has_ghost_vthread_t 0
#endif

#endif
