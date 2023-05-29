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

#ifndef GHOST_STRSET_H_INCLUDED
#define GHOST_STRSET_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Sets all characters in str to c and returns str.
 */
char* ghost_strset(char* str, int c);
#endif

#ifndef ghost_has_ghost_strset
    #ifdef ghost_strset
        #define ghost_has_ghost_strset 1
    #endif
#endif

/* TODO Windows
 * https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strset-strset-l-wcsset-wcsset-l-mbsset-mbsset-l?view=msvc-170 */

/* Otherwise we provide a slow but small fallback implementation. */
#ifndef ghost_has_ghost_strset
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/impl/ghost_impl_function.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strset(char* str, int ic) GHOST_IMPL_DEF({
        char* original_str = str;
        char c = ghost_static_cast(char, ic);
        for (; *str != '\000'; ++str)
            *str = c;
        return original_str;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strset 1
#endif

#endif
