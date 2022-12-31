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

#ifndef GHOST_GVEC_REMOVE_H_INCLUDED
#define GHOST_GVEC_REMOVE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Removes elements from the vector.
 *
 * You must have already freed or destroyed or otherwise cleaned up the
 * elements.
 *
 * This may re-allocate the vector to shrink it. If memory allocation fails,
 * the program aborts.
 */
void ghost_gvec_remove(ghost_gvec_t* vector, size_t element_size, size_t index, size_t count);
#endif

#ifndef ghost_has_ghost_gvec_remove
    #ifdef ghost_gvec_remove
        #define ghost_has_ghost_gvec_remove 1
    #endif
#endif

#ifndef ghost_has_ghost_gvec_remove
    #include "ghost/container/generic/gvec/ghost_gvec_t.h"
    #if !ghost_has(ghost_gvec_t)
        #define ghost_has_ghost_gvec_remove 0
    #endif
#endif

#ifndef ghost_has_ghost_gvec_remove
    #include "ghost/impl/ghost_impl_noinline.h"
    #include "ghost/debug/ghost_assert.h"
    #include "ghost/debug/ghost_ensure.h"
    #include "ghost/string/ghost_memmove.h"
    #include "ghost/string/ghost_memcpy.h"
    #include "ghost/math/checked_add/ghost_checked_add_z.h"
    #include "ghost/math/checked_mul/ghost_checked_mul_z.h"
    #include "ghost/math/max/ghost_max_z.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/malloc/ghost_malloc_good_size.h"
    #include "ghost/container/generic/gvec/ghost_gvec_clear.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_noinline
    void ghost_gvec_remove(ghost_gvec_t* ghost_impl_v_gvec,
            ghost_size_t ghost_impl_v_element_size,
            ghost_size_t ghost_impl_v_index,
            ghost_size_t ghost_impl_v_remove_count)
    #if !GHOST_EMIT_DEFS
    ;
    #else
    {
        ghost_assert(ghost_impl_v_element_size == ghost_impl_v_gvec->ghost_impl_v_element_size,
                "vector element size does not match");
        ghost_assert(ghost_impl_v_index <= ghost_impl_v_gvec->ghost_impl_v_count,
                "vector index is out of bounds");

        if (ghost_impl_v_remove_count == 0)
            return;

        /* If we're removing all elements, we forward to clear. It has special
         * handling for empty vectors. */
        if (ghost_impl_v_index == 0 &&
                ghost_impl_v_remove_count == ghost_impl_v_gvec->ghost_impl_v_count) {
            ghost_gvec_clear(ghost_impl_v_gvec, ghost_impl_v_element_size);
            return;
        }

        /* TODO shrink */

        ghost_memmove(
                ghost_impl_v_gvec->ghost_impl_v_buffer + ghost_impl_v_element_size *
                    ghost_impl_v_index,
                ghost_impl_v_gvec->ghost_impl_v_buffer + ghost_impl_v_element_size *
                    (ghost_impl_v_index + ghost_impl_v_remove_count),
                ghost_impl_v_element_size *
                    (ghost_impl_v_gvec->ghost_impl_v_count
                        - ghost_impl_v_index
                        - ghost_impl_v_remove_count));

        ghost_impl_v_gvec->ghost_impl_v_count -= ghost_impl_v_remove_count;
    }
    #endif
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_gvec_remove 1
#endif

#endif
