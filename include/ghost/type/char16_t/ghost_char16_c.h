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

#ifndef GHOST_CHAR16_C_H_INCLUDED
#define GHOST_CHAR16_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR16_C(x) u ## x
 *
 * Defines a character constant of type ghost_char16_t representing a single
 * UTF-16 code unit.
 *
 * The contents of the macro must be a single-quoted character or an escaped
 * UTF-16 code unit.
 *
 * char16_t character constants were added in C11 and C++11. This may not exist
 * in older language standards. Check `#if ghost_has(GHOST_CHAR16_C)` to see if
 * it exists.
 */
#endif

/*
 * The u character constant prefix is in C++11.
 *
 *     https://en.cppreference.com/w/cpp/language/character_literal
 */
#ifndef ghost_has_GHOST_CHAR16_C
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define GHOST_CHAR16_C(x) u ## x
            #define ghost_has_GHOST_CHAR16_C 1
        #endif
    #endif
#endif

/*
 * The u character constant prefix is in C11.
 *
 *     https://en.cppreference.com/w/c/language/character_constant
 */
#ifndef ghost_has_GHOST_CHAR16_C
    /* Kefir doesn't support this yet despite declaring C11 support. */
    #if defined(__STDC_VERSION__) && !defined(__KEFIRCC__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 201112L
            #define GHOST_CHAR16_C(x) u ## x
            #define ghost_has_GHOST_CHAR16_C 1
        #endif
    #endif
#endif

/* TODO check if wchar_t is 16 bits, we could use L"" */

/* Otherwise we don't have this. */
#ifndef ghost_has_GHOST_CHAR16_C
    #define ghost_has_GHOST_CHAR16_C 0
#endif

#endif
