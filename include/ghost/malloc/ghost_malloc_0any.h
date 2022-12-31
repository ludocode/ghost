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

#ifndef GHOST_MALLOC_0ANY_H_INCLUDED
#define GHOST_MALLOC_0ANY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Allocates a block of memory of the given non-zero size and returns its
 * address.
 *
 * The behaviour when size is zero is implementation-defined (i.e. it may have
 * "any" behaviour.)
 *
 * This is mostly useful as an override. If you have a custom malloc() function
 * and you don't know or care about its behaviour when size is zero, just
 * pre-define ghost_malloc_0any to it. The other Ghost malloc functions will
 * wrap it with checks. You can then use ghost_malloc() or ghost_malloc_0null()
 * and get consistent behaviour.
 */
void* ghost_malloc_0any(size_t size);
#endif

/* Include non-synthetic ghost_impl_ex_malloc_0any(), which also handles
 * ghost_malloc_0any() override. */
#include "ghost/impl/malloc/ghost_impl_ex_malloc_0any.h"

/* If we have a non-synthetic function, use it. */
#ifndef ghost_has_ghost_malloc_0any
    #if ghost_has(ghost_impl_ex_malloc_0any)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_malloc_0any(x) ghost_auto_cast(ghost_impl_ex_malloc_0any(x))
        #define ghost_has_ghost_malloc_0any 1
    #endif
#endif

/* Wrap any other external malloc() function regardless of its behaviour on
 * zero. */
#ifndef ghost_has_ghost_malloc_0any
    #include "ghost/impl/malloc/ghost_impl_ex_malloc.h"
    #if ghost_has(ghost_impl_ex_malloc)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_malloc_0any(x) ghost_auto_cast(ghost_impl_ex_malloc(x))
        #define ghost_has_ghost_malloc_0any 1
    #endif
#endif
#ifndef ghost_has_ghost_malloc_0any
    #include "ghost/impl/malloc/ghost_impl_ex_malloc_0null.h"
    #if ghost_has(ghost_impl_ex_malloc_0null)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_malloc_0any(x) ghost_auto_cast(ghost_impl_ex_malloc_0null(x))
        #define ghost_has_ghost_malloc_0any 1
    #endif
#endif

/* Synthesize from any other external allocator function, passing through zero
 * regardless of its behaviour. We prefer functions that don't zero the
 * allocation to avoid unnecessary zeroing. */
#ifndef ghost_has_ghost_malloc_0any
    /* non-zeroing */
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0any.h"
    #include "ghost/impl/malloc/ghost_impl_ex_realloc.h"
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0alloc.h"
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0free.h"
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0null.h"
    /* zeroing */
    #include "ghost/impl/malloc/ghost_impl_ex_calloc_0any.h"
    #include "ghost/impl/malloc/ghost_impl_ex_calloc.h"
    #include "ghost/impl/malloc/ghost_impl_ex_calloc_0null.h"

    #if \
            ghost_has(ghost_impl_ex_realloc_0any) || \
            ghost_has(ghost_impl_ex_realloc) || \
            ghost_has(ghost_impl_ex_realloc_0alloc) || \
            ghost_has(ghost_impl_ex_realloc_0free) || \
            ghost_has(ghost_impl_ex_realloc_0null) || \
            \
            ghost_has(ghost_impl_ex_calloc_0any) || \
            ghost_has(ghost_impl_ex_calloc) || \
            ghost_has(ghost_impl_ex_calloc_0null)

        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_MALLOC
        GHOST_IMPL_ATTRIB_ALLOC_SIZE((1))
        ghost_impl_inline
        void* ghost_malloc_0any(ghost_size_t ghost_impl_v_size) {
            #if ghost_has(ghost_impl_ex_realloc_0any)
                return ghost_impl_ex_realloc_0any(ghost_null, ghost_impl_v_size);
            #elif ghost_has(ghost_impl_ex_realloc)
                return ghost_impl_ex_realloc(ghost_null, ghost_impl_v_size);
            #elif ghost_has(ghost_impl_ex_realloc_0alloc)
                return ghost_impl_ex_realloc_0alloc(ghost_null, ghost_impl_v_size);
            #elif ghost_has(ghost_impl_ex_realloc_0free)
                return ghost_impl_ex_realloc_0free(ghost_null, ghost_impl_v_size);
            #elif ghost_has(ghost_impl_ex_realloc_0null)
                return ghost_impl_ex_realloc_0null(ghost_null, ghost_impl_v_size);
            #elif ghost_has(ghost_impl_ex_calloc_0any)
                return ghost_impl_ex_calloc_0any(1, ghost_impl_v_size);
            #elif ghost_has(ghost_impl_ex_calloc)
                return ghost_impl_ex_calloc(1, ghost_impl_v_size);
            #elif ghost_has(ghost_impl_ex_calloc_0null)
                return ghost_impl_ex_calloc_0null(1, ghost_impl_v_size);
            #else
                #error
            #endif
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_malloc_0any(x) ghost_auto_cast(ghost_malloc_0any(x))
        #define ghost_has_ghost_malloc_0any 1
    #endif
#endif

/* Otherwise we have no ghost_malloc_0any(). */
#ifndef ghost_has_ghost_malloc_0any
    #define ghost_has_ghost_malloc_0any 0
#endif

#endif
