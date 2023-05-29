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

#ifndef GHOST_STRNLEN_H_INCLUDED
#define GHOST_STRNLEN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the length of the given string up to a maximum of maxlen.
 *
 * At most maxlen characters will be checked. If a null terminator is not
 * found before maxlen, this returns maxlen.
 *
 * If s is null, the behaviour is undefined.
 */
size_t ghost_strnlen(const char* s, size_t maxlen);
#endif

#ifndef ghost_has_ghost_strnlen
    #ifdef ghost_strnlen
        #define ghost_has_ghost_strnlen 1
    #endif
#endif

/* Use the builtin if possible. */
#ifndef ghost_has_ghost_strnlen
    /* If we have __has_builtin we check. (Note that Clang doesn't currently
     * support this.) */
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_strnlen)
            #define ghost_strnlen __builtin_strnlen
            #define ghost_has_ghost_strnlen 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* __builtin_strnlen was added in GCC 9.
             *     https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html */
            #if __GNUC__ >= 9
                #define ghost_strnlen __builtin_strnlen
                #define ghost_has_ghost_strnlen 1
            #endif
        #endif
    #endif
#endif

/* These platforms support strnlen() natively. */
#ifndef ghost_has_ghost_strnlen
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__DragonFly__) || defined(_WIN32)
        #include "ghost/header/c/ghost_string_h.h"
        #define ghost_strnlen strnlen
        #define ghost_has_ghost_strnlen 1
    #endif
#endif

/* Linux libcs only define strnlen() under _GNU_SOURCE or >2008 _POSIX_C_SOURCE.
 * We assume all Linux libcs have the symbol.
 * Apple platforms also declare it conditionally. */
#ifndef ghost_has_ghost_strnlen
    #if defined(__linux__) || defined(__APPLE__)
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_asm_label.h"
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/impl/ghost_impl_libc_noexcept.h"
        #include "ghost/preprocessor/ghost_nothing.h"
        #if GHOST_IMPL_LIBC_ASM
            ghost_dllimport
            ghost_size_t ghost_strnlen(const char* s, ghost_size_t maxlen)
                ghost_impl_libc_noexcept(ghost_impl_libc_asm("strnlen"));
        #else
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            ghost_size_t ghost_strnlen(const char* s, ghost_size_t maxlen) {
                ghost_dllimport
                ghost_size_t strnlen(const char* s, ghost_size_t maxlen)
                    ghost_impl_libc_noexcept(GHOST_NOTHING);
                return strnlen(s, maxlen);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #endif
        #define ghost_has_ghost_strnlen 1
    #endif
#endif

/* TODO we should try to detect POSIX support here, it's in POSIX 2008. */

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_strnlen
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_size_t ghost_strnlen(const char* s, ghost_size_t maxlen) GHOST_IMPL_DEF({
        const char* maxend = s + maxlen;
        const char* end = s;
        while (end != maxend && *end != '\000')
            ++end;
        return ghost_static_cast(ghost_size_t, end - s);
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strnlen 1
#endif

#endif
