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

#ifndef GHOST_SIZE_C_H_INCLUDED
#define GHOST_SIZE_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SIZE_C(x) x
 *
 * Defines a preprocessor constant of type ghost_size_t.
 */
#define ghost_has_GHOST_SIZE_C 1
#endif

/* For some reason there is no SIZE_C() in C. */

/* C++23 will add a Z suffix for size_t-sized integer literals. */
#ifndef ghost_has_GHOST_SIZE_C
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus > 202000L && GHOST_ENABLE_CXX23
            #define GHOST_SIZE_C(x) x ## UZ
            #define ghost_has_GHOST_SIZE_C 1
        #endif
    #endif
#endif

/* Otherwise we try to check widths */

/* Check if int is the correct width */
#ifndef ghost_has_GHOST_SIZE_C
    #include "ghost/type/size_t/ghost_size_width.h"
    #ifdef GHOST_SIZE_WIDTH
        #include "ghost/type/int/ghost_int_width.h"
        #if ghost_has_GHOST_INT_WIDTH
            #if GHOST_SIZE_WIDTH == GHOST_INT_WIDTH
                #define GHOST_SIZE_C(x) x ## U
                #define ghost_has_GHOST_SIZE_C 1
            #endif
        #endif
    #endif
#endif

/* Check if long is the correct width */
#ifndef ghost_has_GHOST_SIZE_C
    #ifdef GHOST_SIZE_WIDTH
        #include "ghost/type/long/ghost_long_width.h"
        #if ghost_has_GHOST_LONG_WIDTH
            #if GHOST_SIZE_WIDTH == GHOST_LONG_WIDTH
                #define GHOST_SIZE_C(x) x ## UL
                #define ghost_has_GHOST_SIZE_C 1
            #endif
        #endif
    #endif
#endif

/* Check if long long is the correct width */
#ifndef ghost_has_GHOST_SIZE_C
    #ifdef GHOST_SIZE_WIDTH
        #include "ghost/type/llong/ghost_llong_width.h"
        #if ghost_has_GHOST_LLONG_WIDTH
            #if GHOST_SIZE_WIDTH == GHOST_LLONG_WIDTH
                #define GHOST_SIZE_C(x) x ## ULL
                #define ghost_has_GHOST_SIZE_C 1
            #endif
        #endif
    #endif
#endif

/* If we still haven't figured out a suffix that fits, we use the biggest
 * suffix we can. This may cause truncation warnings. */
#ifndef ghost_has_GHOST_SIZE_C
    #include "ghost/type/llong/ghost_llong.h"
    #if ghost_has(ghost_llong)
        #define GHOST_SIZE_C(x) x ## ULL
    #else
        #define GHOST_SIZE_C(x) x ## UL
    #endif
    #define ghost_has_GHOST_SIZE_C 1
#endif

#endif
