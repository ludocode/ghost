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

#ifndef GHOST_STORE_HE_U64_H_INCLUDED
#define GHOST_STORE_HE_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Stores a host-endian uint64_t at a possibly unaligned address.
 */
void ghost_store_he_u64(void* p, uint64_t v);
#endif

#ifndef ghost_has_ghost_store_he_u64
    #ifdef ghost_store_he_u64
        #define ghost_has_ghost_store_he_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_store_he_u64
    /* TODO this should be protected under GHOST_IMPL */
    #ifdef GHOST_STORE_HE_U64_USE_UNALIGNED
        #error
    #endif
    #ifndef GHOST_STORE_HE_U64_USE_UNALIGNED
        #if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
            /* Unaligned 64-bit load/store is allowed and relatively fast on x86. */
            #define GHOST_STORE_HE_U64_USE_UNALIGNED 1
        #endif
    #endif
    #ifndef GHOST_STORE_HE_U64_USE_UNALIGNED
        #define GHOST_STORE_HE_U64_USE_UNALIGNED 0
    #endif

    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #if !GHOST_STORE_HE_U64_USE_UNALIGNED
        #include "ghost/type/uint8_t/ghost_uint8_t.h"
        #include "ghost/language/ghost_reinterpret_cast.h"
        #include "ghost/language/ghost_restrict.h"
    #endif

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    void ghost_store_he_u64(void* p, ghost_uint64_t v) {
        #if GHOST_STORE_HE_U64_USE_UNALIGNED
            *ghost_static_cast(ghost_uint64_t*, p) = v;
        #else
            /* GCC and Clang with optimizations enabled can recognize this as an
             * unaligned store and emit the appropriate instruction on CPUs that
             * support it. */
            ghost_uint8_t* ghost_restrict to = ghost_static_cast(ghost_uint8_t*, p);
            ghost_uint8_t* ghost_restrict from = ghost_reinterpret_cast(ghost_uint8_t*, &v);
            to[0] = from[0];
            to[1] = from[1];
            to[2] = from[2];
            to[3] = from[3];
            to[4] = from[4];
            to[5] = from[5];
            to[6] = from[6];
            to[7] = from[7];
        #endif
    }
    GHOST_IMPL_FUNCTION_CLOSE

    #undef GHOST_STORE_HE_U64_USE_UNALIGNED
    #define ghost_has_ghost_store_he_u64 1
#endif

#endif
