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

#ifndef GHOST_CHAR_MIN_H_INCLUDED
#define GHOST_CHAR_MIN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR_MIN CHAR_MIN
 *
 * The minimum value of char.
 *
 * Note that char may be signed or unsigned. If char is unsigned, this will be
 * 0.
 *
 * @see GHOST_CHAR_IS_SIGNED
 */
#endif

#ifndef ghost_has_GHOST_CHAR_MIN
    #ifdef GHOST_CHAR_MIN
        #define ghost_has_GHOST_CHAR_MIN 1
    #endif
#endif

/* <limits.h> has CHAR_MIN */
#ifndef ghost_has_GHOST_CHAR_MIN
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef CHAR_MIN
        #define GHOST_CHAR_MIN CHAR_MIN
        #define ghost_has_GHOST_CHAR_MIN 1
    #endif
#endif

/* If we know whether we're signed, min is either 0 or the two's complement
 * inverse of max (if we have max, and assuming two's complement.) */
#ifndef ghost_has_GHOST_CHAR_MIN
    #include "ghost/type/char/ghost_char_is_signed.h"
    #if ghost_has(GHOST_CHAR_IS_SIGNED)
        #if GHOST_CHAR_IS_SIGNED
            #include "ghost/type/char/ghost_char_max.h"
            #if ghost_has_GHOST_CHAR_MAX
                #include "ghost/impl/ghost_impl_assumptions.h"
                #if GHOST_IMPL_ASSUME_TWOS_COMPLEMENT
                    #define GHOST_CHAR_MIN (-1 - GHOST_CHAR_MAX)
                    #define ghost_has_GHOST_CHAR_MIN 1
                #endif
            #endif
        #else
            #define GHOST_CHAR_MIN 0
            #define ghost_has_GHOST_CHAR_MIN 1
        #endif
    #endif
#endif

/* Otherwise we don't have min. */
#ifndef ghost_has_GHOST_CHAR_MIN
    #define ghost_has_GHOST_CHAR_MIN 0
#endif

/* TODO figure out a static assert to test min */

#endif
