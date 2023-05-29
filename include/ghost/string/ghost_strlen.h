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

#ifndef GHOST_STRLEN_H_INCLUDED
#define GHOST_STRLEN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * The standard strlen() function
 */
size_t ghost_strlen(const char* s);
#endif

/* Allow override via #define */
#ifndef ghost_has_ghost_strlen
    #ifdef ghost_strlen
        #define ghost_has_ghost_strlen 1
    #endif
#endif

/* Use the builtin if possible. */
#ifndef ghost_has_ghost_strlen
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_strlen)
            /* https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html */
            #define ghost_strlen __builtin_strlen
            #define ghost_has_ghost_strlen 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_strlen __builtin_strlen
            #define ghost_has_ghost_strlen 1
        #endif
    #endif
#endif

/* Use the standard C library function if possible. */
#ifndef ghost_has_ghost_strlen
    #include "ghost/header/c/ghost_string_h.h"
    #if ghost_has(ghost_string_h)
        #define ghost_strlen strlen
        #define ghost_has_ghost_strlen 1
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_strlen
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_size_t ghost_strlen(const char* s) GHOST_IMPL_DEF({
        const char* end = s;
        while (*end != '\000')
            ++end;
        return ghost_static_cast(ghost_size_t, end - s);
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strlen 1
#endif

#endif
