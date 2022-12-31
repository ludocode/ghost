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

#ifndef GHOST_STRCAT_H_INCLUDED
#define GHOST_STRCAT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 *
 */
char* strcat(char* restrict dest, const char* restrict src);
#endif

#ifndef ghost_has_ghost_strcat
    #ifdef ghost_strcat
        #define ghost_has_ghost_strcat 1
    #endif
#endif

/* Under MSVC, the use of strcat() is only allowed if _CRT_SECURE_NO_WARNINGS
 * is defined. We don't want to depend on that macro because the user might not
 * have defined it yet or might change its value. Instead we wrap strcat() and
 * silence the warning. */
#ifndef ghost_has_ghost_strcat
    #ifdef _MSC_VER
        #include "ghost/header/c/ghost_string_h.h"
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        char* ghost_strcat(char* ghost_restrict to, const char* ghost_restrict from) {
            #pragma warning(push)
            #pragma warning(disable:4996)
            /* https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strcat-wcscpy-mbscpy */
            return strcat(to, from);
            #pragma warning(pop)
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_strcat 1
    #endif
#endif

/* Use the builtin if possible. */
#ifndef ghost_has_ghost_strcat
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_strcat)
            #define ghost_strcat __builtin_strcat
            #define ghost_has_ghost_strcat 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_strcat __builtin_strcat
            #define ghost_has_ghost_strcat 1
        #endif
    #endif
#endif

/* If we're hosted, use the standard C library function. */
#ifndef ghost_has_ghost_strcat
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has_ghost_string_h
            #define ghost_strcat strcat
            #define ghost_has_ghost_strcat 1
        #endif
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_strcat
    #include "ghost/impl/ghost_impl_function.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* strcat(char* restrict dest, const char* restrict src) GHOST_IMPL_DEF({
        char* original_dest = dest;
        while (*dest != '\0')
            ++dest;
        for (;;) {
            *dest = *src;
            if (*src == '\0')
                break;
            ++src;
            ++dest;
        }
        return original_dest;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strcat 1
#endif

#endif
