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

#ifndef GHOST_REALLOC_0ALLOC_H_INCLUDED
#define GHOST_REALLOC_0ALLOC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Resizes the given allocation to the given size, potentially moving it to a
 * new address, and returns its address; or returns a new allocation if the
 * given pointer is null (of minimum size if size is zero.)
 *
 * In other words:
 *
 * - If ptr is non-null and size is non-zero, returns a resized allocation;
 * - If ptr is non-null and size is zero, returns a resized-to-minimum allocation;
 * - If ptr is null and size is non-zero, returns a new allocation;
 * - If ptr is null and size is zero, returns a new minimum-size allocation.
 *
 * This always tries to return a unique allocation regardless of whether the
 * given pointer is null or whether size is 0. It only returns null on error.
 *
 * This is the behaviour of realloc() on the BSD platforms, probably macOS/iOS,
 * and possibly others. Unlike ghost_realloc_0null() and ghost_realloc_0free(),
 * there is no way for this function to behave as free().
 *
 * The behaviour of realloc() on several platforms is described here:
 *
 *     http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2396.htm#dr_400
 */
void* ghost_realloc_0alloc(void* ptr, size_t size);
#endif

/* Include non-synthetic ghost_impl_ex_realloc_0alloc(), which also handles
 * ghost_realloc_0alloc() override. */
#include "ghost/impl/malloc/ghost_impl_ex_realloc_0alloc.h"

/* If we have a non-synthetic function, use it. */
#ifndef ghost_has_ghost_realloc_0alloc
    #if ghost_has(ghost_impl_ex_realloc_0alloc)
        #include "ghost/language/ghost_auto_cast.h"
        #define ghost_realloc_0alloc(p, n) ghost_auto_cast(ghost_impl_ex_realloc_0alloc(p, n))
        #define ghost_has_ghost_realloc_0alloc 1
    #endif
#endif

/* Synthesize from ghost_realloc_0any() and ghost_free(), handling size 0 ourselves. */
#ifndef ghost_has_ghost_realloc_0alloc
    #include "ghost/malloc/ghost_realloc_0any.h"
    #include "ghost/malloc/ghost_free.h"
    #if ghost_has(ghost_realloc_0any) && ghost_has(ghost_free)
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_auto_cast.h"
        #include "ghost/impl/malloc/ghost_impl_attrib_alloc_size.h"

        GHOST_IMPL_FUNCTION_OPEN

        GHOST_IMPL_ATTRIB_ALLOC_SIZE((2))
        ghost_impl_function
        void* ghost_realloc_0alloc(void* ghost_impl_v_ptr, ghost_size_t ghost_impl_v_size) GHOST_IMPL_DEF({
            if (ghost_impl_v_size == 0) {
                ghost_free(ghost_impl_v_ptr);
                return ghost_realloc_0any(ghost_null, 1);
            }
            return ghost_realloc_0any(ghost_impl_v_ptr, ghost_impl_v_size);
        })

        GHOST_IMPL_FUNCTION_CLOSE

        #define ghost_realloc_0alloc(p, n) ghost_auto_cast(ghost_realloc_0alloc(p, n))
        #define ghost_has_ghost_realloc_0alloc 1
    #endif
#endif

/* Otherwise we have no ghost_realloc_0alloc(). */
#ifndef ghost_has_ghost_realloc_0alloc
    #define ghost_has_ghost_realloc_0alloc 0
#endif

#endif
