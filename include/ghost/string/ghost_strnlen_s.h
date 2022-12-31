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

#ifndef GHOST_STRNLEN_S_H_INCLUDED
#define GHOST_STRNLEN_S_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * A wrapper around strnlen() that returns 0 if s is null.
 *
 * This is otherwise identical to strnlen().
 *
 *     https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strnlen-strnlen-s
 */
size_t ghost_strnlen_s(const char* s, size_t maxlen);
#endif

#ifndef ghost_has_ghost_strnlen_s
    #ifdef ghost_strnlen_s
        #define ghost_has_ghost_strnlen_s 1
    #endif
#endif

/* Windows */
#ifndef ghost_has_ghost_strnlen_s
    #ifdef _WIN32
        #include "ghost/header/c/ghost_string_h.h"
        #define ghost_strnlen_s strnlen_s
        #define ghost_has_ghost_strnlen_s 1
    #endif
#endif

/* strnlen_s is in C11 Annex K but it's not widely implemented, detection is
 * not reliable, and we prefer to wrap builtin strnlen anyway. We ignore it. */

/* We otherwise just always_inline a check and wrapper around strnlen() because
 * strnlen() is provided as a builtin on some compilers. */
#ifndef ghost_has_ghost_strnlen_s
    #include "ghost/string/ghost_strnlen.h"
    #include "ghost/impl/ghost_impl_always_inline.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    ghost_impl_always_inline
    ghost_size_t ghost_strnlen_s(const char* s, ghost_size_t maxlen) {
        if (!s)
            return 0;
        return ghost_strnlen(s, maxlen);
    }
    #define ghost_has_ghost_strnlen_s 1
#endif

#endif
