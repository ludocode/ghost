/*
 * MIT No Attribution
 *
 * Copyright (c) 2026 Fraser Heavy Software
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

#ifndef GHOST_SYS_PARAM_H_H_INCLUDED
#define GHOST_SYS_PARAM_H_H_INCLUDED

/**
 * @file
 *
 * Includes <sys/param.h> if possible.
 *
 * This is not a POSIX header but it's commonly available on POSIX systems
 * including Linux and the BSDs. It contains system macros such as
 * __FreeBSD_version.
 *
 * Check `#if ghost_has(ghost_sys_param_h)` to see whether it was actually
 * included.
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* If we can check whether <sys/param.h> exists, prefer that. */
#ifndef ghost_has_ghost_sys_param_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<sys/param.h>)
            #include <sys/param.h>
            #define ghost_has_ghost_sys_param_h 1
        #else
            #define ghost_has_ghost_sys_param_h 0
        #endif
    #endif
#endif

/* If this is a UNIX-like system, assume it exists. */
#ifndef ghost_has_ghost_param_h
    #include "ghost/detect/ghost_unix.h"
    #if GHOST_UNIX
        #include <sys/param.h>
        #define ghost_has_ghost_sys_param_h 1
    #endif
#endif

/* Otherwise assume it doesn't. */
#ifndef ghost_has_ghost_sys_param_h
    #define ghost_has_ghost_sys_param_h 0
#endif

#endif
