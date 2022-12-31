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

#ifndef GHOST_REALLOC_0NULL_H_INCLUDED
#define GHOST_REALLOC_0NULL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Resizes the given allocation to the given non-zero size, potentially moving
 * it to a new address, and returns its address; or frees the given pointer (if
 * non-null) and returns null if size is 0.
 *
 * In other words:
 *
 * - If ptr is non-null and size is non-zero, returns a resized allocation;
 * - If ptr is non-null and size is zero, frees ptr and returns null;
 * - If ptr is null and size is non-zero, returns a new allocation;
 * - If ptr is null and size is zero, returns null.
 *
 * This always returns null if size is 0, freeing the given pointer if any.
 * Whether errno is set when size is 0 is implementation-defined.
 *
 * The behaviour of realloc() on several platforms is described here:
 *
 *     http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2396.htm#dr_400
 *
 * @see ghost_malloc_0null()
 */
void* ghost_realloc_0null(void* ptr, size_t size);
#endif

/* Include non-synthetic ghost_impl_ex_realloc_0null(), which also handles
 * ghost_realloc_0null() override. */
#include "ghost/impl/malloc/ghost_impl_ex_realloc_0null.h"

/* If we have a non-synthetic function, use it. */
#ifndef ghost_has_ghost_realloc_0null
    #if ghost_has(ghost_impl_ex_realloc_0null)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_realloc_0null(p, n) ghost_auto_cast(ghost_impl_ex_realloc_0null(p, n))
        #define ghost_has_ghost_realloc_0null 1
    #endif
#endif

/* Synthesize from external 0free() since it can free the given pointer. */
#ifndef ghost_has_ghost_realloc_0null
    #include "ghost/impl/malloc/ghost_impl_ex_realloc_0free.h"
    #if ghost_has(ghost_impl_ex_realloc_0free)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_ALLOC_SIZE((2))
        ghost_impl_inline
        void* ghost_realloc_0null(void* ptr, ghost_size_t size) {
            if (size == 0 && ptr == ghost_null)
                return ghost_null;
            return ghost_impl_ex_realloc_0free(ptr, size);
        }

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_realloc_0null(p, n) ghost_auto_cast(ghost_realloc_0null(p, n))
        #define ghost_has_ghost_realloc_0null 1
    #endif
#endif

/* Synthesize from ghost_realloc_0any() and ghost_free(), handling size 0 ourselves. */
#ifndef ghost_has_ghost_realloc_0null
    #include "ghost/malloc/ghost_realloc_0any.h"
    #include "ghost/malloc/ghost_free.h"
    #if ghost_has(ghost_free) && ghost_has(ghost_realloc_0any)
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_ALLOC_SIZE((2))
        ghost_impl_function
        void* ghost_realloc_0null(void* ptr, ghost_size_t size) GHOST_IMPL_DEF({
            if (size == 0) {
                ghost_free(ptr);
                return ghost_null;
            }
            return ghost_realloc_0any(ptr, size);
        })

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_realloc_0null(p, n) ghost_auto_cast(ghost_realloc_0null(p, n))
        #define ghost_has_ghost_realloc_0null 1
    #endif
#endif

/* Otherwise we have no ghost_realloc_0null(). */
#ifndef ghost_has_ghost_realloc_0null
    #define ghost_has_ghost_realloc_0null 0
#endif

#endif
