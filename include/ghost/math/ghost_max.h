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

#ifndef GHOST_MAX_H_INCLUDED
#define GHOST_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the greater of the arguments for any supported type T.
 *
 * The type of each argument must exactly match. This is enforced if _Generic
 * selections are available. In C++ it may be more lax due to type promotion
 * rules but you should not rely on this behaviour.
 */
T ghost_max(T left, T right)
#endif

#ifndef ghost_has_ghost_max
    #ifdef ghost_max
        #define ghost_has_ghost_max 1
    #endif
#endif

/* Use _Generic if possible. */
#ifndef ghost_has_ghost_max
    #include "ghost/language/ghost_generic.h"
    #if ghost_has(ghost_generic)
        #include "ghost/math/max/ghost_max_sc.h"
        #include "ghost/math/max/ghost_max_uc.h"
        #include "ghost/math/max/ghost_max_h.h"
        #include "ghost/math/max/ghost_max_uh.h"
        #include "ghost/math/max/ghost_max_i.h"
        #include "ghost/math/max/ghost_max_u.h"
        #include "ghost/math/max/ghost_max_l.h"
        #include "ghost/math/max/ghost_max_ul.h"
        #include "ghost/math/max/ghost_max_ll.h"
        #include "ghost/math/max/ghost_max_ull.h"
        #include "ghost/math/max/ghost_max_f.h"
        #include "ghost/math/max/ghost_max_d.h"
        #include "ghost/math/max/ghost_max_ld.h"
        #include "ghost/math/max/ghost_max_c8.h"
        #include "ghost/math/max/ghost_max_c16.h"
        #include "ghost/math/max/ghost_max_c32.h"

        #include "ghost/language/ghost_maybe_unused.h"
        #include "ghost/type/char8_t/ghost_char8_is_distinct.h"
        #include "ghost/type/char16_t/ghost_char16_is_distinct.h"
        #include "ghost/type/char32_t/ghost_char32_is_distinct.h"
        #include "ghost/impl/type/llong/ghost_impl_llong_is_distinct.h"

        #ifdef GHOST_IMPL_MAX_GENERIC_LL
            #error
        #elif ghost_has(ghost_max_ll) && GHOST_IMPL_LLONG_IS_DISTINCT
            #define GHOST_IMPL_MAX_GENERIC_LL(x) , x
        #else
            #define GHOST_IMPL_MAX_GENERIC_LL(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MAX_GENERIC_ULL
            #error
        #elif ghost_has(ghost_max_ull) && GHOST_IMPL_LLONG_IS_DISTINCT
            #define GHOST_IMPL_MAX_GENERIC_ULL(x) , x
        #else
            #define GHOST_IMPL_MAX_GENERIC_ULL(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MAX_GENERIC_F
            #error
        #elif ghost_has(ghost_max_f)
            #define GHOST_IMPL_MAX_GENERIC_F(x) , x
        #else
            #define GHOST_IMPL_MAX_GENERIC_F(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MAX_GENERIC_D
            #error
        #elif ghost_has(ghost_max_d)
            #define GHOST_IMPL_MAX_GENERIC_D(x) , x
        #else
            #define GHOST_IMPL_MAX_GENERIC_D(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MAX_GENERIC_LD
            #error
        #elif ghost_has(ghost_max_ld)
            #define GHOST_IMPL_MAX_GENERIC_LD(x) , x
        #else
            #define GHOST_IMPL_MAX_GENERIC_LD(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MAX_GENERIC_C8
            #error
        #elif ghost_has(ghost_max_c8) && GHOST_CHAR8_IS_DISTINCT
            #define GHOST_IMPL_MAX_GENERIC_C8(x) , x
        #else
            #define GHOST_IMPL_MAX_GENERIC_C8(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MAX_GENERIC_C16
            #error
        #elif ghost_has(ghost_max_c16) && GHOST_CHAR16_IS_DISTINCT
            #define GHOST_IMPL_MAX_GENERIC_C16(x) , x
        #else
            #define GHOST_IMPL_MAX_GENERIC_C16(x) /*nothing*/
        #endif

        #ifdef GHOST_IMPL_MAX_GENERIC_C32
            #error
        #elif ghost_has(ghost_max_c32) && GHOST_CHAR32_IS_DISTINCT
            #define GHOST_IMPL_MAX_GENERIC_C32(x) , x
        #else
            #define GHOST_IMPL_MAX_GENERIC_C32(x) /*nothing*/
        #endif

        /* Note that very old versions of Clang (<3.8) don't properly strip
         * const and volatile from types in _Generic selections. Ghost doesn't
         * bother to work around this so you may get errors on these old
         * compilers. */

        /* no arguments to these functions, causing a compiler error if types don't match */
        ghost_maybe_unused static void GHOST_MAX_ERROR_UNMATCHED_TYPES(void) {}
        ghost_maybe_unused static void GHOST_MAX_ERROR_UNHANDLED_TYPE(void) {}

        /* Note about char: We should be able to put it in here because it is
         * supposed to be distinct from both signed char and unsigned char but
         * PCC complains. It doesn't seem to hurt anything to leave it off. */

        #define ghost_max(a, b) \
            ghost_generic((a), \
                /*char: ghost_generic((b), char: ghost_max_c, default: GHOST_MAX_ERROR_UNMATCHED_TYPES),*/ \
                signed char: ghost_generic((b), signed char: ghost_max_sc, default: GHOST_MAX_ERROR_UNMATCHED_TYPES), \
                unsigned char: ghost_generic((b), unsigned char: ghost_max_uc, default: GHOST_MAX_ERROR_UNMATCHED_TYPES), \
                short: ghost_generic((b), short: ghost_max_h, default: GHOST_MAX_ERROR_UNMATCHED_TYPES), \
                unsigned short: ghost_generic((b), unsigned short: ghost_max_uh, default: GHOST_MAX_ERROR_UNMATCHED_TYPES), \
                int: ghost_generic((b), int: ghost_max_i, default: GHOST_MAX_ERROR_UNMATCHED_TYPES), \
                unsigned int: ghost_generic((b), unsigned int: ghost_max_u, default: GHOST_MAX_ERROR_UNMATCHED_TYPES), \
                long: ghost_generic((b), long: ghost_max_l, default: GHOST_MAX_ERROR_UNMATCHED_TYPES), \
                unsigned long: ghost_generic((b), unsigned long: ghost_max_ul, default: GHOST_MAX_ERROR_UNMATCHED_TYPES) \
                GHOST_IMPL_MAX_GENERIC_LL(long long: ghost_generic((b), long long: ghost_max_ll, default: GHOST_MAX_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MAX_GENERIC_ULL(unsigned long long: ghost_generic((b), unsigned long long: ghost_max_ull, default: GHOST_MAX_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MAX_GENERIC_F(float: ghost_generic((b), float: ghost_max_f, default: GHOST_MAX_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MAX_GENERIC_D(double: ghost_generic((b), double: ghost_max_d, default: GHOST_MAX_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MAX_GENERIC_LD(long double: ghost_generic((b), long double: ghost_max_ld, default: GHOST_MAX_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MAX_GENERIC_C8(ghost_char8_t: ghost_generic((b), ghost_char8_t: ghost_max_c8, default: GHOST_MAX_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MAX_GENERIC_C16(ghost_char16_t: ghost_generic((b), ghost_char16_t: ghost_max_c16, default: GHOST_MAX_ERROR_UNMATCHED_TYPES)) \
                GHOST_IMPL_MAX_GENERIC_C32(ghost_char32_t: ghost_generic((b), ghost_char32_t: ghost_max_c32, default: GHOST_MAX_ERROR_UNMATCHED_TYPES)) \
                , default: GHOST_MAX_ERROR_UNHANDLED_TYPE \
            )(a, b)

        #define ghost_has_ghost_max 1
    #endif
#endif

/* In C++ we can define function overloads. */
#ifndef ghost_has_ghost_max
    #ifdef __cplusplus
        #include "ghost/math/max/ghost_max_c.h"
        #include "ghost/math/max/ghost_max_sc.h"
        #include "ghost/math/max/ghost_max_uc.h"
        #include "ghost/math/max/ghost_max_h.h"
        #include "ghost/math/max/ghost_max_uh.h"
        #include "ghost/math/max/ghost_max_i.h"
        #include "ghost/math/max/ghost_max_u.h"
        #include "ghost/math/max/ghost_max_l.h"
        #include "ghost/math/max/ghost_max_ul.h"
        #include "ghost/math/max/ghost_max_ll.h"
        #include "ghost/math/max/ghost_max_ull.h"
        #include "ghost/math/max/ghost_max_f.h"
        #include "ghost/math/max/ghost_max_d.h"
        #include "ghost/math/max/ghost_max_ld.h"
        #include "ghost/math/max/ghost_max_c8.h"
        #include "ghost/math/max/ghost_max_c16.h"
        #include "ghost/math/max/ghost_max_c32.h"

        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/char8_t/ghost_char8_is_distinct.h"
        #include "ghost/type/char16_t/ghost_char16_is_distinct.h"
        #include "ghost/type/char32_t/ghost_char32_is_distinct.h"

        GHOST_IMPL_CXX_FUNCTION_OPEN

        ghost_impl_always_inline
        char ghost_max(char a, char b) {
            return ghost_max_c(a, b);
        }

        ghost_impl_always_inline
        signed char ghost_max(signed char a, signed char b) {
            return ghost_max_sc(a, b);
        }

        ghost_impl_always_inline
        unsigned char ghost_max(unsigned char a, unsigned char b) {
            return ghost_max_uc(a, b);
        }

        ghost_impl_always_inline
        short ghost_max(short a, short b) {
            return ghost_max_h(a, b);
        }

        ghost_impl_always_inline
        unsigned short ghost_max(unsigned short a, unsigned short b) {
            return ghost_max_uh(a, b);
        }

        ghost_impl_always_inline
        int ghost_max(int a, int b) {
            return ghost_max_i(a, b);
        }

        ghost_impl_always_inline
        unsigned ghost_max(unsigned a, unsigned b) {
            return ghost_max_u(a, b);
        }

        ghost_impl_always_inline
        long ghost_max(long a, long b) {
            return ghost_max_l(a, b);
        }

        ghost_impl_always_inline
        unsigned long ghost_max(unsigned long a, unsigned long b) {
            return ghost_max_ul(a, b);
        }

        #if ghost_has(ghost_max_ll)
            ghost_impl_always_inline
            long long ghost_max(long long a, long long b) {
                return ghost_max_ll(a, b);
            }
        #endif

        #if ghost_has(ghost_max_ull)
            ghost_impl_always_inline
            unsigned long long ghost_max(unsigned long long a, unsigned long long b) {
                return ghost_max_ull(a, b);
            }
        #endif

        #if ghost_has(ghost_max_f)
            ghost_impl_always_inline
            float ghost_max(float a, float b) {
                return ghost_max_f(a, b);
            }
        #endif

        #if ghost_has(ghost_max_d)
            ghost_impl_always_inline
            double ghost_max(double a, double b) {
                return ghost_max_d(a, b);
            }
        #endif

        #if ghost_has(ghost_max_ld)
            ghost_impl_always_inline
            long double ghost_max(long double a, long double b) {
                return ghost_max_ld(a, b);
            }
        #endif

        #if ghost_has(ghost_max_c8) && GHOST_CHAR8_IS_DISTINCT
            ghost_impl_always_inline
            ghost_char8_t ghost_max(ghost_char8_t a, ghost_char8_t b) {
                return ghost_max_c8(a, b);
            }
        #endif

        #if ghost_has(ghost_max_c16) && GHOST_CHAR16_IS_DISTINCT
            ghost_impl_always_inline
            ghost_char16_t ghost_max(ghost_char16_t a, ghost_char16_t b) {
                return ghost_max_c16(a, b);
            }
        #endif

        #if ghost_has(ghost_max_c32) && GHOST_CHAR32_IS_DISTINCT
            ghost_impl_always_inline
            ghost_char32_t ghost_max(ghost_char32_t a, ghost_char32_t b) {
                return ghost_max_c32(a, b);
            }
        #endif

        GHOST_IMPL_CXX_FUNCTION_CLOSE
        #define ghost_has_ghost_max 1
    #endif
#endif

#ifndef ghost_has_ghost_max
    #define ghost_has_ghost_max 0
#endif

#endif
