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

#ifndef GHOST_STRLCAT_H_INCLUDED
#define GHOST_STRLCAT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Defines ghost_strlcat() to BSD strlcat() or an equivalent.
 */
#endif

#ifndef ghost_has_ghost_strlcat
    #ifdef ghost_strlcat
        #define ghost_has_ghost_strlcat 1
    #endif
#endif

/* The BSDs and macOS provide strlcat() in <string.h>. */
#ifndef ghost_has_ghost_strlcat
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
            defined(__DragonFly__) || defined(__APPLE__)
        /* https://man.openbsd.org/strlcat */
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has(ghost_string_h)
            #define ghost_strlcat strlcat
            #define ghost_has_ghost_strlcat 1
        #endif
    #endif
#endif

/* libbsd ports BSD strlcat() to other platforms. */
#ifndef ghost_strlcat
    #include "ghost/impl/binding/libbsd/ghost_impl_libbsd_config.h"
    #if GHOST_USE_LIBBSD
        #include "ghost/impl/binding/libbsd/ghost_impl_libbsd_string_h.h"
        #define ghost_strlcat strlcat
        #define ghost_has_ghost_strlcat 1
    #endif
#endif

/* Otherwise we provide a slow but small fallback implementation. Since not
 * many platforms support this, I'm open to making this faster. */
#ifndef ghost_strlcat
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/language/ghost_expect_true.h"
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_size_t ghost_strlcat(char* ghost_restrict to,
            const char* ghost_restrict from, ghost_size_t count) GHOST_IMPL_DEF(
    {
        const char* from_start = from;

        /* Find the end of the destination. */
        while (*to != '\0' && count != 0) {
            ++to;
            --count;
        }

        /* Write bytes (if there's any space left) */
        if (count > 0) {

            /* copy up to count-1 bytes */
            char* to_end = to + count - 1;
            while (to != to_end && *from) {
                ++to;
                ++from;
            }

            /* write the null-terminator */
            *to = 0;
        }

        /* return the total length of from */
        while (*from)
            ++from;
        return ghost_static_cast(ghost_size_t, from - from_start);
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strlcat 1
#endif

#endif
