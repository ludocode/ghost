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

#ifndef GHOST_REALLOC_H_INCLUDED
#define GHOST_REALLOC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Resizes the given allocation to the given non-zero size, potentially moving
 * it to a new address, and returns the address; or if ptr is null, returns a
 * new allocation of the given size (or minimum size if size is zero.)
 *
 * The behaviour is undefined if ptr is not null and size is zero.
 *
 * In other words:
 *
 * - If ptr is non-null and size is non-zero, returns a resized allocation;
 * - If ptr is non-null and size is zero, the behaviour is undefined (asserted at least in debug);
 * - If ptr is null and size is non-zero, returns a new allocation;
 * - If ptr is null and size is zero, returns a new minimum-size allocation.
 *
 * This function most closely matches the behaviour of C23 realloc() where
 * malloc(0) returns non-null (which is most modern platforms.)
 *
 * Before C23, realloc() with a non-null pointer and size of 0 was allowed to
 * be implementation-defined, and implementations vary:
 *
 *     http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2396.htm#dr_400
 *
 * As of C23, calling realloc() with a non-null pointer and a size of zero is
 * undefined behaviour. In debug builds Ghost asserts against this, and
 * otherwise leaves it up the the underlying realloc(). We don't implement any
 * specific behaviour for this because we want to minimize overhead and adhere
 * to the (future) C standard.
 *
 * If you want specific behaviour when size is 0 (for both null and non-null
 * pointers), use either ghost_realloc_0alloc(), ghost_realloc_0free() or
 * ghost_realloc_0null().
 *
 * If you want to override Ghost's realloc() functions but you're unsure of
 * your custom realloc()'s behaviour when size is 0, override
 * ghost_realloc_0any() instead.
 *
 * @see ghost_realloc_0alloc
 * @see ghost_realloc_0free
 * @see ghost_realloc_0null
 * @see ghost_realloc_0any
 */
void* ghost_realloc(void* ptr, size_t size);
#endif

/* Include non-synthetic ghost_impl_ex_realloc(), which also handles
 * ghost_realloc() override. */
#include "ghost/impl/malloc/ghost_impl_ex_realloc.h"

/* If we have a non-synthetic ghost_realloc() with this behaviour, use it.
 * (This is unlikely because it would have to call Ghost's assertion handler in
 * debug mode but we check anyway for consistency.) */
#ifndef ghost_has_ghost_realloc
    #if ghost_has(ghost_impl_ex_realloc)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_realloc(x) ghost_auto_cast(ghost_impl_ex_realloc(x))
        #define ghost_has_ghost_realloc 1
    #endif
#endif

/* Synthesize from external 0alloc or 0free which have matching behaviour on
 * (null,0) so we can pass it through with an assert */
#ifndef ghost_has_ghost_realloc
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0alloc.h"
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0free.h"
    #if ghost_has(ghost_impl_ex_realloc_0alloc) || ghost_has(ghost_impl_ex_realloc_0free)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_assert.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_ALLOC_SIZE((2))
        ghost_impl_inline
        void* ghost_realloc(void* ghost_impl_v_p, ghost_size_t ghost_impl_v_size ) {
            ghost_assert(!(ghost_impl_v_p != ghost_null && ghost_impl_v_size == 0),
                    "cannot realloc() non-null pointer with zero size");
            #if ghost_has(ghost_impl_ex_realloc_0alloc)
                return ghost_impl_ex_realloc_0alloc(ghost_impl_v_p, ghost_impl_v_size);
            #elif ghost_has(ghost_impl_ex_realloc_0free)
                return ghost_impl_ex_realloc_0free(ghost_impl_v_p, ghost_impl_v_size);
            #else
                #error
            #endif
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_realloc(p, n) ghost_auto_cast(ghost_realloc(p, n))
        #define ghost_has_ghost_realloc 1
    #endif
#endif

/* Synthesize from ghost_realloc_0any() which will wrap anything else. We abort
 * if possible on (non-null,0). */
#ifndef ghost_has_ghost_realloc
    #include "ghost/malloc/ghost_realloc_0any.h"
    #if ghost_has(ghost_realloc_0any)
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/debug/ghost_ensure.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_ALLOC_SIZE((2))
        ghost_impl_function
        void* ghost_realloc(void* ghost_impl_v_p, ghost_size_t ghost_impl_v_size)
        #if !GHOST_EMIT_DEFS
        ;
        #else
        {
            #if ghost_has(ghost_ensure)
                /* since the fallback behaviour of leaking the allocation makes
                 * no sense, we try to abort even in release. */
                ghost_ensure(!(ghost_impl_v_p != ghost_null && ghost_impl_v_size == 0),
                        "ghost_realloc() cannot be called on a non-null pointer with zero size");
            #endif

            if (ghost_impl_v_size == 0)
                return ghost_realloc_0any(ghost_null, 1);
            return ghost_realloc_0any(ghost_impl_v_p, ghost_impl_v_size);
        }
        #endif

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_realloc(p, n) ghost_auto_cast(ghost_realloc(p, n))
        #define ghost_has_ghost_realloc 1
    #endif
#endif

/* Otherwise we have no realloc(). */
#ifndef ghost_has_ghost_realloc
    #define ghost_has_ghost_realloc 0
#endif

#endif
