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

#ifndef GHOST_MEMCMP_H_INCLUDED
#define GHOST_MEMCMP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Performs an ordering comparison of the given memory regions, returning 0 if
 * they are equal, less than 0 if a "comes before" b, and greater than 0
 * otherwise.
 *
 * This compares char-by-char starting at the beginning of a and b. If all
 * count chars are equal, 0 is returned.
 *
 * If a non-matching char is found, -1 is returned if the first non-matching
 * char in a is less than the char in b (where a and b are interpreted as
 * unsigned char) and 1 otherwise.
 */
int ghost_memcmp(const void* a, const void* b, size_t count);
#endif

#ifndef ghost_has_ghost_memcmp
    #ifdef ghost_memcmp
        #define ghost_has_ghost_memcmp 1
    #endif
#endif

/* Use builtin if possible. */
#ifndef ghost_has_ghost_memcmp
    /* As usual, if we have __has_builtin we check, but we otherwise assume
     * GNU C compilers support the builtin. */
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_memcmp)
            /* https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
             * https://clang.llvm.org/docs/LanguageExtensions.html#string-builtins */
            #define ghost_memcmp __builtin_memcmp
            #define ghost_has_ghost_memcmp 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define ghost_memcmp __builtin_memcmp
            #define ghost_has_ghost_memcmp 1
        #endif
    #endif
#endif

/* If we're hosted, use the standard C library function. (GCC and Clang will
 * recognize this as a builtin unless -fno-builtins is specified, and we assume
 * MSVC recognizes this as an intrinsic as well.) */
#ifndef ghost_has_ghost_memcmp
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has(ghost_string_h)
            #define ghost_memcmp memcmp
            #define ghost_has_ghost_memcmp 1
        #endif
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_memcmp
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/debug/ghost_static_assert.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    int ghost_memcmp(const void* p1, const void* p2, ghost_size_t count) GHOST_IMPL_DEF({
        const unsigned char* c1 = ghost_static_cast(const unsigned char*, p1);
        const unsigned char* c2 = ghost_static_cast(const unsigned char*, p2);
        const unsigned char* end = c1 + count;
        while (c1 != end) {
            if (*c1 != *c2) {
                ghost_static_assert(sizeof(int) > sizeof(unsigned char), "");
                return ghost_static_cast(int, *c1) - ghost_static_cast(int, *c2);
            }
            ++c1;
            ++c2;
        }
        return 0;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memcmp 1
#endif

#endif
