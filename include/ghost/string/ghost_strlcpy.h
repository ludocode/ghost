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

#ifndef GHOST_STRLCPY_H_INCLUDED
#define GHOST_STRLCPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Copies a string from src to the non-overlapping buffer dest of size n,
 * guaranteeing null-termination (provided n is non-zero.)
 *
 * At most n-1 bytes will be copied from src. A null terminator is always
 * appended to the destination string unless n is zero.
 *
 * The total length of the src string is returned, not including its null
 * terminator. You can therefore detect truncation by checking if the return
 * value is greater than or equal to n.
 *
 * Unlike strncpy(), this *is* a safer strcpy(). Prefer this instead of
 * strcpy() and strncpy().
 *
 *     https://man.openbsd.org/strlcpy
 */
size_t ghost_strlcpy(char* restrict dest, const char* restrict src, size_t n);
#endif

/* The BSDs and macOS provide strlcpy() in libc.
 *     https://man.openbsd.org/strlcpy */
#ifndef ghost_has_ghost_strlcpy
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__DragonFly__) || defined(__APPLE__)
        #include "ghost/header/c/ghost_string_h.h"
        #define ghost_strlcpy strlcpy
        #define ghost_has_ghost_strlcpy 1
    #endif
#endif

/* libbsd ports BSD strlcpy() to other platforms. */
#ifndef ghost_has_ghost_strlcpy
    #include "ghost/impl/binding/libbsd/ghost_impl_libbsd_config.h"
    #if GHOST_USE_LIBBSD
        #include "ghost/impl/binding/libbsd/ghost_impl_libbsd_string_h.h"
        #define ghost_strlcpy strlcpy
        #define ghost_has_ghost_strlcpy 1
    #endif
#endif

/* Otherwise we provide a small fallback implementation. */
#ifndef ghost_has_ghost_strlcpy
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/language/ghost_expect_true.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"

    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_size_t ghost_strlcpy(char* ghost_restrict to,
            const char* ghost_restrict from, ghost_size_t count) GHOST_IMPL_DEF(
    {
        const char* from_start = from;

        /* TODO test this */

        /* If count is 0, we can't even write a null-terminator. I can't
         * imagine how calling this with a size of 0 could ever be reasonable
         * in correct code but the man page implies that it's not undefined
         * behaviour so we have to handle it "safely". */
        if (ghost_expect_true(count > 0)) {

            /* copy up to count-1 bytes */
            char* to_end = to + count - 1;
            while (to != to_end && *from != '\000') {
                *to = *from;
                ++to;
                ++from;
            }

            /* write the null-terminator */
            *to = 0;
        }

        /* return the total length of from */
        while (*from)
            ++from;
        return ghost_static_cast(size_t, from - from_start);
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strlcpy 1
#endif

#endif
