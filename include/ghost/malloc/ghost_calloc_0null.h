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

#ifndef GHOST_CALLOC_0NULL_H_INCLUDED
#define GHOST_CALLOC_0NULL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Allocates zeroed memory, or returns null if either or both parameters are
 * zero.
 *
 * This can be more efficient than zeroing with memset() because in-process
 * zeroing won't be necessary if the operating system can provide zeroed
 * memory.
 *
 * @see ghost_malloc_0null()
 */
void* ghost_calloc_0null(size_t count, size_t element_size);
#endif

/* Include non-synthetic ghost_impl_ex_calloc_0null(), which also handles
 * ghost_calloc_0null() override. */
#include "ghost/impl/malloc/ghost_impl_ex_calloc_0null.h"

/* If we have a non-synthetic function with the correct behaviour, use it. */
#ifndef ghost_has_ghost_calloc_0null
    #if ghost_has(ghost_impl_ex_calloc_0null)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_calloc_0null(n, z) ghost_auto_cast(ghost_impl_ex_calloc_0null(n, z))
        #define ghost_has_ghost_calloc_0null 1
    #endif
#endif

/* Synthesize from ghost_calloc_0any(), checking if the size is 0. */
#ifndef ghost_has_ghost_calloc_0null
    #include "ghost/malloc/ghost_calloc_0any.h"
    #if ghost_has(ghost_calloc_0any)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_MALLOC
        GHOST_IMPL_ATTRIB_ALLOC_SIZE((1, 2))
        ghost_impl_inline
        void* ghost_calloc_0null(ghost_size_t ghost_impl_v_count, ghost_size_t ghost_impl_v_stride) {
            if (ghost_impl_v_count == 0 || ghost_impl_v_stride == 0)
                return ghost_null;
            return ghost_calloc_0any(ghost_impl_v_count, ghost_impl_v_stride);
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_calloc_0null(n, z) ghost_auto_cast(ghost_calloc_0null(n, z))
        #define ghost_has_ghost_calloc_0null 1
    #endif
#endif

/* Otherwise we have no ghost_calloc_0null(). */
#ifndef ghost_has_ghost_calloc_0null
    #define ghost_has_ghost_calloc_0null 0
#endif

#endif
