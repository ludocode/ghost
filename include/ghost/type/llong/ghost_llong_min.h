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

#ifndef GHOST_LLONG_MIN_H_INCLUDED
#define GHOST_LLONG_MIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_LLONG_MIN LLONG_MIN
 *
 * The minimum value of (signed) `long long`.
 *
 * This may cause a -Wlong-long warning on GNU C compilers in older language
 * standards where `long long` is an extension. You should probably disable or
 * silence this warning if you intend to use this in older language standards.
 *
 * @see GHOST_SILENCE_LONG_LONG
 */
#endif

#ifndef ghost_has_GHOST_LLONG_MIN
    #ifdef GHOST_LLONG_MIN
        #define ghost_has_GHOST_LLONG_MIN 1
    #endif
#endif

#ifndef ghost_has_GHOST_LLONG_MIN
    #include "ghost/type/llong/ghost_llong.h"
    #if !ghost_has(ghost_llong)
        #define ghost_has_GHOST_LLONG_MIN 0
    #endif
#endif

/* <limits.h> has LLONG_MIN in C99. It might be backported. */
#ifndef ghost_has_GHOST_LLONG_MIN
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef LLONG_MIN
        #define GHOST_LLONG_MIN LLONG_MIN
        #define ghost_has_GHOST_LLONG_MIN 1
    #endif
#endif

/* Calculate min from max, assuming two's complement */
#ifndef ghost_has_GHOST_LLONG_MIN
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
        #include "ghost/type/llong/ghost_llong_max.h"
        #if ghost_has(GHOST_LLONG_MAX)
            #define GHOST_LLONG_MIN (-1 - GHOST_LLONG_MAX)
            #define ghost_has_GHOST_LLONG_MIN 1
        #endif
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_LLONG_MIN
    #define ghost_has_GHOST_LLONG_MIN 0
#endif

/* Test min from max, assuming two's complement */
#if ghost_has(GHOST_LLONG_MIN)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
        #include "ghost/type/llong/ghost_llong_max.h"
        #if ghost_has(GHOST_LLONG_MAX)
            #include "ghost/silence/ghost_silence_push_pop.h"
            #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
                #include "ghost/silence/ghost_silence_long_long.h"
                GHOST_SILENCE_PUSH
                GHOST_SILENCE_LONG_LONG
            #endif

            #include "ghost/debug/ghost_static_assert.h"
            #include "ghost/language/ghost_static_cast.h"
            ghost_static_assert(GHOST_LLONG_MIN == -1LL - GHOST_LLONG_MAX,
                    "GHOST_LLONG_MIN is incorrect");

            #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
                GHOST_SILENCE_POP
            #endif
        #endif
    #endif
#endif

#endif
