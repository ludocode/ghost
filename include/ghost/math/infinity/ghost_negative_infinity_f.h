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

#ifndef GHOST_NEGATIVE_INFINITY_F_H_INCLUDED
#define GHOST_NEGATIVE_INFINITY_F_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_NEGATIVE_INFINITY_F
 *
 * A constant of type float representing floating-point negative infinity.
 *
 * This exists because some compilers will issue constant overflow warnings on
 * expressions like `(-INFINITY)`. In particular, some versions of Visual
 * Studio under /W4 warn about this.
 *
 * You don't have to use this if you aren't worried about such warnings. You
 * can just use (-INFINITY) or (-GHOST_INFINITY_F).
 */
#endif

/* This requires float. */
#ifndef ghost_has_GHOST_INFINITY_F
    #include "ghost/type/float/ghost_float.h"
    #if !ghost_has(ghost_float)
        #define ghost_has_GHOST_INFINITY_F 0
    #endif
#endif

/* Under MSVC we use a wrapper function to silence warnings about constant
 * arithmetic overflow. */
#ifndef ghost_has_GHOST_NEGATIVE_INFINITY_F
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
            float ghost_impl_negative_infinity_f(void) {
                return -ghost_static_cast(float, (INFINITY));
            }
            GHOST_IMPL_FUNCTION_CLOSE
            #pragma warning(pop)
            #define GHOST_NEGATIVE_INFINITY_F (ghost_impl_negative_infinity_f())
            #define ghost_has_GHOST_NEGATIVE_INFINITY_F 1
        #endif
    #endif
#endif

/* Otherwise we wrap the positive infinity. */
#ifndef ghost_has_GHOST_NEGATIVE_INFINITY_F
    #include "ghost/math/infinity/ghost_infinity_f.h"
    #if ghost_has(GHOST_INFINITY_F)
        #define GHOST_NEGATIVE_INFINITY_F (-GHOST_INFINITY_F)
        #define ghost_has_GHOST_NEGATIVE_INFINITY_F 1
    #endif
#endif

#ifndef ghost_has_GHOST_NEGATIVE_INFINITY_F
    #define ghost_has_GHOST_NEGATIVE_INFINITY_F 0
#endif

#endif
