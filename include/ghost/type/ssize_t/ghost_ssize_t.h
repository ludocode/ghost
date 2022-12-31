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

#ifndef GHOST_SSIZE_T_H_INCLUDED
#define GHOST_SSIZE_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * An alias of ssize_t or SSIZE_T (if possible), which is a signed integer
 * type the same width as the result type of `sizeof`.
 */
typedef ssize_t ghost_ssize_t;
#endif

/* Include system headers to make sure the real ssize_t and SSIZE_T will be
 * defined if possible. */
#ifdef _WIN32
    /*
     * TODO we should probably wrap this header. It's not clear if we should
     * include it directly or if we should just include <Windows.h>; unlike most
     * Windows documentation, the documentation here does not say we should include
     * <Windows.h>:
     *
     *     https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types?redirectedfrom=MSDN
     *
     * It would be nice to avoid <Windows.h> wherever possible.
     */
    #include <BaseTsd.h>
#else
    #include "ghost/header/posix/ghost_sys_types_h.h"
#endif

#ifndef ghost_has_ghost_ssize_t
    #ifdef ghost_ssize_t
        #define ghost_has_ghost_ssize_t 1
    #endif
#endif

/* Windows has SSIZE_T. */
#ifndef ghost_has_ghost_ssize_t
    #ifdef _WIN32
        typedef SSIZE_T ghost_ssize_t;
        #define ghost_has_ghost_ssize_t 1
    #endif
#endif

/* ssize_t is in POSIX. */
#ifndef ghost_has_ghost_ssize_t
    /* TODO for now assume it exists if <unistd.h> does. We need better
     * POSIX detection. */
    #include "ghost/header/posix/ghost_unistd_h.h"
    #if ghost_has(ghost_unistd_h)
        typedef ssize_t ghost_ssize_t;
        #define ghost_has_ghost_ssize_t 1
    #endif
#endif

/* Technically ssize_t isn't required by POSIX to be the same width as size_t.
 * If any platforms exist where they don't have the same width, this would be
 * because the platform defines ssize_t itself which we should detect above.
 * Since we're defining it ourselves, we can define it to be the same width as
 * size_t. */
/* TODO define this the same width as size_t */

#ifndef ghost_has_ghost_ssize_t
    #define ghost_has_ghost_ssize_t 0
#endif

#endif
