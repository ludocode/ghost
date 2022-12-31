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

#ifndef GHOST_COMPARE_U_H_INCLUDED
#define GHOST_COMPARE_U_H_INCLUDED

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
int ghost_compare_u(unsigned left, unsigned right);
#endif

#ifndef ghost_has_ghost_compare_u
    #ifdef ghost_compare_u
        #define ghost_has_ghost_compare_u 1
    #endif
#endif

#ifndef ghost_has_ghost_compare_u
    #include "ghost/type/uint/ghost_uint.h"
    #if !ghost_has(ghost_uint)
        #define ghost_has_ghost_compare_u 0
    #endif
#endif

/* If the type is smaller than int, we can cast to int and do a subtraction. */
#ifndef ghost_has_ghost_compare_u
    #include "ghost/type/uint/ghost_uint_width.h"
    #if ghost_has(GHOST_UINT_WIDTH)
        #include "ghost/type/int/ghost_int_width.h"
        #if ghost_has(GHOST_INT_WIDTH)
            #if GHOST_UINT_WIDTH < GHOST_INT_WIDTH
                #include "ghost/impl/ghost_impl_inline.h"
                #include "ghost/language/ghost_static_cast.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_inline
                int ghost_compare_u(unsigned ghost_impl_v_left, unsigned ghost_impl_v_right) {
                    int ghost_impl_v_ileft = ghost_static_cast(int, ghost_impl_v_left);
                    int ghost_impl_v_iright = ghost_static_cast(int, ghost_impl_v_right);
                    return ghost_impl_v_ileft - ghost_impl_v_iright;
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_compare_u 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we branch. */
#ifndef ghost_has_ghost_compare_u
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    int ghost_compare_u(unsigned ghost_impl_v_left, unsigned ghost_impl_v_right) {
        return (ghost_impl_v_left > ghost_impl_v_right) ? -1 :
                ((ghost_impl_v_left < ghost_impl_v_right) ? 1 : 0);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_compare_u 1
#endif

#endif
