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

#ifndef GHOST_ERRNO_T_H_INCLUDED
#define GHOST_ERRNO_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * An alias of int, matching the behaviour of C11 Annex K errno_t.
 */
typedef errno_t ghost_errno_t;

/* TODO document the constants/macros below */
#endif

/* errno_t in C11 Annex K is a typedef to int. We don't bother to check whether
 * C11 Annex K is available. We just use int. */

/* ghost_errno_t (alias of int) */
#ifndef ghost_has_ghost_errno_t
    #ifndef ghost_errno_t
        typedef int ghost_errno_t;
    #endif
    #define ghost_has_ghost_errno_t 1
#endif

/* GHOST_ERRNO_MIN (alias of GHOST_INT_MIN) */
#ifndef ghost_has_GHOST_ERRNO_MIN
    #ifdef GHOST_ERRNO_MIN
        #define ghost_has_GHOST_ERRNO_MIN 1
    #else
        #include "ghost/type/int/ghost_int_min.h"
        #if ghost_has(GHOST_INT_MIN)
            #define GHOST_ERRNO_MIN GHOST_INT_MIN
            #define ghost_has_GHOST_ERRNO_MIN 1
        #else
            #define ghost_has_GHOST_ERRNO_MIN 0
        #endif
    #endif
#endif

/* GHOST_ERRNO_MAX (alias of GHOST_INT_MAX) */
#ifndef ghost_has_GHOST_ERRNO_MAX
    #ifdef GHOST_ERRNO_MAX
        #define ghost_has_GHOST_ERRNO_MAX 1
    #else
        #include "ghost/type/int/ghost_int_max.h"
        #if ghost_has(GHOST_INT_MAX)
            #define GHOST_ERRNO_MAX GHOST_INT_MAX
            #define ghost_has_GHOST_ERRNO_MAX 1
        #else
            #define ghost_has_GHOST_ERRNO_MAX 0
        #endif
    #endif
#endif

/* GHOST_ERRNO_WIDTH (alias of GHOST_INT_WIDTH) */
#ifndef ghost_has_GHOST_ERRNO_WIDTH
    #ifdef GHOST_ERRNO_WIDTH
        #define ghost_has_GHOST_ERRNO_WIDTH 1
    #else
        #include "ghost/type/int/ghost_int_width.h"
        #if ghost_has(GHOST_INT_WIDTH)
            #define GHOST_ERRNO_WIDTH GHOST_INT_WIDTH
            #define ghost_has_GHOST_ERRNO_WIDTH 1
        #else
            #define ghost_has_GHOST_ERRNO_WIDTH 0
        #endif
    #endif
#endif

/* GHOST_ERRNO_C (alias of GHOST_INT_C) */
#ifndef ghost_has_GHOST_ERRNO_C
    #ifdef GHOST_ERRNO_C
        #define ghost_has_GHOST_ERRNO_C 1
    #else
        #include "ghost/type/int/ghost_int_c.h"
        #if ghost_has(GHOST_INT_C)
            #include "ghost/preprocessor/ghost_cparser_pp.h"
            #if GHOST_CPARSER_PP
                /* Workaround for cparser's busted preprocessor */
                #define GHOST_ERRNO_C(x) GHOST_INT_C(x)
            #else
                #define GHOST_ERRNO_C GHOST_INT_C
            #endif
            #define ghost_has_GHOST_ERRNO_C 1
        #else
            #define ghost_has_GHOST_ERRNO_C 0
        #endif
    #endif
#endif

#endif
