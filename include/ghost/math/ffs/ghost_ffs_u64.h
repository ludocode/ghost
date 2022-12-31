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

#ifndef GHOST_FFS_U64_H_INCLUDED
#define GHOST_FFS_U64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the position of the least significant bit set in x (where the least
 * significant bit has position 1), or 0 if no bits in x are set.
 *
 *     https://en.wikipedia.org/wiki/Find_first_set
 */
int ghost_ffs_u64(uint64_t x);
#endif

#ifndef ghost_has_ghost_ffs_u64
    #ifdef ghost_ffs_u64
        #define ghost_has_ghost_ffs_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_ffs_u64
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #if !ghost_has(ghost_uint64_t)
        #define ghost_has_ghost_ffs_u64 0
    #endif
#endif

/* GNU C compilers have a builtin for ffs but it only works with basic types.
 * We need to know what basic type fits uint64_t to use it. */

/* For types smaller than int, we use int. */
#ifndef ghost_has_ghost_ffs_u64
    #include "ghost/impl/math/ghost_impl_has_builtin_ffs.h"
    #if GHOST_IMPL_HAS_BUILTIN_FFS
        #include "ghost/type/int/ghost_int_width.h"
        #if ghost_has(GHOST_INT_WIDTH)
            #if GHOST_INT_WIDTH >= 64
                #include "ghost/language/ghost_static_cast.h"
                #define ghost_ffs_u64(x) __builtin_ffs(ghost_static_cast(int, (x)))
                #define ghost_has_ghost_ffs_u64 1
            #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_ffs_u64
    #include "ghost/impl/math/ghost_impl_has_builtin_ffs.h"
    #if GHOST_IMPL_HAS_BUILTIN_FFS
        #include "ghost/type/ghost_long_all.h"
        #if ghost_has(GHOST_LONG_WIDTH)
            #if GHOST_LONG_WIDTH >= 64
                #include "ghost/language/ghost_static_cast.h"
                #define ghost_ffs_u64(x) __builtin_ffs(ghost_static_cast(long, (x)))
                #define ghost_has_ghost_ffs_u64 1
            #endif
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_ffs_u64
    #include "ghost/impl/math/ghost_impl_has_builtin_ffs.h"
    #if GHOST_IMPL_HAS_BUILTIN_FFS
        #include "ghost/type/ghost_llong_all.h"
        #if ghost_has(GHOST_LLONG_WIDTH)
            #if GHOST_LLONG_WIDTH >= 64
                #include "ghost/language/ghost_static_cast.h"
                #define ghost_ffs_u64(x) __builtin_ffs(ghost_static_cast(long long, (x)))
                #define ghost_has_ghost_ffs_u64 1
            #endif
        #endif
    #endif
#endif

/* GNU C compilers also have __builtin_ctz() which can be used to implement
 * ffs(). We don't bother wrapping it. We assume any compiler that supports
 * __builtin_ctz() also supports __builtin_ffs(). */

/* MSVC has _BitScanForward64 on 64-bit platforms. It works like ctz so we need
 * special handling for zero. */
#ifndef ghost_has_ghost_ffs_u64
    #if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64))
        #include <intrin.h>
        #pragma intrinsic(_BitScanForward64)
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        int ghost_ffs_u64(uint64_t x) {
            unsigned long ghost_i;
            /* I don't know whether it's faster just check if x==0 rather than
             * checking the result of this. */
            if (_BitScanForward64(&ghost_i, x) == 0)
                return 0;
            return ghost_static_cast(int, ghost_i + 1);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_ffs_u64 1
    #endif
#endif

/* Intel's compiler has _bit_scan_forward but it might not work on all
 * processors (it appears to require Skylake or later.) For now we avoid it. */

/*
 * Otherwise we implement it ourselves. This is based on the simplest
 * implementation here:
 *
 *     https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightParallel
 *
 * It's hacked up a bit to make it behave like ffs() rather than ctz().
 */
#ifndef ghost_has_ghost_ffs_u64
    #include "ghost/type/uint64_t/ghost_uint64_c.h"
    #if ghost_has(GHOST_UINT64_C)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/uint64_t/ghost_uint64_t.h"
        #include "ghost/type/int64_t/ghost_int64_t.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        int ghost_ffs_u64(ghost_uint64_t x) {
            int c = 64;
            if (x == 0)
                return 0;
            x &= ghost_static_cast(ghost_uint64_t, -ghost_static_cast(ghost_int64_t, x));
            if (x & GHOST_UINT64_C(0x00000000FFFFFFFF)) c -= 32;
            if (x & GHOST_UINT64_C(0x0000FFFF0000FFFF)) c -= 16;
            if (x & GHOST_UINT64_C(0x00FF00FF00FF00FF)) c -= 8;
            if (x & GHOST_UINT64_C(0x0F0F0F0F0F0F0F0F)) c -= 4;
            if (x & GHOST_UINT64_C(0x3333333333333333)) c -= 2;
            if (x & GHOST_UINT64_C(0x5555555555555555)) c -= 1;
            return c;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_ffs_u64 1
    #endif
#endif

#ifndef ghost_has_ghost_ffs_u64
    #define ghost_has_ghost_ffs_u64 0
#endif

#endif
