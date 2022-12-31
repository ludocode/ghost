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

#ifndef GHOST_SYS_MMAN_H_H_INCLUDED
#define GHOST_SYS_MMAN_H_H_INCLUDED

/**
 * @file
 *
 * Includes <sys/mman.h> if possible, which declares mmap() and friends.
 *
 * Check `#if ghost_has(ghost_sys_mman_h)` to see whether it was actually included.
 *
 *     https://man.archlinux.org/man/sys_mman.h.0p.en
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* If we can check whether <sys/mman.h> exists, prefer that. */
#ifndef ghost_has_ghost_sys_mman_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<sys/mman.h>)
            #include <sys/mman.h>
            #define ghost_has_ghost_sys_mman_h 1
        #else
            #define ghost_has_ghost_sys_mman_h 0
        #endif
    #endif
#endif

/* If this is a UNIX-like system, assume it exists. */
#ifndef ghost_has_ghost_pthread_h
    #include "ghost/detect/ghost_unix.h"
    #if GHOST_UNIX
        #include <sys/mman.h>
        #define ghost_has_ghost_sys_mman_h 1
    #endif
#endif

/* sys/mman.h and mmap() are specified by POSIX. Maybe we should be checking a
 * macro like `_POSIX_VERSION` or `_POSIX_C_SOURCE` here like we do for
 * <unistd.h>. For now we don't do it. */

/* Otherwise assume it doesn't. */
#ifndef ghost_has_ghost_sys_mman_h
    #define ghost_has_ghost_sys_mman_h 0
#endif

#endif
