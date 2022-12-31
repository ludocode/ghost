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

#ifndef GHOST_CALLOC_0ANY_H_INCLUDED
#define GHOST_CALLOC_0ANY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Allocates zeroed memory for the given non-zero count and element size.
 *
 * The behaviour when either or both parameters is zero is
 * implementation-defined (i.e. it may have "any" behaviour.)
 *
 * This is mostly useful as an override. If you have a custom calloc() function
 * and you don't know or care about its behaviour when the total size is zero,
 * just pre-define ghost_calloc_0any to it. The other Ghost calloc functions
 * will wrap it with checks. You can then use ghost_calloc() or
 * ghost_calloc_0null() and get consistent behaviour.
 *
 * @see ghost_malloc_0any()
 */
void* ghost_calloc_0any(size_t count, size_t element_size);
#endif

/* Include non-synthetic ghost_impl_ex_calloc_0any(), which also handles
 * ghost_calloc_0any() override. */
#include "ghost/impl/malloc/ghost_impl_ex_calloc_0any.h"

/* If we have a non-synthetic function, use it. */
#ifndef ghost_has_ghost_calloc_0any
    #if ghost_has(ghost_impl_ex_calloc_0any)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_calloc_0any(n, z) ghost_auto_cast(ghost_impl_ex_calloc_0any(n, z))
        #define ghost_has_ghost_calloc_0any 1
    #endif
#endif

/* Wrap any other external calloc() function regardless of its behaviour on
 * size 0. */
#ifndef ghost_has_ghost_calloc_0any
    #include "ghost/impl/malloc/ghost_impl_ex_calloc.h"
    #if ghost_has(ghost_impl_ex_calloc)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_calloc_0any(p, n) ghost_auto_cast(ghost_impl_ex_calloc(p, n))
        #define ghost_has_ghost_calloc_0any 1
    #endif
#endif
#ifndef ghost_has_ghost_calloc_0any
    #include "ghost/impl/malloc/ghost_impl_ex_calloc_0null.h"
    #if ghost_has(ghost_impl_ex_calloc_0null)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_calloc_0any(p, n) ghost_auto_cast(ghost_impl_ex_calloc_0null(p, n))
        #define ghost_has_ghost_calloc_0any 1
    #endif
#endif

/* Synthesize from ghost_malloc_0any(), performing an overflow check and
 * zeroing the memory ourselves. */
#ifndef ghost_has_ghost_calloc_0any
    #include "ghost/malloc/ghost_malloc_0any.h"
    #if ghost_has(ghost_malloc_0any)
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/math/checked_mul/ghost_checked_mul_z.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/string/ghost_bzero.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/error/ghost_errno_store.h"
        #include "ghost/language/ghost_expect_false.h"
        #include "ghost/language/ghost_expect_true.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_malloc.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_MALLOC
        GHOST_IMPL_ATTRIB_ALLOC_SIZE((1, 2))
        ghost_impl_inline
        void* ghost_calloc_0any(ghost_size_t ghost_impl_v_count, ghost_size_t ghost_impl_v_stride) {
            void* ghost_impl_v_ret;
            ghost_size_t ghost_impl_v_total;

            if (ghost_expect_false(ghost_checked_mul_z(&ghost_impl_v_total, ghost_impl_v_count, ghost_impl_v_stride))) {
                ghost_errno_store(EINVAL);
                return ghost_null;
            }

            /* Note that we pass through the behaviour on zero. */
            ghost_impl_v_ret = ghost_malloc_0any(ghost_impl_v_total);
            if (ghost_expect_true(ghost_impl_v_ret != ghost_null))
                ghost_bzero(ghost_impl_v_ret, ghost_impl_v_total);
            return ghost_impl_v_ret;
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_calloc_0any(n, z) ghost_auto_cast(ghost_calloc_0any(n, z))
        #define ghost_has_ghost_calloc_0any 1
    #endif
#endif

/* Otherwise we have no ghost_calloc_0any(). */
#ifndef ghost_has_ghost_calloc_0any
    #define ghost_has_ghost_calloc_0any 0
#endif

#endif
