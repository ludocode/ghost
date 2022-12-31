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

#ifndef GHOST_POPCOUNT_U32_H_INCLUDED
#define GHOST_POPCOUNT_U32_H_INCLUDED

#include "ghost/ghost_core.h"

/* TODO fix later */
#define ghost_has_ghost_popcount_u32 0
#if 0

#include "ghost/type/uint32_t/ghost_uint32_t.h"
#include "ghost/language/ghost_always_inline.h"

#ifdef _MSC_VER
#include <intrin.h>
#pragma intrinsic(__popcnt)
#endif

/* TODO C++20 has std::popcount in <bit>  https://en.cppreference.com/w/cpp/header/bit */

/**
 * Count the number of bits set in the binary representation of the given
 * integer.
 *
 * This is short for "population count". Another name for it is "Hamming
 * weight".
 *
 * https://en.wikipedia.org/wiki/Hamming_weight#Efficient_implementation
 */
ghost_always_inline
static
uint32_t ghost_popcount_u32(uint32_t v) {

    #ifdef _MSC_VER
        #if defined(__AVX__) || defined(__POPCNT__)
            /*
             * MSVC
             *
             * We use the CPU instruction if __AVX__ or __POPCNT__ are defined,
             * this way /arch:AVX will enable it. POPCNT isn't actually in
             * AVX but we assume all CPUs that support AVX will support POPCNT.
             * If you want to use POPCNT without AVX, define __POPCNT__.
             * If you have a CPU that supports AVX but not POPCNT, I guess,
             * file a bug against Ghost?
             *     https://docs.microsoft.com/en-us/cpp/intrinsics/popcnt16-popcnt-popcnt64
             *     https://docs.microsoft.com/en-us/cpp/build/reference/arch-x86
             *     https://docs.microsoft.com/en-us/cpp/build/reference/arch-x64
             * TODO this is wrong, the intrinsic pragma can only be used outside of a function:
             *     https://docs.microsoft.com/en-us/cpp/preprocessor/intrinsic?view=msvc-170
             */
            return __popcnt(v);
            #define GHOST_POPCOUNT_U32_INTRINSIC
        #endif

    #elif defined(__has_builtin) /* TODO ghost_has_builtin*/
        /* TODO detect this even without __has_builtin, __builtin_popcount is super old */
        #if __has_builtin(__builtin_popcount)
            /*
             * GNUC
             *
             * https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005fpopcount
             *
             * If POPCNT isn't available, GCC will emit a call to a libgcc
             * popcount function and Clang will emit a bunch of machine code to
             * do it inline.
             * You can enable the POPCNT instruction on x86_64 with -mpopcnt or
             * -msse4.2 or various other flags.
             */
            return __builtin_popcount(v);
            #define GHOST_POPCOUNT_U32_INTRINSIC
        #endif
    #endif

    #ifndef GHOST_POPCOUNT_U32_INTRINSIC
    /*
     * Standard C fallback implementation
     *
     * https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
     * https://en.wikipedia.org/wiki/Hamming_weight#Efficient_implementation
     */
    v -= (v >> 1) & 0x55555555U;
    v = (v & 0x33333333U) + ((v >> 2) & 0x33333333U);
    return ((v + (v >> 4) & 0x0F0F0F0FU) * 0x01010101U) >> 24;
    #endif

    #undef GHOST_POPCOUNT_U32_INTRINSIC
}

#endif
#endif
