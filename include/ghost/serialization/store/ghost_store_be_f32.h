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

#ifndef GHOST_STORE_BE_F32_H_INCLUDED
#define GHOST_STORE_BE_F32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Stores a big-endian float32_t at a possibly unaligned address.
 */
void ghost_store_be_f32(void* p, float32_t v);
#endif

#ifndef ghost_has_ghost_store_be_f32
    #ifdef ghost_store_be_f32
        #define ghost_has_ghost_store_be_f32 1
    #endif
#endif

/* Require ghost_float32_t */
#ifndef ghost_has_ghost_store_be_f32
    #include "ghost/type/float32_t/ghost_float32_t.h"
    #if !ghost_has(ghost_float32_t)
        #define ghost_has_ghost_store_be_f32 0
    #endif
#endif

/* Require ghost_store_be_u32() */
#ifndef ghost_has_ghost_store_be_f32
    #include "ghost/serialization/store/ghost_store_be_u32.h"
    #if !ghost_has(ghost_store_be_u32)
        #define ghost_has_ghost_store_be_f32 0
    #endif
#endif

#ifndef ghost_has_ghost_store_be_f32
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/type/uint32_t/ghost_uint32_t.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    void ghost_store_be_f32(void* vp, ghost_float32_t value) {
        /* TODO GHOST_CHECK_FLOAT_ORDER();
         * TODO we probably should not type-pun through a union if we can avoid it
         * TODO replace this with ghost_bit_cast
         * TODO see ghost_load_be_f32 */
        union {
            ghost_float32_t f;
            ghost_uint32_t u;
        } v;
        v.f = value;
        ghost_store_be_u32(vp, v.u);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_store_be_f32 1
#endif

#endif
