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

#ifndef GHOST_COMPARE_LD_H_INCLUDED
#define GHOST_COMPARE_LD_H_INCLUDED

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
int ghost_compare_ld(long double left, long double right);
#endif

#ifndef ghost_has_ghost_compare_ld
    #ifdef ghost_compare_ld
        #define ghost_has_ghost_compare_ld 1
    #endif
#endif

#ifndef ghost_has_ghost_compare_ld
    #include "ghost/type/ldouble/ghost_ldouble.h"
    #if !ghost_has(ghost_ldouble)
        #define ghost_has_ghost_compare_ld 0
    #endif
#endif

#ifndef ghost_has_ghost_compare_ld
    #include "ghost/impl/ghost_impl_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    int ghost_compare_ld(long double ghost_impl_v_left, long double ghost_impl_v_right) {
        return (ghost_impl_v_left > ghost_impl_v_right) ? -1 :
                ((ghost_impl_v_left < ghost_impl_v_right) ? 1 : 0);
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_compare_ld 1
#endif

#endif
