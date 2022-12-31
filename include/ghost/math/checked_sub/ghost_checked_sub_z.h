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

#ifndef GHOST_CHECKED_SUB_Z_H_INCLUDED
#define GHOST_CHECKED_SUB_Z_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Subtracts size_t-sized integers a and b, checking for overflow and placing the
 * truncated result in out.
 *
 * Subtraction is performed as if the integer type had infinite width.
 *
 * If the result of the subtraction fits within size_t, the result is placed in
 * out and the function returns false.
 *
 * If the resulting value does not fit within size_t, the result is wrapped
 * to the range of size_t and placed in out, and the function returns true.
 *
 * Another way to think of this is that it returns the carry flag of the
 * subtraction.
 *
 * Use it like this:
 *
 *     size_t x;
 *     if (ghost_checked_sub_z(&x, a, b)) {
 *         // Subtraction failed! Handle error here
 *     }
 *
 * Or like this:
 *
 *     size_t x;
 *     ghost_ensure(!ghost_checked_sub_z(&x, a, b), "overflow");
 *
 * @return The carry flag of the subtraction: true if it overflowed, false if the
 *         result is correct
 */
bool ghost_checked_sub_z(size_t* out, size_t a, size_t b);
#define ghost_has_ghost_checked_sub_z 1
#endif

#ifndef ghost_has_ghost_checked_sub_z
    #ifdef ghost_checked_sub_z
        #define ghost_has_ghost_checked_sub_z 1
    #endif
#endif

/* We need ghost_size_t. */
#ifndef ghost_has_ghost_checked_sub_z
    #include "ghost/type/size_t/ghost_size_t.h"
    #if !ghost_has(ghost_size_t)
        #define ghost_has_ghost_checked_sub_z 0
    #endif
#endif

/*
 * C23 will have type-generic ckd_sub(). ghost_checked_sub_*() are modeled
 * after its behaviour and argument order, except we don't support differing
 * types: the types of all arguments must match. We do this to make it easier
 * to implement in plain C, and because Ghost is just generally more strongly
 * typed than the C standard library.
 *
 * (We also don't leave out random letters from the name. Is it "chk" or "ckd"
 * or "chd" or something else? I keep forgetting. This is madness.)
 */
#ifndef ghost_has_ghost_checked_sub_z
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION > 202000L && GHOST_IMPL_ENABLE_C23
            #include "ghost/header/c/ghost_stdckdint_h.h"
            #ifdef ckd_sub
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/type/bool/ghost_bool.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_bool ghost_checked_sub_z(
                        ghost_size_t* ghost_impl_v_out,
                        ghost_size_t ghost_impl_v_a,
                        ghost_size_t ghost_impl_v_b)
                {
                    return ckd_sub(
                            ghost_impl_v_out,
                            ghost_impl_v_a,
                            ghost_impl_v_b);
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_checked_sub_z 1
            #endif
        #endif
    #endif
#endif

/* GNU C compilers have a type-generic __builtin_sub_overflow(). (GCC also has
 * type-specific functions __builtin_<type>sub_overflow() for basic types but
 * we don't bother to wrap them right now because we'd have to convert from
 * basic types to fixed-width types.) */
#ifndef ghost_has_ghost_checked_sub_z
    #include "ghost/impl/math/ghost_impl_has_builtin_sub_overflow.h"
    #if GHOST_IMPL_HAS_BUILTIN_SUB_OVERFLOW
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        ghost_bool ghost_checked_sub_z(
                ghost_size_t* ghost_impl_v_out,
                ghost_size_t ghost_impl_v_a,
                ghost_size_t ghost_impl_v_b)
        {
            return __builtin_sub_overflow(
                    ghost_impl_v_a,
                    ghost_impl_v_b,
                    ghost_impl_v_out);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_checked_sub_z 1
    #endif
#endif

/*
 * MSVC and Intel have _subborrow_u32() and _subborrow_u64() on x86 and amd64
 * processors.
 *
 *     https://docs.microsoft.com/en-us/cpp/intrinsics/x86-intrinsics-list
 *     https://docs.microsoft.com/en-us/cpp/intrinsics/x64-amd64-intrinsics-list
 *     https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_subborrow_u32&ig_expand=196
 *     https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_subborrow_u64&ig_expand=197
 *
 * Note that we don't bother with _subborrowx_*() at the moment since they
 * require ADX processors. While almost all modern processors have this, Ghost
 * is meant to run on anything. We are more concerned with correctness than
 * performance and we don't want to have to handle the case of it not existing.
 */
/* TODO _subborrow_u64() is only available in x86_64, need to split this up */
/*TODO only on VS2015+ (or maybe VS2013?)*/
#if 0
#ifndef ghost_has_ghost_checked_sub_z
    #include "ghost/detect/ghost_x86_32.h"
    #include "ghost/detect/ghost_x86_64.h"
    #if (GHOST_X86_32 || GHOST_X86_64) && \
            (defined(_MSC_VER) || defined(__INTEL_COMPILER))
        #ifdef _MSC_VER
            #include <intrin.h>
            #if GHOST_X86_32
                #pragma intrinsic(_subborrow_u32)
            #elif GHOST_X86_64
                #pragma intrinsic(_subborrow_u64)
            #else
                #error
            #endif
        #elif defined(__INTEL_COMPILER)
            #include <immintrin.h>
        #else
            #error
        #endif

        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/type/int32_t/ghost_int32_t.h"
        #include "ghost/type/uint32_t/ghost_uint32_t.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        ghost_bool ghost_checked_sub_z(
                ghost_size_t* ghost_impl_v_out,
                ghost_size_t ghost_impl_v_a,
                ghost_size_t ghost_impl_v_b)
        {
            return !!
                #if GHOST_X86_32
                    _subborrow_u32
                #elif GHOST_X86_64
                    _subborrow_u64
                #else
                    #error
                #endif
                (
                    0,
                    ghost_impl_v_a,
                    ghost_impl_v_b,
                    ghost_impl_v_out);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_checked_sub_z 1
    #endif
#endif
#endif

/* Plain C implementation */
#ifndef ghost_has_ghost_checked_sub_z
    #include "ghost/type/size_t/ghost_size_t.h"
    #if ghost_has(ghost_size_t)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/bool/ghost_bool.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_bool ghost_checked_sub_z(
                ghost_size_t* ghost_impl_v_out,
                ghost_size_t ghost_impl_v_a,
                ghost_size_t ghost_impl_v_b)
        {
            ghost_size_t ghost_impl_v_result = ghost_impl_v_a + ghost_impl_v_b;
            *ghost_impl_v_out = ghost_impl_v_result;
            return ghost_impl_v_result < ghost_impl_v_a;
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_checked_sub_z 1
    #endif
#endif

#ifndef ghost_has_ghost_checked_sub_z
    #define ghost_has_ghost_checked_sub_z 0
#endif

#endif
