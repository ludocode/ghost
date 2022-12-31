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

#ifndef GHOST_CHAR32_T_H_INCLUDED
#define GHOST_CHAR32_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_char32_t
 *
 * An unsigned type capable of storing UTF-32 code units.
 *
 * This is an alias of char32_t if supported, or a typedef to uint_least32_t or
 * equivalent otherwise.
 *
 * This may be its own distinct type or it may be a typedef of another type.
 * Check GHOST_CHAR32_IS_DISTINCT to see if it's a distinct type.
 *
 * @see GHOST_CHAR32_IS_DISTINCT
 */
#endif

#ifndef ghost_has_ghost_char32_t
    #ifdef ghost_char32_t
        #define ghost_has_ghost_char32_t 1
    #endif
#endif

/*
 * C++11 has char32_t as a distinct type.
 * (It might make more sense to feature-test __cpp_unicode_characters >= 200704L)
 *
 *     https://en.cppreference.com/w/cpp/language/types
 */
#ifndef ghost_has_ghost_char32_t
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            typedef char32_t ghost_char32_t;
            #define ghost_has_ghost_char32_t 1
        #endif
    #endif
#endif

/*
 * C11 has char32_t in <uchar.h>. It should be a typedef to `uint_least32_t`.
 *
 *     https://en.cppreference.com/w/c/string/multibyte/char32_t
 */
#ifndef ghost_has_ghost_char32_t
    #include "ghost/header/c/ghost_uchar_h.h"
    #if ghost_has(ghost_uchar_h)
        #ifdef __STDC_VERSION_UCHAR_H__
            #if __STDC_VERSION_UCHAR_H__ >= 202311L
                typedef char32_t ghost_char32_t;
                #define ghost_has_ghost_char32_t 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we fallback to uint32_t (since Ghost doesn't currently have
 * uint_least32_t.) */
#ifndef ghost_has_ghost_char32_t
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    typedef ghost_uint32_t ghost_char32_t;
    #define ghost_has_ghost_char32_t 1
#endif

#endif
