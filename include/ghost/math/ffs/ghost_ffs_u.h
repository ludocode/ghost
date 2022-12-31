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

#ifndef GHOST_FFS_U_H_INCLUDED
#define GHOST_FFS_U_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the position of the least significant bit set in x (where the least
 * significant bit has position 1), or 0 if no bits in x are set.
 *
 *     https://en.wikipedia.org/wiki/Find_first_set
 */
int ghost_ffs_u(unsigned x);
#endif

#ifndef ghost_has_ghost_ffs_u
    #ifdef ghost_ffs_u
        #define ghost_has_ghost_ffs_u 1
    #endif
#endif

/* TODO also implement ghost_ffs_uc, ghost_ffs_uh, ghost_ffs_ul, ghost_ffs_ull, ghost_ffs_up, ghost_ffs_z */

/* GNU C compilers have __builtin_ffs() */
#ifndef ghost_has_ghost_ffs_u
    #include "ghost/impl/math/ghost_impl_has_builtin_ffs.h"
    #if GHOST_IMPL_HAS_BUILTIN_FFS
        #include "ghost/language/ghost_static_cast.h"
        #define ghost_ffs_u(x) __builtin_ffs(ghost_static_cast(int, (x)))
        #define ghost_has_ghost_ffs_u 1
    #endif
#endif

/*
 * GNU C compilers also have __builtin_ctz() which can be used to implement
 * ffs(). For now we don't bother wrapping it; we assume any compiler that
 * supports __builtin_ctz() also supports __builtin_ffs().
 */

/*
 * MSVC has _BitScanForward which works like ctz. We need special handling for
 * zero.
 *     https://docs.microsoft.com/en-us/cpp/intrinsics/bitscanforward-bitscanforward64
 */
#ifndef ghost_has_ghost_ffs_u
    #ifdef _MSC_VER
        #include <intrin.h>
        #pragma intrinsic(_BitScanForward)
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        int ghost_ffs_u(unsigned x) {
            unsigned long ghost_i;
            /* I don't know whether it's faster just check if x==0 rather than
             * checking the result of this. */
            if (_BitScanForward(&ghost_i, x) == 0)
                return 0;
            return ghost_static_cast(int, ghost_i + 1);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_ffs_u 1
    #endif
#endif

/* Intel's compiler has _bit_scan_forward but it might not work on all
 * processors (it appears to require Skylake or later.) For now we avoid it. */

/* TODO FreeBSD has ffs() in <strings.h>:
 * https://www.unix.com/man-page/freebsd/3/fls/
 * TODO so does glibc but only under _GNU_SOURCE or whatever. maybe don't use the glibc functions? */

/* If we know the size of unsigned we can try to wrap a fixed-width type. */
#ifndef ghost_has_ghost_ffs_u
    #include "ghost/type/ghost_uint_all.h"
    #if ghost_has_GHOST_UINT_WIDTH
        #if GHOST_UINT_WIDTH <= 8
            #include "ghost/math/ffs/ghost_ffs_u8.h"
            #if ghost_has_ghost_ffs_u8
                #include "ghost/type/uint8_t/ghost_uint8_t.h"
                #include "ghost/language/ghost_static_cast.h"
                #define ghost_ffs_u(x) ghost_static_cast(unsigned, ghost_ffs_u8(ghost_static_cast(ghost_uint8_t, (x))))
                #define ghost_has_ghost_ffs_u 1
            #endif
        #elif GHOST_UINT_WIDTH <= 16
            #include "ghost/math/ffs/ghost_ffs_u16.h"
            #if ghost_has_ghost_ffs_u16
                #include "ghost/type/uint16_t/ghost_uint16_t.h"
                #include "ghost/language/ghost_static_cast.h"
                #define ghost_ffs_u(x) ghost_static_cast(unsigned, ghost_ffs_u16(ghost_static_cast(ghost_uint16_t, (x))))
                #define ghost_has_ghost_ffs_u 1
            #endif
        #elif GHOST_UINT_WIDTH <= 32
            #include "ghost/math/ffs/ghost_ffs_u32.h"
            #if ghost_has_ghost_ffs_u32
                #include "ghost/type/uint32_t/ghost_uint32_t.h"
                #include "ghost/language/ghost_static_cast.h"
                #define ghost_ffs_u(x) ghost_static_cast(unsigned, ghost_ffs_u32(ghost_static_cast(ghost_uint32_t, (x))))
                #define ghost_has_ghost_ffs_u 1
            #endif
        #elif GHOST_UINT_WIDTH <= 64
            #include "ghost/math/ffs/ghost_ffs_u64.h"
            #if ghost_has_ghost_ffs_u64
                #include "ghost/type/uint64_t/ghost_uint64_t.h"
                #include "ghost/language/ghost_static_cast.h"
                #define ghost_ffs_u(x) ghost_static_cast(unsigned, ghost_ffs_u64(ghost_static_cast(ghost_uint64_t, (x))))
                #define ghost_has_ghost_ffs_u 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we write a function that will check at runtime. */
#ifndef ghost_has_ghost_ffs_u
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/math/ffs/ghost_ffs_u8.h"
    #include "ghost/math/ffs/ghost_ffs_u16.h"
    #include "ghost/math/ffs/ghost_ffs_u32.h"
    #include "ghost/math/ffs/ghost_ffs_u64.h"
    #include "ghost/type/uint8_t/ghost_uint8_t.h"
    #include "ghost/type/uint16_t/ghost_uint16_t.h"
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    #include "ghost/type/uint64_t/ghost_uint64_t.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    int ghost_ffs_u(unsigned x) {

        /* These if statements can be resolved at compile time so this should
         * be optimized to only one implementation. */

        #if ghost_has(ghost_ffs_u8)
        if (sizeof(x) <= sizeof(ghost_uint8_t))
            return ghost_ffs_u8(ghost_static_cast(ghost_uint8_t, (x)))
        #endif

        #if ghost_has(ghost_ffs_u16)
        if (sizeof(x) <= sizeof(ghost_uint16_t))
            return ghost_ffs_u16(ghost_static_cast(ghost_uint16_t, (x)))
        #endif

        #if ghost_has(ghost_ffs_u32)
        if (sizeof(x) <= sizeof(ghost_uint32_t))
            return ghost_ffs_u32(ghost_static_cast(ghost_uint32_t, (x)))
        #endif

        #if ghost_has(ghost_ffs_u64)
        if (sizeof(x) <= sizeof(ghost_uint64_t))
            return ghost_ffs_u64(ghost_static_cast(ghost_uint64_t, (x)))
        #endif

        /*
         * If we can't wrap an existing function, we have no idea what size
         * unsigned is so we have no choice but to use a slow loop.
         *
         * TODO there's a minor optimization here, could eliminate the `& 1` in
         * the loop, could also add a special case for 0:
         *     https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightLinear
         */
        int n = 0;
        while (x) {
            ++n;
            if (x & 1)
                return n;
            x >>= 1;
        }
        return n;
        /* TODO test this */
    }
    GHOST_IMPL_FUNCTION_CLOSE
#endif

#endif
