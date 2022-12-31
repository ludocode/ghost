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

#ifndef GHOST_CHAR8_S_H_INCLUDED
#define GHOST_CHAR8_S_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR8_S(string) u8 ## string
 *
 * Declares a UTF-8 string literal of type `ghost_char8_t[N]` where N is
 * the size of the string (including the null-terminator.)
 *
 * Example:
 *
 *     const ghost_char8_t* hello = GHOST_CHAR8_S("Hello world!");
 */
#endif

#ifndef ghost_has_GHOST_CHAR8_S
    #ifdef GHOST_CHAR8_S
        #define ghost_has_GHOST_CHAR8_S 1
    #endif
#endif

/*
 * The u8 string literal prefix is available in C++ since C++11.
 *
 * In C++20, the u8 prefix declares a string of type `const char8_t[N]`.
 *
 * In C++11 through C++17, it declares a string of type `char[N]`, and not
 * `unsigned char[N]`. Our ghost_char8_t will be `char` to match.
 *
 *     https://en.cppreference.com/w/cpp/language/string_literal
 */
#ifndef ghost_has_GHOST_CHAR8_S
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define GHOST_CHAR8_S(x) u8 ## x
            #define ghost_has_GHOST_CHAR8_S 1
        #endif
    #endif
#endif

/*
 * The u8 string literal prefix is available in C11.
 *
 * In C23, it will be a string of type `unsigned char[N]`, which matches the
 * `char8_t` typedef.
 *
 * In C11 through C17, it is `char[N]`, so our ghost_char8_t will be `char`.
 *
 *     https://en.cppreference.com/w/c/language/string_literal
 */
#ifndef ghost_has_GHOST_CHAR8_S
    /* Kefir doesn't support this yet despite declaring C11 support. */
    #if defined(__STDC_VERSION__) && !defined(__KEFIRCC__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 201112L
            #define GHOST_CHAR8_S(x) u8 ## x
            #define ghost_has_GHOST_CHAR8_S 1
        #endif
    #endif
#endif

/* Otherwise our string is unprefixed. */
#ifndef ghost_has_GHOST_CHAR8_S
    #define GHOST_CHAR8_S(x) x
    #define ghost_has_GHOST_CHAR8_S 1
#endif

#endif
