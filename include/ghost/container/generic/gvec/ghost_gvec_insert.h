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

#ifndef GHOST_GVEC_INSERT_H_INCLUDED
#define GHOST_GVEC_INSERT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Inserts space for new elements into the vector returning a pointer to the
 * first one.
 *
 * The returned space is uninitialized.
 *
 * If memory allocation fails, the program aborts.
 */
/*TODO rename to insert_bulk_at and also remove_bulk_at, pottery naming conventions */
void* ghost_gvec_insert(ghost_gvec_t* vector, size_t element_size, size_t index, size_t count);
#endif

#ifndef ghost_has_ghost_gvec_insert
    #ifdef ghost_gvec_insert
        #define ghost_has_ghost_gvec_insert 1
    #endif
#endif

#ifndef ghost_has_ghost_gvec_insert
    #include "ghost/container/generic/gvec/ghost_gvec_t.h"
    #if !ghost_has(ghost_gvec_t)
        #define ghost_has_ghost_gvec_insert 0
    #endif
#endif

#ifndef ghost_has_ghost_gvec_insert
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

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_noinline
    void* ghost_gvec_insert(ghost_gvec_t* ghost_impl_v_gvec,
            ghost_size_t ghost_impl_v_element_size,
            ghost_size_t ghost_impl_v_index,
            ghost_size_t ghost_impl_v_insert_count)
    #if !GHOST_EMIT_DEFS
    ;
    #else
    {
        ghost_size_t ghost_impl_v_new_count;

        ghost_assert(ghost_impl_v_element_size == ghost_impl_v_gvec->ghost_impl_v_element_size,
                "vector element size does not match");
        ghost_assert(ghost_impl_v_index <= ghost_impl_v_gvec->ghost_impl_v_count,
                "vector index is out of bounds");
        ghost_assert(ghost_impl_v_insert_count >= 1,
                "cannot insert zero elements");

        ghost_ensure(!ghost_checked_add_z(
                    &ghost_impl_v_new_count,
                    ghost_impl_v_insert_count,
                    ghost_impl_v_gvec->ghost_impl_v_count),
                "vector count overflow");

        /* See if there is already enough capacity */
        if (ghost_impl_v_new_count <= ghost_impl_v_gvec->ghost_impl_v_capacity) {
            ghost_memmove(
                    ghost_impl_v_gvec->ghost_impl_v_buffer + ghost_impl_v_element_size *
                        (ghost_impl_v_index + ghost_impl_v_insert_count),
                    ghost_impl_v_gvec->ghost_impl_v_buffer + ghost_impl_v_element_size *
                        ghost_impl_v_index,
                    ghost_impl_v_element_size *
                        (ghost_impl_v_gvec->ghost_impl_v_count - ghost_impl_v_index));
            ghost_impl_v_gvec->ghost_impl_v_count = ghost_impl_v_new_count;

        } else {
            /* Otherwise we grow */
            char* ghost_impl_v_new_buffer;
            ghost_size_t ghost_impl_v_new_capacity;
            ghost_size_t ghost_impl_v_new_size;
            ghost_size_t ghost_impl_v_minimum_capacity = 4;

            /* Grow by a factor of 1.5. */
            ghost_ensure(!ghost_checked_mul_z(
                        &ghost_impl_v_new_capacity,
                        ghost_impl_v_gvec->ghost_impl_v_capacity / 2 + 1,
                        3),
                    "vector capacity overflow");
            ghost_impl_v_new_capacity = ghost_max_z(ghost_max_z(
                        ghost_impl_v_new_capacity,
                        ghost_impl_v_minimum_capacity),
                    ghost_impl_v_new_count);
            ghost_ensure(!ghost_checked_mul_z(
                        &ghost_impl_v_new_size,
                        ghost_impl_v_new_capacity,
                        ghost_impl_v_element_size),
                    "vector size overflow");

            /* If the platform can tell us a better capacity for our vector,
             * use it to avoid wasting allocator padding. */
            #if ghost_has(ghost_malloc_good_size)
            ghost_impl_v_new_capacity = ghost_malloc_good_size(ghost_impl_v_new_size)
                    / ghost_impl_v_element_size;
            #endif

            /*
             * Note that we don't realloc().
             *
             * realloc() will often need to move the allocation which will copy
             * elements. We also need to move elements within the allocation to
             * make space for the insertion so this will result in moving all
             * elements after the insertion point twice. This is inefficient.
             *
             * It's possible this is insignificant compared to the cost of
             * realloc(), and the occasional resize in place would make up for
             * it. This would need to be tested.
             *
             * We could also in theory attempt something like jemalloc's
             * xallocx() to try to resize in place and if that fails, fall back
             * to malloc().
             */
            ghost_impl_v_new_buffer = ghost_static_cast(char*,
                    ghost_malloc(ghost_impl_v_new_size));
            ghost_ensure(ghost_impl_v_new_buffer != ghost_null,
                    "vector allocation failed");

            ghost_memcpy(
                    ghost_impl_v_new_buffer,
                    ghost_impl_v_gvec->ghost_impl_v_buffer,
                    ghost_impl_v_element_size * ghost_impl_v_index);
            ghost_memcpy(
                    ghost_impl_v_new_buffer + ghost_impl_v_element_size *
                        (ghost_impl_v_index + ghost_impl_v_insert_count),
                    ghost_impl_v_gvec->ghost_impl_v_buffer + ghost_impl_v_element_size *
                        ghost_impl_v_index,
                    ghost_impl_v_element_size *
                        (ghost_impl_v_gvec->ghost_impl_v_count - ghost_impl_v_index));

            ghost_free(ghost_impl_v_gvec->ghost_impl_v_buffer);
            ghost_impl_v_gvec->ghost_impl_v_buffer = ghost_impl_v_new_buffer;
            ghost_impl_v_gvec->ghost_impl_v_capacity = ghost_impl_v_new_capacity;
            ghost_impl_v_gvec->ghost_impl_v_count = ghost_impl_v_new_count;
        }

        return ghost_impl_v_gvec->ghost_impl_v_buffer +
                ghost_impl_v_element_size * ghost_impl_v_index;
    }
    #endif
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_gvec_insert 1
#endif

#endif
