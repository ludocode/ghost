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

#ifndef GHOST_STRCSPN_H_INCLUDED
#define GHOST_STRCSPN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the length of the longest prefix of s in which none of the
 * characters are in the set of characters in reject.
 */
size_t ghost_strcspn(const char* s, const char* reject);
#endif

#ifndef ghost_has_ghost_strcspn
    #ifdef ghost_strcspn
        #define ghost_has_ghost_strcspn 1
    #endif
#endif

/* TODO glibc has this */

#ifndef ghost_has_ghost_strcspn
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_size_t ghost_strcspn(const char* s, const char* reject) GHOST_IMPL_DEF({
        const char* start = s;
        while (*s) {
            const char* k;
            for (k = reject; *k != '\000'; ++k)
                if (*s == *k)
                    goto done;
            ++s;
        }
    done:
        return ghost_static_cast(size_t, s - start);
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_strcspn 1
#endif

#endif
