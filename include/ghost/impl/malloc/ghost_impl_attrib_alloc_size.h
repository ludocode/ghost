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

#ifndef GHOST_IMPL_ATTRIB_ALLOC_SIZE_H_INCLUDED
#define GHOST_IMPL_ATTRIB_ALLOC_SIZE_H_INCLUDED

#ifdef GHOST_IMPL_ATTRIB_ALLOC_SIZE
    #error
#endif

/* If we have standard attributes, we should use it. (Clang doesn't allow
 * __attribute__((...)) before [[..]].)
 *
 * We don't use this on NVidia/PGI because the storage specifier (e.g.
 * `static`) has to come between C++11-style attributes and `inline`. The
 * `__attribute__` fallback below has no such restriction.
 */
#ifndef GHOST_IMPL_ATTRIB_ALLOC_SIZE
    #if defined(__GNUC__) && !defined(__PGI)
        #include "ghost/impl/language/ghost_impl_standard_attribute.h"
        #if GHOST_IMPL_STANDARD_ATTRIBUTE
            #include "ghost/impl/language/ghost_impl_attribute_namespace_gnu.h"
            #define GHOST_IMPL_ATTRIB_ALLOC_SIZE(x) [[GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU::__alloc_size__ x]]
        #endif
    #endif
#endif

/* The alloc_size attribute was first implemented in Clang 4.
 * TODO this version check doesn't work on variants like Apple Clang. */
#ifndef GHOST_IMPL_ATTRIB_ALLOC_SIZE
    #ifdef __clang__
        #if defined(__APPLE__) || __clang_major__ >= 4
            #define GHOST_IMPL_ATTRIB_ALLOC_SIZE(x) __attribute__((alloc_size x))
        #endif
    #endif
#endif

#ifndef GHOST_IMPL_ATTRIB_ALLOC_SIZE
    #ifdef __GNUC__
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* The alloc_size attribute was first implemented in GCC in version 4.4 or so. */
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)
                #define GHOST_IMPL_ATTRIB_ALLOC_SIZE(x) __attribute__((alloc_size x))
            #endif
        #elif !defined(__clang__)
            /* We assume other GNU C compilers support it. */
            #define GHOST_IMPL_ATTRIB_ALLOC_SIZE(x) __attribute__((alloc_size x))
        #endif
    #endif
#endif

#ifndef GHOST_IMPL_ATTRIB_ALLOC_SIZE
    #define GHOST_IMPL_ATTRIB_ALLOC_SIZE(x) /*nothing*/
#endif

#endif
