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

#ifndef GHOST_STRCHR_H_INCLUDED
#define GHOST_STRCHR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches the given string, returning a pointer to the first instance of the
 * given character or null if not found.
 */
char* ghost_strchr(const char* s, int c);
#endif

#ifndef ghost_has_ghost_strchr
    #ifdef ghost_strchr
        #define ghost_has_ghost_strchr 1
    #endif
#endif

/* Use builtin if possible. */
#ifndef ghost_has_ghost_strchr
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_strchr)
            /* https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
             * https://clang.llvm.org/docs/LanguageExtensions.html#string-builtins */
            #define ghost_strchr __builtin_strchr
            #define ghost_has_ghost_strchr 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_strchr __builtin_strchr
            #define ghost_has_ghost_strchr 1
        #endif
    #endif
#endif

/* Use the standard C library function if possible. C++ declares this as two
 * overloads, one taking and returning const and one not. */
#ifndef ghost_has_ghost_strchr
    #include "ghost/header/c/ghost_string_h.h"
    #if ghost_has(ghost_string_h)
        #define ghost_strchr strchr
        #define ghost_has_ghost_strchr 1
    #endif
#endif

/* Otherwise we define our own. We don't bother with the C++ overloads. */
#ifndef ghost_has_ghost_strchr
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/language/ghost_const_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strchr(const char* s, int c) GHOST_IMPL_DEF({
        for (;;) {
            if (*s == c)
                return ghost_const_cast(char*, s);
            if (*s != '\000')
                break;
            ++s;
        }
        return ghost_null;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strchr 1
#endif

#endif
