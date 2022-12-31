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

#ifndef GHOST_CHECKED_ADD_I32_H_INCLUDED
#define GHOST_CHECKED_ADD_I32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Adds int32_t-sized integers a and b, checking for overflow and underflow and
 * placing the truncated result in out.
 *
 * Addition is performed as if the integer type had infinite width.
 *
 * If the result of the addition fits within int32_t, the result is placed in
 * out and the function returns false.
 *
 * If the resulting value does not fit within int32_t, the result is wrapped by
 * two's complement to the range of int32_t and placed in out, and the function
 * returns true.
 *
 * Another way to think of this is that it returns the carry or overflow flag
 * of the addition.
 *
 * Use it like this:
 *
 *     int32_t x;
 *     if (ghost_checked_add_i32(&x, a, b)) {
 *         // Addition failed! Handle error here
 *     }
 *
 * Or like this:
 *
 *     int32_t x;
 *     ghost_ensure(!ghost_checked_i32(&x, a, b), "overflow");
 *
 * Signed overflow is undefined so compilers may assume it never happens and
 * make optimization decisions that break your code. This implementation avoids
 * undefined behaviour and always provides the correct result wrapped/truncated
 * by two's complement.
 *
 * @return The carry/overflow flag of the addition: true if it overflowed or
 *         underflowed, false if the result is correct
 */
bool ghost_checked_add_i32(int32_t* out, int32_t a, int32_t b);
#endif

#ifndef ghost_has_ghost_checked_add_i32
    #ifdef ghost_checked_add_i32
        #define ghost_has_ghost_checked_add_i32 1
    #endif
#endif

/* We need ghost_int32_t. We also need it to be two's complement. */
#ifndef ghost_has_ghost_checked_add_i32
    #include "ghost/type/int32_t/ghost_int32_t.h"
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if !ghost_has(ghost_int32_t) || !GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
        #define ghost_has_ghost_checked_add_i32 0
    #endif
#endif

/*
 * C23 will have type-generic ckd_add(). ghost_checked_add_*() are modeled
 * after its behaviour and argument order, except we don't support differing
 * types: the types of all arguments must match. We do this to make it easier
 * to implement in plain C, and because Ghost is just generally more strongly
 * typed than the C standard library.
 *
 * (We also don't leave out random letters from the name. Is it "chk" or "ckd"
 * or "chd" or something else? I keep forgetting. This is madness.)
 */
#ifndef ghost_has_ghost_checked_add_i32
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            #include "ghost/header/c/ghost_stdckdint_h.h"
            #ifdef ckd_add
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/type/bool/ghost_bool.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_bool ghost_checked_add_i32(
                        ghost_int32_t* ghost_impl_v_out,
                        ghost_int32_t ghost_impl_v_a,
                        ghost_int32_t ghost_impl_v_b)
                {
                    return ckd_add(
                            ghost_impl_v_out,
                            ghost_impl_v_a,
                            ghost_impl_v_b);
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_checked_add_i32 1
            #endif
        #endif
    #endif
#endif

/* GNU C compilers have a type-generic __builtin_add_overflow(). (GCC also has
 * type-specific functions __builtin_<type>add_overflow() for basic types but
 * we don't bother to wrap them right now because we'd have to convert from
 * basic types to fixed-width types.) */
#ifndef ghost_has_ghost_checked_add_i32
    #include "ghost/impl/math/ghost_impl_has_builtin_add_overflow.h"
    #if GHOST_IMPL_HAS_BUILTIN_ADD_OVERFLOW
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        ghost_bool ghost_checked_add_i32(
                ghost_int32_t* ghost_impl_v_out,
                ghost_int32_t ghost_impl_v_a,
                ghost_int32_t ghost_impl_v_b)
        {
            return __builtin_add_overflow(
                    ghost_impl_v_a,
                    ghost_impl_v_b,
                    ghost_impl_v_out);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_checked_add_i32 1
    #endif
#endif

/* MSVC and Intel have _addcarry_u32() on x86 and amd64 processors but don't
 * appear to have an equivalent signed operation. */

/* Plain C implementation */
#ifndef ghost_has_ghost_checked_add_i32
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    #if ghost_has(ghost_uint32_t)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_bool ghost_checked_add_i32(
                ghost_int32_t* ghost_impl_v_out,
                ghost_int32_t ghost_impl_v_a,
                ghost_int32_t ghost_impl_v_b)
        {
            /* Signed overflow is technically undefined so we do everything as
             * unsigned and cast back. */
            ghost_uint32_t ghost_impl_v_ua = ghost_static_cast(ghost_uint32_t, ghost_impl_v_a);
            ghost_uint32_t ghost_impl_v_ub = ghost_static_cast(ghost_uint32_t, ghost_impl_v_b);
            ghost_uint32_t ghost_impl_v_result = ghost_impl_v_ua + ghost_impl_v_ub;
            *ghost_impl_v_out = ghost_static_cast(ghost_int32_t, ghost_impl_v_result);

            /*
             * Branchless implementation similar to:
             *     https://stackoverflow.com/a/44830670
             *
             * "0x80000000" -- We're checking the sign bit of the following two
             * expressions:
             *
             * "~(a ^ b)" -- If the arguments have different sign, the result
             * cannot overflow
             *
             * "(a ^ result)" -- If the arguments and result have the same
             * sign, the result cannot overflow
             *
             * If both of these expressions are true (i.e. the arguments
             * have the same sign and it is different from the result), the
             * addition overflowed.
             */
            return !!(0x80000000u
                    & (~(ghost_impl_v_ua ^ ghost_impl_v_ub))
                    & (ghost_impl_v_ua ^ ghost_impl_v_result));

            #if 0
                /* Alternate implementation I found somewhere. Compilers might be
                 * better at recognizing and optimizing this than the branchless
                 * implementation (assuming it works; TODO test it.) */
                return (ghost_impl_v_b < 0) ?
                    (ghost_impl_v_a < GHOST_INT32_MIN - ghost_impl_v_b) :
                    (ghost_impl_v_a > GHOST_INT32_MAX - ghost_impl_v_b);
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_checked_add_i32 1
    #endif
#endif

#ifndef ghost_has_ghost_checked_add_i32
    #define ghost_has_ghost_checked_add_i32 0
#endif

#endif
