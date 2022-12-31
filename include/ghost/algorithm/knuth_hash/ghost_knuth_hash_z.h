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

#ifndef GHOST_KNUTH_HASH_Z_H_INCLUDED
#define GHOST_KNUTH_HASH_Z_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Performs a Knuth multiplicative hash and range reduction on the given
 * `size_t` value, returning the given number of most-significant bits.
 *
 * This is a trivial hash function to reduce a size_t hash value to a power
 * of two, ensuring only that all bits of the input are used. It provides a
 * basic pseudo-random distribution even for sequential values, making it
 * not entirely terrible for non-cryptographic hashing of keys (such as in a
 * hash table.)
 *
 * The return value is dependent on the size of size_t. Don't use this for
 * hashes that must be consistent across different systems.
 *
 * @see ghost_knuth_hash_u64
 */
size_t ghost_knuth_hash_z(size_t value, size_t bits);
#endif

#ifndef ghost_has_ghost_knuth_hash_z
    #ifdef ghost_knuth_hash_z
        #define ghost_has_ghost_knuth_hash_z 1
    #endif
#endif

/* If we know the size at compile time we can call directly */

#ifndef ghost_has_ghost_knuth_hash_z
    #include "ghost/type/size_t/ghost_size_width.h"
    #if ghost_has(GHOST_SIZE_WIDTH)
        #if GHOST_SIZE_WIDTH <= 16
            #include "ghost/algorithm/knuth_hash/ghost_knuth_hash_u16.h"
            #if ghost_has(ghost_knuth_hash_u16)
                #include "ghost/type/size_t/ghost_size_t.h"
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/language/ghost_static_cast.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_size_t ghost_knuth_hash_z(ghost_size_t value, ghost_size_t bits) {
                    return ghost_static_cast(ghost_size_t,
                            ghost_knuth_hash_u16(ghost_static_cast(ghost_uint16_t, value), bits));
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_knuth_hash_z 1
            #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_knuth_hash_z
    #include "ghost/type/size_t/ghost_size_width.h"
    #if ghost_has(GHOST_SIZE_WIDTH)
        #if GHOST_SIZE_WIDTH <= 32
            #include "ghost/algorithm/knuth_hash/ghost_knuth_hash_u32.h"
            #if ghost_has(ghost_knuth_hash_u32)
                #include "ghost/type/size_t/ghost_size_t.h"
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/language/ghost_static_cast.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_size_t ghost_knuth_hash_z(ghost_size_t value, ghost_size_t bits) {
                    return ghost_static_cast(ghost_size_t,
                            ghost_knuth_hash_u32(ghost_static_cast(ghost_uint32_t, value), bits));
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_knuth_hash_z 1
            #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_knuth_hash_z
    #include "ghost/type/size_t/ghost_size_width.h"
    #if ghost_has(GHOST_SIZE_WIDTH)
        #if GHOST_SIZE_WIDTH <= 64
            #include "ghost/algorithm/knuth_hash/ghost_knuth_hash_u64.h"
            #if ghost_has(ghost_knuth_hash_u64)
                #include "ghost/type/size_t/ghost_size_t.h"
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/language/ghost_static_cast.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_size_t ghost_knuth_hash_z(ghost_size_t value, ghost_size_t bits) {
                    return ghost_static_cast(ghost_size_t,
                            ghost_knuth_hash_u64(ghost_static_cast(ghost_uint64_t, value), bits));
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_knuth_hash_z 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we check at runtime. This should be trivially optimized to a
 * direct call to the correct hash function. We need at least u16 to exist. */

#ifndef ghost_has_ghost_knuth_hash_z
    #include "ghost/algorithm/knuth_hash/ghost_knuth_hash_u16.h"
    #if !ghost_has(ghost_knuth_hash_u16)
        #define ghost_has_ghost_knuth_hash_z 0
    #endif
#endif

#ifndef ghost_has_ghost_knuth_hash_z
    #include "ghost/algorithm/knuth_hash/ghost_knuth_hash_u32.h"
    #include "ghost/algorithm/knuth_hash/ghost_knuth_hash_u64.h"
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/type/char/ghost_char_width.h"

    /* We've only implemented this up to 64 bits. */
    ghost_static_assert(sizeof(ghost_size_t) <= sizeof(ghost_uint64_t));

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    ghost_size_t ghost_knuth_hash_z(ghost_size_t value, ghost_size_t bits) {
        #if ghost_has(ghost_uint64_t)
            if (sizeof(ghost_size_t) * GHOST_CHAR_WIDTH > 32) {
                return ghost_static_cast(ghost_size_t,
                        ghost_knuth_hash_u64(ghost_static_cast(ghost_uint64_t, value), bits));
            }
        #endif

        #if ghost_has(ghost_uint32_t)
            if (sizeof(ghost_size_t) * GHOST_CHAR_WIDTH > 16) {
                return ghost_static_cast(ghost_size_t,
                        ghost_knuth_hash_u32(ghost_static_cast(ghost_uint32_t, value), bits));
            }
        #endif

        return ghost_static_cast(ghost_size_t,
                ghost_knuth_hash_u16(ghost_static_cast(ghost_uint16_t, value), bits));
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_knuth_hash_z 1
#endif

#endif
