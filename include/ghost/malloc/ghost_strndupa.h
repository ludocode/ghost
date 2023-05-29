/*
 * MIT No Attribution
 *
 * Copyright (c) 2022-2023 Fraser Heavy Software
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

#ifndef GHOST_STRNDUPA_H_INCLUDED
#define GHOST_STRNDUPA_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns a copy of the given string limited to the given length (not
 * including the null terminator), allocating the copy from the stack as if by
 * alloca().
 *
 * The resulting stack allocation will be at most max_length+1 bytes. It will
 * always be null-terminated.
 *
 * @warning This function can be dangerous! It can consume arbitrary amounts of
 *          stack space, overflowing the stack.
 *
 * @note This macro is not available on some popular platforms, in particular
 *       Windows. Don't use it if you want your code to be portable.
 */
char* ghost_strndup(const char* s, size_t n);
#endif

#ifndef ghost_has_ghost_strndupa
    #ifdef ghost_strndupa
        #define ghost_has_ghost_strndupa 1
    #endif
#endif

/* strndupa() is available on a few platforms including glibc and Solaris. It
 * is highly likely to be implemented as a macro since it must call alloca() in
 * the caller so we can check whether it exists. With glibc it requires
 * _GNU_SOURCE. */
#ifndef ghost_has_ghost_strndupa
    #include "ghost/header/c/ghost_string_h.h"
    #ifdef strndupa
        #define ghost_strndupa strndupa
        #define ghost_has_ghost_strndupa 1
    #endif
#endif

/* We need GNU statement expressions to avoid evaluating the argument twice. */
#ifndef ghost_has_ghost_strndupa
    #ifdef __GNUC__
        #include "ghost/malloc/ghost_alloca.h"
        #if ghost_has(ghost_alloca)
            #include "ghost/string/ghost_strlen.h"
            #include "ghost/string/ghost_memcpy.h"
            #include "ghost/math/min/ghost_min_z.h"
            #include "ghost/type/size_t/ghost_size_t.h"
            #include "ghost/language/ghost_static_cast.h"
            #define ghost_strndupa(s, n) ( __extension__ \
                ({ \
                    const char* ghost_impl_v_s = (s); \
                    /* don't copy the null-terminator in case we're */ \
                    /* truncating; write it ourselves afterwards */ \
                    ghost_size_t ghost_impl_v_len = ghost_min_z(ghost_strlen(ghost_impl_v_s), (n)); \
                    char* ghost_impl_v_p = ghost_static_cast(char*, ghost_alloca(ghost_impl_v_len) + 1); \
                    ghost_memcpy(ghost_impl_v_p, ghost_impl_v_s, ghost_impl_v_len); \
                    ghost_impl_v_p[ghost_impl_v_len] = '\000'; \
                    ghost_impl_v_p; \
                })
            #define ghost_has_ghost_strndupa 1
        #endif
    #endif
#endif

/* Otherwise we can't safely implement it. */
#ifndef ghost_has_ghost_strndupa
    #define ghost_has_ghost_strndupa 0
#endif

#endif
