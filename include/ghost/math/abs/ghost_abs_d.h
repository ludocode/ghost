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

#ifndef GHOST_ABS_D_H_INCLUDED
#define GHOST_ABS_D_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the absolute value of the given double.
 */
double ghost_abs_d(double);
#endif

/* Allow override */
#ifndef ghost_has_ghost_abs_d
    #ifdef ghost_abs_d
        #define ghost_has_ghost_abs_d 1
    #endif
#endif

/* We need double. */
#ifndef ghost_has_ghost_abs_d
    #include "ghost/type/double/ghost_double.h"
    #if !ghost_has(ghost_double)
        #define ghost_has_ghost_abs_d 0
    #endif
#endif

/*
 * C++ has an overloaded abs() function for any numeric type and an overloaded
 * fabs() function for floating-point types. We prefer fabs() to match C and to
 * reduce the amount of overloading.
 *
 * In C99 or later when <tgmath.h> has been included, fabs() is a type-generic
 * macro. Otherwise fabs() is a function that takes and returns double.
 *
 * GNU C compilers have a builtin for fabs() but since they need to replicate
 * the behaviour of fabs() under <tgmath.h>, it is (probably) type-generic as
 * well.
 *
 * We need to undo all of this nonsense to get a proper strongly-typed
 * function. In all cases we want to make sure our function only takes doubles
 * so we always wrap it.
 */

/* First figure out whether we have the builtin */
#ifdef GHOST_IMPL_ABS_D_BUILTIN
    #error
#endif
#ifndef ghost_has_ghost_abs_d
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_fabs)
            #define GHOST_IMPL_ABS_D_BUILTIN
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define GHOST_IMPL_ABS_D_BUILTIN
        #endif
    #endif
#endif

/* Require <math.h> if we don't have the builtin. */
#ifndef ghost_has_ghost_abs_d
    #ifndef GHOST_IMPL_ABS_D_BUILTIN
        #include "ghost/header/c/ghost_math_h.h"
        #if !ghost_has(ghost_math_h)
            #define ghost_has_ghost_abs_d 0
        #endif
    #endif
#endif

/* Define our wrapper */
#ifndef ghost_has_ghost_abs_d
    #include "ghost/impl/ghost_impl_always_inline.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    double ghost_abs_d(double ghost_impl_v_x) {
        /* No casts here. This should take and return double. */
        #ifdef GHOST_IMPL_ABS_D_BUILTIN
            return __builtin_fabs(ghost_impl_v_x);
        #elif defined(__cplusplus)
            return ::std::fabs(ghost_impl_v_x);
        #else
            /* May or may not be type-generic; doesn't matter because we're
             * taking and returning double. */
            return fabs(ghost_impl_v_x);
        #endif
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_abs_d 1
#endif

#undef GHOST_IMPL_ABS_D_BUILTIN

#endif
