/*
 * MIT No Attribution
 *
 * Copyright (c) 2022-2023 Fraser Heavy Software
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

#ifndef GHOST_STRCPY_H_INCLUDED
#define GHOST_STRCPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies a string, including the null-terminator.
 *
 * The destination buffer must have enough space for the string including the
 * null-terminator. If it does not, the behaviour is undefined.
 */
char* strcpy(char* restrict to, const char* restrict from);
#endif

#ifndef ghost_has_ghost_strcpy
    #ifdef ghost_strcpy
        #define ghost_has_ghost_strcpy 1
    #endif
#endif

/* Under MSVC, the use of strcpy() is only allowed if _CRT_SECURE_NO_WARNINGS
 * is defined. We don't want to depend on that macro because the user might not
 * have defined it yet or might change its value. Instead we wrap strcpy() and
 * silence the warning. */
#ifndef ghost_has_ghost_strcpy
    #ifdef _MSC_VER
        #include "ghost/header/c/ghost_string_h.h"
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        char* ghost_strcpy(char* ghost_restrict to, const char* ghost_restrict from) {
            #pragma warning(push)
            #pragma warning(disable:4996)
            /* https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strcpy-wcscpy-mbscpy */
            return strcpy(to, from);
            #pragma warning(pop)
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_strcpy 1
    #endif
#endif

/* If we're hosted, use the standard C library function. */
#ifndef ghost_has_ghost_strcpy
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has_ghost_string_h
            #define ghost_strcpy strcpy
            #define ghost_has_ghost_strcpy 1
        #endif
    #endif
#endif

/* Use the builtin if possible. */
#ifndef ghost_has_ghost_strcpy
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_strcpy)
            #define ghost_strcpy __builtin_strcpy
            #define ghost_has_ghost_strcpy 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this.
             * https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html */
            #define ghost_strcpy __builtin_strcpy
            #define ghost_has_ghost_strcpy 1
        #endif
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_strcpy
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/impl/ghost_impl_function.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strcpy(char* ghost_restrict dest, const char* ghost_restrict src) GHOST_IMPL_DEF({
        char* original_dest = dest;
        for (;;) {
            *dest = *src;
            if (*src == '\000')
                break;
            ++dest;
            ++src;
        }
        return original_dest;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strcpy 1
#endif

#endif
