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

#ifndef GHOST_MAP_CONCEAL_H_INCLUDED
#define GHOST_MAP_CONCEAL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Creates an anonymous read/write memory mapping of the given size and tries
 * to exclude it from core dumps and swap if the system supports such hints.
 *
 * If the system does not support ways to conceal the memory, this will be an
 * ordinary mapping (the same as ghost_map_anon().)
 *
 * Use this to allocate memory (or to implement a memory allocator) that will
 * store sensitive data such as encryption keys.
 *
 * Returns NULL on failure (unlike POSIX mmap which returns -1.) Getting a
 * reason for the failure is platform-specific but you can probably assume
 * it's because of insufficient memory or address space.
 */
void* ghost_map_conceal(size_t length);
#endif

#ifndef ghost_has_ghost_map_conceal
    #ifdef ghost_map_conceal
        #define ghost_has_ghost_map_conceal 1
    #endif
#endif

/* Security-related stuff in Ghost is experimental. */
#ifndef ghost_has_ghost_map_conceal
    #if !GHOST_EXPERIMENTAL
        #define ghost_has_ghost_map_conceal 0
    #endif
#endif

/* Some functions like madvise() and mlock() return EAGAIN if "a resource" is
 * unavailable. Apparently the kernel can be busy doing something so we need to
 * try again later, but it doesn't give any indication as to how much later.
 * For now we just try again a few times. */
#ifndef GHOST_IMPL_MAP_CONCEAL_RETRY_COUNT
    #define GHOST_IMPL_MAP_CONCEAL_RETRY_COUNT 10
#endif

/* Linux hides pages from core dumps via madvise(). It also has mlock2() with
 * MLOCK_ONFAULT which will lock pages after they are populated so we don't
 * need to populate them right away. */
#ifndef ghost_has_ghost_map_conceal
    #ifdef __linux__
        #include "ghost/header/posix/ghost_sys_mman_h.h"
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/language/ghost_expect_true.h"
        #include "ghost/error/ghost_errno_is.h"
        #include "ghost/debug/ghost_fatal.h"
        #include "ghost/thread/ghost_thread_yield.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        void* ghost_map_conceal(ghost_size_t size) GHOST_IMPL_DEF({
            void* address = mmap(ghost_null, size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            if (address == MAP_FAILED)
                return ghost_null;

            /* madvise() MADV_DONTDUMP */
            /* TODO musl hides MADV_DONTDUMP under _GNU_SOURCE or _BSD_SOURCE */
            size_t i;
            for (i = 0; i < GHOST_IMPL_MAP_CONCEAL_RETRY_COUNT; ++i) {
                int ret = madvise(address, size, MADV_DONTDUMP);
                if (ghost_expect_true(ret == 0))
                    break;
                if (!ghost_errno_is(EAGAIN)) {
                    /* We got some mystery error from madvise(). Fail. */
                    if (0 != munmap(address, size))
                        ghost_fatal("Failed to munmap() memory just mapped!");
                    return ghost_null;
                }
                #if ghost_has(ghost_thread_yield)
                    ghost_thread_yield();
                #endif
            }

            /* mlock2() MLOCK_ONFAULT */
            size_t i;
            for (i = 0; i < GHOST_IMPL_MAP_CONCEAL_RETRY_COUNT; ++i) {
                int ret = mlock2(address, size, MLOCK_ONFAULT);
                if (ghost_expect_true(ret == 0))
                    break;
                if (!ghost_errno_is(EAGAIN)) {
                    /* We got some mystery error from mlock2(). Fail. */
                    if (0 != munmap(address, size))
                        ghost_fatal("Failed to munmap() memory just mapped!");
                    return ghost_null;
                }
                #if ghost_has(ghost_thread_yield)
                    ghost_thread_yield();
                #endif
            }

            return address;
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_map_conceal 1
    #endif
#endif

/*
 * Other UNIX mmap()
 *
 * We create the mapping, populate the pages, hide them from core dumps, and
 * lock them to prevent swapping. Some of this can be done with flags to
 * mmap().
 *
 * We need to populate the pages first because otherwise mlock() might only
 * lock copy-on-write pages of zeroes, not the real pages when it actually
 * populates them. It's not clear whether mlock() populates on all platforms or
 * whether all platforms will lock the new pages upon copying.
 */
#ifndef ghost_has_ghost_map_conceal
    #include "ghost/header/posix/ghost_sys_mman_h.h"
    #if ghost_has(ghost_sys_mman_h) && (defined(MAP_ANON) || defined(MAP_ANONYMOUS))
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        void* ghost_map_conceal(ghost_size_t size) GHOST_IMPL_DEF({

            int flags = MAP_PRIVATE |
                    #ifdef MAP_ANON
                        MAP_ANON
                    #else
                        MAP_ANONYMOUS
                    #endif

                    /* These platforms provide a mapping flag that can be
                     * passed to mmap(). */
                    #ifdef __OpenBSD__
                        | MAP_CONCEAL
                    #elif defined(__FreeBSD__)
                        | MAP_NOCORE
                    #endif
                    ;

            /* OpenBSD and possibly others require that fd be -1 for
             * anonymous mappings. */
            int fd = -1;

            void* address = mmap(ghost_null, size, PROT_READ | PROT_WRITE, flags, fd, 0);
            if (address == MAP_FAILED)
                return ghost_null;

            /* For now we'll assume mlock() populates. */
            size_t i;
            for (i = 0; i < GHOST_IMPL_MAP_CONCEAL_RETRY_COUNT; ++i) {
                int ret = mlock(address, size);
                if (ghost_expect_true(ret == 0))
                    break;
                if (!ghost_errno_is(EAGAIN)) {
                    /* We got some mystery error from mlock2(). Fail. */
                    if (0 != munmap(address, size))
                        ghost_fatal("Failed to munmap() memory just mapped!");
                    return ghost_null;
                }
                #if ghost_has(ghost_thread_yield)
                    ghost_thread_yield();
                #endif
            }

            return address;
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_map_conceal 1
    #endif
#endif

/* Fallback to ordinary ghost_map_anon() */
#ifndef ghost_has_ghost_map_conceal
    #include "ghost/system/map_anon/ghost_map_anon.h"
    #if ghost_has(ghost_map_anon)
        #define ghost_map_conceal ghost_map_anon
        #define ghost_has_ghost_map_conceal 1
    #endif
#endif

/* Otherwise we don't have it. */
#ifndef ghost_has_ghost_map_conceal
    #define ghost_has_ghost_map_conceal 0
#endif

#endif
