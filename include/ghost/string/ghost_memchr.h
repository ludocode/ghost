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

#ifndef GHOST_MEMCHR_H_INCLUDED
#define GHOST_MEMCHR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches the given memory range for the character c, returning a pointer to
 * the first instance of it or null if not found.
 */
void* ghost_memchr(const void* s, int c, size_t n);
#endif

#ifndef ghost_has_ghost_memchr
    #ifdef ghost_memchr
        #define ghost_has_ghost_memchr 1
    #endif
#endif

/*
 * There's a possibility of using Clang's __builtin_char_memchr() here to make
 * this constexpr on char* in C++, perhaps with a template that matches on a
 * char* argument. I haven't bothered to implement this yet. One issue is that
 * it would return char*, not void*, which could potentially break code.
 * Another issue is it would complicate the rest of the configuration of
 * ghost_memchr in this file because the alternate would also have to be a
 * template or override, not a macro.
 */

/* Use builtin if possible. */
#ifndef ghost_has_ghost_memchr
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_memchr)
            /* https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
             * https://clang.llvm.org/docs/LanguageExtensions.html#string-builtins */
            #define ghost_memchr __builtin_memchr
            #define ghost_has_ghost_memchr 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* __builtin_memchr is available as of GCC 4.1. */
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)
                #define ghost_memchr __builtin_memchr
                #define ghost_has_ghost_memchr 1
            #endif
        #endif
    #endif
#endif

/* Use the standard C library function if possible. C++ declares this as two
 * overloads, one taking and returning const and one not. */
#ifndef ghost_has_ghost_memchr
    #include "ghost/header/c/ghost_string_h.h"
    #if ghost_has(ghost_string_h)
        #define ghost_memchr memchr
        #define ghost_has_ghost_memchr 1
    #endif
#endif

/* Otherwise we define our own. We don't bother with the C++ overloads. */
#ifndef ghost_has_ghost_memchr
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/language/ghost_const_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    void* ghost_memchr(const void* vdata, int c, ghost_size_t count) GHOST_IMPL_DEF({
        const char* data = ghost_static_cast(const char*, vdata);
        ghost_size_t i;
        for (i = 0; i < count; ++i)
            if (data[i] == c)
                return ghost_const_cast(char*, data + i);
        return ghost_null;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memchr 1
#endif

#endif
