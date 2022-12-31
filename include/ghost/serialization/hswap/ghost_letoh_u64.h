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

#ifndef GHOST_LETOH_U64_H_INCLUDED
#define GHOST_LETOH_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Converts the given uint64_t from little-endian to host byte order.
 *
 * This is a drop-in replacement for the common extension letoh64() or
 * le64toh().
 *
 *     https://man.archlinux.org/man/byteorder.3.en
 *     https://man.archlinux.org/man/endian.3.en
 */
uint64_t ghost_letoh_u64(uint64_t u);
#endif

#ifndef ghost_has_ghost_letoh_u64
    #ifdef ghost_letoh_u64
        #define ghost_has_ghost_letoh_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_letoh_u64
    #include "ghost/serialization/ghost_little_endian.h"
    #if GHOST_LITTLE_ENDIAN
        #define ghost_letoh_u64(x) (x)
        #define ghost_has_ghost_letoh_u64 1
    #endif
#endif

/* glibc and BSDs have le64toh()/letoh64(). For now we ignore them. */

#ifndef ghost_has_ghost_letoh_u64
    #include "ghost/serialization/load/ghost_load_le_u64.h"
    #if ghost_has(ghost_load_le_u64)
        #include "ghost/type/uint64_t/ghost_uint64_t.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_uint64_t ghost_letoh_u64(ghost_uint64_t u) {
            return ghost_load_le_u64(&u);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_letoh_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_letoh_u64
    #define ghost_has_ghost_letoh_u64 0
#endif

#endif
