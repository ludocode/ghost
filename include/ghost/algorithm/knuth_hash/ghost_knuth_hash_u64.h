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

#ifndef GHOST_KNUTH_HASH_U64_H_INCLUDED
#define GHOST_KNUTH_HASH_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Performs a Knuth multiplicative hash and range reduction on the given 64-bit
 * value, returning the given number of most-significant bits.
 *
 * This is a trivial hash function to reduce a 64-bit hash value to a power
 * of two, ensuring only that all bits of the input are used. It provides a
 * basic pseudo-random distribution even for sequential values, making it
 * not entirely terrible for non-cryptographic hashing of keys (such as in a
 * hash table.)
 *
 * @see ghost_knuth_hash_u32
 * @see ghost_knuth_hash_s
 */
uint64_t ghost_knuth_hash_u64(uint64_t value, size_t bits);
#endif

#ifndef ghost_has_ghost_knuth_hash_u64
    #ifdef ghost_knuth_hash_u64
        #define ghost_has_ghost_knuth_hash_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_knuth_hash_u64
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #include "ghost/type/uint64_t/ghost_uint64_c.h"
    #if !ghost_has(ghost_uint64_t) || !ghost_has(GHOST_UINT64_C)
        #define ghost_has_ghost_knuth_hash_u64 0
    #endif
#endif

#ifndef ghost_has_ghost_knuth_hash_u64
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/debug/ghost_assert.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_uint64_t ghost_knuth_hash_u64(ghost_uint64_t value, ghost_size_t bits) {
        ghost_uint64_t prime;
        ghost_assert(bits > 0, "");
        ghost_assert(bits <= 64, "");

        /*
         * This number is defined for 64-bit the same way as the prime in Knuth's
         * 32-bit multiplicative hash: it is the largest prime that is less than
         * the quotient of UINT64_MAX by the golden ratio.
         *     https://www.wolframalpha.com/input?i=largest+prime+less+than+floor%28%282%5E64-1%29%2Fgolden+ratio%29
         */
        prime = GHOST_UINT64_C(11400714819323198393);
        return (value * prime) >> (64 - bits);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_knuth_hash_u64 1
#endif

#endif
