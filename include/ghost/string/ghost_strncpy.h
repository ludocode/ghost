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

#ifndef GHOST_STRNCPY_H_INCLUDED
#define GHOST_STRNCPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies the src string into the given non-overlapping dest buffer of size n,
 * truncates it if it doesn't fit, pads any remaining buffer space with zeroes,
 * and returns the dest buffer.
 *
 * This always writes exactly n bytes. The source string does not need to
 * be null-terminated if it contains n or more bytes.
 *
 * This is designed to copy a null-terminated string into an old-school fixed
 * size buffer, where such a buffer need not be null-terminated if the string
 * length exactly matches the size of the buffer. Such fixed size buffers are
 * used for serialization (among other things) which is why strncpy() pads the
 * whole buffer with zeroes to clear uninitialized memory or any remnants of an
 * old string.
 *
 * strncpy() is therefore *not* a safer strcpy(). You probably want strlcpy()
 * instead which always null-terminates and does not write unnecessary zeroes.
 * Alternatively, you can place a null terminator at the start of dest and then
 * use strncat() (but note that strncat() writes up to n+1 bytes.)
 *
 * @see ghost_strlcpy()
 */
char* ghost_strncpy(char* restrict dest, const char* restrict src, size_t n);
#endif

/* Under MSVC, the use of strncpy() is only allowed if _CRT_SECURE_NO_WARNINGS
 * is defined. We want ghost_strncpy() to work without this so we wrap
 * strncpy() and silence the warning. */
#ifndef ghost_has_ghost_strncpy
    #ifdef _MSC_VER
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/header/c/ghost_string_h.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        char* ghost_strncpy(char* ghost_restrict to, const char* ghost_restrict from, ghost_size_t count) {
            #pragma warning(push)
            #pragma warning(disable:4996)
            /* https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strncpy-strncpy-l-wcsncpy-wcsncpy-l-mbsncpy-mbsncpy-l */
            return strncpy(to, from, count);
            #pragma warning(pop)
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_strncpy 1
    #endif
#endif

/* If we're hosted, use the standard C library function. */
#ifndef ghost_has_ghost_strncpy
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has_ghost_string_h
            #define ghost_strncpy strncpy
            #define ghost_has_ghost_strncpy 1
        #endif
    #endif
#endif

/* Compilers that support GNU C extensions provide a builtin for strncpy(). */
#ifndef ghost_has_ghost_strncpy
    /* As usual, if we have __has_builtin we check, but we otherwise assume GNU
     * C compilers support the builtin. */
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_strncpy)
            #define ghost_strncpy __builtin_strncpy
            #define ghost_has_ghost_strncpy 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this.
             * https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html */
            #define ghost_strncpy __builtin_strncpy
            #define ghost_has_ghost_strncpy 1
        #endif
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_strncpy
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
/* TODO test this */

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strncpy_impl(char* ghost_restrict to, const char* ghost_restrict from, ghost_size_t count) GHOST_IMPL_DEF({
        char* ret = to;
        char* end = to + count;
        while (to != end && *from != '\000') {
            *to = *from;
            ++to;
            ++from;
        }
        /* strncpy() pads with zeroes. */
        while (to != end)
            *to++ = 0;
        return ret;
    })
    GHOST_IMPL_FUNCTION_CLOSE

    #define ghost_strncpy ghost_strncpy_impl
    #define ghost_has_ghost_strncpy 1
#endif

#endif
