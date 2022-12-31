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

#ifndef GHOST_ALIGNED_MALLOC_H_INCLUDED
#define GHOST_ALIGNED_MALLOC_H_INCLUDED

#include "ghost/ghost_core.h"

/* ghost_aligned_malloc() and ghost_aligned_free() should be defined together
 * so we define them both in this file. */

#if GHOST_DOCUMENTATION
/**
 * Allocates memory aligned to the given alignment.
 *
 * The alignment must be a power of two. The size must be a multiple of the
 * alignment.
 *
 * You must free memory allocated by ghost_aligned_malloc() with
 * ghost_aligned_free(), not ghost_free()!
 *
 * Some platforms use a separate heap for aligned allocations. Other platforms
 * don't support an aligned allocation so Ghost will perform alignment
 * manually, which must be undone to be freed. For these reasons, you cannot
 * free Ghost's aligned allocations with ghost_free().
 *
 * @see ghost_aligned_free()
 */
void* ghost_aligned_malloc(size_t alignment, size_t size);

/**
 * Frees the given aligned pointer.
 *
 * You must use this instead of ghost_free() to free memory allocated by
 * ghost_aligned_malloc().
 *
 * @see ghost_aligned_malloc
 */
void ghost_aligned_free(void* ptr);
#endif

/* Overrides are handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/* TODO rewrite later */
#define ghost_has_ghost_aligned_free 0
#define ghost_has_ghost_aligned_malloc 0
#if 0


/* TODO ghost_has this file, what a mess */




/* TODO wrap in function push/pop */
#include "ghost/impl/ghost_impl_inline.h"

/* TODO fix headers */
#include "ghost/language/ghost_cplusplus.h"
#include "ghost/language/ghost_hosted.h"
#include "ghost/language/ghost_null.h"
#include "ghost/language/ghost_static_cast.h"
#include "ghost/language/ghost_bless.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/type/uintptr_t/ghost_uintptr_t.h"
#include "ghost/math/is_pow2/ghost_is_pow2_z.h"

#if GHOST_HOSTED
#include "ghost/header/c/ghost_stdlib_h.h"
#endif
#ifdef _MSC_VER
#include <malloc.h>
#endif

/* TODO use GHOST_IMPL_FUNCTION_OPEN/CLOSE */

/*
 * We check for MSVC _aligned_malloc() first. MSVC currently does not support
 * aligned_alloc() even in C11 mode. If MSVC adds the standard aligned_alloc()
 * later, we may not be able to switch to it because different translation
 * units may be using different versions of Ghost, and their alloc/free
 * functions need to be compatible.
 */
#ifdef _MSC_VER
    /* https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/aligned-malloc */
    #ifndef ghost_aligned_malloc
        #define ghost_aligned_malloc(alignment, size) _aligned_malloc(size, alignment)
    #endif
    #ifndef ghost_aligned_free
        #define ghost_aligned_free(p) _aligned_free(p)
    #endif
#endif

/* aligned_alloc() is in C11 and C++17 and can be freed with free() */
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ >= 201112L
        #ifndef ghost_aligned_malloc
            #define ghost_aligned_malloc aligned_alloc
        #endif
        #ifndef ghost_aligned_free
            #define ghost_aligned_free ghost_free
        #endif
    #endif
#endif
#ifdef __cplusplus
    #if __cplusplus >= 201703L
        #ifndef ghost_aligned_malloc
            #define ghost_aligned_malloc aligned_alloc
        #endif
        #ifndef ghost_aligned_free
            #define ghost_aligned_free ghost_free
        #endif
    #endif
#endif

/*
 * posix_memalign() is required by POSIX. It's been around in glibc since
 * 2.1.91 which was released in 2000 or so? For now we just assume __unix__
 * covers it. If we find some UNIX platforms that don't support it we can turn
 * them off here, or we can convert this to a better test.
 *
 * TODO GHOST_UNIX, or do this properly with POSIX feature test macro
 */
#ifdef __unix__
    #ifndef ghost_aligned_malloc
        /* posix_memalign() may not actually be declared in the headers if the
         * user isn't compiling with POSIX support so we declare it ourselves. */
        ghost_impl_inline
        void* ghost_aligned_malloc(ghost_size_t alignment, ghost_size_t size) {
            int posix_memalign(void**, ghost_size_t, ghost_size_t);
            void* ret;
            if (0 != posix_memalign(&ret, alignment, size))
                return ghost_null;
            return ret;
        }
        #define ghost_aligned_malloc ghost_aligned_malloc
    #endif
    #ifndef ghost_aligned_free
        /* posix_memalign() can be freed with free(). */
        #define ghost_aligned_free ghost_free
    #endif
#endif

/*
 * Some old systems supported memalign(). On some such systems, memory
 * allocated with memalign() could be freed with free(), but apparently there
 * are others where memory aligned with memalign() cannot ever be freed.
 * Obviously we should not use memalign() on systems where it can't be freed.
 * For now we assume any relevant systems at least have posix_memalign() so we
 * don't bother with memalign().
 */
#if 0
    #ifndef ghost_aligned_alloc
        #define ghost_aligned_alloc(alignment, size) memalign(size, alignment)
    #endif
    #ifndef ghost_aligned_free
        #define ghost_aligned_free ghost_free
    #endif
#endif

/* manual alignment */
#ifndef ghost_aligned_malloc
    ghost_impl_inline
    void* ghost_aligned_malloc_impl(ghost_size_t alignment, ghost_size_t size) {
        ghost_assert(ghost_is_pow2_z(alignment));

        /* must align to at least pointer for our stashed pointer to be valid
         * (technically this would not be a requirement if we used unaligned
         * load/store for the stashed pointer but we don't bother because who would
         * use this for smaller than pointer alignment?) */
        if (alignment < sizeof(void*))
            alignment = sizeof(void*);

        /* expand the allocation to include enough space for us to manually align,
         * plus space to stash the original pointer */
        size = size + alignment + sizeof(void*);
        char* original = ghost_static_cast(char*, ghost_malloc(size));
        if (original == ghost_null)
            return ghost_null;

        /* align and stash the original pointer */
        char* p = original;
        p += sizeof(void*);
        p += ghost_cast(uintptr_t, p + alignment - 1) & (alignment - 1);
        *ghost_bless(void*, 1, ghost_cast(uintptr_t, p) - sizeof(void*)) = original;

        return p;
    }
    #define ghost_aligned_malloc ghost_aligned_malloc_impl
#endif
#ifndef ghost_aligned_free
    ghost_impl_inline
    void* ghost_aligned_free_impl(void* p) {
        ghost_free(ghost_static_cast(void**, p)[-1]);
    }
    #define ghost_aligned_free ghost_aligned_free_impl
#endif

/* TODO above file is a mess, needs to be split up */

#define ghost_has_ghost_aligned_free 1
#define ghost_has_ghost_aligned_malloc 1
#endif

#endif
