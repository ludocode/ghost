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

#ifndef GHOST_GVEC_CLEAR_H_INCLUDED
#define GHOST_GVEC_CLEAR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Clears the given vector.
 */
void ghost_gvec_clear(ghost_gvec_t* vector, size_t element_size);
#endif

#ifndef ghost_has_ghost_gvec_clear
    #ifdef ghost_gvec_clear
        #define ghost_has_ghost_gvec_clear 1
    #endif
#endif

#ifndef ghost_has_ghost_gvec_clear
    #include "ghost/container/generic/gvec/ghost_gvec_t.h"
    #if !ghost_has(ghost_gvec_t)
        #define ghost_has_ghost_gvec_clear 0
    #endif
#endif

#ifndef ghost_has_ghost_gvec_clear
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/language/ghost_discard.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    void ghost_gvec_clear(ghost_gvec_t* ghost_impl_v_gvec,
            ghost_size_t ghost_impl_v_element_size)
    {
        ghost_assert(ghost_impl_v_element_size == ghost_impl_v_gvec->ghost_impl_v_element_size,
                "vector element size does not match");
        ghost_discard(ghost_impl_v_element_size);

        /* TODO keep the allocation if it's less than or equal to double the
         * minimum size (call malloc_good_size() also?) */

        ghost_free(ghost_impl_v_gvec->ghost_impl_v_buffer);

        /* TODO this is duplicated from gvec_init, should probably pull it out
         * into shared code so as not to call an init() function without a
         * matching destroy() */

        #if GHOST_DEBUG
            /* As in ghost_gvec_init(), we keep a one-byte allocation around as
             * a leak check. */
            ghost_impl_v_gvec->ghost_impl_v_buffer = ghost_static_cast(char*, ghost_malloc(1));
            ghost_ensure(ghost_impl_v_gvec->ghost_impl_v_buffer != ghost_null,
                    "vector debug allocation failed");
        #else
            ghost_impl_v_gvec->ghost_impl_v_buffer = ghost_null;
        #endif

        ghost_impl_v_gvec->ghost_impl_v_capacity = 0;
        ghost_impl_v_gvec->ghost_impl_v_count = 0;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_gvec_clear 1
#endif

#endif
