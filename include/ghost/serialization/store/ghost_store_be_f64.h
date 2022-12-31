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

#ifndef GHOST_STORE_BE_F64_H_INCLUDED
#define GHOST_STORE_BE_F64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Stores a big-endian float64_t at a possibly unaligned address.
 */
void ghost_store_be_f64(void* p, float64_t v);
#endif

#ifndef ghost_has_ghost_store_be_f64
    #ifdef ghost_store_be_f64
        #define ghost_has_ghost_store_be_f64 1
    #endif
#endif

/* Require ghost_float64_t */
#ifndef ghost_has_ghost_store_be_f64
    #include "ghost/type/float64_t/ghost_float64_t.h"
    #if !ghost_has(ghost_float64_t)
        #define ghost_has_ghost_store_be_f64 0
    #endif
#endif

/* Require ghost_store_be_u64() */
#ifndef ghost_has_ghost_store_be_f64
    #include "ghost/serialization/store/ghost_store_be_u64.h"
    #if !ghost_has(ghost_store_be_u64)
        #define ghost_has_ghost_store_be_f64 0
    #endif
#endif

#ifndef ghost_has_ghost_store_be_f64
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/type/uint64_t/ghost_uint64_t.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    void ghost_store_be_f64(void* vp, ghost_float64_t value) {
        /* TODO see ghost_store_be_f32 */
        union {
            ghost_float64_t f;
            ghost_uint64_t u;
        } v;
        v.f = value;
        ghost_store_be_u64(vp, v.u);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_store_be_f64 1
#endif

#endif
