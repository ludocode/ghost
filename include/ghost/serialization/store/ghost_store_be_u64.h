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

#ifndef GHOST_STORE_BE_U64_H_INCLUDED
#define GHOST_STORE_BE_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Stores a big-endian uint64_t at a possibly unaligned address.
 */
void ghost_store_be_u64(void* p, uint64_t v);
#endif

#ifndef ghost_has_ghost_store_be_u64
    #ifdef ghost_store_be_u64
        #define ghost_has_ghost_store_be_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_store_be_u64
    #include "ghost/serialization/ghost_big_endian.h"
    #if GHOST_BIG_ENDIAN
        #include "ghost/serialization/store/ghost_store_he_u64.h"
        #define ghost_store_be_u64 ghost_store_he_u64
        #define ghost_has_ghost_store_be_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_store_be_u64
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #if ghost_has(ghost_uint64_t)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/uint8_t/ghost_uint8_t.h"
        #include "ghost/serialization/ghost_little_endian.h"
        #if GHOST_LITTLE_ENDIAN
            #include "ghost/serialization/store/ghost_store_he_u64.h"
            #include "ghost/serialization/bswap/ghost_bswap_u64.h"
        #else
            #include "ghost/type/uint8_t/ghost_uint8_t.h"
            #include "ghost/language/ghost_static_cast.h"
        #endif

        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_store_be_u64(void* vp, ghost_uint64_t v) {
            #if GHOST_LITTLE_ENDIAN
                ghost_store_he_u64(vp, ghost_bswap_u64(v));
            #else
                ghost_uint8_t* p = ghost_static_cast(ghost_uint8_t*, vp);
                p[0] = ghost_static_cast(uint8_t, (v >> 56) & 0xFF);
                p[1] = ghost_static_cast(uint8_t, (v >> 48) & 0xFF);
                p[2] = ghost_static_cast(uint8_t, (v >> 40) & 0xFF);
                p[3] = ghost_static_cast(uint8_t, (v >> 32) & 0xFF);
                p[4] = ghost_static_cast(uint8_t, (v >> 24) & 0xFF);
                p[5] = ghost_static_cast(uint8_t, (v >> 16) & 0xFF);
                p[6] = ghost_static_cast(uint8_t, (v >>  8) & 0xFF);
                p[7] = ghost_static_cast(uint8_t,  v        & 0xFF);
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_store_be_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_store_be_u64
    #define ghost_has_ghost_store_be_u64 0
#endif

#endif
