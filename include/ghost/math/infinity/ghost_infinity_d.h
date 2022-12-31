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

#ifndef GHOST_INFINITY_D_H_INCLUDED
#define GHOST_INFINITY_D_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INFINITY_D
 *
 * A constant of type double representing floating-point positive infinity.
 */
#endif

/* This requires double. */
#ifndef ghost_has_GHOST_INFINITY_D
    #include "ghost/type/double/ghost_double.h"
    #if !ghost_has(ghost_double)
        #define ghost_has_GHOST_INFINITY_D 0
    #endif
#endif

/* In C++ we use std::numeric_limits. */
#ifndef ghost_has_GHOST_INFINITY_D
    #ifdef __cplusplus
        #include "ghost/header/cxx/ghost_cxx_limits_h.h"
        #if ghost_has(ghost_cxx_limits_h)
            #define GHOST_INFINITY_D (std::numeric_limits<double>::infinity())
            #define ghost_has_GHOST_INFINITY_D 1
        #endif
    #endif
#endif

/* GCC and Clang have __builtin_inf(). */
#ifndef ghost_has_GHOST_INFINITY_D
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_inf)
            #define GHOST_INFINITY_D (__builtin_inf())
            #define ghost_has_GHOST_INFINITY_D 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define GHOST_INFINITY_D (__builtin_inf())
            #define ghost_has_GHOST_INFINITY_D 1
        #endif
    #endif
#endif

/* Under MSVC we use a wrapper function to silence warnings about constant
 * arithmetic overflow. */
#ifndef ghost_has_GHOST_INFINITY_D
    #ifdef _MSC_VER
        #include "ghost/header/c/ghost_math_h.h"
        #ifdef INFINITY
            #pragma warning(push)
            #pragma warning(disable:4056) // overflow in floating-point constant arithmetic
            #pragma warning(disable:4756) // overflow in constant arithmetic
            #include "ghost/impl/ghost_impl_always_inline.h"
            #include "ghost/language/ghost_static_cast.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            double ghost_impl_infinity_d(void) {
                return ghost_static_cast(double, (INFINITY));
            }
            GHOST_IMPL_FUNCTION_CLOSE
            #pragma warning(pop)
            #define GHOST_INFINITY_D (ghost_impl_infinity_d())
            #define ghost_has_GHOST_INFINITY_D 1
        #endif
    #endif
#endif

/*
 * INFINITY is in C99. It is often backported to C89. It's required to be a
 * macro so we can check whether it's defined.
 *
 * It's supposed to be a constant of type float. Casting it to double should
 * preserve the infinity.
 *
 * It is possible the implementation does not support floating point
 * infinities, in which case INFINITY may (or must?) be defined to a value that
 * causes a compiler warning. We should detect such platforms and disable this.
 */
#ifndef ghost_has_GHOST_INFINITY_D
    #include "ghost/header/c/ghost_math_h.h"
    #ifdef INFINITY
        #include "ghost/language/ghost_static_cast.h"
        #define GHOST_INFINITY_D ghost_static_cast(double, (INFINITY))
        #define ghost_has_GHOST_INFINITY_D 1
    #endif
#endif

/*
 * If the floating point implementation is IEEE 754, we could generate our own
 * infinity by specifying the appropriate hex and bitcasting it to double. We
 * don't bother doing this (yet.)
 */

/* Otherwise we don't have infinity. */
#ifndef ghost_has_GHOST_INFINITY_D
    #define ghost_has_GHOST_INFINITY_D 0
#endif

#endif
