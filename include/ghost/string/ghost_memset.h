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

#ifndef GHOST_MEMSET_H_INCLUDED
#define GHOST_MEMSET_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * The standard memset() function.
 */
void* ghost_memset(void* dest, int c, size_t count);
#endif

#ifndef ghost_has_ghost_memset
    #ifdef ghost_memset
        #define ghost_has_ghost_memset 1
    #endif
#endif

/* Use the builtin if possible. */
#ifndef ghost_has_ghost_memset
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_memset)
            #define ghost_memset __builtin_memset
            #define ghost_has_ghost_memset 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_memset __builtin_memset
            #define ghost_has_ghost_memset 1
        #endif
    #endif
#endif

/* If we're hosted, use the standard C library function. */
#ifndef ghost_has_ghost_memset
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has_ghost_string_h
            #define ghost_memset memset
            #define ghost_has_ghost_memset 1
        #endif
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_memset
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    void* ghost_memset(void* vdest, int c, ghost_size_t count) GHOST_IMPL_DEF({
        /* TODO test this */
        unsigned char* ghost_restrict dest = ghost_static_cast(unsigned char*, vdest);
        unsigned char* start = dest;
        unsigned char* end = dest + count;
        unsigned char uc = ghost_static_cast(unsigned char, c);
        while (dest != end)
            *dest++ = uc;
        return start;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memset 1
#endif

#endif
