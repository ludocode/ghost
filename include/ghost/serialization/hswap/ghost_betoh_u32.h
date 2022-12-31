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

#ifndef GHOST_BETOH_U32_H_INCLUDED
#define GHOST_BETOH_U32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Converts the given uint32_t from big-endian to host byte order.
 *
 * This is a drop-in replacement for POSIX ntohl() as well as the common
 * extension betoh32() or be32toh().
 *
 *     https://man.archlinux.org/man/byteorder.3.en
 *     https://man.archlinux.org/man/endian.3.en
 */
uint32_t ghost_betoh_u32(uint32_t u);
#endif

#ifndef ghost_has_ghost_betoh_u32
    #ifdef ghost_betoh_u32
        #define ghost_has_ghost_betoh_u32 1
    #endif
#endif

#ifndef ghost_has_ghost_betoh_u32
    #include "ghost/serialization/ghost_big_endian.h"
    #if GHOST_BIG_ENDIAN
        #define ghost_betoh_u32(x) (x)
        #define ghost_has_ghost_betoh_u32 1
    #endif
#endif

/* POSIX has ntohl() and glibc and BSDs have be32toh()/betoh32(). For now we
 * ignore them. */

#ifndef ghost_has_ghost_betoh_u32
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/serialization/load/ghost_load_be_u32.h"
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_uint32_t ghost_betoh_u32(ghost_uint32_t u) {
        return ghost_load_be_u32(&u);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_betoh_u32 1
#endif

#endif
