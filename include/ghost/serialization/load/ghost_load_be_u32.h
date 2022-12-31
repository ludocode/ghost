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

#ifndef GHOST_LOAD_BE_U32_H_INCLUDED
#define GHOST_LOAD_BE_U32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Loads a big-endian uint32_t from a possibly unaligned address.
 */
uint32_t ghost_load_be_u32(const void* p);
#endif

#ifndef ghost_has_ghost_load_be_u32
    #ifdef ghost_load_be_u32
        #define ghost_has_ghost_load_be_u32 1
    #endif
#endif

#ifndef ghost_has_ghost_load_be_u32
    #include "ghost/serialization/ghost_big_endian.h"
    #if GHOST_BIG_ENDIAN
        #include "ghost/serialization/load/ghost_load_he_u32.h"
        #define ghost_load_be_u32 ghost_load_he_u32
        #define ghost_has_ghost_load_be_u32 1
    #endif
#endif

#ifndef ghost_has_ghost_load_be_u32
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    #include "ghost/type/uint8_t/ghost_uint8_t.h"
    #include "ghost/serialization/ghost_little_endian.h"
    #if GHOST_LITTLE_ENDIAN
        #include "ghost/serialization/load/ghost_load_he_u32.h"
        #include "ghost/serialization/bswap/ghost_bswap_u32.h"
    #else
        #include "ghost/type/uint8_t/ghost_uint8_t.h"
        #include "ghost/language/ghost_static_cast.h"
    #endif

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    ghost_uint32_t ghost_load_be_u32(const void* vp) {
        #if GHOST_LITTLE_ENDIAN
            return ghost_bswap_u32(ghost_load_he_u32(vp));
        #else
            const ghost_uint8_t* p = ghost_static_cast(const ghost_uint8_t*, vp);
            return ghost_static_cast(ghost_uint32_t,
                    (ghost_static_cast(ghost_uint32_t, p[0]) << 24) |
                    (ghost_static_cast(ghost_uint32_t, p[1]) << 16) |
                    (ghost_static_cast(ghost_uint32_t, p[2]) << 8) |
                    (ghost_static_cast(ghost_uint32_t, p[3])));
        #endif
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_load_be_u32 1
#endif

#endif
