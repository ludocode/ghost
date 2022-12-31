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

#ifndef GHOST_BSWAP_U16_H_INCLUDED
#define GHOST_BSWAP_U16_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Swaps the bytes in the given 16-bit value.
 */
uint16_t ghost_bswap_u16(uint16_t u);
#endif

#ifndef ghost_has_ghost_bswap_u16
    #ifdef ghost_bswap_u16
        #define ghost_has_ghost_bswap_u16 1
    #endif
#endif

#ifndef ghost_has_ghost_bswap_u16
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        /* TODO look at MPack, we should add additional version-based
         * restrictions. The GCC builtins suck especially on ARM. */
        #if __has_builtin(__builtin_bswap16)
            #define ghost_bswap_u16 __builtin_bswap16
            #define ghost_has_ghost_bswap_u16 1
        #endif
    #endif
#endif

/* TODO C++23 will have std::byteswap(). Can check __cpp_lib_byteswap. */

#ifndef ghost_has_ghost_bswap_u16
    #if defined(_MSC_VER) && defined(_WIN16)
        #include <stdlib.h>
        #define ghost_bswap_u16 _byteswap_ulong
        #define ghost_has_ghost_bswap_u16 1
    #endif
#endif

/* Some libcs have functions to do this, e.g. glibc has bswap_16() in
 * <byteswap.h>. For now we ignore these. */

#ifndef ghost_has_ghost_bswap_u16
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/type/uint16_t/ghost_uint16_t.h"
    #include "ghost/type/uint8_t/ghost_uint8_t.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_uint16_t ghost_bswap_u16(ghost_uint16_t u) {
        return ghost_static_cast(ghost_uint16_t,
                ((u & 0x00FF) << 8) |
                ((u & 0xFF00) >> 8));
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_bswap_u16 1
#endif

#endif
