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

#ifndef GHOST_STRNCMP_H_INCLUDED
#define GHOST_STRNCMP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 *
 */
int ghost_strncmp(const char* left, const char* right, size_t n);
#endif

#ifndef ghost_has_ghost_strncmp
    #ifdef ghost_strncmp
        #define ghost_has_ghost_strncmp 1
    #endif
#endif

/* Use the builtin if possible. */
#ifndef ghost_has_ghost_strncmp
    /* As usual, if we have __has_builtin we check, but we otherwise assume GNU
     * C compilers support the builtin. */
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_strncmp)
            #define ghost_strncmp __builtin_strncmp
            #define ghost_has_ghost_strncmp 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_strncmp __builtin_strncmp
            #define ghost_has_ghost_strncmp 1
        #endif
    #endif
#endif

/* If we're hosted, use the standard C library function. */
#ifndef ghost_has_ghost_strncmp
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has_ghost_string_h
            #define ghost_strncmp strncmp
            #define ghost_has_ghost_strncmp 1
        #endif
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_strncmp
    #include "ghost/impl/ghost_impl_function.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    int ghost_strncmp(const char* a, const char* b, size_t n) GHOST_IMPL_DEF({
        const char* end = a + n;
        while (*a == *b && a != end) {
            if (*a == '\0')
                return 0;
            ++a;
            ++b;
        }
        return ghost_static_cast(int, ghost_static_cast(unsigned char, *a)) -
            ghost_static_cast(int, ghost_static_cast(unsigned char, *b));
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strncmp 1
#endif

#endif
