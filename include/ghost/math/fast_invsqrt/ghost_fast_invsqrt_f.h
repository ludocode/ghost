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

#ifndef GHOST_FAST_INVSQRT_F_H_INCLUDED
#define GHOST_FAST_INVSQRT_F_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns a close approximation of the inverse square root of the given float.
 *
 * The given float must be normal and positive. If it is negative, subnormal,
 * zero, infinity or NaN, the result is undefined.
 *
 * This is the magic inverse square root bitcasting hack commonly used in early
 * 3D video games. It was popularized by Quake 3 Arena.
 *
 *     https://en.wikipedia.org/wiki/Fast_inverse_square_root
 *
 * This implementation has a relative error of less than 0.07% for all valid
 * inputs. It uses the improved constants from Jan Kadlec:
 *
 *     http://rrrola.wz.cz/inv_sqrt.html
 *
 * On modern architectures this is no longer useful since fast hardware
 * instructions are typically available (e.g. SSE2 in x86 has `rsqrtss`.)
 * However this may still be useful if you need to target old or embedded
 * hardware that does not have such instructions.
 */
#endif

#ifndef ghost_has_ghost_fast_invsqrt_f
    #ifdef ghost_fast_invsqrt_f
        #define ghost_has_ghost_fast_invsqrt_f 1
    #endif
#endif

/* TODO move this to float32_t, use it for this and double if they match width */
#ifndef ghost_has_ghost_fast_invsqrt_f
    #include "ghost/type/float/ghost_float.h"
    #if ghost_has(ghost_float)
        #include "ghost/type/uint32_t/ghost_uint32_t.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_bit_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        float ghost_fast_invsqrt_f(const float ghost_impl_f) {
            ghost_uint32_t ghost_impl_u;
            float ghost_impl_r;
            ghost_impl_u = ghost_bit_cast(ghost_uint32_t, float, ghost_impl_f);
            ghost_impl_u = 0x5F1FFFF9U - (ghost_impl_u >> 1);
            ghost_impl_r = ghost_bit_cast(float, ghost_uint32_t, ghost_impl_u);
            ghost_impl_r *= 0.703952253F * (2.38924456F - ghost_impl_f * ghost_impl_r * ghost_impl_r);
            return ghost_impl_r;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_fast_invsqrt_f 1
    #endif
#endif

#ifndef ghost_has_ghost_fast_invsqrt_f
    #define ghost_has_ghost_fast_invsqrt_f 0
#endif

#endif
