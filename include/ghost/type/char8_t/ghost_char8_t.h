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

#ifndef GHOST_CHAR8_T_H_INCLUDED
#define GHOST_CHAR8_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_char8_t
 *
 * A type capable of storing UTF-8 code units.
 *
 * This is an alias of `char8_t` if supported, or a typedef to either `char` or
 * `unsigned char` otherwise.
 *
 * This may be its own distinct type or it may be a typedef of another type.
 * Check GHOST_CHAR8_IS_DISTINCT to see if it's a distinct type.
 *
 * This may or may not be signed, even though the standard C and C++ `char8_t`
 * are unsigned. Check GHOST_CHAR8_IS_SIGNED to see if it's signed. (This is
 * because unless `u8""` is of type `char8_t`, literal strings must be of type
 * `char[]`. On platforms where char is signed, there is no way to assign such
 * a literal string to a `const unsigned char*` so `ghost_char8_t` must be
 * signed.)
 *
 * @see GHOST_CHAR8_IS_DISTINCT
 * @see GHOST_CHAR8_IS_SIGNED
 */
#endif

#ifndef ghost_has_ghost_char8_t
    #ifdef ghost_char8_t
        #define ghost_has_ghost_char8_t 1
    #endif
#endif

/* C++20 has char8_t as a distinct type.
 * (It might make more sense to feature-test __cpp_char8_t >= 201811L) */
#ifndef ghost_has_ghost_char8_t
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 202002L
            typedef char8_t ghost_char8_t;
            #define ghost_has_ghost_char8_t 1
        #endif
    #endif
#endif

/* C23 has char8_t in <uchar.h>. It should be a typedef to `unsigned char`
 * but compilers may have extensions for it so we use it if possible. */
#ifndef ghost_has_ghost_char8_t
    #include "ghost/header/c/ghost_uchar_h.h"
    #if ghost_has(ghost_uchar_h)
        #ifdef __STDC_VERSION_UCHAR_H__
            #if __STDC_VERSION_UCHAR_H__ >= 202311L
                typedef char8_t ghost_char8_t;
                #define ghost_has_ghost_char8_t 1
            #endif
        #endif
    #endif
#endif

/* In C23, if we don't have <uchar.h>, we still need to make it `unsigned char`
 * because the u8 character prefix will be `unsigned char`. */
#ifndef ghost_has_ghost_char8_t
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 202000L /*TODO C23*/
            typedef unsigned char ghost_char8_t;
            #define ghost_has_ghost_char8_t 1
        #endif
    #endif
#endif

/* Otherwise, since we won't have the u8 character prefix, we need to make this
 * char so we can assign literal strings to it. It may or may not be signed. */
#ifndef ghost_has_ghost_char8_t
    typedef char ghost_char8_t;
    #define ghost_has_ghost_char8_t 1
#endif

#endif
