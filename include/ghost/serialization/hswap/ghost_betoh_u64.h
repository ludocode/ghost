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

#ifndef GHOST_BETOH_U64_H_INCLUDED
#define GHOST_BETOH_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Converts the given uint64_t from big-endian to host byte order.
 *
 * This is a drop-in replacement for the common extension betoh64() or
 * be64toh().
 *
 *     https://man.archlinux.org/man/byteorder.3.en
 *     https://man.archlinux.org/man/endian.3.en
 */
uint64_t ghost_betoh_u64(uint64_t u);
#endif

#ifndef ghost_has_ghost_betoh_u64
    #ifdef ghost_betoh_u64
        #define ghost_has_ghost_betoh_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_betoh_u64
    #include "ghost/serialization/ghost_big_endian.h"
    #if GHOST_BIG_ENDIAN
        #define ghost_betoh_u64(x) (x)
        #define ghost_has_ghost_betoh_u64 1
    #endif
#endif

/* POSIX has ntohl() and glibc and BSDs have be64toh()/betoh64(). For now we
 * ignore them. */

#ifndef ghost_has_ghost_betoh_u64
    #include "ghost/serialization/load/ghost_load_be_u64.h"
    #if ghost_has(ghost_load_be_u64)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/uint64_t/ghost_uint64_t.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_uint64_t ghost_betoh_u64(ghost_uint64_t u) {
            return ghost_load_be_u64(&u);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_betoh_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_betoh_u64
    #define ghost_has_ghost_betoh_u64 0
#endif

#endif
