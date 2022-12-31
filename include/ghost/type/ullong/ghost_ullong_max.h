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

#ifndef GHOST_ULLONG_MAX_H_INCLUDED
#define GHOST_ULLONG_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_ULLONG_MAX ULLONG_MAX
 *
 * The maximum value of `unsigned long long`.
 *
 * This may cause a -Wlong-long warning on GNU C compilers in older language
 * standards where `long long` is an extension. You should probably disable or
 * silence this warning if you intend to use this in older language standards.
 *
 * @see GHOST_SILENCE_LONG_LONG
 */
#endif

#ifndef ghost_has_GHOST_ULLONG_MAX
    #ifdef GHOST_ULLONG_MAX
        #define ghost_has_GHOST_ULLONG_MAX 1
    #endif
#endif

#ifndef ghost_has_GHOST_ULLONG_MAX
    #include "ghost/type/ullong/ghost_ullong.h"
    #if !ghost_has(ghost_ullong)
        #define ghost_has_GHOST_ULLONG_MAX 0
    #endif
#endif

/* <limits.h> has ULLONG_MAX */
#ifndef ghost_has_GHOST_ULLONG_MAX
    #ifdef ULLONG_MAX
        #define GHOST_ULLONG_MAX ULLONG_MAX
        #define ghost_has_GHOST_ULLONG_MAX 1
    #endif
#endif

/* GNU C compilers define __LONG_LONG_MAX__ but not an unsigned equivalent. We
 * could in theory define it from this assuming same width and two's
 * complement but this would require an unsigned cast which would make it
 * unusable in preprocessor arithmetic. For now we avoid it. */

/* Calculate max directly from width, assuming arithmetic types have no padding
 * bits. */
#ifndef ghost_has_GHOST_ULLONG_MAX
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/type/ullong/ghost_ullong_width.h"
        #if ghost_has(GHOST_ULLONG_WIDTH)
            #if GHOST_ULLONG_WIDTH == 64
                #define GHOST_ULLONG_MAX 18446744073709551615ULL
            #elif GHOST_ULLONG_WIDTH == 32
                #define GHOST_ULLONG_MAX 4294967295ULL
            #elif GHOST_ULLONG_WIDTH == 16
                #define GHOST_ULLONG_MAX 65535ULL
            #elif GHOST_ULLONG_WIDTH == 8
                #define GHOST_ULLONG_MAX 255ULL
            #else
                /* Careful not to overflow... */
                #define GHOST_ULLONG_MAX ((((1ULL << (GHOST_ULLONG_WIDTH - 1)) - 1ULL) << 1) + 1ULL)
            #endif
            #define ghost_has_GHOST_ULLONG_MAX 1
        #endif
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_ULLONG_MAX
    #define ghost_has_GHOST_ULLONG_MAX 0
#endif

/* Test max from sizeof, assuming no padding bits */
#if ghost_has(GHOST_ULLONG_MAX)
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
        ghost_static_assert(GHOST_ULLONG_MAX ==
                    ((((1ULL << (sizeof(ghost_ullong) * GHOST_CHAR_WIDTH - 1)) - 1ULL) << 1) + 1ULL),
                "GHOST_ULLONG_MAX is incorrect");

        #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
            GHOST_SILENCE_POP
        #endif
    #endif
#endif

/* Test max via unsigned overflow */
#if ghost_has(GHOST_ULLONG_MAX)
    #include "ghost/silence/ghost_silence_push_pop.h"
    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        #include "ghost/silence/ghost_silence_cast_truncates_constant.h"
        #include "ghost/silence/ghost_silence_constant_overflow.h"
        #include "ghost/silence/ghost_silence_long_long.h"
        GHOST_SILENCE_PUSH
        GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
        GHOST_SILENCE_CONSTANT_OVERFLOW
        GHOST_SILENCE_LONG_LONG
    #endif

    ghost_static_assert(0 == ghost_static_cast(ghost_ullong, GHOST_ULLONG_MAX + 1ULL),
            "GHOST_ULLONG_MAX is incorrect");

    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        GHOST_SILENCE_POP
    #endif
#endif

#endif
