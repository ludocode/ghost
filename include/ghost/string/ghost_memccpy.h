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

#ifndef GHOST_MEMCCPY_H_INCLUDED
#define GHOST_MEMCCPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies n bytes of src to the non-overlapping memory region dest, stopping
 * after the first instance of the character c is found and returning a pointer
 * to the character in dest after it, or null if c is not found.
 *
 * If c is found, all bytes up to and including the first c are copied, and the
 * next character after c in dest (not src) is returned.
 *
 * If c is not found, all n bytes are copied and ghost_null is returned.
 *
 * If multiple instances of c are in src, only the first is copied and copying
 * stops.
 */
void* ghost_memccpy(void* restrict dest, const void* restrict src, int c, size_t n);
#endif

/* POSIX requires memccpy(). This will also become standard in C23.
 * https://en.cppreference.com/w/c/string/byte/memccpy */
#ifndef ghost_has_ghost_memccpy
    #include "ghost/header/c/ghost_string_h.h"
    #if ghost_has_ghost_string_h
        #if defined(__linux__) || defined(__EMSCRIPTEN__)

            /* The Linux libcs seem to declare memccpy() only under certain
             * conditions (e.g. _GNU_SOURCE) even though the man page doesn't
             * mention it. We wrap it in any case. */

            #include "ghost/language/ghost_dllimport.h"
            #include "ghost/type/size_t/ghost_size_t.h"
            #include "ghost/language/ghost_restrict.h"
            #include "ghost/impl/ghost_impl_libc_asm.h"
            #include "ghost/impl/ghost_impl_libc_noexcept.h"

            #if GHOST_IMPL_LIBC_ASM
                #include "ghost/language/ghost_extern_c.h"
                ghost_extern_c
                ghost_dllimport
                void* ghost_memccpy(void* ghost_restrict dest,
                        const void* ghost_restrict src, int c, ghost_size_t count)
                    ghost_impl_libc_noexcept(ghost_impl_libc_asm("memccpy"));
            #else
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/preprocessor/ghost_nothing.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                void* ghost_memccpy(void* ghost_restrict dest,
                        const void* ghost_restrict src, int c, ghost_size_t count)
                {
                    ghost_dllimport
                    extern void* memccpy(void* ghost_restrict dest,
                            const void* ghost_restrict src, int c, ghost_size_t count)
                        ghost_impl_libc_noexcept(GHOST_NOTHING);
                    return memccpy(dest, src, c, count);
                }
                GHOST_IMPL_FUNCTION_CLOSE
            #endif
            #define ghost_has_ghost_memccpy 1

        #elif defined(__unix__) || defined(__APPLE__)
            /* We expect other UNIX platforms to declare it unconditionally. */
            #define ghost_memccpy memccpy
            #define ghost_has_ghost_memccpy 1
        #endif
    #endif
#endif

/* There is no __builtin_memccpy() in GCC or Clang (yet.) */

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_memccpy
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/language/ghost_null.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    void* ghost_memccpy(void* ghost_restrict vdest, const void* ghost_restrict vsrc,
            int c, ghost_size_t count) GHOST_IMPL_DEF(
    {
        const unsigned char* ghost_restrict src = ghost_static_cast(const unsigned char*, vsrc);
        unsigned char* dest = ghost_static_cast(unsigned char*, vdest);
        unsigned char* end = dest + count;

        /* The C23 standard specifies that we're searching for `(unsigned char)c`. */
        unsigned char uc = ghost_static_cast(unsigned char, c);

        while (dest != end) {
            /* The character is supposed to be copied even if it matches. */
            *dest = *src;

            /* Return a pointer to the next character after the match. */
            ++dest;
            if (*src == uc)
                return dest;
            ++src;
        }

        /* Return NULL if the character was not found. */
        return ghost_null;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memccpy 1
#endif

#endif
