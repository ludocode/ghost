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

#ifndef GHOST_USHORT_MAX_H_INCLUDED
#define GHOST_USHORT_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_USHORT_MAX USHRT_MAX
 *
 * The maximum value of unsigned short.
 */
#endif

#ifndef ghost_has_GHOST_USHORT_MAX
    #ifdef GHOST_USHORT_MAX
        #define ghost_has_GHOST_USHORT_MAX 1
    #endif
#endif

/* <limits.h> has USHRT_MAX */
#ifndef ghost_has_GHOST_USHORT_MAX
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef USHRT_MAX
        #define GHOST_USHORT_MAX USHRT_MAX
        #define ghost_has_GHOST_USHORT_MAX 1
    #endif
#endif

/* We don't define from SHORT_MAX since this would require an unsigned cast which
 * would make this unusable in preprocessor arithmetic. */

/* Calculate max directly from width, assuming arithmetic types have no padding
 * bits. */
#ifndef ghost_has_GHOST_USHORT_MAX
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/type/ushort/ghost_ushort_width.h"
        #if ghost_has(GHOST_USHORT_WIDTH)
            #if GHOST_USHORT_WIDTH == 64
                #define GHOST_USHORT_MAX 18446744073709551615U
            #elif GHOST_USHORT_WIDTH == 32
                #define GHOST_USHORT_MAX 4294967295U
            #elif GHOST_USHORT_WIDTH == 16
                #define GHOST_USHORT_MAX 65535U
            #elif GHOST_USHORT_WIDTH == 8
                #define GHOST_USHORT_MAX 255U
            #else
                /* Careful not to overflow... */
                #define GHOST_USHORT_MAX ((((1U << (GHOST_USHORT_WIDTH - 1)) - 1U) << 1) + 1U)
            #endif
            #define ghost_has_GHOST_USHORT_MAX 1
        #endif
    #endif
#endif

/* Otherwise we don't know. */
#ifndef ghost_has_GHOST_USHORT_MAX
    #define ghost_has_GHOST_USHORT_MAX 0
#endif

/* Test max from sizeof, assuming no padding bits */
#if ghost_has(GHOST_USHORT_MAX)
    #include "ghost/impl/ghost_impl_assumptions.h"
    #if GHOST_IMPL_ASSUME_INTEGERS_HAVE_NO_PADDING_BITS
        #include "ghost/debug/ghost_static_assert.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/char/ghost_char_width.h"
        ghost_static_assert(GHOST_USHORT_MAX ==
                    ((((1U << (sizeof(unsigned short) * GHOST_CHAR_WIDTH - 1)) - 1U) << 1) + 1U),
                "GHOST_USHORT_MAX is incorrect");
    #endif
#endif

/* Test max via unsigned overflow */
#if ghost_has(GHOST_USHORT_MAX)
    #include "ghost/silence/ghost_silence_push_pop.h"
    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        #include "ghost/silence/ghost_silence_cast_truncates_constant.h"
        #include "ghost/silence/ghost_silence_constant_overflow.h"
        GHOST_SILENCE_PUSH
        GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
        GHOST_SILENCE_CONSTANT_OVERFLOW
    #endif

    ghost_static_assert(0 == ghost_static_cast(unsigned short, GHOST_USHORT_MAX + 1U),
            "GHOST_USHORT_MAX is incorrect");

    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        GHOST_SILENCE_POP
    #endif
#endif

#endif
