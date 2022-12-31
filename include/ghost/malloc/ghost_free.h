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

#ifndef GHOST_FREE_H_INCLUDED
#define GHOST_FREE_H_INCLUDED

/* Override is handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/* Use the standard C free() function if possible */
#ifndef ghost_has_ghost_free
    #if GHOST_MALLOC_SYSTEM
        #include "ghost/header/c/ghost_stdlib_h.h"
        #if ghost_has(ghost_stdlib_h)
            #ifdef __cplusplus
                #define ghost_free ::free
            #else
                #define ghost_free free
            #endif
            #define ghost_has_ghost_free 1
        #endif
    #endif
#endif

/* Synthesize from a realloc() function that can free */
#ifndef ghost_has_ghost_free
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0free.h"
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0null.h"
    #if ghost_has(ghost_impl_ex_realloc_0free) || ghost_has(ghost_impl_ex_realloc_0null)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/size_t/ghost_size_t.h"

        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_free(void* ptr) {
            #if ghost_has(ghost_impl_ex_realloc_0free)
                ghost_impl_ex_realloc_0free(ptr, 0);
            #elif ghost_has(ghost_impl_ex_realloc_0null)
                ghost_impl_ex_realloc_0null(ptr, 0);
            #else
                #error
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_free 1
    #endif
#endif

/* Otherwise we have no allocator. */
#ifndef ghost_has_ghost_free
    #define ghost_has_ghost_free 0
#endif

#endif
