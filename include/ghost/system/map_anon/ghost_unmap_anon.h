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

#ifndef GHOST_UNMAP_ANON_H_INCLUDED
#define GHOST_UNMAP_ANON_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Free an anonymous read/write memory mapping of the given size that was
 * created with ghost_map_anon().
 *
 * You must pass the exact pointer and size from a previous call to
 * ghost_map_anon() if you want to be portable. Some platforms do not support
 * freeing a portion of a mapping.
 *
 * This is a wrapper around munmap() on Linux and VirtualFree() on Windows. Use
 * this to implement a simple custom memory allocator (for example.)
 *
 * If unmapping fails, the program aborts.
 *
 * @see ghost_map_anon()
 */
void ghost_unmap_anon(void* address, size_t length);
#endif

#ifndef ghost_has_ghost_unmap_anon
    #ifdef ghost_unmap_anon
        #define ghost_has_ghost_unmap_anon 1
    #endif
#endif

/*
 * Windows VirtualFree()
 *     https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualfree
 */
#ifndef ghost_has_ghost_unmap_anon
    #ifdef _WIN32
        #include "ghost/header/windows/ghost_windows_h.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/header/windows/ghost_windows_h.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/language/ghost_discard.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_unmap_anon(void* address, ghost_size_t size) {
            /* Note that we pass the size as 0 here. Windows does not allow you
             * to release a portion of pages from a previous VirtualAlloc().
             *
             * TODO see if there's a way to query a mapping size to assert it. Using VirtualQuery() maybe?
             * https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualquery
             */
            ghost_discard(size);
            ghost_ensure(VirtualFree(address, 0, MEM_RELEASE), "VirtualFree() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_unmap_anon 1
    #endif
#endif

/* UNIX munmap() */
#ifndef ghost_has_ghost_unmap_anon
    #include "ghost/header/posix/ghost_sys_mman_h.h"
    #if ghost_has(ghost_sys_mman_h) && (defined(MAP_ANON) || defined(MAP_ANONYMOUS))
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_ensure.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_unmap_anon(void* address, ghost_size_t size) {
            ghost_ensure(0 == munmap(address, size), "munmap() failed");
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_unmap_anon 1
    #endif
#endif

/* Without any of the above we have no support for anonymous mappings. */
#ifndef ghost_has_ghost_unmap_anon
    #define ghost_has_ghost_unmap_anon 0
#endif

#endif
