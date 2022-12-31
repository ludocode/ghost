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

#ifndef GHOST_CHAR8_C_H_INCLUDED
#define GHOST_CHAR8_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR8_C(x) u8 ## x
 *
 * Defines a character constant of type ghost_char8_t representing a single
 * UTF-8 code unit.
 *
 * The contents of the macro must be a single-quoted character or an escaped
 * UTF-8 code unit.
 */
#endif

/*
 * The u8 character constant prefix is in C++17.
 *
 * In C++20 and later it's a char8_t; in C++17 it's a char.
 *
 *     https://en.cppreference.com/w/cpp/language/character_literal
 */
#ifndef ghost_has_GHOST_CHAR8_C
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201703L
            #define GHOST_CHAR8_C(x) u8 ## x
            #define ghost_has_GHOST_CHAR8_C 1
        #endif
    #endif
#endif

/*
 * The u8 character constant prefix will be available in C23. It will be an
 * unsigned char.
 *
 *     https://en.cppreference.com/w/c/language/character_constant
 */
#ifndef ghost_has_GHOST_CHAR8_C
    /* Kefir doesn't support this yet despite declaring C11 support. */
    #if defined(__STDC_VERSION__) && !defined(__KEFIRCC__)
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 202000L
            #define GHOST_CHAR8_C(x) u8 ## x
            #define ghost_has_GHOST_CHAR8_C 1
        #endif
    #endif
#endif

/* Otherwise we leave it unprefixed. */
#ifndef ghost_has_GHOST_CHAR8_C
    #define GHOST_CHAR8_C(x) x
    #define ghost_has_GHOST_CHAR8_C 1
#endif

#endif
