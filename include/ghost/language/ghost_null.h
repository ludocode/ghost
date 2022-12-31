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

#ifndef GHOST_NULL_H_INCLUDED
#define GHOST_NULL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def ghost_null
 *
 * Defines ghost_null to ((void*)0) in C or nullptr in C++11 or an equivalent.
 */
#endif

/* TODO none of this works, there is no __null in C, and I can't replicate the
 * problem I had with using ((void*)0) in a ternary */

/*
 * In C, ghost_null is defined to a compiler-specific extension or ((void*)0).
 * The C spec allows implementations to define NULL as 0 so we avoid it to
 * prevent platform-specific behaviour. We require compiler extensions on some
 * compilers (like __null in GCC/Clang) because ((void*)0) causes C++
 * compatibility warnings (e.g. from -Wc++-compat, because void* cannot be
 * implicitly cast to a typed pointer in C++.)
 *
 * The above rules guarantee that, when compiling as C, ghost_null will be the
 * size of a pointer when used as an argument to a variadic function and should
 * always match a pointer (or at least a void pointer) in a _Generic on all
 * platforms.
 *
 * In C++11 or later, ghost_null is defined to nullptr which also satisfies the
 * above criteria.
 *
 * In C++98, ghost_null is defined to NULL. Unfortunately ((void*)0) cannot be
 * implicitly converted to a typed pointer in C++. The C++ spec requires NULL
 * to be 0 since it must be an int for the purpose of overload resolution. Some
 * compilers nevertheless define NULL to an extension. We therefore simply use
 * NULL to take advantage of this without having to list them. On platforms
 * that don't have a special null, ghost_null in C++98 may have
 * incompatibilities with C and C++11 in varargs arguments, _Generic selection
 * and C++ function overload selection.
 *
 * Note that ghost_typeof(ghost_null) differs between C and C++. Ghost does not
 * have C++ nullptr_t.
 *
 * https://en.cppreference.com/w/c/types/NULL
 * https://en.cppreference.com/w/cpp/types/NULL
 * https://en.cppreference.com/w/cpp/language/nullptr
 */

#ifndef ghost_has_ghost_null
    #ifdef ghost_null
        #define ghost_has_ghost_null 1
    #endif
#endif

#ifndef ghost_has_ghost_null
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            /* In C++11 we use nullptr. */
            #define ghost_null nullptr
        #else
            /* Apparently a whole lot of headers can provide us NULL. We prefer
             * <stddef.h>. */
            #include "ghost/header/c/ghost_stddef_h.h"
            /* Even if some crazy C++ compiler doesn't have <stddef.h> we
             * assume it still somehow provides NULL. */
            #define ghost_null NULL
        #endif
    #else
        /* In C it's always ((void*)0). We avoid NULL in case it's 0; we don't
         * want ghost_null to be an int. */
        #define ghost_null ((void*)0)
    #endif
    #define ghost_has_ghost_null 1
#endif

#endif
