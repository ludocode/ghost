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

#ifndef GHOST_IVEC_INIT_H_INCLUDED
#define GHOST_IVEC_INIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Initializes the given vector.
 *
 * The vector will initially be empty.
 */
void ghost_ivec_init(ghost_ivec_t* vector);
#endif

#ifndef ghost_has_ghost_ivec_init
    #ifdef ghost_ivec_init
        #define ghost_has_ghost_ivec_init 1
    #endif
#endif

#ifndef ghost_has_ghost_ivec_init
    #include "ghost/container/common/ivec/ghost_ivec_t.h"
    #if !ghost_has(ghost_ivec_t)
        #define ghost_has_ghost_ivec_init 0
    #endif
#endif

#ifndef ghost_has_ghost_ivec_init
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/container/generic/gvec/ghost_gvec_init.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    void ghost_ivec_init(ghost_ivec_t* ghost_impl_v_ivec) {
        ghost_gvec_init(&ghost_impl_v_ivec->ghost_impl_v_gvec, sizeof(int));
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_ivec_init 1
#endif

#endif
