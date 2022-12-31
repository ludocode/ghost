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

#ifndef GHOST_UNMAP_CONCEAL_H_INCLUDED
#define GHOST_UNMAP_CONCEAL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Frees an anonymous concealed read/write memory mapping of the given size
 * that was created with ghost_map_conceal().
 *
 * You must pass the exact pointer and size from a previous call to
 * ghost_map_conceal() if you want to be portable. Some platforms do not
 * support freeing a portion of a mapping.
 *
 * If unmapping fails, the program aborts.
 */
void ghost_unmap_anon(void* address, size_t length);
#endif

#ifndef ghost_has_ghost_unmap_conceal
    #ifdef ghost_unmap_conceal
        #define ghost_has_ghost_unmap_conceal 1
    #endif
#endif

/* Security-related stuff in Ghost is experimental. */
#ifndef ghost_has_ghost_unmap_conceal
    #if !GHOST_EXPERIMENTAL
        #define ghost_has_ghost_unmap_conceal 0
    #endif
#endif

/* Currently this is just a wrapper around ghost_unmap_anon(). */
#ifndef ghost_has_ghost_unmap_conceal
    #include "ghost/system/map_anon/ghost_unmap_anon.h"
    #if ghost_has(ghost_unmap_anon)
        #define ghost_unmap_conceal ghost_unmap_anon
        #define ghost_has_ghost_unmap_conceal 1
    #endif
#endif

#ifndef ghost_has_ghost_unmap_conceal
    #define ghost_has_ghost_unmap_conceal 0
#endif

#endif
