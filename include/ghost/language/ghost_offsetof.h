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

#ifndef GHOST_OFFSETOF_H_INCLUDED
#define GHOST_OFFSETOF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_offsetof(type_name, member_name)
 *
 * Returns the offset in bytes of a member of a struct relative to the start of
 * the struct.
 *
 * For example:
 *
 *     struct foo_t {
 *         int a;
 *         int b;
 *     };
 *
 *     size_t offset = ghost_offsetof(struct foo_t, b);
 */
#endif

#ifndef ghost_has_ghost_offsetof
    #ifdef ghost_offsetof
        #define ghost_has_ghost_offsetof 1
    #endif
#endif

/* Use a builtin if possible. */
#ifndef ghost_has_ghost_offsetof
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_offsetof)
            #define ghost_offsetof(structure, member) __builtin_offsetof(structure, member)
            #define ghost_has_ghost_offsetof 1
        #endif
    #else
        /* Real GCC has supported __builtin_offsetof roughly forever. Compilers
         * that impersonate it may not. */
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define ghost_offsetof(structure, member) __builtin_offsetof(structure, member)
            #define ghost_has_ghost_offsetof 1
        #endif
    #endif
#endif

/* kefir doesn't yet provide <stddef.h>. The one from GCC assumes support for
 * __builtin_offsetof but kefir doesn't support that either. We use an
 * implementation in plain C. */
#ifndef ghost_has_ghost_offsetof
    #ifdef __KEFIRCC__
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/type/uintptr_t/ghost_uintptr_t.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/language/ghost_reinterpret_cast.h"
        #include "ghost/language/ghost_null.h"
        /* This is technically a null pointer dereference so it is not
         * technically legal C. It seems to work well enough for the compilers
         * that use it. */
        #define ghost_offsetof(structure, member) \
                ghost_static_cast(size_t, ghost_reinterpret_cast(uintptr_t, ghost_reinterpret_cast(const char*, \
                            &ghost_reinterpret_cast(structure*, ghost_static_cast(ghost_uintptr_t, 0u))->member)))
        #define ghost_has_ghost_offsetof 1
    #endif
#endif

/* offsetof is required by all C and C++ standards. We assume it exists and
 * behaves properly. */
#ifndef ghost_has_ghost_offsetof
    #include <stddef.h>
    #define ghost_offsetof offsetof
    #define ghost_has_ghost_offsetof 1
#endif

#endif
