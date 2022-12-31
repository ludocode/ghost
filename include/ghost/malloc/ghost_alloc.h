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

#ifndef GHOST_ALLOC_H_INCLUDED
#define GHOST_ALLOC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_alloc(T) (T*) ghost_malloc(sizeof(T))
 *
 * Allocates a value of the given type.
 *
 * This is a typed wrapper macro around malloc(). It does the sizeof and cast
 * for you.
 *
 * A macro for allocating a type is very common in different projects and
 * libraries. Ghost calls this macro "alloc". Use it like this:
 *
 *     foo_t* foo = ghost_alloc(foo_t);
 *     // do stuff with foo
 *     ghost_free(foo);
 *
 * The contents of the value are uninitialized. If you want the value to be
 * zeroed, use ghost_alloc_zero() instead.
 *
 * If you want to allocate an array, use ghost_alloc_array().
 *
 * This does not handle types with extended alignment requirements. If you want
 * to allocate such a type, use ghost_aligned_malloc() and
 * ghost_aligned_free().
 *
 * Some compilers support an extension where structs can be empty and have zero
 * size. If used on such a struct, ghost_alloc() will still try to allocate a
 * unique minimum-size allocation. It will only return null if an error occurs.
 *
 * @see ghost_alloc_zero
 * @see ghost_alloc_array
 * @see ghost_alloc_array_zero
 */
#endif

#ifndef ghost_has_ghost_alloc
    #ifdef ghost_alloc
        #define ghost_has_ghost_alloc 1
    #endif
#endif

#ifndef ghost_has_ghost_alloc
    #include "ghost/malloc/ghost_malloc.h"
    #if ghost_has(ghost_malloc)
        #include "ghost/language/ghost_bless.h"
        #define ghost_alloc(T) ghost_bless(T, 1, ghost_malloc(sizeof(T)))
        #define ghost_has_ghost_alloc 1
    #else
        #define ghost_has_ghost_alloc 0
    #endif
#endif

#endif
