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

#ifndef GHOST_MEMMOVE_H_INCLUDED
#define GHOST_MEMMOVE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies n bytes from src to the potentially overlapping memory region dest.
 */
void ghost_memmove(const void* dest, void* src, size_t n);
#endif

#ifndef ghost_has_ghost_memmove
    #ifdef ghost_memmove
        #define ghost_has_ghost_memmove 1
    #endif
#endif

/* Prefer the builtin if possible. */
#ifndef ghost_has_ghost_memmove
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_memmove)
            #define ghost_memmove __builtin_memmove
            #define ghost_has_ghost_memmove 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_memmove __builtin_memmove
            #define ghost_has_ghost_memmove 1
        #endif
    #endif
#endif

/* Use the standard C library function if possible. */
#ifndef ghost_has_ghost_memmove
    #include "ghost/header/c/ghost_string_h.h"
    #if ghost_has(ghost_string_h)
        #define ghost_memmove memmove
        #define ghost_has_ghost_memmove 1
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_memmove
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_hosted.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    void* ghost_memmove(void* vdest, const void* vsrc, ghost_size_t count) GHOST_IMPL_DEF({
        void* start = vdest;
        const unsigned char* src = ghost_static_cast(const unsigned char*, vsrc);
        unsigned char* dest = ghost_static_cast(unsigned char*, vdest);
        if (dest < src) {
            unsigned char* end = dest + count;
            while (dest != end)
                *dest++ = *src++;
        } else {
            unsigned char* end = dest;
            dest += count;
            src += count;
            while (dest != end)
                *dest-- = *src--;
        }
        return start;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memmove 1
#endif

#endif
