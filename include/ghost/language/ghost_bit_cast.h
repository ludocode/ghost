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

#ifndef GHOST_BIT_CAST_H_INCLUDED
#define GHOST_BIT_CAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_bit_cast(To, From, x)
 *
 * Converts x bitwise from the From type to the To type as if by memcpy().
 *
 * The types must have the same size.
 *
 * In C89 without extensions, x must be an l-value. (The only way to implement
 * this as an expression in C89 is to take the value's address.)
 */
#endif

#ifndef ghost_has_ghost_bit_cast
    #ifdef ghost_bit_cast
        #define ghost_has_ghost_bit_cast 1
    #endif
#endif

/*
 * C++20 has std::bit_cast in header <bit>. It's possible that the header won't
 * define std::bit_cast unless we're C++20 even if <bit> exists. For this
 * reason we require both. This could be expanded to detect platforms that
 * backport it.
 * (Also, __cpp_lib_bit_cast should be defined to 201806L in <version>; TODO check this.)
 */
#ifndef ghost_has_ghost_bit_cast
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 202002L
            #include "ghost/header/cxx/ghost_cxx_bit_h.h"
            #if ghost_has(ghost_cxx_bit_h)
                #define ghost_bit_cast(To, From, x) std::bit_cast<To, From>(x)
                #define ghost_has_ghost_bit_cast 1
            #endif
        #endif
    #endif
#endif

/* In older C++ we can use a template implementation similar to std::bit_cast.
 * We don't bother to make it constexpr for now. We use ghost_memcpy which will
 * be mapped to an intrinsic where possible so compilers should optimize this
 * properly. */
#ifndef ghost_has_ghost_bit_cast
    #ifdef __cplusplus
        #include "ghost/string/ghost_memcpy.h"
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        /*#include "ghost/header/cxx/ghost_cxx_type_traits_h.h"*/

        GHOST_IMPL_CXX_FUNCTION_OPEN
        template <class ghost_impl_v_To, class ghost_impl_v_From>
        ghost_impl_always_inline
        /* TODO cleanup */
        #if 0&&ghost_cplusplus >= 201103L && ghost_has(ghost_cxx_type_traits_h)
            /* Add some safety. ghost_bit_cast() should only exist if To and
             * From types are the same size and trivially copyable. See the
             * example implementation here:
             *     https://en.cppreference.com/w/cpp/numeric/bit_cast
             * TODO We might get better compiler errors if we moved this check into
             * the static assert below. */
            std::enable_if<
                sizeof(ghost_impl_v_To) == sizeof(ghost_impl_v_From) &&
                std::is_trivially_copyable<ghost_impl_v_From>::value &&
                std::is_trivially_copyable<ghost_impl_v_To>::value,
                ghost_impl_v_To>::type
        #else
            ghost_impl_v_To
        #endif
        ghost_bit_cast_impl(ghost_impl_v_From ghost_impl_v_from) {
            ghost_static_assert(sizeof(ghost_impl_v_From) == sizeof(ghost_impl_v_To),
                    "cannot bit_cast between types of different size");
            ghost_impl_v_To ghost_impl_v_to;
            ghost_memcpy(&ghost_impl_v_to, &ghost_impl_v_from, sizeof(ghost_impl_v_To));
            return ghost_impl_v_to;
        }
        GHOST_IMPL_CXX_FUNCTION_CLOSE

        #define ghost_bit_cast(To, From, x) ghost_bit_cast_impl<To, From>(x)
        #define ghost_has_ghost_bit_cast 1
    #endif
#endif

/* In GNU C we use an expression statement and __builtin_memcpy(). Compilers
 * that support this will recognize it as a bit cast and optimize it correctly. */
#ifndef ghost_has_ghost_bit_cast
    #ifdef __GNUC__
        #include "ghost/debug/ghost_static_assert.h"
        #define ghost_bit_cast(To, From, x) ( __extension__ ({ \
                    ghost_static_assert(sizeof(From) == sizeof(To), \
                            "cannot bit_cast between types of different size"); \
                    To ghost_impl_v_to; \
                    From ghost_impl_v_from = (x); \
                    __builtin_memcpy(&ghost_impl_v_to, &ghost_impl_v_from, sizeof(ghost_impl_v_to)); \
                    ghost_impl_v_to; \
                }))
        #define ghost_has_ghost_bit_cast 1
    #endif
#endif

/*
 * Otherwise we do the conversion through a union with a compound literal.
 * Compound literals are only available in C99 but ghost_compound_literal()
 * may be available as an extension.
 *
 * In C99, type punning through a union is legal:
 *
 *     https://en.cppreference.com/w/c/language/union
 *
 * (This is technically undefined behaviour in C89 and C++ but compilers for
 * both languages commonly support it as an extension.)
 */
#ifndef ghost_has_ghost_bit_cast
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 199901L
            #include "ghost/language/ghost_compound_literal.h"
            #if ghost_has(ghost_compound_literal)
                #include "ghost/debug/ghost_static_assert_expr.h"
                #define ghost_bit_cast(To, From, x) ( \
                        ghost_static_assert_expr(sizeof(From) == sizeof(To), \
                                "cannot bit_cast between types of different size"), \
                        ghost_compound_literal(union {From ghost_impl_v_from; To ghost_impl_v_to;}, (x)).ghost_impl_v_to \
                    )
                #define ghost_has_ghost_bit_cast 1
            #endif
        #endif
    #endif
#endif

/*
 * In C89 the only way to bit cast as an expression is to take the address and
 * cast pointers. This requires that the argument is an l-value.
 *
 * This is a strict aliasing violation so it's not technically legal C but
 * compilers that would fallback to this (e.g. old MSVC or toy compilers)
 * generally don't do strict aliasing optimizations. Note that GCC, which does
 * optimize based on strict aliasing, will use the safe memcpy expression
 * statement above. We put in ghost_may_alias anyway just in case.
 */
#ifndef ghost_has_ghost_bit_cast
    #include "ghost/type/uintptr_t/ghost_uintptr_t.h"
    #include "ghost/language/ghost_may_alias.h"

    #ifdef _MSC_VER
        #define ghost_bit_cast(To, From, x) ( \
                /* TODO move out this pragma to push/pop */ \
                __pragma(warning(disable:4244)) \
                /*ghost_static_assert_expr(sizeof(From) == sizeof(To),*/ \
                        /*"cannot bit_cast between types of different size"),*/ \
                (*(To ghost_may_alias *)(void*)(From*)(&(x))) \
            )
    #else
        #define ghost_bit_cast(To, From, x) ( \
                (*(To ghost_may_alias *)(void*)(From*)(&(x))) \
            )
    #endif
    #define ghost_has_ghost_bit_cast 1
#endif

#endif
