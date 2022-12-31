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

#ifndef GHOST_VVEC_REMOVE_LAST_H_INCLUDED
#define GHOST_VVEC_REMOVE_LAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Removes the first element.
 *
 * The vector must not be empty.
 */
void ghost_vvec_remove_last(ghost_vvec_t* vector);
#endif

#ifndef ghost_has_ghost_vvec_remove_last
    #ifdef ghost_vvec_remove_last
        #define ghost_has_ghost_vvec_remove_last 1
    #endif
#endif

#ifndef ghost_has_ghost_vvec_remove_last
    #include "ghost/container/common/vvec/ghost_vvec_t.h"
    #if !ghost_has(ghost_vvec_t)
        #define ghost_has_ghost_vvec_remove_last 0
    #endif
#endif

#ifndef ghost_has_ghost_vvec_remove_last
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/container/generic/gvec/ghost_gvec_remove.h"
    #include "ghost/container/common/vvec/ghost_vvec_count.h"
    #include "ghost/container/common/vvec/ghost_vvec_is_empty.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    void ghost_vvec_remove_last(ghost_vvec_t* ghost_impl_v_vvec) {
        ghost_assert(!ghost_vvec_is_empty(ghost_impl_v_vvec),
                "cannot remove last from empty vector");
        ghost_gvec_remove(
                &ghost_impl_v_vvec->ghost_impl_v_gvec,
                sizeof(void*),
                ghost_vvec_count(ghost_impl_v_vvec) - 1,
                1);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_vvec_remove_last 1
#endif

#endif
