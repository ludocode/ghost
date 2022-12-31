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

#ifndef GHOST_COMPARE_ULL_H_INCLUDED
#define GHOST_COMPARE_ULL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Performs a three-way comparison of the arguments, returning their relative
 * ordering.
 *
 * @return 0 if the arguments are equal; less than 0 if the first argument is
 *         less than the second; and greater than 0 if the first argument is
 *         greater than the second.
 */
int ghost_compare_ull(unsigned long long left, unsigned long long right);
#endif

#ifndef ghost_has_ghost_compare_ull
    #ifdef ghost_compare_ull
        #define ghost_has_ghost_compare_ull 1
    #endif
#endif

#ifndef ghost_has_ghost_compare_ull
    #include "ghost/type/ullong/ghost_ullong.h"
    #if !ghost_has(ghost_ullong)
        #define ghost_has_ghost_compare_ull 0
    #endif
#endif

/* If the type is smaller than int, we can cast to int and do a subtraction. */
#ifndef ghost_has_ghost_compare_ull
    #include "ghost/type/ullong/ghost_ullong_width.h"
    #if ghost_has(GHOST_ULLONG_WIDTH)
        #include "ghost/type/int/ghost_int_width.h"
        #if ghost_has(GHOST_INT_WIDTH)
            #if GHOST_ULLONG_WIDTH < GHOST_INT_WIDTH
                #include "ghost/impl/ghost_impl_inline.h"
                #include "ghost/language/ghost_static_cast.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_inline
                int ghost_compare_ull(ghost_ullong ghost_impl_v_left, ghost_ullong ghost_impl_v_right) {
                    int ghost_impl_v_ileft = ghost_static_cast(int, ghost_impl_v_left);
                    int ghost_impl_v_iright = ghost_static_cast(int, ghost_impl_v_right);
                    return ghost_impl_v_ileft - ghost_impl_v_iright;
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_compare_ull 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we branch. */
#ifndef ghost_has_ghost_compare_ull
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    int ghost_compare_ull(ghost_ullong ghost_impl_v_left, ghost_ullong ghost_impl_v_right) {
        return (ghost_impl_v_left > ghost_impl_v_right) ? -1 :
                ((ghost_impl_v_left < ghost_impl_v_right) ? 1 : 0);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_compare_ull 1
#endif

#endif
