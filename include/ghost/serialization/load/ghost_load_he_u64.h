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

#ifndef GHOST_LOAD_HE_U64_H_INCLUDED
#define GHOST_LOAD_HE_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Loads a host-endian uint64_t from a possibly unaligned address.
 */
uint64_t ghost_load_he_u64(const void* p);
#endif

#ifndef ghost_has_ghost_load_he_u64
    #ifdef ghost_load_he_u64
        #define ghost_has_ghost_load_he_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_load_he_u64
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #if ghost_has(ghost_uint64_t)
        #ifndef GHOST_LOAD_HE_U64_USE_UNALIGNED
            #if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
                /* Unaligned 64-bit load/store is allowed and relatively fast on x86. */
                #define GHOST_LOAD_HE_U64_USE_UNALIGNED 1
            #endif
            /* See ghost_load_he_u32() for notes on under platforms. */
        #endif
        #ifndef GHOST_LOAD_HE_U64_USE_UNALIGNED
            #define GHOST_LOAD_HE_U64_USE_UNALIGNED 0
        #endif

        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/uint8_t/ghost_uint8_t.h"
        #if !GHOST_LOAD_HE_U64_USE_UNALIGNED
            #include "ghost/type/uint8_t/ghost_uint8_t.h"
            #include "ghost/language/ghost_reinterpret_cast.h"
            #include "ghost/language/ghost_restrict.h"
        #endif

        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        ghost_uint64_t ghost_load_he_u64(const void* p) {
            #if GHOST_LOAD_HE_U64_USE_UNALIGNED
                return *ghost_static_cast(const ghost_uint64_t*, p);
            #else
                /* GCC and Clang with optimizations enabled can recognize this as an
                 * unaligned load and emit the appropriate instruction on CPUs that
                 * support it. */
                uint64_t value;
                ghost_uint8_t* ghost_restrict to = ghost_reinterpret_cast(ghost_uint8_t*, &value);
                const ghost_uint8_t* ghost_restrict from = ghost_static_cast(const ghost_uint8_t*, p);
                to[0] = from[0];
                to[1] = from[1];
                to[2] = from[2];
                to[3] = from[3];
                to[4] = from[4];
                to[5] = from[5];
                to[6] = from[6];
                to[7] = from[7];
                return value;
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE

        #undef GHOST_LOAD_HE_U64_USE_UNALIGNED
        #define ghost_has_ghost_load_he_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_load_he_u64
    #define ghost_has_ghost_load_he_u64 0
#endif

#endif
