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

#ifndef GHOST_ISATTY_H_INCLUDED
#define GHOST_ISATTY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
int ghost_isatty(int fd);
#endif

#ifndef ghost_has_ghost_isatty
    #ifdef ghost_isatty
        #define ghost_has_ghost_isatty 1
    #endif
#endif

/* On Windows we have to use _isatty() from <io.h>. */
#ifndef ghost_has_ghost_isatty
    #ifdef _WIN32
        #include <io.h>
        #ifdef __cplusplus
            #define ghost_isatty ::_isatty
        #else
            #define ghost_isatty _isatty
        #endif
        #define ghost_has_ghost_isatty 1
    #endif
#endif

/* POSIX isatty() is otherwise in <unistd.h>. */
#ifndef ghost_has_ghost_isatty
    #include "ghost/header/posix/ghost_unistd_h.h"
    #if !ghost_has(ghost_unistd_h)
        #define ghost_has_ghost_isatty 0
    #endif
#endif

/* If we have a new enough POSIX, it will have isatty(). */
#ifndef ghost_has_ghost_isatty
    #ifdef _POSIX_VERSION
        #if _POSIX_VERSION >= 199506L
            #ifdef __cplusplus
                #define ghost_isatty ::isatty
            #else
                #define ghost_isatty isatty
            #endif
            #define ghost_has_ghost_isatty 1
        #endif
    #endif
#endif

/* isatty() is usually declared unconditionally in <unistd.h> regardless of
 * _POSIX_C_SOURCE or _POSIX_VERSION. On these platforms we assume it was
 * declared. */
#ifndef ghost_has_ghost_isatty
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__DragonFly__) || defined(__APPLE__) || defined(__linux__)
        #ifdef __cplusplus
            #define ghost_isatty ::isatty
        #else
            #define ghost_isatty isatty
        #endif
        #define ghost_has_ghost_isatty 1
    #endif
#endif

#ifndef ghost_has_ghost_isatty
    #define ghost_has_ghost_isatty 0
#endif

#endif
