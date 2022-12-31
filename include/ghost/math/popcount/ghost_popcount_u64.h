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

#ifndef GHOST_POPCOUNT_U64_H_INCLUDED
#define GHOST_POPCOUNT_U64_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO fix later */
#define ghost_has_ghost_popcount_u64 0
#if 0

#include "ghost/type/uint64_t/ghost_uint64_t.h"
#include "ghost/language/ghost_always_inline.h"
#include "ghost/language/ghost_extern_c.h"

#ifdef _MSC_VER
/* TODO is this right? only do if necessary */
#include <intrin.h>
#pragma intrinsic(__popcnt)
#endif

GHOST_EXTERN_C_PUSH
ghost_always_inline
static
uint64_t ghost_popcount_u64(uint64_t v) {

    /* TODO */

    #ifndef GHOST_POPCOUNT_U64_INTRINSIC
    /*
     * Standard C
     *
     * https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
     * https://en.wikipedia.org/wiki/Hamming_weight#Efficient_implementation
     */
    v -= (v >> 1) & 0x5555555555555555ULL;
    v = (v & 0x3333333333333333ULL) + ((v >> 2) & 0x3333333333333333ULL);
    return ((v + (v >> 4) & 0x0F0F0F0F0F0F0F0FULL) * 0x0101010101010101ULL) >> 56;
    #endif

    #undef GHOST_POPCOUNT_U64_INTRINSIC
}
GHOST_EXTERN_C_POP

#endif
#endif
