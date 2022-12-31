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

#ifndef GHOST_ALLOC_ARRAY_ZERO_H_INCLUDED
#define GHOST_ALLOC_ARRAY_ZERO_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_alloc_array_zero(T, n) (T*) ghost_calloc(n, sizeof(T))
 *
 * Allocates an array of values of the given type and zeroes it.
 *
 * This can be more efficient than zeroing with memset() because in-process
 * zeroing won't be necessary if the operating system can provide zeroed
 * memory.
 *
 * This returns a minimum-size allocation if the count is zero (or if sizeof(T)
 * is zero for those language standards or extensions where zero-size types are
 * allowed.)
 */
#endif

#ifndef ghost_has_ghost_alloc_array_zero
    #ifdef ghost_alloc_array_zero
        #define ghost_has_ghost_alloc_array_zero 1
    #endif
#endif

#ifndef ghost_alloc_array_zero
    #include "ghost/malloc/ghost_calloc.h"
    #if ghost_has(ghost_calloc)
        #include "ghost/language/ghost_bless.h"
        #define ghost_alloc_array_zero(T, n) ghost_bless(T, n, ghost_calloc((n), sizeof(T)))
        #define ghost_has_ghost_alloc_array_zero 1
    #else
        #define ghost_has_ghost_alloc_array_zero 0
    #endif
#endif

#endif
