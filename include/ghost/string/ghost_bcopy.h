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

#ifndef GHOST_BCOPY_H_INCLUDED
#define GHOST_BCOPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies count bytes from src to the potentially overlapping memory region
 * dest.
 *
 * This is identical to memmove() except the pointer parameters are in the
 * opposite order.
 */
void ghost_bcopy(const void* src, void* dest, size_t count);
#endif

#ifndef ghost_has_ghost_bcopy
    #ifdef ghost_bcopy
        #define ghost_has_ghost_bcopy 1
    #endif
#endif

#ifndef ghost_has_ghost_bcopy
    /* The bcopy() function is obsolete. We don't bother to wrap any real
     * bcopy(). bcopy() allows overlap so we map it to memmove(). */
    #include "ghost/string/ghost_memmove.h"
    #define ghost_bcopy(src, dest, n) ghost_memmove((dest), (src), (n))
    #define ghost_has_ghost_bcopy 1
#endif

#endif
