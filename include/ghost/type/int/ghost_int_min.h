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

#ifndef GHOST_INT_MIN_H_INCLUDED
#define GHOST_INT_MIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_INT_MIN INT_MIN
 *
 * The minimum value of signed int.
 */
#endif

#ifndef ghost_has_GHOST_INT_MIN
    #ifdef GHOST_INT_MIN
        #define ghost_has_GHOST_INT_MIN 1
    #endif
#endif

#ifndef ghost_has_GHOST_INT_WIDTH
    #include "ghost/type/int/ghost_int.h"
    #if !ghost_has(ghost_int)
        #define ghost_has_GHOST_INT_WIDTH 0
    #endif
#endif

/* <limits.h> has INT_MIN */
#ifndef ghost_has_GHOST_INT_MIN
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef INT_MIN
        #define GHOST_INT_MIN INT_MIN
        #define ghost_has_GHOST_INT_MIN 1
    #endif
#endif

/* Calculate min from max, assuming two's complement */
#ifndef ghost_has_GHOST_INT_MIN
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
        #include "ghost/type/int/ghost_int_max.h"
        #if ghost_has(GHOST_INT_MAX)
            #define GHOST_INT_MIN (-1 - GHOST_INT_MAX)
            #define ghost_has_GHOST_INT_MIN 1
        #endif
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_INT_MIN
    #define ghost_has_GHOST_INT_MIN 0
#endif

/* Test min from max, assuming two's complement */
#if ghost_has(GHOST_INT_MIN)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
        #include "ghost/type/int/ghost_int_max.h"
        #if ghost_has(GHOST_INT_MAX)
            #include "ghost/debug/ghost_static_assert.h"
            #include "ghost/language/ghost_static_cast.h"
            ghost_static_assert(GHOST_INT_MIN == -1 - GHOST_INT_MAX,
                    "GHOST_INT_MIN is incorrect");
        #endif
    #endif
#endif

#endif
