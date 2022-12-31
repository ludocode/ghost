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

#ifndef GHOST_STRNCAT_H_INCLUDED
#define GHOST_STRNCAT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * strncat() appends src onto dest, using at most n bytes from src and
 * appending a null-terminator if one was not found in the first n bytes of
 * src.
 *
 * This will write up to n+1 bytes. The destination buffer must have space for
 * at least n+1 bytes plus the length of the existing string.
 *
 * The source string does not need to be null-terminated if it contains n
 * or more bytes.
 */
char* ghost_strncat(char* restrict dest, const char* restrict src, size_t n);
#endif

/* Under MSVC, the use of strncat() is only allowed if _CRT_SECURE_NO_WARNINGS
 * is defined. We want ghost_strncat() to work without this so we wrap
 * strncat() and silence the warning. */
#ifndef ghost_has_ghost_strncat
    #ifdef _MSC_VER
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/header/c/ghost_string_h.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        char* ghost_strncat(char* ghost_restrict to, const char* ghost_restrict from, ghost_size_t count) {
            #pragma warning(push)
            #pragma warning(disable:4996)
            /* https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strncat-strncat-l-wcsncpy-wcsncpy-l-mbsncpy-mbsncpy-l */
            return strncat(to, from, count);
            #pragma warning(pop)
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_strncat 1
    #endif
#endif

/* If we're hosted, use the standard C library function. */
#ifndef ghost_has_ghost_strncat
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has_ghost_string_h
            #define ghost_strncat strncat
            #define ghost_has_ghost_strncat 1
        #endif
    #endif
#endif

/* Compilers that support GNU C extensions provide a builtin for strncat(). */
#ifndef ghost_has_ghost_strncat
    /* As usual, if we have __has_builtin we check, but we otherwise assume GNU
     * C compilers support the builtin. */
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_strncat)
            #define ghost_strncat __builtin_strncat
            #define ghost_has_ghost_strncat 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this.
             * https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html */
            #define ghost_strncat __builtin_strncat
            #define ghost_has_ghost_strncat 1
        #endif
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_strncat
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
/* TODO test this */

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strncat_impl(char* ghost_restrict dest, const char* ghost_restrict src, ghost_size_t n) GHOST_IMPL_DEF({
        char* original_dest = dest;
        while (*dest != '\0')
            ++dest;
        char* end = src + n;
        while (*src != '\0' && src != end) {
            *dest = *src;
            ++dest;
            ++src;
        }
        *dest = '\0';
        return original_dest;
    })
    GHOST_IMPL_FUNCTION_CLOSE

    #define ghost_strncat ghost_strncat_impl
    #define ghost_has_ghost_strncat 1
#endif

#endif
