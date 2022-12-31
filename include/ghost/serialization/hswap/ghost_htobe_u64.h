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

#ifndef GHOST_HTOBE_U64_H_INCLUDED
#define GHOST_HTOBE_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Converts the given uint64_t from host to big-endian byte order.
 *
 * This is a drop-in replacement for the common extension htobe64().
 *
 *     https://man.archlinux.org/man/endian.3.en
 */
uint64_t ghost_htobe_u64(uint64_t u);
#endif

#ifndef ghost_has_ghost_htobe_u64
    #ifdef ghost_htobe_u64
        #define ghost_has_ghost_htobe_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_htobe_u64
    #include "ghost/serialization/ghost_big_endian.h"
    #if GHOST_BIG_ENDIAN
        #define ghost_htobe_u64(x) (x)
        #define ghost_has_ghost_htobe_u64 1
    #endif
#endif

/* glibc and BSDs have htobe64(). For now we ignore it. */

#ifndef ghost_has_ghost_htobe_u64
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #if ghost_has(ghost_uint64_t)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/serialization/store/ghost_store_be_u64.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_uint64_t ghost_htobe_u64(ghost_uint64_t u) {
            ghost_uint64_t ret;
            ghost_store_be_u64(&ret, u);
            return ret;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_htobe_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_htobe_u64
    #define ghost_has_ghost_htobe_u64 0
#endif

#endif
