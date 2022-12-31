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

#ifndef GHOST_CLOSE_H_INCLUDED
#define GHOST_CLOSE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A wrapper around POSIX close().
 *
 * @warning close() has platform-specific behaviour around returning EINTR.
 *          Consider using ghost_close_nointr().
 *
 * @see ghost_close_nointr()
 */
int ghost_close(int fd);
#endif

#ifndef ghost_has_ghost_close
    #ifdef ghost_close
        #define ghost_has_ghost_close 1
    #endif
#endif

/* Windows has _close() in <io.h>. */
#ifndef ghost_has_ghost_close
    #ifdef _WIN32
        #include <io.h>
        #ifdef __cplusplus
            #define ghost_close ::_close
        #else
            #define ghost_close _close
        #endif
        #define ghost_has_ghost_close 1
    #endif
#endif

/* POSIX close() is in <unistd.h>. If we have <unistd.h> we assume close() is
 * available regardless of the POSIX version. */
#ifndef ghost_has_ghost_close
    #include "ghost/header/posix/ghost_unistd_h.h"
    #if ghost_has_ghost_unistd_h
        #ifdef __cplusplus
            #define ghost_close ::close
        #else
            #define ghost_close close
        #endif
        #define ghost_has_ghost_close 1
    #endif
#endif

/* Otherwise we don't have it. */
#ifndef ghost_has_ghost_close
    #define ghost_has_ghost_close 0
#endif

#endif
