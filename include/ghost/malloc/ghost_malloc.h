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

#ifndef GHOST_MALLOC_H_INCLUDED
#define GHOST_MALLOC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
#define ghost_has_ghost_malloc 1

/**
 * Allocates a block of memory of the given size (even if zero), returning its
 * address.
 *
 * This always returns a unique non-null pointer when successful even if size
 * is zero. If size is zero, the returned pointer must not be dereferenced, but
 * must still be passed to ghost_free() (or ghost_free_nonnull()) to avoid
 * leaks.
 *
 * The C standard allows implementations to return null or a non-null pointer
 * that must be freed when size is zero. Most platforms implement the latter
 * behaviour (with the additional restriction that the pointer must be unique.)
 * This behaviour is also generally simpler (i.e. it only ever returns NULL in
 * case of error) so Ghost enforces this as the default behaviour on all
 * platforms. If you want malloc(0) to return null, use ghost_malloc_0null().
 *
 * @see ghost_malloc_0null()
 */
void* ghost_malloc(size_t size);

#endif

/* Include non-synthetic ghost_impl_ex_malloc(), which also handles
 * ghost_malloc() override. */
#include "ghost/impl/malloc/ghost_impl_ex_malloc.h"

/* If we have a non-synthetic function with the correct behaviour, use it. */
#ifndef ghost_has_ghost_malloc
    #if ghost_has(ghost_impl_ex_malloc)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_malloc(x) ghost_auto_cast(ghost_impl_ex_malloc(x))
        #define ghost_has_ghost_malloc 1
    #endif
#endif

/* Synthesize from ghost_malloc_0any(), checking if the size is 0. */
#ifndef ghost_has_ghost_malloc
    #include "ghost/malloc/ghost_malloc_0any.h"
    #if ghost_has(ghost_malloc_0any)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_MALLOC
        GHOST_IMPL_ATTRIB_ALLOC_SIZE((1))
        ghost_impl_inline
        void* ghost_malloc(ghost_size_t ghost_impl_v_size) {
            if (ghost_impl_v_size == 0)
                ghost_impl_v_size = 1;
            return ghost_malloc_0any(ghost_impl_v_size);
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_malloc(x) ghost_auto_cast(ghost_malloc(x))
        #define ghost_has_ghost_malloc 1
    #endif
#endif

/* Otherwise we don't have this. */
#ifndef ghost_has_ghost_malloc
    #define ghost_has_ghost_malloc 0
#endif

#endif
