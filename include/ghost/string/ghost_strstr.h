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

#ifndef GHOST_STRSTR_H_INCLUDED
#define GHOST_STRSTR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches for needle in haystack, returning the first instance of it or null
 * if it is not found.
 */
char* ghost_strstr(const char* haystack, const char* needle);
#endif

#ifndef ghost_has_ghost_strstr
    #ifdef ghost_strstr
        #define ghost_has_ghost_strstr 1
    #endif
#endif

/* TODO posix 2001, BSDs, glibc, musl */

/*
 * Otherwise implement a standard C fallback.
 * For now we don't bother to write a fast search algorithm that can handle
 * null-terminated strings. Instead we just use strlen() and pass it over to
 * memmem(). This means the haystack will be scanned twice, but most platforms
 * probably have a very fast memmem() and if they don't, Ghost's fallback
 * memmem() is simple and has reasonable performance.
 */
#ifndef ghost_has_ghost_strstr
    #include "ghost/language/ghost_restrict.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/string/ghost_memmem.h"
    #include "ghost/string/ghost_strlen.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    char* ghost_strstr(const char* haystack, const char* needle) GHOST_IMPL_DEF({
        return ghost_static_cast(char*,
                ghost_memmem(haystack, ghost_strlen(haystack),
                    needle, ghost_strlen(needle)));
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strstr 1
#endif

#endif
