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

#ifndef GHOST_HTOLE_U16_H_INCLUDED
#define GHOST_HTOLE_U16_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Converts the given uint16_t from host to little-endian byte order.
 *
 * This is a drop-in replacement for the common extension htole16().
 *
 *     https://man.archlinux.org/man/endian.3.en
 */
uint16_t ghost_htole_u16(uint16_t u);
#endif

#ifndef ghost_has_ghost_htole_u16
    #ifdef ghost_htole_u16
        #define ghost_has_ghost_htole_u16 1
    #endif
#endif

#ifndef ghost_has_ghost_htole_u16
    #include "ghost/serialization/ghost_little_endian.h"
    #if GHOST_LITTLE_ENDIAN
        #define ghost_htole_u16(x) (x)
        #define ghost_has_ghost_htole_u16 1
    #endif
#endif

/* glibc and BSDs have htole16(). For now we ignore it. */

#ifndef ghost_has_ghost_htole_u16
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/serialization/store/ghost_store_le_u16.h"
    #include "ghost/type/uint16_t/ghost_uint16_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_uint16_t ghost_htole_u16(ghost_uint16_t u) {
        ghost_uint16_t ret;
        ghost_store_le_u16(&ret, u);
        return ret;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_htole_u16 1
#endif

#endif
