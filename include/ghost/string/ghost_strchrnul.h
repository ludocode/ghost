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

#ifndef GHOST_STRCHRNUL_H_INCLUDED
#define GHOST_STRCHRNUL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches the given string, returning a pointer to the first instance of the
 * given character or a pointer to the null terminator of the string if not
 * found.
 */
char* ghost_strchrnul(const char* s, int c);
#endif

/* This is a glibc extension. It's only declared under _GNU_SOURCE.
 * In C++ we require asm labels because the glibc headers use asm labels to
 * declare C++ variant functions (const and non-const.) All C++ compilers built
 * against glibc should support asm labels. */
#ifndef ghost_has_ghost_strchrnul
    #include "ghost/header/c/ghost_string_h.h"
    #if ghost_has(ghost_string_h)
        #include "ghost/detect/ghost_libc.h"
        #include "ghost/detect/ghost_glibc.h"
        #include "ghost/impl/ghost_impl_glibc_compat.h"
        #if GHOST_GLIBC && GHOST_GLIBC_COMPAT == 0
            #include "ghost/impl/ghost_impl_libc_asm.h"
            #include "ghost/impl/ghost_impl_libc_noexcept.h"
            #if GHOST_IMPL_LIBC_ASM || !defined(__cplusplus)
                #include "ghost/impl/ghost_impl_always_inline.h"
                #include "ghost/language/ghost_dllimport.h"
                #include "ghost/preprocessor/ghost_nothing.h"

                #if GHOST_IMPL_LIBC_ASM
                    ghost_dllimport
                    char* ghost_strchrnul(const char*, int)
                        ghost_impl_libc_noexcept(ghost_impl_libc_asm("strchrnul"));
                #else
                    GHOST_IMPL_FUNCTION_OPEN
                    ghost_impl_always_inline
                    char* ghost_strchrnul(const char* ghost_impl_v_s, int ghost_impl_v_c) {
                        ghost_dllimport
                        extern char* strchrnul(const char*, int)
                            ghost_impl_libc_noexcept(GHOST_NOTHING);
                        return strchrnul(ghost_impl_v_s, ghost_impl_v_c);
                    }
                    GHOST_IMPL_FUNCTION_CLOSE
                #endif

                #define ghost_has_ghost_strchrnul 1
            #endif
        #endif
    #endif
#endif

/* Otherwise define a slow but small fallback. */
#ifndef ghost_has_ghost_strchrnul
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_const_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strchrnul(const char* s, int c) GHOST_IMPL_DEF({
        while (*s != '\0') {
            if (*s == c)
                break;
            ++s;
        }
        return ghost_const_cast(char*, s);
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strchrnul 1
#endif

#endif
