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

#ifndef GHOST_ALLOCA_H_INCLUDED
#define GHOST_ALLOCA_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
#define ghost_has_ghost_alloc 1

/**
 * Allocates memory from the current stack frame which will be freed
 * automatically when the function returns.
 *
 * If there is not enough stack space available, the behaviour is
 * undefined.
 *
 * Not all platforms or compilers support this. Check
 * ghost_has(ghost_alloca) to see whether it's supported.
 *
 * @warning ghost_alloca() can be dangerous. Never use this with any size
 * that comes from user input. Stack sizes vary widely among platforms so
 * code that uses this may not be portable.
 *
 * Note that some platforms have restrictions on where alloca() is allowed.
 * Take a look at Microsoft's restrictions in particular:
 *
 *     https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/alloca
 */
void* ghost_alloca(size_t size);

#endif

/* If the user has overridden it directly, there's nothing to do. */
#ifndef ghost_has_ghost_alloca
    #ifdef ghost_alloca
        #define ghost_has_ghost_alloca 1
    #endif
#endif

/* Prefer to use the builtin if it's available. */
#ifndef ghost_has_ghost_alloca
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_alloca)
            #define ghost_has_ghost_alloca 1
            #define ghost_alloca __builtin_alloca
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define ghost_has_ghost_alloca 1
            #define ghost_alloca __builtin_alloca
        #endif
    #endif
#endif

/* MSVC supports the alias _alloca() (with some limitations around its several
 * forms of exception handling.)
 *     https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/alloca
 */
#ifndef ghost_has_ghost_alloca
    #ifdef _MSC_VER
        #include <malloc.h>
        #define ghost_alloca _alloca
        #define ghost_has_ghost_alloca 1
    #endif
#endif

/* cproc doesn't support alloca. */
#ifndef ghost_has_ghost_alloca
    #include "ghost/detect/ghost_cproc.h"
    #if GHOST_CPROC
        #define ghost_has_ghost_alloca 0
    #endif
#endif

/* alloca() is not in POSIX. It is widely supported by the BSDs and various
 * other unixes but it is defined in different headers on each platform. */
#ifndef ghost_has_ghost_alloca

    /* Include <string.h> to detect the libc */
    #include "ghost/header/c/ghost_string_h.h"

    /* On the BSDs it's in <stdlib.h>. */
    #if defined(__FreeBSD__) || defined(__NetBSD__) || \
            defined(__OpenBSD__) || defined(__DragonFly__)
        #include "ghost/header/c/ghost_stdlib_h.h"
        #if ghost_has(ghost_stdlib_h)
            #define ghost_alloca alloca
            #define ghost_has_ghost_alloca 1
        #endif
    #endif

    /* On Linux and macOS it's in <alloca.h>.
     * (On macOS it's apparently also in <stdlib.h>.)
     * We don't bother to put this in ghost/header/ since this is the only file
     * that uses this. */
    #if defined(__linux__) || defined(__APPLE__)
        /* If we can check, we check, but we otherwise assume the platform has it. */
        #include "ghost/preprocessor/ghost_has_include.h"
        #if ghost_has(ghost_has_include)
            #if __has_include(<alloca.h>)
                #include <alloca.h>
                #define ghost_alloca alloca
                #define ghost_has_ghost_alloca 1
            #endif
        #else
            #include <alloca.h>
            #define ghost_alloca alloca
            #define ghost_has_ghost_alloca 1
        #endif
    #endif

    /* Many more platforms need to be supported. */
#endif

/* Otherwise we don't support it. */
#ifndef ghost_has_ghost_alloca
    #define ghost_has_ghost_alloca 0
#endif

#endif
