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

#ifndef GHOST_IVEC_POP_AT_H_INCLUDED
#define GHOST_IVEC_POP_AT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Removes the int at the given index and returns it.
 */
[[nodiscard]] int ghost_ivec_pop_at(ghost_ivec_t* vector, size_t index);
#endif

#ifndef ghost_has_ghost_ivec_pop_at
    #ifdef ghost_ivec_pop_at
        #define ghost_has_ghost_ivec_pop_at 1
    #endif
#endif

#ifndef ghost_has_ghost_ivec_pop_at
    #include "ghost/container/common/ivec/ghost_ivec_t.h"
    #if !ghost_has(ghost_ivec_t)
        #define ghost_has_ghost_ivec_pop_at 0
    #endif
#endif

#ifndef ghost_has_ghost_ivec_pop_at
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/container/common/ivec/ghost_ivec_at.h"
    #include "ghost/container/common/ivec/ghost_ivec_remove_at.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/language/ghost_nodiscard.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_nodiscard
    ghost_impl_inline
    int ghost_ivec_pop_at(ghost_ivec_t* ghost_impl_v_ivec, ghost_size_t ghost_impl_v_index) {
        int ghost_impl_v_ret = ghost_ivec_at(ghost_impl_v_ivec, ghost_impl_v_index);
        ghost_ivec_remove_at(ghost_impl_v_ivec, ghost_impl_v_index);
        return ghost_impl_v_ret;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_ivec_pop_at 1
#endif

#endif
