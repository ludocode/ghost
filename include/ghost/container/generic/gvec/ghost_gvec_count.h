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

#ifndef GHOST_GVEC_COUNT_H_INCLUDED
#define GHOST_GVEC_COUNT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the number of elements in the given vector.
 */
size_t ghost_gvec_count(ghost_gvec_t* vector, size_t element_size);
#endif

#ifndef ghost_has_ghost_gvec_count
    #ifdef ghost_gvec_count
        #define ghost_has_ghost_gvec_count 1
    #endif
#endif

#ifndef ghost_has_ghost_gvec_count
    #include "ghost/container/generic/gvec/ghost_gvec_t.h"
    #if !ghost_has(ghost_gvec_t)
        #define ghost_has_ghost_gvec_count 0
    #endif
#endif

#ifndef ghost_has_ghost_gvec_count
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/debug/ghost_assert.h"
    #include "ghost/language/ghost_discard.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_size_t ghost_gvec_count(ghost_gvec_t* ghost_impl_v_gvec, ghost_size_t ghost_impl_v_element_size) {
        ghost_assert(ghost_impl_v_element_size == ghost_impl_v_gvec->ghost_impl_v_element_size,
                "vector element size does not match");
        ghost_discard(ghost_impl_v_element_size);
        return ghost_impl_v_gvec->ghost_impl_v_count;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_gvec_count 1
#endif

#endif
