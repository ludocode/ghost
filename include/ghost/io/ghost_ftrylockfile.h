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

#ifndef GHOST_FTRYLOCKFILE_H_INCLUDED
#define GHOST_FTRYLOCKFILE_H_INCLUDED

/* This file is almost identical between flockfile(), funlockfile() and
 * ftrylockfile(). It's not practical to merge them so they should be kept in
 * sync. */

#ifndef ghost_has_ghost_ftrylockfile
    #ifdef ghost_ftrylockfile
        #define ghost_has_ghost_ftrylockfile 1
    #endif
#endif

/* ftrylockfile() is declared in <stdio.h>. */
#ifndef ghost_has_ghost_ftrylockfile
    #include "ghost/header/c/ghost_stdio_h.h"
    #if !ghost_has(ghost_stdio_h)
        #define ghost_has_ghost_ftrylockfile 0
    #endif
#endif

/* These platforms have ftrylockfile but don't necessarily declare it. We link
 * against it manually. */
#ifndef ghost_has_ghost_ftrylockfile
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__DragonFly__) || defined(__APPLE__) || defined(__linux__) || \
            defined(__EMSCRIPTEN__)
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/impl/ghost_impl_libc_noexcept.h"
        #if GHOST_IMPL_LIBC_ASM
            #include "ghost/language/ghost_extern_c.h"
            ghost_extern_c
            ghost_dllimport
            int ghost_ftrylockfile(FILE*)
                ghost_impl_libc_noexcept(ghost_impl_libc_asm("ftrylockfile"));
        #else
            #include "ghost/impl/ghost_impl_always_inline.h"
            #include "ghost/preprocessor/ghost_nothing.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            int ghost_ftrylockfile(FILE* ghost_file) {
                ghost_dllimport
                extern int ftrylockfile(FILE*)
                    ghost_impl_libc_noexcept(GHOST_NOTHING);
                return ftrylockfile(ghost_file);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #endif
        #define ghost_has_ghost_ftrylockfile 1
    #endif
#endif

/* ftrylockfile() is in POSIX 1996. We'll need <unistd.h> to check the version. */
#ifndef ghost_has_ghost_ftrylockfile
    #include "ghost/header/posix/ghost_unistd_h.h"
    #ifdef _POSIX_VERSION
        #if _POSIX_VERSION >= 199506L
            #ifdef __cplusplus
                #define ghost_ftrylockfile ::ftrylockfile
            #else
                #define ghost_ftrylockfile ftrylockfile
            #endif
            #define ghost_has_ghost_ftrylockfile 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_ftrylockfile
    #define ghost_has_ghost_ftrylockfile 0
#endif

#endif
