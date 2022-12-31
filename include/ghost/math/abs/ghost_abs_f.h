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

#ifndef GHOST_ABS_F_H_INCLUDED
#define GHOST_ABS_F_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the absolute value of the given float.
 */
float ghost_abs_f(float);
#endif

/* Allow override */
#ifndef ghost_has_ghost_abs_f
    #ifdef ghost_abs_f
        #define ghost_has_ghost_abs_f 1
    #endif
#endif

/* We need float. */
#ifndef ghost_has_ghost_abs_f
    #include "ghost/type/float/ghost_float.h"
    #if !ghost_has(ghost_float)
        #define ghost_has_ghost_abs_f 0
    #endif
#endif

/* GNU C compilers have a builtin. */
#ifndef ghost_has_ghost_abs_f
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_fabsf)
            #define ghost_abs_f __builtin_fabsf
            #define ghost_has_ghost_abs_f 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_abs_f __builtin_fabsf
            #define ghost_has_ghost_abs_f 1
        #endif
    #endif
#endif

/* The rest of our implementations will require <math.h>. */
#ifndef ghost_has_ghost_abs_f
    #include "ghost/header/c/ghost_math_h.h"
    #if !ghost_has(ghost_math_h)
        #define ghost_has_ghost_abs_f 0
    #endif
#endif

/* fabsf() does exactly what we want. It's only available in C99 and C++11. */
#ifndef ghost_has_ghost_abs_f
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define ghost_abs_f ::std::fabsf
            #define ghost_has_ghost_abs_f 1
        #endif
    #else
        #include "ghost/language/ghost_stdc_version.h"
        #ifdef GHOST_STDC_VERSION
            #if GHOST_STDC_VERSION >= 199901L
                #define ghost_abs_f fabsf
                #define ghost_has_ghost_abs_f 1
            #endif
        #endif
    #endif
#endif

/* C++ has an overloaded abs() function. We wrap it to make sure it's actually
 * being used on a float. */
#ifndef ghost_has_ghost_abs_f
    #ifdef __cplusplus
        #include "ghost/impl/ghost_impl_always_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        float ghost_abs_f(float ghost_impl_x) {
            /* No casts here. This should take and return float, not double. */
            return ::std::abs(ghost_impl_x);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_abs_f 1
    #endif
#endif

/* C89 only had fabs() which uses doubles. We wrap it and explicitly cast to
 * float. */
#ifndef ghost_has_ghost_abs_f
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/type/double/ghost_double.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    float ghost_abs_f(float ghost_impl_x) {
        #if ghost_has(ghost_double)
            return ghost_static_cast(float, fabs(ghost_static_cast(double, ghost_impl_x)));
        #else
            /* If for some weird reason we have float but not double, we'll
             * still assume fabs() exists; we just won't cast to double. */
            return ghost_static_cast(float, fabs(ghost_impl_x));
        #endif
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_abs_f 1
#endif

#endif
