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

#ifndef GHOST_ALLOC_ZERO_H_INCLUDED
#define GHOST_ALLOC_ZERO_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_alloc_zero(T) (T*) ghost_calloc(1, sizeof(T))
 *
 * Allocates a value of the given type and zeroes it.
 *
 * This can be more efficient than zeroing with memset() because in-process
 * zeroing won't be necessary if the operating system can provide zeroed
 * memory.
 *
 * Some compilers support an extension where structs can be empty and have zero
 * size. If used on such a struct, ghost_alloc() will still try to allocate a
 * unique minimum-size allocation. It will only return null if an error occurs.
 */
#endif

#ifndef ghost_has_ghost_alloc_zero
    #ifdef ghost_alloc_zero
        #define ghost_has_ghost_alloc_zero 1
    #endif
#endif

#ifndef ghost_has_ghost_alloc_zero
    #include "ghost/malloc/ghost_calloc.h"
    #if ghost_has(ghost_calloc)
        #include "ghost/language/ghost_bless.h"
        #define ghost_alloc_zero(T) ghost_bless(T, 1, ghost_calloc(1, sizeof(T)))
        #define ghost_has_ghost_alloc_zero 1
    #else
        #define ghost_has_ghost_alloc_zero 0
    #endif
#endif

#endif
