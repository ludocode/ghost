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

#ifndef GHOST_FNV1A_Z_H_INCLUDED
#define GHOST_FNV1A_Z_H_INCLUDED

#include "ghost/ghost_core.h"

#ifndef ghost_has_ghost_fnv1a_z
    #ifdef ghost_fnv1a_z
        #define ghost_has_ghost_fnv1a_z 1
    #endif
#endif

/* If we know the size at compile time we can call directly */

#ifndef ghost_has_ghost_fnv1a_z
    #include "ghost/type/size_t/ghost_size_width.h"
    #if ghost_has(GHOST_SIZE_WIDTH)
        #if GHOST_SIZE_WIDTH <= 32
            #include "ghost/algorithm/fnv1a/ghost_fnv1a_u32.h"
            #if ghost_has(ghost_fnv1a_u32)
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/type/size_t/ghost_size_t.h"
                #include "ghost/language/ghost_static_cast.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_size_t ghost_fnv1a_z(const void* bytes, ghost_size_t length) {
                    return ghost_static_cast(ghost_size_t, ghost_fnv1a_u32(bytes, length));
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_fnv1a_z 1
            #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_fnv1a_z
    #if ghost_has(GHOST_SIZE_WIDTH)
        #if GHOST_SIZE_WIDTH <= 64
            #include "ghost/algorithm/fnv1a/ghost_fnv1a_u64.h"
            #if ghost_has(ghost_fnv1a_u64)
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/type/size_t/ghost_size_t.h"
                #include "ghost/language/ghost_static_cast.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_size_t ghost_fnv1a_z(const void* bytes, ghost_size_t length) {
                    return ghost_static_cast(ghost_size_t, ghost_fnv1a_u64(bytes, length));
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_fnv1a_z 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we check at runtime. This should be trivially optimized to a
 * direct call to the correct hash function. We need at least u32 to exist. */

#ifndef ghost_has_ghost_fnv1a_z
    #include "ghost/algorithm/fnv1a/ghost_fnv1a_u32.h"
    #if !ghost_has(ghost_fnv1a_u32)
        #define ghost_has_ghost_fnv1a_z 0
    #endif
#endif

#ifndef ghost_has_ghost_fnv1a_z
    #include "ghost/algorithm/fnv1a/ghost_fnv1a_u64.h"
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/type/char/ghost_char_width.h"

    /* We haven't bothered to implement size_t larger than 64 bits. */
    ghost_static_assert(sizeof(ghost_size_t) <= sizeof(ghost_uint64_t));

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    ghost_size_t ghost_fnv1a_z(const void* bytes, ghost_size_t length) {
        #if ghost_has(ghost_fnv1a_u64)
            if (sizeof(ghost_size_t) * GHOST_CHAR_WIDTH > 32)
                return ghost_static_cast(ghost_size_t, ghost_fnv1a_u64(bytes, length));
        #endif
        return ghost_static_cast(ghost_size_t, ghost_fnv1a_u32(bytes, length));
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_fnv1a_z 1
#endif

#endif
