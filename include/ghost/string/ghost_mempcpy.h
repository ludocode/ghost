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

#ifndef GHOST_MEMPCPY_H_INCLUDED
#define GHOST_MEMPCPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Same as `memcpy()` except it returns `dest + n` instead of `dest`.
 *
 * https://man.archlinux.org/man/mempcpy.3.en
 */
void* mempcpy(void* restrict dest, const void* restrict src, size_t n);
#endif

#ifndef ghost_has_ghost_mempcpy
    #ifdef ghost_mempcpy
        #define ghost_has_ghost_mempcpy 1
    #endif
#endif

/* Use the builtin if possible. */
#ifndef ghost_has_ghost_mempcpy
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_mempcpy)
            #define ghost_mempcpy __builtin_mempcpy
            #define ghost_has_ghost_mempcpy 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* Assume GCC has this. */
            #define ghost_mempcpy __builtin_mempcpy
            #define ghost_has_ghost_mempcpy 1
        #endif
    #endif
#endif

#ifndef ghost_has_ghost_mempcpy
    #include "ghost/detect/ghost_libc.h"
    #include "ghost/impl/ghost_impl_glibc_compat.h"
    #if (defined(__GLIBC__) || GHOST_MUSL) && GHOST_GLIBC_COMPAT == 0

        /* glibc and musl have this but only under _GNU_SOURCE. Wrap it so that
         * it works without it.
         * TODO check more libcs */

        #include "ghost/language/ghost_asm_label.h"
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/language/ghost_restrict.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/impl/ghost_impl_libc_noexcept.h"

        #if GHOST_IMPL_LIBC_ASM
            #include "ghost/language/ghost_extern_c.h"
            ghost_extern_c
            ghost_dllimport
            void* ghost_mempcpy(void* ghost_restrict dest, const void* ghost_restrict src,
                    ghost_size_t n)
                ghost_impl_libc_noexcept(ghost_impl_libc_asm("mempcpy"));
        #else
            #include "ghost/impl/ghost_impl_always_inline.h"
            #include "ghost/preprocessor/ghost_nothing.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            void* ghost_mempcpy(void* ghost_restrict dest, const void* ghost_restrict src,
                    ghost_size_t n)
            {
                ghost_dllimport
                void* mempcpy(void* ghost_restrict dest, const void* ghost_restrict src,
                        ghost_size_t n)
                    ghost_impl_libc_noexcept(GHOST_NOTHING);
                return mempcpy(dest, src, n);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #endif
        #define ghost_has_ghost_mempcpy 1
    #endif
#endif

/* As a fallback we just wrap ghost_memcpy(). */
#ifndef ghost_has_ghost_mempcpy
    #include "ghost/string/ghost_memcpy.h"
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/language/ghost_discard.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_always_inline
    void* ghost_mempcpy(void* ghost_restrict dest, const void* ghost_restrict src, ghost_size_t n) {
        ghost_discard(ghost_memcpy(dest, src, n));
        return ghost_static_cast(char*, dest) + n;
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_mempcpy 1
#endif

#endif
