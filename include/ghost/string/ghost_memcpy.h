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

#ifndef GHOST_MEMCPY_H_INCLUDED
#define GHOST_MEMCPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies count bytes from src to the non-overlapping memory region dest,
 * returning dest.
 */
void* ghost_memcpy(const void* restrict dest, void* restrict src, size_t count);
#endif

/* TODO: we should seriously consider just mapping memcpy() to memmove(),
 * especailly if we're freestanding. The Linux kernel does this internally for
 * safety; Linus has had a lot to say about this. In modern implementations
 * memcpy() isn't any faster than memmove() anyway. */

#ifndef ghost_has_ghost_memcpy
    #ifdef ghost_memcpy
        #define ghost_has_ghost_memcpy 1
    #endif
#endif

/*
 * Prefer the builtin if possible. We want constant-size memcpy() to be
 * optimized even if compiling under flags like -ansi or -fno-builtins. This is
 * necessary for a proper implementation of features like ghost_bit_cast().
 *
 * In a hosted environment the builtin will fallback to libc memcpy() anyway.
 * In freestanding it will fallback to a libgcc function in GCC or some inline
 * code in Clang, both of which will be faster than our plain C implementation
 * below.
 */
#ifndef ghost_has_ghost_memcpy
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_memcpy)
            #define ghost_memcpy __builtin_memcpy
            #define ghost_has_ghost_memcpy 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_memcpy __builtin_memcpy
            #define ghost_has_ghost_memcpy 1
        #endif
    #endif
#endif

/* Use the standard C library function if possible. */
#ifndef ghost_has_ghost_memcpy
    #include "ghost/header/c/ghost_string_h.h"
    #if ghost_has(ghost_string_h)
        #define ghost_memcpy memcpy
        #define ghost_has_ghost_memcpy 1
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_memcpy
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    void* ghost_memcpy(void* ghost_restrict vdest, const void* ghost_restrict vsrc, ghost_size_t count) GHOST_IMPL_DEF({
        const unsigned char* ghost_restrict src = ghost_static_cast(const unsigned char*, vsrc);
        unsigned char* dest = ghost_static_cast(unsigned char*, vdest);
        unsigned char* end = dest + count;
        while (dest != end)
            *dest++ = *src++;
        return vdest;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memcpy 1
#endif

#endif
