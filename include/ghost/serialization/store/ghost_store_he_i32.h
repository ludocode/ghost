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

#ifndef GHOST_STORE_HE_I32_H_INCLUDED
#define GHOST_STORE_HE_I32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Stores a host-endian int32_t at a possibly unaligned address.
 */
void ghost_store_he_i32(void* p, int32_t v);
#endif

#ifndef ghost_has_ghost_store_he_i32
    #ifdef ghost_store_he_i32
        #define ghost_has_ghost_store_he_i32 1
    #endif
#endif

#ifndef ghost_has_ghost_store_he_i32
    #include "ghost/serialization/store/ghost_store_he_u32.h"
    #if ghost_has(ghost_store_he_u32)
        #include "ghost/type/int32_t/ghost_int32_t.h"
        #define ghost_store_he_i32(p, v) \
                ghost_store_he_u32(x, ghost_static_cast(ghost_uint32_t, v))
        #define ghost_has_ghost_store_he_i32 1
    #endif
#endif

#ifndef ghost_has_ghost_store_he_i32
    #define ghost_has_ghost_store_he_i32 0
#endif

#endif
