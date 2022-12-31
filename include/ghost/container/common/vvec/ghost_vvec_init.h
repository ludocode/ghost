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

#ifndef GHOST_VVEC_INIT_H_INCLUDED
#define GHOST_VVEC_INIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Initializes the given vector.
 *
 * The vector will initially be empty.
 */
void ghost_vvec_init(ghost_vvec_t* vector);
#endif

#ifndef ghost_has_ghost_vvec_init
    #ifdef ghost_vvec_init
        #define ghost_has_ghost_vvec_init 1
    #endif
#endif

#ifndef ghost_has_ghost_vvec_init
    #include "ghost/container/common/vvec/ghost_vvec_t.h"
    #if !ghost_has(ghost_vvec_t)
        #define ghost_has_ghost_vvec_init 0
    #endif
#endif

#ifndef ghost_has_ghost_vvec_init
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/container/generic/gvec/ghost_gvec_init.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    void ghost_vvec_init(ghost_vvec_t* ghost_impl_v_vvec) {
        ghost_gvec_init(&ghost_impl_v_vvec->ghost_impl_v_gvec, sizeof(void*));
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_vvec_init 1
#endif

#endif
