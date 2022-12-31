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

#ifndef GHOST_LLONG_MAX_H_INCLUDED
#define GHOST_LLONG_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_LLONG_MAX LLONG_MAX
 *
 * The maximum value of (signed) `long long`.
 *
 * This may cause a -Wlong-long warning on GNU C compilers in older language
 * standards where `long long` is an extension. You should probably disable or
 * silence this warning if you intend to use this in older language standards.
 *
 * @see GHOST_SILENCE_LONG_LONG
 */
#endif

#ifndef ghost_has_GHOST_LLONG_MAX
    #ifdef GHOST_LLONG_MAX
        #define ghost_has_GHOST_LLONG_MAX 1
    #endif
#endif

#ifndef ghost_has_GHOST_LLONG_MAX
    #include "ghost/type/llong/ghost_llong.h"
    #if !ghost_has(ghost_llong)
        #define ghost_has_GHOST_LLONG_MAX 0
    #endif
#endif

/* <limits.h> has LLONG_MAX in C99. It might be backported. */
#ifndef ghost_has_GHOST_LLONG_MAX
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef LLONG_MAX
        #define GHOST_LLONG_MAX LLONG_MAX
        #define ghost_has_GHOST_LLONG_MAX 1
    #endif
#endif

/* GNU C compilers define __LONG_LONG_MAX__. */
#ifndef ghost_has_GHOST_LLONG_MAX
    #ifdef __LONG_LONG_MAX__
        #define GHOST_LLONG_MAX __LONG_LONG_MAX__
        #define ghost_has_GHOST_LLONG_MAX 1
    #endif
#endif

/* Calculate max directly from width, assuming arithmetic types have no padding
 * bits. */
#ifndef ghost_has_GHOST_LLONG_MAX
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/type/llong/ghost_llong_width.h"
        #if ghost_has(GHOST_LLONG_WIDTH)
            /* Use hardcoded values if possible to make nicer compiler errors */
            #if GHOST_LLONG_WIDTH == 64
                #define GHOST_LLONG_MAX 9223372036854775807LL
            #elif GHOST_LLONG_WIDTH == 32
                #define GHOST_LLONG_MAX 2147483647LL
            #elif GHOST_LLONG_WIDTH == 16
                #define GHOST_LLONG_MAX 32767LL
            #elif GHOST_LLONG_WIDTH == 8
                #define GHOST_LLONG_MAX 127LL
            #else
                /* Careful not to overflow... */
                #define GHOST_LLONG_MAX ((((1LL << (GHOST_LLONG_WIDTH - 2)) - 1LL) << 1) + 1LL)
            #endif
            #define ghost_has_GHOST_LLONG_MAX 1
        #endif
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_LLONG_MAX
    #define ghost_has_GHOST_LLONG_MAX 0
#endif

/* Test max from sizeof, assuming no padding bits */
#if ghost_has(GHOST_LLONG_MAX)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/silence/ghost_silence_push_pop.h"
        #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
            #include "ghost/silence/ghost_silence_long_long.h"
            GHOST_SILENCE_PUSH
            GHOST_SILENCE_LONG_LONG
        #endif

        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(GHOST_LLONG_MAX ==
                    ((((1LL << (sizeof(ghost_llong) * GHOST_CHAR_WIDTH - 2)) - 1LL) << 1) + 1LL),
                "GHOST_LLONG_MAX is incorrect");

        #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
            GHOST_SILENCE_POP
        #endif
    #endif
#endif

#endif
