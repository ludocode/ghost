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

#ifndef GHOST_BZERO_H_INCLUDED
#define GHOST_BZERO_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Zeroes the given memory region.
 */
void ghost_bzero(void* p, size_t count);
#endif

#ifndef ghost_has_ghost_bzero
    #ifdef ghost_bzero
        #define ghost_has_ghost_bzero 1
    #endif
#endif

/* The bzero() function is obsolete. Many platforms have bzero() and Windows
 * has ZeroMemory() but (at least for now) we don't bother to wrap them. We
 * just map it to memset(). */
#ifndef ghost_has_ghost_bzero
    #include "ghost/string/ghost_memset.h"
    #define ghost_bzero(s, n) ghost_memset((s), 0, (n))
    #define ghost_has_ghost_bzero 1
#endif

#endif
