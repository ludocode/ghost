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

#ifndef GHOST_MAP_ANON_H_INCLUDED
#define GHOST_MAP_ANON_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Create an anonymous read/write memory mapping of the given size.
 *
 * This is a wrapper around mmap(MAP_ANONYMOUS) on UNIX and VirtualAlloc() on
 * Windows. Use this to get large blocks of memory from the operating system
 * to, for example, implement a simple custom memory allocator.
 *
 * Returns NULL on failure (unlike POSIX mmap which returns -1.) Getting a
 * reason for the failure is platform-specific but you can probably assume
 * it's because of insufficient memory or address space.
 *
 * @see ghost_unmap_anon()
 */
void* ghost_map_anon(size_t length);
#endif

#ifndef ghost_has_ghost_map_anon
    #ifdef ghost_map_anon
        #define ghost_has_ghost_map_anon 1
    #endif
#endif

/* Windows VirtualAlloc() */
#ifndef ghost_has_ghost_map_anon
    #ifdef _WIN32
        #include "ghost/header/windows/ghost_windows_h.h"
        #include "ghost/language/ghost_null.h"
        #define ghost_map_anon(size) \
            VirtualAlloc(ghost_null, (size), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)
        #define ghost_has_ghost_map_anon 1
    #endif
#endif

/* UNIX mmap() */
#ifndef ghost_has_ghost_map_anon
    #include "ghost/header/posix/ghost_sys_mman_h.h"
    #if ghost_has(ghost_sys_mman_h) && (defined(MAP_ANON) || defined(MAP_ANONYMOUS))
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_null.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_function
        void* ghost_map_anon(ghost_size_t size)
        #if !GHOST_EMIT_DEFS
        ;
        #else
        {

            /* Linux seems to prefer MAP_ANONYMOUS but the BSDs prefer MAP_ANON
             * and Solaris and QNX only document MAP_ANON. */
            int flags = MAP_PRIVATE |
                    #ifdef MAP_ANON
                        MAP_ANON
                    #else
                        MAP_ANONYMOUS
                    #endif
                    ;

            /* OpenBSD and possibly others require that fd be -1 for
             * anonymous mappings. */
            int fd = -1;

            void* address = mmap(ghost_null, size, PROT_READ | PROT_WRITE, flags, fd, 0);
            if (address == MAP_FAILED)
                return ghost_null;
            return address;
        }
        #endif
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_map_anon 1
    #endif
#endif

/* Apparently on some older UNIX that didn't support MAP_ANON you could open
 * /dev/zero and mmap it. This would give you copy-on-write pages of zeroes
 * that won't be written back to a file so it's the same as an anonymous
 * mapping. We don't bother implementing this. */

/* Without any of the above we have no support for anonymous mappings. */
#ifndef ghost_has_ghost_map_anon
    #define ghost_has_ghost_map_anon 0
#endif

#endif
