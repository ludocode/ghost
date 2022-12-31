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

#ifndef GHOST_CHECKED_MUL_Z_H_INCLUDED
#define GHOST_CHECKED_MUL_Z_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Multiplies size_t-sized integers a and b, checking for overflow and placing
 * the truncated result in out.
 *
 * Multiplication is performed as if the integer type had infinite width.
 *
 * If the result fits within size_t, the result is placed in out and the
 * function returns false.
 *
 * If the result does not fit within size_t, the result is wrapped to the range
 * of size_t and placed in out, and the function returns true.
 *
 * Use it like this:
 *
 *     size_t x;
 *     if (ghost_checked_mul_z(&x, a, b)) {
 *         // Multiplication failed! Handle error here
 *     }
 *
 * Or like this:
 *
 *     size_t x;
 *     ghost_ensure(!ghost_checked_mul_z(&x, a, b), "overflow");
 *
 * @return True if the multiplication overflowed, false if the result is
 *         correct
 */
bool ghost_checked_add_z(size_t* out, size_t a, size_t b);
#endif

#ifndef ghost_has_ghost_checked_add_z
    #ifdef ghost_checked_add_z
        #define ghost_has_ghost_checked_add_z 1
    #endif
#endif

/* We need ghost_size_t. */
#ifndef ghost_has_ghost_checked_add_z
    #include "ghost/type/size_t/ghost_size_t.h"
    #if !ghost_has(ghost_size_t)
        #define ghost_has_ghost_checked_add_z 0
    #endif
#endif

/*
 * C23 will have type-generic ckd_mul(). ghost_checked_mul_*() are modeled
 * after its behaviour and argument order, except we don't support differing
 * types: the types of all arguments must match. We do this to make it easier
 * to implement in plain C, and because Ghost is just generally more strongly
 * typed than the C standard library.
 *
 * (We also don't leave out random letters from the name. Is it "chk" or "ckd"
 * or "chd" or something else? I keep forgetting. This is madness.)
 */
#ifndef ghost_has_ghost_checked_mul_z
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            #include "ghost/header/c/ghost_stdckdint_h.h"
            #ifdef ckd_mul
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/type/bool/ghost_bool.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_bool ghost_checked_mul_z(
                        ghost_size_t* ghost_impl_v_out,
                        ghost_size_t ghost_impl_v_a,
                        ghost_size_t ghost_impl_v_b)
                {
                    return ckd_mul(
                            ghost_impl_v_out,
                            ghost_impl_v_a,
                            ghost_impl_v_b);
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_checked_mul_z 1
            #endif
        #endif
    #endif
#endif

/* GNU C compilers have a type-generic __builtin_mul_overflow(). (GCC also has
 * type-specific functions __builtin_<type>mul_overflow() for basic types but
 * we don't bother to wrap them right now because we'd have to convert from
 * basic types to fixed-width types.) */
#ifndef ghost_has_ghost_checked_mul_z
    #include "ghost/impl/math/ghost_impl_has_builtin_mul_overflow.h"
    #if GHOST_IMPL_HAS_BUILTIN_MUL_OVERFLOW
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        ghost_bool ghost_checked_mul_z(
                ghost_size_t* ghost_impl_v_out,
                ghost_size_t ghost_impl_v_a,
                ghost_size_t ghost_impl_v_b)
        {
            return __builtin_mul_overflow(
                    ghost_impl_v_a,
                    ghost_impl_v_b,
                    ghost_impl_v_out);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_checked_mul_z 1
    #endif
#endif

/* Plain C implementation */
#ifndef ghost_has_ghost_checked_mul_z
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_8_BIT_CHAR
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_bool ghost_checked_mul_z(
                ghost_size_t* ghost_impl_v_out,
                ghost_size_t ghost_impl_v_a,
                ghost_size_t ghost_impl_v_b)
        {
            ghost_size_t ghost_impl_v_large = (ghost_static_cast(ghost_size_t, 1)
                    << ghost_static_cast(ghost_size_t, (sizeof(ghost_size_t) * 4)));

            *ghost_impl_v_out = ghost_impl_v_a * ghost_impl_v_b;

            return (ghost_impl_v_a >= ghost_impl_v_large
                        || ghost_impl_v_b >= ghost_impl_v_large)
                    && ghost_impl_v_a != 0
                    && *ghost_impl_v_out / ghost_impl_v_a != ghost_impl_v_b;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_checked_mul_z 1
    #endif
#endif

#ifndef ghost_has_ghost_checked_mul_z
    #define ghost_has_ghost_checked_mul_z 0
#endif

#endif
