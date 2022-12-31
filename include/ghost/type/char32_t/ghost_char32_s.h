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

#ifndef GHOST_CHAR32_S_H_INCLUDED
#define GHOST_CHAR32_S_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR32_S(string) U ## string
 *
 * Declares a UTF-32 string literal of type `ghost_char32_t[N]` where N is
 * the size of the string (including the null-terminator.)
 *
 * Example:
 *
 *     const ghost_char32_t* hello = GHOST_CHAR32_S("Hello world!");
 *
 * `char32_t[]` literal strings were added in C11 and C++11. This may not exist
 * in older language standards. Check `#if ghost_has(GHOST_CHAR32_C)` to see if
 * it exists.
 */
#endif

#ifndef ghost_has_GHOST_CHAR32_S
    #ifdef GHOST_CHAR32_S
        #define ghost_has_GHOST_CHAR32_S 1
    #endif
#endif

/*
 * The U string literal prefix is in C++11.
 *
 *     https://en.cppreference.com/w/cpp/language/string_literal
 */
#ifndef ghost_has_GHOST_CHAR32_S
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define GHOST_CHAR32_S(x) U ## x
            #define ghost_has_GHOST_CHAR32_S 1
        #endif
    #endif
#endif

/*
 * The U string literal prefix is in C11.
 *
 *     https://en.cppreference.com/w/c/language/string_literal
 */
#ifndef ghost_has_GHOST_CHAR32_S
    /* Kefir doesn't support this yet despite declaring C11 support. */
    #if defined(__STDC_VERSION__) && !defined(__KEFIRCC__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 201112L
            #define GHOST_CHAR32_S(x) U ## x
            #define ghost_has_GHOST_CHAR32_S 1
        #endif
    #endif
#endif

/* TODO check if wchar_t is 32 bits, we could use L"" */

/* Otherwise we don't have this. */
#ifndef ghost_has_GHOST_CHAR32_S
    #define ghost_has_GHOST_CHAR32_S 0
#endif

#endif
