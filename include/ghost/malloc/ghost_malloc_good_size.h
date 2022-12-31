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

#ifndef GHOST_MALLOC_GOOD_SIZE_H_INCLUDED
#define GHOST_MALLOC_GOOD_SIZE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 *
 */
#endif

/* Override is handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/* See if the platform supports it */
/* TODO clean this up to be more like ghost_malloc_size */
#ifndef ghost_has_ghost_malloc_good_size
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/impl/binding/jemalloc/ghost_impl_jemalloc.h"
        #if GHOST_USE_JEMALLOC
            #include <jemalloc/jemalloc.h>
            #define ghost_malloc_good_size(size) nallocx(size, 0)
            #define ghost_has_ghost_malloc_good_size 1
        #elif defined(__FreeBSD__)
            #include <malloc_np.h>
            #define ghost_malloc_good_size(size) nallocx(size, 0)
            #define ghost_has_ghost_malloc_good_size 1
        #elif defined(__APPLE__)
            #include <malloc/malloc.h>
            #define ghost_malloc_good_size malloc_good_size
            #define ghost_has_ghost_malloc_good_size 1
        #endif
    #endif
#endif

/* Otherwise we have no support. */
#ifndef ghost_has_ghost_malloc_good_size
    #define ghost_has_ghost_malloc_good_size 0
#endif

#endif
