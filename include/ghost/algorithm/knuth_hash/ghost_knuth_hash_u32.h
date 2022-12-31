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

#ifndef GHOST_KNUTH_HASH_U32_H_INCLUDED
#define GHOST_KNUTH_HASH_U32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Performs a Knuth multiplicative hash and range reduction on the given 32-bit
 * value, returning the given number of most-significant bits.
 *
 * This is a trivial hash function to reduce a 32-bit hash value to a power
 * of two, ensuring only that all bits of the input are used. It provides a
 * basic pseudo-random distribution even for sequential values, making it
 * not entirely terrible for non-cryptographic hashing of keys (such as in a
 * hash table.)
 *
 * @see ghost_knuth_hash_u64
 * @see ghost_knuth_hash_s
 */
uint32_t ghost_knuth_hash_u32(uint32_t value, size_t bits);
#endif

#ifndef ghost_has_ghost_knuth_hash_u32
    #ifdef ghost_knuth_hash_u32
        #define ghost_has_ghost_knuth_hash_u32 1
    #endif
#endif

#ifndef ghost_has_ghost_knuth_hash_u32
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    #include "ghost/type/uint32_t/ghost_uint32_c.h"
    #if !ghost_has(ghost_uint32_t) || !ghost_has(GHOST_UINT32_C)
        #define ghost_has_ghost_knuth_hash_u32 0
    #endif
#endif

#ifndef ghost_has_ghost_knuth_hash_u32
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/debug/ghost_assert.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_uint32_t ghost_knuth_hash_u32(ghost_uint32_t value, ghost_size_t bits) {
        ghost_uint32_t prime;
        ghost_assert(bits > 0, "");
        ghost_assert(bits <= 32, "");

        /*
         * The original Knuth hash. This is the largest prime less than the
         * quotient of UINT32_MAX by the golden ratio.
         *     https://www.wolframalpha.com/input?i=largest+prime+less+than+floor%28%282%5E32-1%29%2Fgolden+ratio%29
         */
        prime = GHOST_UINT32_C(2654435761);
        return (value * prime) >> (32 - bits);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_knuth_hash_u32 1
#endif

#endif
