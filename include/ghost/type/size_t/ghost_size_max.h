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

#ifndef GHOST_SIZE_MAX_H_INCLUDED
#define GHOST_SIZE_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SIZE_MAX SIZE_MAX
 *
 * The maximum value of ghost_size_t.
 */
#define ghost_has_GHOST_SIZE_MAX 1
#endif

/*
 * SIZE_MAX is supposed to be defined in <stdint.h>. We include it
 * unconditionally to make sure the standard macro exists if possible.
 *
 *     https://en.cppreference.com/w/c/types/limits
 */
#include "ghost/header/c/ghost_stdint_h.h"

#ifndef ghost_has_GHOST_SIZE_MAX
    #ifdef GHOST_SIZE_MAX
        #define ghost_has_GHOST_SIZE_MAX 1
    #endif
#endif

/* SIZE_MAX is standard as of C99 and C++11. It might be backported to ANSI C
 * or C++98. */
#ifndef ghost_has_GHOST_SIZE_MAX
    #ifdef SIZE_MAX
        #define GHOST_SIZE_MAX SIZE_MAX
        #define ghost_has_GHOST_SIZE_MAX 1
    #endif
#endif

/* GNU C compilers give us this. */
#ifndef ghost_has_GHOST_SIZE_MAX
    #ifdef __SIZE_MAX__
        #define GHOST_SIZE_MAX __SIZE_MAX__
        #define ghost_has_GHOST_SIZE_MAX 1
    #endif
#endif

/* See if we can figure out max value based on the width. */
#ifndef ghost_has_GHOST_SIZE_MAX
    #include "ghost/type/size_t/ghost_size_width.h"
    #include "ghost/type/size_t/ghost_size_c.h"
    #if ghost_has(GHOST_SIZE_WIDTH) && ghost_has(GHOST_SIZE_C)
        #if GHOST_SIZE_WIDTH == 8
            #define GHOST_SIZE_MAX GHOST_SIZE_C(256)
            #define ghost_has_GHOST_SIZE_MAX 1
        #elif GHOST_SIZE_WIDTH == 16
            #define GHOST_SIZE_MAX GHOST_SIZE_C(65535)
            #define ghost_has_GHOST_SIZE_MAX 1
        #elif GHOST_SIZE_WIDTH == 32
            #define GHOST_SIZE_MAX GHOST_SIZE_C(4294967295)
            #define ghost_has_GHOST_SIZE_MAX 1
        #elif GHOST_SIZE_WIDTH == 64
            #define GHOST_SIZE_MAX GHOST_SIZE_C(18446744073709551615)
            #define ghost_has_GHOST_SIZE_MAX 1
        #endif
    #endif
#endif

/* Otherwise we don't know the max. */
#ifndef ghost_has_GHOST_SIZE_MAX
    #define ghost_has_GHOST_SIZE_MAX 0
#endif

/* TODO figure out why kefir doesn't like this */
/*#if !defined(__KEFIRCC__)*/

/* Ensure max is correct */
#if ghost_has_GHOST_SIZE_MAX
    #include "ghost/silence/ghost_silence_push_pop.h"
    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        #include "ghost/silence/ghost_silence_cast_truncates_constant.h"
        #include "ghost/silence/ghost_silence_constant_overflow.h"
        GHOST_SILENCE_PUSH
        GHOST_SILENCE_CAST_TRUNCATES_CONSTANT
        GHOST_SILENCE_CONSTANT_OVERFLOW
    #endif

    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/language/ghost_static_cast.h"
    ghost_static_assert(0 == ghost_static_cast(ghost_size_t,
                ghost_static_cast(ghost_size_t, GHOST_SIZE_MAX) + 1),
            "GHOST_SIZE_MAX is incorrect");

    #if ghost_has(GHOST_SILENCE_PUSH) && ghost_has(GHOST_SILENCE_POP)
        GHOST_SILENCE_POP
    #endif
#endif

/*#endif*/ /*kefir*/

#endif
