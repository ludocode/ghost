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

#ifndef GHOST_STRNSTR_H_INCLUDED
#define GHOST_STRNSTR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches for needle in the first n characters of haystack (or the entire
 * haystack if it is shorter), returning the first instance of the needle or
 * null if it is not found.
 */
char* ghost_strnstr(const char* haystack, const char* needle, size_t n);
#endif

#ifndef ghost_has_ghost_strnstr
    #ifdef ghost_strnstr
        #define ghost_has_ghost_strnstr 1
    #endif
#endif

/*
 * FreeBSD, NetBSD and DragonFlyBSD have strnstr() in <string.h>. OpenBSD
 * apparently does not.
 *
 *     https://www.freebsd.org/cgi/man.cgi?query=strnstr
 *     https://man.netbsd.org/strnstr.3
 *     https://man.dragonflybsd.org/?command=strnstr&section=ANY
 */
#ifndef ghost_has_ghost_strnstr
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
        #include "ghost/header/c/ghost_string_h.h"
        #define ghost_strnstr strnstr
        #define ghost_has_ghost_strnstr 1
    #endif
#endif

/* libbsd ports BSD strnstr() to other platforms. */
#ifndef ghost_has_ghost_strnstr
    #include "ghost/impl/binding/libbsd/ghost_impl_libbsd_config.h"
    #if GHOST_USE_LIBBSD
        #include "ghost/impl/binding/libbsd/ghost_impl_libbsd_string_h.h"
        #define ghost_strnstr strnstr
        #define ghost_has_ghost_strnstr 1
    #endif
#endif

/* Otherwise implement a standard C fallback.
 * For now we don't bother to write a fast search algorithm that can handle
 * null-terminated strings; see ghost_strstr(). */
#ifndef ghost_has_ghost_strnstr
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/string/ghost_memmem.h"
    #include "ghost/string/ghost_strlen.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/math/max/ghost_max_z.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strnstr(const char* haystack, const char* needle, ghost_size_t n) GHOST_IMPL_DEF({
        return ghost_static_cast(char*,
                ghost_memmem(haystack, ghost_max_z(n, ghost_strlen(haystack)),
                    needle, ghost_strlen(needle)));
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strnstr 1
#endif

#endif
