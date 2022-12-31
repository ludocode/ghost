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

#ifndef GHOST_MEMLCMP_H_INCLUDED
#define GHOST_MEMLCMP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * Performs an ordering comparison of the given memory regions of potentially
 * different lengths, returning 0 if they are equal with matching length, less
 * than 0 if a "comes before" b, and greater than 0 otherwise.
 *
 * This is like memcmp() except the memory regions can differ in length. If the
 * lengths are the same, this is equivalent to memcmp(). Where lengths differ,
 * the smaller of lengths is the number of bytes compared, and if all such
 * bytes are equal, the shorter memory region comes first.
 *
 * This can be used to perform ordering comparisons on non-null-terminated
 * strings.
 *
 * @see ghost_memcmp
 */
int ghost_memlcmp(const void* a, size_t a_length, const void* b, size_t b_length);
#endif

#ifndef ghost_has_ghost_memlcmp
    #ifdef ghost_memlcmp
        #define ghost_has_ghost_memlcmp 1
    #endif
#endif

/*
 * This a Ghost invention. I couldn't find a public function that does this in
 * any platform or third-party library, which is surprising because it seems
 * like a pretty obvious extension for comparing or sorting strings without
 * null terminators. I assume some platforms must implement something like this
 * so let me know and we'll wrap them here.
 */

#ifndef ghost_has_ghost_memlcmp
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/math/min/ghost_min_z.h"
    #include "ghost/math/compare/ghost_compare_z.h"
    #include "ghost/string/ghost_memcmp.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    int ghost_memlcmp(
            const void* ghost_impl_v_a, ghost_size_t ghost_impl_v_a_length,
            const void* ghost_impl_v_b, ghost_size_t ghost_impl_v_b_length) GHOST_IMPL_DEF(
    {
        ghost_size_t ghost_impl_v_length = ghost_min_z(ghost_impl_v_a_length, ghost_impl_v_b_length);
        int ghost_impl_v_ret = ghost_memcmp(ghost_impl_v_a, ghost_impl_v_b, ghost_impl_v_length);
        if (ghost_impl_v_ret != 0)
            return ghost_impl_v_ret;
        return ghost_compare_z(ghost_impl_v_a_length, ghost_impl_v_b_length);
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memlcmp 1
#endif

#endif
