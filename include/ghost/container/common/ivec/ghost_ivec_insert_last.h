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

#ifndef GHOST_IVEC_INSERT_LAST_H_INCLUDED
#define GHOST_IVEC_INSERT_LAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Inserts an int at the start of the vector.
 */
void ghost_ivec_insert_last(ghost_ivec_t* vector, int value);
#endif

#ifndef ghost_has_ghost_ivec_insert_last
    #ifdef ghost_ivec_insert_last
        #define ghost_has_ghost_ivec_insert_last 1
    #endif
#endif

#ifndef ghost_has_ghost_ivec_insert_last
    #include "ghost/container/common/ivec/ghost_ivec_t.h"
    #if !ghost_has(ghost_ivec_t)
        #define ghost_has_ghost_ivec_insert_last 0
    #endif
#endif

#ifndef ghost_has_ghost_ivec_insert_last
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/container/generic/gvec/ghost_gvec_insert.h"
    #include "ghost/container/common/ivec/ghost_ivec_count.h"
    #include "ghost/container/common/ivec/ghost_ivec_is_empty.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    void ghost_ivec_insert_last(ghost_ivec_t* ghost_impl_v_ivec,
            int ghost_impl_v_int)
    {
        *ghost_static_cast(int*, ghost_gvec_insert(
                    &ghost_impl_v_ivec->ghost_impl_v_gvec,
                    sizeof(int),
                    ghost_ivec_count(ghost_impl_v_ivec),
                    1))
            = ghost_impl_v_int;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_ivec_insert_last 1
#endif

#endif
