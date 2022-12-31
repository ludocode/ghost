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

#ifndef GHOST_FILENO_H_INCLUDED
#define GHOST_FILENO_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Gets the file descriptor for the given FILE*.
 */
int ghost_fileno(FILE*);
#endif

#ifndef ghost_has_ghost_fileno
    #ifdef ghost_fileno
        #define ghost_has_ghost_fileno 1
    #endif
#endif

/* If fileno() exists it will be declared in <stdio.h>. */
#ifndef ghost_has_ghost_fileno
    #include "ghost/header/c/ghost_stdio_h.h"
    #if !ghost_has(ghost_stdio_h)
        #define ghost_has_ghost_fileno 0
    #endif
#endif

/* On Windows we have to use _fileno(). */
#ifndef ghost_has_ghost_fileno
    #ifdef _WIN32
        #ifdef __cplusplus
            #define ghost_fileno ::_fileno
        #else
            #define ghost_fileno _fileno
        #endif
        #define ghost_has_ghost_fileno 1
    #endif
#endif

/* On some platforms fileno() is a macro (e.g. on FreeBSD, something to do with
 * an alternate implementation for threaded code.) If it exists we have to wrap
 * it. */
#ifndef ghost_has_ghost_fileno
    #ifdef fileno
        #define ghost_fileno fileno
        #define ghost_has_ghost_fileno 1
    #endif
#endif

/* These platforms have fileno but don't necessarily declare it. We link
 * against it manually. */
#ifndef ghost_has_ghost_fileno
    #if defined(__APPLE__) || defined(__linux__) || defined(__EMSCRIPTEN__)
        #include "ghost/impl/ghost_impl_libc_noexcept.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/language/ghost_dllimport.h"
        #if GHOST_IMPL_LIBC_ASM
            #include "ghost/language/ghost_extern_c.h"
            ghost_extern_c
            ghost_dllimport
            int ghost_fileno(FILE*)
                ghost_impl_libc_noexcept(ghost_impl_libc_asm("fileno"));
        #else
            #include "ghost/impl/ghost_impl_always_inline.h"
            #include "ghost/preprocessor/ghost_nothing.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            int ghost_fileno(FILE* ghost_file) {
                ghost_dllimport
                extern int fileno(FILE*)
                    ghost_impl_libc_noexcept(GHOST_NOTHING);
                return fileno(ghost_file);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #endif
        #define ghost_has_ghost_fileno 1
    #endif
#endif

/* fileno() is in POSIX 1996. We'll need <unistd.h> to check the version. */
#ifndef ghost_has_ghost_fileno
    #include "ghost/header/posix/ghost_unistd_h.h"
    #ifdef _POSIX_VERSION
        #if _POSIX_VERSION >= 199506L
            #ifdef __cplusplus
                #define ghost_fileno ::fileno
            #else
                #define ghost_fileno fileno
            #endif
            #define ghost_has_ghost_fileno 1
        #endif
    #endif
#endif

/* Otherwise we don't have fileno. */
#ifndef ghost_has_ghost_fileno
    #define ghost_has_ghost_fileno 0
#endif

#endif
