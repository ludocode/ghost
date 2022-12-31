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

#ifndef GHOST_MALLOC_SIZE_H_INCLUDED
#define GHOST_MALLOC_SIZE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the real allocated size of the given pointer (which may be larger
 * than requested, and may or may not be the size preserved by realloc().)
 *
 * @warning Be careful using this function with realloc()! It may not preserve
 *          the padding! This function is not as useful as it sounds.
 *
 * If this returns a larger size than you originally asked for, on platforms
 * where this is implemented it is generally safe, though not necessarily wise,
 * to use the additional space. However, it is not safe to use the space if you
 * will later pass the pointer to realloc() because realloc() may or may not
 * preserve the additional bytes. (In particular, FreeBSD's jemalloc and the
 * Apple platforms will preserve the additional bytes but glibc's ptmalloc will
 * not.)
 *
 * Generally you should avoid using this unless you are either implementing a
 * custom realloc() or avoiding realloc() completely. If you want to allocate
 * "at least" a certain amount to avoid wasting the allocator padding, it's
 * better to ask the allocator for an appropriate size with
 * `ghost_malloc_good_size()` (or even just guess, e.g. by rounding up to a
 * power of two) before allocating.
 *
 * Really this is mostly useful just as a debugging tool, as the Linux man
 * page for malloc_usable_size() suggests.
 */
size_t ghost_malloc_size(void*)
#endif

/* Override is handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/* macOS supports this. */
#ifndef ghost_has_ghost_malloc_size
    #if defined(__APPLE__)
        #include <malloc/malloc.h>
        #ifdef __cplusplus
            #define ghost_malloc_size ::malloc_size
        #else
            #define ghost_malloc_size malloc_size
        #endif
        #define ghost_has_ghost_malloc_size 1
    #endif
#endif

/* jemalloc (and therefore FreeBSD) support this via sallocx(). */
#ifndef ghost_has_ghost_malloc_size
    #ifdef GHOST_IMPL_MALLOC_SIZE_JEMALLOC
        #error "You cannot pre-define GHOST_IMPL_MALLOC_SIZE_JEMALLOC."
    #endif

    #include "ghost/impl/binding/jemalloc/ghost_impl_jemalloc.h"
    #if GHOST_USE_JEMALLOC
        #include <jemalloc/jemalloc.h>
        #define GHOST_IMPL_MALLOC_SIZE_JEMALLOC
    #elif defined(__FreeBSD__)
        #include <malloc_np.h>
        #define GHOST_IMPL_MALLOC_SIZE_JEMALLOC
    #endif

    #ifdef GHOST_IMPL_MALLOC_SIZE_JEMALLOC
        #undef GHOST_IMPL_MALLOC_SIZE_JEMALLOC
        #ifdef __cplusplus
            #define ghost_malloc_size(p) ::sallocx((p), 0)
        #else
            #define ghost_malloc_size(p) sallocx((p), 0)
        #endif
        #define ghost_has_ghost_malloc_size 1
    #endif
#endif

/* glibc and musl support malloc_usable_size() in <malloc.h>. */
#ifndef ghost_has_ghost_malloc_size
    #ifdef __linux__
        #include "ghost/detect/ghost_musl.h"
        #if defined(__GLIBC__) || GHOST_MUSL
            #include <malloc.h>
            #ifdef __cplusplus
                #define ghost_malloc_size ::malloc_usable_size
            #else
                #define ghost_malloc_size malloc_usable_size
            #endif
            #define ghost_has_ghost_malloc_size 1
        #endif
    #endif
#endif

/* Otherwise we have no support. */
#ifndef ghost_has_ghost_malloc_size
    #define ghost_has_ghost_malloc_size 0
#endif

#endif
