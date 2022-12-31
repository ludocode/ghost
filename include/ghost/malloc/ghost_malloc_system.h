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

#ifndef GHOST_MALLOC_SYSTEM_H_INCLUDED
#define GHOST_MALLOC_SYSTEM_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_MALLOC_SYSTEM
 *
 * 1 if Ghost will use the system allocator and 0 otherwise.
 *
 * If none of the Ghost allocator functions are overridden, this defaults to 1
 * (in a hosted environment.) All Ghost allocator functions will wrap whatever
 * system allocation functions are available on the platform.
 *
 * TODO all of the below has been moved to README
 *
 * If any of the following Ghost allocator functions are overridden, this
 * defaults to 0:
 *
 * - ghost/malloc/ functions:
 *     - ghost_aligned_free
 *     - ghost_aligned_malloc
 *     - ghost_calloc
 *     - ghost_calloc_0any
 *     - ghost_calloc_0null
 *     - ghost_free
 *     - ghost_free_nonnull
 *     - ghost_malloc
 *     - ghost_malloc_0any
 *     - ghost_malloc_0null
 *     - ghost_malloc_good_size
 *     - ghost_malloc_size
 *     - ghost_memdup
 *     - ghost_realloc
 *     - ghost_realloc_0alloc
 *     - ghost_realloc_0any
 *     - ghost_realloc_0free
 *     - ghost_realloc_0null
 *     - ghost_strdup
 *     - ghost_strndup
 * - ghost/format/ functions:
 *     - ghost_asprintf
 *     - ghost_vasprintf
 *
 * When this is 0, Ghost allocator functions won't exist unless you define some
 * yourself. You can define this to 0 to make Ghost wrap a custom allocator, to
 * customize or correct Ghost's usage of the system allocator, or to disable
 * Ghost's allocator entirely.
 *
 * If you do provide your own allocation functions, Ghost will implement
 * the above functions in terms of others as much as possible. For example if
 * you define only ghost_malloc(), Ghost will define a ghost_calloc() that
 * calls your ghost_malloc() and zeroes the memory.
 *
 * (But if you define ghost_malloc() and also define GHOST_MALLOC_SYSTEM to 1,
 * ghost_calloc() will still use the system calloc().)
 *
 * When providing a custom allocation function, you need to override the
 * variant that correctly matches its behaviour. For example if you override
 * ghost_malloc(), your function must return a minimum-size allocation when
 * size is 0, as Ghost and user code expects. If you're unsure of the behaviour
 * of your function when the size is 0, override ghost_malloc_0any() instead,
 * which accepts any behaviour on size 0. ghost_malloc() will automatically
 * wrap it and ensure the correct behaviour.
 */
#endif

/* All allocator function overrides need to be handled here because the value
 * of GHOST_MALLOC_SYSTEM depends on whether any allocation function is
 * overridden. */
/* TODO move this to an impl/ header. */

/* ghost/malloc/ */
#ifndef ghost_has_ghost_aligned_free
    #ifdef ghost_aligned_free
        #define ghost_has_ghost_aligned_free 1
    #endif
#endif
#ifndef ghost_has_ghost_aligned_malloc
    #ifdef ghost_aligned_malloc
        #define ghost_has_ghost_aligned_malloc 1
    #endif
#endif
#ifndef ghost_has_ghost_calloc
    #ifdef ghost_calloc
        #define ghost_has_ghost_calloc 1
    #endif
#endif
#ifndef ghost_has_ghost_calloc_0any
    #ifdef ghost_calloc_0any
        #define ghost_has_ghost_calloc_0any 1
    #endif
#endif
#ifndef ghost_has_ghost_calloc_0null
    #ifdef ghost_calloc_0null
        #define ghost_has_ghost_calloc_0null 1
    #endif
#endif
#ifndef ghost_has_ghost_free
    #ifdef ghost_free
        #define ghost_has_ghost_free 1
    #endif
#endif
#ifndef ghost_has_ghost_free_nonnull
    #ifdef ghost_free_nonnull
        #define ghost_has_ghost_free_nonnull 1
    #endif
#endif
#ifndef ghost_has_ghost_malloc
    #ifdef ghost_malloc
        #define ghost_has_ghost_malloc 1
    #endif
#endif
#ifndef ghost_has_ghost_malloc_0any
    #ifdef ghost_malloc_0any
        #define ghost_has_ghost_malloc_0any 1
    #endif
#endif
#ifndef ghost_has_ghost_malloc_0null
    #ifdef ghost_malloc_0null
        #define ghost_has_ghost_malloc_0null 1
    #endif
#endif
#ifndef ghost_has_ghost_malloc_good_size
    #ifdef ghost_malloc_good_size
        #define ghost_has_ghost_malloc_good_size 1
    #endif
#endif
#ifndef ghost_has_ghost_malloc_size
    #ifdef ghost_malloc_size
        #define ghost_has_ghost_malloc_size 1
    #endif
#endif
#ifndef ghost_has_ghost_memdup
    #ifdef ghost_memdup
        #define ghost_has_ghost_memdup 1
    #endif
#endif
#ifndef ghost_has_ghost_realloc
    #ifdef ghost_realloc
        #define ghost_has_ghost_realloc 1
    #endif
#endif
#ifndef ghost_has_ghost_realloc_0alloc
    #ifdef ghost_realloc_0alloc
        #define ghost_has_ghost_realloc_0alloc 1
    #endif
#endif
#ifndef ghost_has_ghost_realloc_0any
    #ifdef ghost_realloc_0any
        #define ghost_has_ghost_realloc_0any 1
    #endif
#endif
#ifndef ghost_has_ghost_realloc_0free
    #ifdef ghost_realloc_0free
        #define ghost_has_ghost_realloc_0free 1
    #endif
#endif
#ifndef ghost_has_ghost_realloc_0null
    #ifdef ghost_realloc_0null
        #define ghost_has_ghost_realloc_0null 1
    #endif
#endif
#ifndef ghost_has_ghost_strdup
    #ifdef ghost_strdup
        #define ghost_has_ghost_strdup 1
    #endif
#endif
#ifndef ghost_has_ghost_strndup
    #ifdef ghost_strndup
        #define ghost_has_ghost_strndup 1
    #endif
#endif

/* ghost/format/ */
#ifndef ghost_has_ghost_asprintf
    #ifdef ghost_asprintf
        #define ghost_has_ghost_asprintf 1
    #endif
#endif
#ifndef ghost_has_ghost_vasprintf
    #ifdef ghost_vasprintf
        #define ghost_has_ghost_vasprintf 1
    #endif
#endif



/*
 * Next define GHOST_MALLOC_SYSTEM.
 */

/* Handle override */
#ifndef ghost_has_GHOST_MALLOC_SYSTEM
    #ifdef GHOST_MALLOC_SYSTEM
        #define ghost_has_GHOST_MALLOC_SYSTEM 1
    #endif
#endif

/* If any allocator function is overridden, GHOST_MALLOC_SYSTEM defaults to 0. */
#ifndef ghost_has_GHOST_MALLOC_SYSTEM
    #if \
            /* ghost/malloc/ */ \
            defined(ghost_has_ghost_aligned_free) || \
            defined(ghost_has_ghost_aligned_malloc) || \
            defined(ghost_has_ghost_calloc) || \
            defined(ghost_has_ghost_calloc_0any) || \
            defined(ghost_has_ghost_calloc_0null) || \
            defined(ghost_has_ghost_free) || \
            defined(ghost_has_ghost_free_nonnull) || \
            defined(ghost_has_ghost_malloc) || \
            defined(ghost_has_ghost_malloc_0any) || \
            defined(ghost_has_ghost_malloc_0null) || \
            defined(ghost_has_ghost_malloc_good_size) || \
            defined(ghost_has_ghost_malloc_size) || \
            defined(ghost_has_ghost_memdup) || \
            defined(ghost_has_ghost_realloc) || \
            defined(ghost_has_ghost_realloc_0alloc) || \
            defined(ghost_has_ghost_realloc_0any) || \
            defined(ghost_has_ghost_realloc_0free) || \
            defined(ghost_has_ghost_realloc_0null) || \
            defined(ghost_has_ghost_strdup) || \
            defined(ghost_has_ghost_strndup) || \
            /* ghost/format/ */ \
            defined(ghost_has_ghost_asprintf) || \
            defined(ghost_has_ghost_vasprintf)
        #define GHOST_MALLOC_SYSTEM 0
        #define ghost_has_GHOST_MALLOC_SYSTEM 1
    #endif
#endif

/* Otherwise we use the system allocator if we're hosted. */
#ifndef ghost_has_GHOST_MALLOC_SYSTEM
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #define GHOST_MALLOC_SYSTEM 1
    #else
        #define GHOST_MALLOC_SYSTEM 0
    #endif
    #define ghost_has_GHOST_MALLOC_SYSTEM 1
#endif

#endif
