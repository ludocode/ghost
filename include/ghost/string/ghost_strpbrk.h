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

#ifndef GHOST_STRPBRK_H_INCLUDED
#define GHOST_STRPBRK_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns a pointer to the first character in s that matches any of the
 * characters in accept, or returns null if none are found.
 */
char* ghost_strpbrk(const char* s, const char* accept);
#endif

#ifndef ghost_has_ghost_strpbrk
    #ifdef ghost_strpbrk
        #define ghost_has_ghost_strpbrk 1
    #endif
#endif

/* TODO glibc has this */

#ifndef ghost_has_ghost_strpbrk
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/language/ghost_const_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strpbrk(const char* s, const char* accept) GHOST_IMPL_DEF({
        for (; *s != '\0'; ++s) {
            const char* k;
            for (k = accept; *k != '\0'; ++k)
                if (*s == *k)
                    return ghost_const_cast(char*, s);
        }
        return ghost_null;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strpbrk 1
#endif

#endif
