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

#ifndef GHOST_MEMRCHR_H_INCLUDED
#define GHOST_MEMRCHR_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches the given memory range for the character c, returning a pointer to
 * the last instance of it or null if not found.
 */
void* ghost_memrchr(const void* s, int c, size_t n);
#endif

#ifndef ghost_has_ghost_memrchr
    #ifdef ghost_memrchr
        #define ghost_has_ghost_memrchr 1
    #endif
#endif

/* memrchr() is a GNU extension.
 * TODO glibc, maybe musl and others */

/* Otherwise we define our own. */
#ifndef ghost_has_ghost_memrchr
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/language/ghost_const_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    void* ghost_memrchr(const void* vdata, int c, ghost_size_t count) GHOST_IMPL_DEF({
        const char* data = ghost_static_cast(const char*, vdata);
        ghost_size_t i;
        void* ret = ghost_null;
        for (i = 0; i < count; ++i)
            if (data[i] == c)
                ret = ghost_const_cast(char*, data + i);
        return ret;
    })
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memrchr 1
#endif

#endif
