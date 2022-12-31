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

#ifndef GHOST_ALLOC_ARRAY_H_INCLUDED
#define GHOST_ALLOC_ARRAY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_alloc_array(T, n) (T*) ghost_malloc(n * sizeof(T))
 *
 * Allocates an array of the given type.
 *
 * The contents of the array are uninitialized. If you want the array to be
 * zeroed, use ghost_alloc_array_zero() instead.
 *
 * This returns a minimum-size allocation if the count is zero (or if sizeof(T)
 * is zero for those language standards or extensions where zero-size types are
 * allowed.)
 *
 * @see ghost_alloc_array_zero
 */
#endif

#ifndef ghost_has_ghost_alloc_array
    #ifdef ghost_alloc_array
        #define ghost_has_ghost_alloc_array 1
    #endif
#endif

#ifndef ghost_has_ghost_alloc_array
    #include "ghost/malloc/ghost_malloc.h"
    #if ghost_has(ghost_malloc)

        /* We need a helper function to do the overflow check. */
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/math/checked_mul/ghost_checked_mul_z.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/language/ghost_expect_false.h"
        #include "ghost/error/ghost_errno_store.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"
        GHOST_IMPL_FUNCTION_OPEN
        GHOST_IMPL_ATTRIB_MALLOC
        GHOST_IMPL_ATTRIB_ALLOC_SIZE((1, 2))
        ghost_impl_inline
        void* ghost_impl_alloc_array(ghost_size_t ghost_impl_v_count, ghost_size_t ghost_impl_v_stride) {
            ghost_size_t ghost_impl_v_total;
            if (ghost_expect_false(ghost_checked_mul_z(&ghost_impl_v_total, ghost_impl_v_count, ghost_impl_v_stride))) {
                ghost_errno_store(EINVAL);
                return ghost_null;
            }
            return ghost_malloc(ghost_impl_v_total);
        }
        GHOST_IMPL_FUNCTION_CLOSE

        #include "ghost/language/ghost_bless.h"
        #define ghost_alloc_array(T, n) ghost_bless(T, n, ghost_impl_alloc_array((n), sizeof(T)))
        #define ghost_has_ghost_alloc_array 1
    #else
        #define ghost_has_ghost_alloc_array 0
    #endif
#endif

#endif
