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

#ifndef GHOST_STPCPY_H_INCLUDED
#define GHOST_STPCPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies the string src to the non-overlapping buffer dest, returning a
 * pointer to the null terminator at the end of dest.
 */
char* ghost_stpcpy(char* restrict dest, const char* restrict src);
#endif

#ifndef ghost_has_ghost_stpcpy
    #ifdef ghost_stpcpy
        #define ghost_has_ghost_stpcpy 1
    #endif
#endif

/* TODO posix 2008, BSDs, glibc, maybe musl */

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_stpcpy
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/impl/ghost_impl_function.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_stpcpy(char* ghost_restrict dest, const char* ghost_restrict src) GHOST_IMPL_DEF({
        for (;;) {
            *dest = *src;
            if (*src == '\000')
                break;
            ++dest;
            ++src;
        }
        return dest;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_stpcpy 1
#endif

#endif
