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


#ifndef GHOST_STPNCPY_H_INCLUDED
#define GHOST_STPNCPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies at most n bytes including the null-terminator from the string src
 * to the non-overlapping buffer dest, returning a pointer to one past the last
 * non-null byte written to dest.
 *
 * If the string src is longer than n-1 bytes, the resulting string in dest
 * will not be null-terminated. You can therefore check whether the string was
 * terminated by checking whether the return value points to a null byte.
 *
 * If the string in dest is null-terminated, a pointer to the null-terminator
 * is returned. Otherwise, a pointer to the byte after the last byte in dest is
 * returned (i.e. `dest + n`).
 */
char* ghost_stpncpy(char* restrict dest, const char* restrict src, size_t n);
#endif

#ifndef ghost_has_ghost_stpncpy
    #ifdef ghost_stpncpy
        #define ghost_has_ghost_stpncpy 1
    #endif
#endif

/* TODO posix 2008, BSDs, glibc, maybe musl */

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_stpncpy
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_stpncpy(char* ghost_restrict dest, const char* ghost_restrict src, ghost_size_t n) GHOST_IMPL_DEF({
        char* end = dest + n;
        while (dest != end) {
            *dest = *src;
            if (*src == '\000')
                break;
            ++dest;
            ++src;
        }
        return dest;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_stpncpy 1
#endif

#endif
