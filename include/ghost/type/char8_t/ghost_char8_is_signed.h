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

#ifndef GHOST_CHAR8_IS_SIGNED_H_INCLUDED
#define GHOST_CHAR8_IS_SIGNED_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR8_IS_SIGNED
 *
 * 1 if ghost_char8_t is signed, 0 if it is unsigned.
 *
 * As of C23 and C++20, ghost_char8_t is always unsigned. It may or may not be
 * signed on older language standards.
 */
#endif

#ifndef ghost_has_GHOST_CHAR8_IS_SIGNED
    #ifdef GHOST_CHAR8_IS_SIGNED
        #define ghost_has_GHOST_CHAR8_IS_SIGNED 1
    #endif
#endif

/* C++20 has char8_t as a distinct type, which is unsigned. */
#ifndef ghost_has_GHOST_CHAR8_IS_SIGNED
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 202002L
            #define GHOST_CHAR8_IS_SIGNED 0
            #define ghost_has_GHOST_CHAR8_IS_SIGNED 1
        #endif
    #endif
#endif

/* In C23, ghost_char8_t is one way or another a typedef to `unsigned char`. */
#ifndef ghost_has_ghost_char8_t
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 202000L /*TODO C23*/
            #define GHOST_CHAR8_IS_SIGNED 0
            #define ghost_has_GHOST_CHAR8_IS_SIGNED 1
        #endif
    #endif
#endif

/* Otherwise this matches the signedness of char, which we may or may not know
 * at preprocessing time. */
#ifndef ghost_has_GHOST_CHAR8_IS_SIGNED
    #include "ghost/type/char/ghost_char_is_signed.h"
    #if ghost_has(GHOST_CHAR_IS_SIGNED)
        #if GHOST_CHAR_IS_SIGNED
            #define GHOST_CHAR8_IS_SIGNED 1
        #else
            #define GHOST_CHAR8_IS_SIGNED 0
        #endif
        #define ghost_has_GHOST_CHAR8_IS_SIGNED 1
    #else
        #define ghost_has_GHOST_CHAR8_IS_SIGNED 0
    #endif
#endif

/* Test signedness */
#if ghost_has(GHOST_CHAR8_IS_SIGNED)
    #include "ghost/type/char8_t/ghost_char8_t.h"
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/language/ghost_static_cast.h"
    #if GHOST_CHAR8_IS_SIGNED
        ghost_static_assert(ghost_static_cast(ghost_char8_t, -1) == -1,
                "GHOST_CHAR8_IS_SIGNED is 1 but ghost_char8_t appears to be unsigned.");
    #else
        ghost_static_assert(ghost_static_cast(ghost_char8_t, -1) != -1,
                "GHOST_CHAR8_IS_SIGNED is 0 but ghost_char8_t appears to be signed.");
    #endif
#endif

#endif
