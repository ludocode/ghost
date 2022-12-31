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

#ifndef GHOST_VVEC_NEW_H_INCLUDED
#define GHOST_VVEC_NEW_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Allocates and initializes a vector of void pointers.
 *
 * The vector must be freed with ghost_vvec_delete(), not ghost_vvec_destroy().
 *
 * @see ghost_vvec_delete()
 */
ghost_vvec_t* ghost_vvec_new(void);
#endif

#ifndef ghost_has_ghost_vvec_new
    #ifdef ghost_vvec_new
        #define ghost_has_ghost_vvec_new 1
    #endif
#endif

#ifndef ghost_has_ghost_vvec_new
    #include "ghost/container/common/vvec/ghost_vvec_t.h"
    #if !ghost_has(ghost_vvec_t)
        #define ghost_has_ghost_vvec_new 0
    #endif
#endif

#ifndef ghost_has_ghost_vvec_new
    #include "ghost/malloc/ghost_alloc.h"
    #include "ghost/debug/ghost_ensure.h"
    #include "ghost/container/common/vvec/ghost_vvec_init.h"
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_vvec_t* ghost_vvec_new(void) {
        ghost_vvec_t* ghost_impl_v_vector = ghost_alloc(ghost_vvec_t);
        ghost_ensure(ghost_impl_v_vector != ghost_null,
                "void vector allocation failed");
        ghost_vvec_init(ghost_impl_v_vector);
        return ghost_impl_v_vector;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_vvec_new 1
#endif

#endif
