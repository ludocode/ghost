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

#ifndef GHOST_IMPL_ATTRIB_MALLOC_H_INCLUDED
#define GHOST_IMPL_ATTRIB_MALLOC_H_INCLUDED

/* This is specifically for __attribute__((malloc)) without arguments. Some
 * compilers (like some versions of ICC) don't appear to support the arguments. */

#ifdef GHOST_IMPL_ATTRIB_MALLOC
    #error
#endif

/* If we have standard attributes, we should use it. (Clang doesn't allow
 * __attribute__((...)) before [[..]].)
 *
 * We don't use this on NVidia/PGI because the storage specifier (e.g.
 * `static`) has to come between C++11-style attributes and `inline`. The
 * `__attribute__` fallback below has no such restriction.
 */
#ifndef GHOST_IMPL_ATTRIB_MALLOC
    #if defined(__GNUC__) && !defined(__PGI)
        #include "ghost/impl/language/ghost_impl_standard_attribute.h"
        #if GHOST_IMPL_STANDARD_ATTRIBUTE
            #include "ghost/impl/language/ghost_impl_attribute_namespace_gnu.h"
            #define GHOST_IMPL_ATTRIB_MALLOC [[GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU::__malloc__]]
        #endif
    #endif
#endif

/* The malloc attribute was first implemented in Clang in version 3.2.
 * TODO this version check doesn't work on variants like Apple Clang. */
#ifndef GHOST_IMPL_ATTRIB_MALLOC
    #ifdef __clang__
        #if defined(__APPLE__) || __clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 1)
            #define GHOST_IMPL_ATTRIB_MALLOC __attribute__((malloc))
        #endif
    #endif
#endif

/* The malloc attribute was first implemented in at least GCC 4.0 and at least
 * Clang 3.0. We can worry about older versions later if needed. */
#ifndef GHOST_IMPL_ATTRIB_MALLOC
    #ifdef __GNUC__
        #define GHOST_IMPL_ATTRIB_MALLOC __attribute__((malloc))
    #endif
#endif

#ifndef GHOST_IMPL_ATTRIB_MALLOC
    #define GHOST_IMPL_ATTRIB_MALLOC /*nothing*/
#endif

#endif
