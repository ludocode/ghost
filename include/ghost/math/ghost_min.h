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

#ifndef GHOST_MIN_H_INCLUDED
#define GHOST_MIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the lesser of the arguments for any supported type T.
 *
 * The type of each argument must exactly match. This is enforced if _Generic
 * selections are available. In C++ it may be more lax due to type promotion
 * rules but you should not rely on this behaviour.
 */
T ghost_min(T left, T right)
#endif

#ifndef ghost_has_ghost_min
    #ifdef ghost_min
        #define ghost_has_ghost_min 1
    #endif
#endif

/* Use _Generic if possible. */
#ifndef ghost_has_ghost_min
    #include "ghost/language/ghost_generic.h"
    #if ghost_has(ghost_generic)
        #include "ghost/math/min/ghost_min_sc.h"
        #include "ghost/math/min/ghost_min_uc.h"
        #include "ghost/math/min/ghost_min_h.h"
        #include "ghost/math/min/ghost_min_uh.h"
        #include "ghost/math/min/ghost_min_i.h"
        #include "ghost/math/min/ghost_min_u.h"
        #include "ghost/math/min/ghost_min_l.h"
        #include "ghost/math/min/ghost_min_ul.h"
        #include "ghost/math/min/ghost_min_ll.h"
        #include "ghost/math/min/ghost_min_ull.h"
        #include "ghost/math/min/ghost_min_f.h"
        #include "ghost/math/min/ghost_min_d.h"
        #include "ghost/math/min/ghost_min_ld.h"
        #include "ghost/math/min/ghost_min_c8.h"
        #include "ghost/math/min/ghost_min_c16.h"
        #include "ghost/math/min/ghost_min_c32.h"

        #include "ghost/language/ghost_maybe_unused.h"
        #include "ghost/type/char8_t/ghost_char8_is_distinct.h"
        #include "ghost/type/char16_t/ghost_char16_is_distinct.h"
        #include "ghost/type/char32_t/ghost_char32_is_distinct.h"
        #include "ghost/impl/type/llong/ghost_impl_llong_is_distinct.h"

        #ifdef GHOST_IMPL_MIN_GENERIC_LL
            #error
        #elif ghost_has(ghost_min_ll) && GHOST_IMPL_LLONG_IS_DISTINCT
            #define GHOST_IMPL_MIN_GENERIC_LL(x) , x
        #else
            #define GHOST_IMPL_MIN_GENERIC_LL(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MIN_GENERIC_ULL
            #error
        #elif ghost_has(ghost_min_ull) && GHOST_IMPL_LLONG_IS_DISTINCT
            #define GHOST_IMPL_MIN_GENERIC_ULL(x) , x
        #else
            #define GHOST_IMPL_MIN_GENERIC_ULL(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MIN_GENERIC_F
            #error
        #elif ghost_has(ghost_min_f)
            #define GHOST_IMPL_MIN_GENERIC_F(x) , x
        #else
            #define GHOST_IMPL_MIN_GENERIC_F(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MIN_GENERIC_D
            #error
        #elif ghost_has(ghost_min_d)
            #define GHOST_IMPL_MIN_GENERIC_D(x) , x
        #else
            #define GHOST_IMPL_MIN_GENERIC_D(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MIN_GENERIC_LD
            #error
        #elif ghost_has(ghost_min_ld)
            #define GHOST_IMPL_MIN_GENERIC_LD(x) , x
        #else
            #define GHOST_IMPL_MIN_GENERIC_LD(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MIN_GENERIC_C8
            #error
        #elif ghost_has(ghost_min_c8) && GHOST_CHAR8_IS_DISTINCT
            #define GHOST_IMPL_MIN_GENERIC_C8(x) , x
        #else
            #define GHOST_IMPL_MIN_GENERIC_C8(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MIN_GENERIC_C16
            #error
        #elif ghost_has(ghost_min_c16) && GHOST_CHAR16_IS_DISTINCT
            #define GHOST_IMPL_MIN_GENERIC_C16(x) , x
        #else
            #define GHOST_IMPL_MIN_GENERIC_C16(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MIN_GENERIC_C32
            #error
        #elif ghost_has(ghost_min_c32) && GHOST_CHAR32_IS_DISTINCT
            #define GHOST_IMPL_MIN_GENERIC_C32(x) , x
        #else
            #define GHOST_IMPL_MIN_GENERIC_C32(x) /*nothing*/
        #endif

        /* Note that very old versions of Clang (<3.8) don't properly strip
         * const and volatile from types in _Generic selections. Ghost doesn't
         * bother to work around this so you may get errors on these old
         * compilers. */

        /* no arguments to these functions, causing a compiler error if types don't match */
        ghost_maybe_unused static void GHOST_MIN_ERROR_UNMATCHED_TYPES(void) {}
        ghost_maybe_unused static void GHOST_MIN_ERROR_UNHANDLED_TYPE(void) {}

        /* Note about char: We should be able to put it in here because it is
         * supposed to be distinct from both signed char and unsigned char but
         * PCC complains. It doesn't seem to hurt anything to leave it off. */

        #define ghost_min(a, b) \
            ghost_generic((a), \
                /*char: ghost_generic((b), char: ghost_min_c, default: GHOST_MIN_ERROR_UNMATCHED_TYPES),*/ \
                signed char: ghost_generic((b), signed char: ghost_min_sc, default: GHOST_MIN_ERROR_UNMATCHED_TYPES), \
                unsigned char: ghost_generic((b), unsigned char: ghost_min_uc, default: GHOST_MIN_ERROR_UNMATCHED_TYPES), \
                short: ghost_generic((b), short: ghost_min_h, default: GHOST_MIN_ERROR_UNMATCHED_TYPES), \
                unsigned short: ghost_generic((b), unsigned short: ghost_min_uh, default: GHOST_MIN_ERROR_UNMATCHED_TYPES), \
                int: ghost_generic((b), int: ghost_min_i, default: GHOST_MIN_ERROR_UNMATCHED_TYPES), \
                unsigned int: ghost_generic((b), unsigned int: ghost_min_u, default: GHOST_MIN_ERROR_UNMATCHED_TYPES), \
                long: ghost_generic((b), long: ghost_min_l, default: GHOST_MIN_ERROR_UNMATCHED_TYPES), \
                unsigned long: ghost_generic((b), unsigned long: ghost_min_ul, default: GHOST_MIN_ERROR_UNMATCHED_TYPES) \
                GHOST_IMPL_MIN_GENERIC_LL(long long: ghost_generic((b), long long: ghost_min_ll, default: GHOST_MIN_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MIN_GENERIC_ULL(unsigned long long: ghost_generic((b), unsigned long long: ghost_min_ull, default: GHOST_MIN_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MIN_GENERIC_F(float: ghost_generic((b), float: ghost_min_f, default: GHOST_MIN_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MIN_GENERIC_D(double: ghost_generic((b), double: ghost_min_d, default: GHOST_MIN_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MIN_GENERIC_LD(long double: ghost_generic((b), long double: ghost_min_ld, default: GHOST_MIN_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MIN_GENERIC_C8(ghost_char8_t: ghost_generic((b), ghost_char8_t: ghost_min_c8, default: GHOST_MIN_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MIN_GENERIC_C16(ghost_char16_t: ghost_generic((b), ghost_char16_t: ghost_min_c16, default: GHOST_MIN_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MIN_GENERIC_C32(ghost_char32_t: ghost_generic((b), ghost_char32_t: ghost_min_c32, default: GHOST_MIN_ERROR_UNMATCHED_TYPES)) \
                , default: GHOST_MIN_ERROR_UNHANDLED_TYPE \
            )(a, b)

        #define ghost_has_ghost_min 1
    #endif
#endif

/* In C++ we can define function overloads. */
#ifndef ghost_has_ghost_min
    #ifdef __cplusplus
        #include "ghost/math/min/ghost_min_c.h"
        #include "ghost/math/min/ghost_min_sc.h"
        #include "ghost/math/min/ghost_min_uc.h"
        #include "ghost/math/min/ghost_min_h.h"
        #include "ghost/math/min/ghost_min_uh.h"
        #include "ghost/math/min/ghost_min_i.h"
        #include "ghost/math/min/ghost_min_u.h"
        #include "ghost/math/min/ghost_min_l.h"
        #include "ghost/math/min/ghost_min_ul.h"
        #include "ghost/math/min/ghost_min_ll.h"
        #include "ghost/math/min/ghost_min_ull.h"
        #include "ghost/math/min/ghost_min_f.h"
        #include "ghost/math/min/ghost_min_d.h"
        #include "ghost/math/min/ghost_min_ld.h"
        #include "ghost/math/min/ghost_min_c8.h"
        #include "ghost/math/min/ghost_min_c16.h"
        #include "ghost/math/min/ghost_min_c32.h"

        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/char8_t/ghost_char8_is_distinct.h"
        #include "ghost/type/char16_t/ghost_char16_is_distinct.h"
        #include "ghost/type/char32_t/ghost_char32_is_distinct.h"

        GHOST_IMPL_CXX_FUNCTION_OPEN

        ghost_impl_always_inline
        char ghost_min(char a, char b) {
            return ghost_min_c(a, b);
        }

        ghost_impl_always_inline
        signed char ghost_min(signed char a, signed char b) {
            return ghost_min_sc(a, b);
        }

        ghost_impl_always_inline
        unsigned char ghost_min(unsigned char a, unsigned char b) {
            return ghost_min_uc(a, b);
        }

        ghost_impl_always_inline
        short ghost_min(short a, short b) {
            return ghost_min_h(a, b);
        }

        ghost_impl_always_inline
        unsigned short ghost_min(unsigned short a, unsigned short b) {
            return ghost_min_uh(a, b);
        }

        ghost_impl_always_inline
        int ghost_min(int a, int b) {
            return ghost_min_i(a, b);
        }

        ghost_impl_always_inline
        unsigned ghost_min(unsigned a, unsigned b) {
            return ghost_min_u(a, b);
        }

        ghost_impl_always_inline
        long ghost_min(long a, long b) {
            return ghost_min_l(a, b);
        }

        ghost_impl_always_inline
        unsigned long ghost_min(unsigned long a, unsigned long b) {
            return ghost_min_ul(a, b);
        }

        #if ghost_has(ghost_min_ll)
            ghost_impl_always_inline
            long long ghost_min(long long a, long long b) {
                return ghost_min_ll(a, b);
            }
        #endif

        #if ghost_has(ghost_min_ull)
            ghost_impl_always_inline
            unsigned long long ghost_min(unsigned long long a, unsigned long long b) {
                return ghost_min_ull(a, b);
            }
        #endif

        #if ghost_has(ghost_min_f)
            ghost_impl_always_inline
            float ghost_min(float a, float b) {
                return ghost_min_f(a, b);
            }
        #endif

        #if ghost_has(ghost_min_d)
            ghost_impl_always_inline
            double ghost_min(double a, double b) {
                return ghost_min_d(a, b);
            }
        #endif

        #if ghost_has(ghost_min_ld)
            ghost_impl_always_inline
            long double ghost_min(long double a, long double b) {
                return ghost_min_ld(a, b);
            }
        #endif

        #if ghost_has(ghost_min_c8) && GHOST_CHAR8_IS_DISTINCT
            ghost_impl_always_inline
            ghost_char8_t ghost_min(ghost_char8_t a, ghost_char8_t b) {
                return ghost_min_c8(a, b);
            }
        #endif

        #if ghost_has(ghost_min_c16) && GHOST_CHAR16_IS_DISTINCT
            ghost_impl_always_inline
            ghost_char16_t ghost_min(ghost_char16_t a, ghost_char16_t b) {
                return ghost_min_c16(a, b);
            }
        #endif

        #if ghost_has(ghost_min_c32) && GHOST_CHAR32_IS_DISTINCT
            ghost_impl_always_inline
            ghost_char32_t ghost_min(ghost_char32_t a, ghost_char32_t b) {
                return ghost_min_c32(a, b);
            }
        #endif

        GHOST_IMPL_CXX_FUNCTION_CLOSE
        #define ghost_has_ghost_min 1
    #endif
#endif

#ifndef ghost_has_ghost_min
    #define ghost_has_ghost_min 0
#endif

#endif
