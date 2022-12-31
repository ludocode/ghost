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

#ifndef GHOST_BSWAP_U64_H_INCLUDED
#define GHOST_BSWAP_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Swaps the order of bytes in the given 64-bit value.
 */
uint64_t ghost_bswap_u64(uint64_t u);
#endif

#ifndef ghost_has_ghost_bswap_u64
    #ifdef ghost_bswap_u64
        #define ghost_has_ghost_bswap_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_bswap_u64
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        /* TODO look at MPack, we should add additional version-based
         * restrictions. The GCC builtins suck especially on ARM, or at least
         * they did on older versions. Older GCC also doesn't support
         * __has_builtin but still supports __builtin_bswap. */
        #if __has_builtin(__builtin_bswap64)
            #define ghost_bswap_u64 __builtin_bswap64
            #define ghost_has_ghost_bswap_u64 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_bswap_u64
    #if defined(_MSC_VER) && defined(_WIN64)
        #include <stdlib.h>
        #define ghost_bswap_u64 _byteswap_uint64
        #define ghost_has_ghost_bswap_u64 1
    #endif
#endif

/* Some libcs have functions to do this, e.g. glibc has bswap_64() in
 * <byteswap.h>. For now we ignore these. */

#ifndef ghost_has_ghost_bswap_u64
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #if ghost_has(ghost_uint64_t)
        #include "ghost/type/uint64_t/ghost_uint64_c.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/uint8_t/ghost_uint8_t.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_uint64_t ghost_bswap_u64(ghost_uint64_t u) {
            #if ghost_has(GHOST_UINT64_C)
                return ghost_static_cast(ghost_uint64_t,
                        ((u & GHOST_UINT64_C(0x00000000000000FF)) << 56) |
                        ((u & GHOST_UINT64_C(0x000000000000FF00)) << 40) |
                        ((u & GHOST_UINT64_C(0x0000000000FF0000)) << 24) |
                        ((u & GHOST_UINT64_C(0x00000000FF000000)) << 8) |
                        ((u & GHOST_UINT64_C(0x000000FF00000000)) >> 8) |
                        ((u & GHOST_UINT64_C(0x0000FF0000000000)) >> 24) |
                        ((u & GHOST_UINT64_C(0x00FF000000000000)) >> 40) |
                        ((u & GHOST_UINT64_C(0xFF00000000000000)) >> 56));
            #else
                return ghost_static_cast(ghost_uint64_t,
                        ((u & (ghost_static_cast(ghost_uint64_t, 0xFF)      )) << 56) |
                        ((u & (ghost_static_cast(ghost_uint64_t, 0xFF) <<  8)) << 40) |
                        ((u & (ghost_static_cast(ghost_uint64_t, 0xFF) << 16)) << 24) |
                        ((u & (ghost_static_cast(ghost_uint64_t, 0xFF) << 24)) <<  8) |
                        ((u & (ghost_static_cast(ghost_uint64_t, 0xFF) << 32)) >>  8) |
                        ((u & (ghost_static_cast(ghost_uint64_t, 0xFF) << 40)) >> 24) |
                        ((u & (ghost_static_cast(ghost_uint64_t, 0xFF) << 48)) >> 40) |
                        ((u & (ghost_static_cast(ghost_uint64_t, 0xFF) << 56)) >> 56));
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_bswap_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_bswap_u64
    #define ghost_has_ghost_bswap_u64 0
#endif

#endif
