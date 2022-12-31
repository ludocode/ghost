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

#ifndef GHOST_GLIBC_H_INCLUDED
#define GHOST_GLIBC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_GLIBC
 *
 * Defined to 1 if the libc is glibc (and not a similar libc like uClibc), and
 * 0 otherwise.
 */
#endif

/* uClibc masquerades as glibc. We make sure when we check glibc, we mean
 * glibc, not any pretenders. */
#ifndef ghost_has_GHOST_GLIBC
    #ifndef GHOST_GLIBC
        #include "ghost/detect/ghost_libc.h"
        #if defined(__GLIBC__) && !defined(__UCLIBC__)
            #define GHOST_GLIBC 1
        #else
            #define GHOST_GLIBC 0
        #endif
    #endif
    #define ghost_has_GHOST_GLIBC 1
#endif

#endif
