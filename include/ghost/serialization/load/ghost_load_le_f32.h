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

#ifndef GHOST_LOAD_LE_F32_H_INCLUDED
#define GHOST_LOAD_LE_F32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Loads a little-endian 32-bit float from a possibly unaligned address.
 */
float ghost_load_le_f32(const void* p);
#endif

#ifndef ghost_has_ghost_load_le_f32
    #ifdef ghost_load_le_f32
        #define ghost_has_ghost_load_le_f32 1
    #endif
#endif

/* Require ghost_float32_t */
#ifndef ghost_has_ghost_load_le_f32
    #include "ghost/type/float32_t/ghost_float32_t.h"
    #if !ghost_has(ghost_float32_t)
        #define ghost_has_ghost_load_le_f32 0
    #endif
#endif

/* Require ghost_load_le_u32() */
#ifndef ghost_has_ghost_load_le_f32
    #include "ghost/serialization/load/ghost_load_le_u32.h"
    #if !ghost_has(ghost_load_le_u32)
        #define ghost_has_ghost_load_le_f32 0
    #endif
#endif

#ifndef ghost_has_ghost_load_le_f32
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    #include "ghost/language/ghost_bit_cast.h"
    #if !ghost_has_ghost_bit_cast
        #include "ghost/string/ghost_memcpy.h"
    #endif

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    ghost_float32_t ghost_load_le_f32(const void* vp) {
        ghost_uint32_t u = ghost_load_le_u32(vp);
        #if ghost_has(ghost_bit_cast)
            return ghost_bit_cast(ghost_float32_t, ghost_uint32_t, u);
        #else
            ghost_float32_t f;
            ghost_memcpy(&f, &u, sizeof(f));
            return f;
        #endif
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_load_le_f32 1
#endif

#endif
