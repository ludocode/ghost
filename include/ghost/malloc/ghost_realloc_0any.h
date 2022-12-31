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

#ifndef GHOST_REALLOC_0ANY_H_INCLUDED
#define GHOST_REALLOC_0ANY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Resizes the given allocation to the given non-zero size, potentially moving
 * it to a new address, and returns its address.
 *
 * The behaviour when size is zero is undefined (i.e. it may have "any"
 * behaviour.)
 *
 * In other words:
 *
 * - If ptr is non-null and size is non-zero, returns a resized allocation;
 * - If ptr is non-null and size is zero, the behaviour is undefined;
 * - If ptr is null and size is non-zero, returns a new allocation;
 * - If ptr is null and size is zero, the behaviour is undefined.
 *
 * If called with size 0 the implementation may abort(), return null, allocate
 * memory, leak the given allocation, format the hard drive, etc. You can call
 * this portably to get the most efficient underlying realloc() if you're sure
 * your size will never be 0 but that's not really why this exists. It's so
 * that you can override it.
 *
 * This is intended to be overridden when you don't know or care what the size
 * 0 behaviour of your custom realloc() function is, or when the behaviour
 * doesn't map cleanly to any of the other ghost_realloc() functions. If you
 * set GHOST_MALLOC_SYSTEM to 0 and override only this function and
 * ghost_free(), Ghost will provide well-defined behaviour for all other
 * allocation functions automatically regardless of the behaviour on 0 of your
 * underlying realloc().
 */
void* ghost_realloc_0any(void* ptr, size_t size);
#endif

/* Include non-synthetic ghost_impl_ex_realloc_0any(), which also handles
 * ghost_realloc_0any() override. */
#include "ghost/impl/malloc/ghost_impl_ex_realloc_0any.h"

/* If we have a non-synthetic external function, use it. */
#ifndef ghost_has_ghost_realloc_0any
    #if ghost_has(ghost_impl_ex_realloc_0any)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_realloc_0any(p, n) ghost_auto_cast(ghost_impl_ex_realloc_0any(p, n))
        #define ghost_has_ghost_realloc_0any 1
    #endif
#endif

/* Wrap any other external realloc() function regardless of its behaviour on
 * size 0. */
#ifndef ghost_has_ghost_realloc_0any
    #include "ghost/impl/malloc/ghost_impl_ex_realloc.h"
    #if ghost_has(ghost_impl_ex_realloc)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_realloc_0any(p, n) ghost_auto_cast(ghost_impl_ex_realloc(p, n))
        #define ghost_has_ghost_realloc_0any 1
    #endif
#endif
#ifndef ghost_has_ghost_realloc_0any
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0alloc.h"
    #if ghost_has(ghost_impl_ex_realloc_0alloc)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_realloc_0any(p, n) ghost_auto_cast(ghost_impl_ex_realloc_0alloc(p, n))
        #define ghost_has_ghost_realloc_0any 1
    #endif
#endif
#ifndef ghost_has_ghost_realloc_0any
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0free.h"
    #if ghost_has(ghost_impl_ex_realloc_0free)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_realloc_0any(p, n) ghost_auto_cast(ghost_impl_ex_realloc_0free(p, n))
        #define ghost_has_ghost_realloc_0any 1
    #endif
#endif
#ifndef ghost_has_ghost_realloc_0any
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0null.h"
    #if ghost_has(ghost_impl_ex_realloc_0null)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_realloc_0any(p, n) ghost_auto_cast(ghost_impl_ex_realloc_0null(p, n))
        #define ghost_has_ghost_realloc_0any 1
    #endif
#endif

/* Synthesize from ghost_malloc_0any() and ghost_malloc_size() by copying
 * ourselves. We abort if size is 0. */
#ifndef ghost_has_ghost_realloc_0any
    #include "ghost/malloc/ghost_malloc_0any.h"
    #include "ghost/malloc/ghost_malloc_size.h"
    #include "ghost/malloc/ghost_free.h"
    #if ghost_has(ghost_malloc_0any) && ghost_has(ghost_malloc_size) && ghost_has(ghost_free)
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/math/min/ghost_min_z.h"
        #include "ghost/language/ghost_expect_false.h"
        #include "ghost/debug/ghost_ensure.h"
        #include "ghost/string/ghost_memcpy.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_ALLOC_SIZE((2))
        ghost_impl_function
        void* ghost_realloc_0any(void* ghost_impl_v_old_p, ghost_size_t ghost_impl_v_new_size)
        #if !GHOST_EMIT_DEFS
        ;
        #else
        {
            ghost_size_t ghost_impl_v_old_size;
            void* ghost_impl_v_new_p;

            #if ghost_has(ghost_ensure)
                ghost_ensure(ghost_impl_v_new_size != 0, "ghost_realloc_0any() size cannot be 0");
            #endif

            ghost_impl_v_new_p = ghost_malloc_0any(ghost_impl_v_new_size);
            if (ghost_expect_false(ghost_impl_v_new_p == ghost_null))
                return ghost_null;
            if (ghost_impl_v_old_p == ghost_null)
                return ghost_impl_v_new_p;

            ghost_impl_v_old_size = ghost_malloc_size(ghost_impl_v_old_p);
            ghost_memcpy(
                    ghost_impl_v_new_p,
                    ghost_impl_v_old_p,
                    ghost_min_z(
                        ghost_impl_v_new_size,
                        ghost_impl_v_old_size));
            ghost_free(ghost_impl_v_old_p);

            return ghost_impl_v_new_p;
        }
        #endif

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_realloc_0any(p, n) ghost_auto_cast(ghost_realloc_0any(p, n))
        #define ghost_has_ghost_realloc 1
    #endif
#endif

/* Otherwise we have no ghost_realloc_0any(). */
#ifndef ghost_has_ghost_realloc_0any
    #define ghost_has_ghost_realloc_0any 0
#endif

#endif
