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

#ifndef GHOST_CHAR_MAX_H_INCLUDED
#define GHOST_CHAR_MAX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR_MAX CHAR_MAX
 *
 * The maximum value of char.
 *
 * Note that char may be signed or unsigned.
 */
#endif

#ifndef ghost_has_GHOST_CHAR_MAX
    #ifdef GHOST_CHAR_MAX
        #define ghost_has_GHOST_CHAR_MAX 1
    #endif
#endif

/* <limits.h> has CHAR_MAX */
#ifndef ghost_has_GHOST_CHAR_MAX
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef CHAR_MAX
        #define GHOST_CHAR_MAX CHAR_MAX
        #define ghost_has_GHOST_CHAR_MAX 1
    #endif
#endif

/* If we know the width of char and we know whether it's signed, we can figure
 * out the max. (char is not allowed to have padding bits.) */
#ifndef ghost_has_GHOST_CHAR_MAX
    #include "ghost/type/char/ghost_char_is_signed.h"
    #if ghost_has(GHOST_CHAR_IS_SIGNED)
        #include "ghost/type/char/ghost_char_width.h"
        /* Careful not to overflow... */
        #if GHOST_CHAR_IS_SIGNED
            #define GHOST_CHAR_MAX ((((1 << (GHOST_CHAR_WIDTH - 2)) - 1) << 1) + 1)
        #else
            #define GHOST_CHAR_MAX ((((1U << (GHOST_CHAR_WIDTH - 1U)) - 1U) << 1U) + 1U)
        #endif
        #define ghost_has_GHOST_CHAR_MAX 1
    #endif
#endif

/* Otherwise we don't know max. */
#ifndef ghost_has_GHOST_CHAR_MAX
    #define ghost_has_GHOST_CHAR_MAX 0
#endif

/* Test max from sizeof. (char is not allowed to have padding bits.) */
#if ghost_has(GHOST_CHAR_MAX)
    #include "ghost/type/char/ghost_char_is_signed.h"
    #if ghost_has(GHOST_CHAR_IS_SIGNED)
        #include "ghost/debug/ghost_static_assert.h"
        #if GHOST_CHAR_IS_SIGNED
            #include "ghost/type/char/ghost_char_width.h"
            ghost_static_assert(GHOST_CHAR_MAX ==
                        ((((1 << (GHOST_CHAR_WIDTH - 2)) - 1) << 1) + 1),
                    "GHOST_CHAR_MAX is incorrect");
        #else
            #include "ghost/language/ghost_static_cast.h"
            ghost_static_assert(GHOST_CHAR_MAX == ghost_static_cast(char, (~0)),
                    "GHOST_CHAR_MAX is incorrect");
        #endif
    #endif
#endif

#endif
