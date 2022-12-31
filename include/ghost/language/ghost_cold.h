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

#ifndef GHOST_COLD_H_INCLUDED
#define GHOST_COLD_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_cold [[cold]]
 *
 * Tells the compiler that this function is cold, meaning it is rarely used. If
 * supported, it may be less likely to be inlined, and may be placed in a
 * separate section with other cold functions.
 *
 * This may be ignored if profile-guided optimization is used. Profile-guided
 * optimization is generally a better way of determining which functions are
 * hot or cold.
 */
#endif

#ifndef ghost_has_ghost_cold
    #ifdef ghost_cold
        #define ghost_has_ghost_cold 1
    #endif
#endif

/* With Clang we have to use C++11-style [[gnu::cold]] where possible,
 * otherwise it will complain if __attribute__((cold)) appears between
 * C++11-style attributes like [[noreturn]] and [[maybe_unused]]. */
#ifndef ghost_has_ghost_cold
    #if defined(__clang__)
        #include "ghost/impl/language/ghost_impl_standard_attribute.h"
        #if GHOST_IMPL_STANDARD_ATTRIBUTE
            #include "ghost/impl/language/ghost_impl_attribute_namespace_gnu.h"
            #define ghost_cold [[GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU::__cold__]]
            #define ghost_has_ghost_cold 1
        #endif
    #endif
#endif

/* We otherwise prefer the GCC-style attribute since it has less placement
 * restrictions. We assume all __GNUC__ compilers support it other than those
 * explicitly listed. */
#ifndef ghost_has_ghost_cold
    #if defined(__GNUC__) && !defined(__CPARSER__) && !defined(__PCC__)
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
                /* GCC 4.2 added attribute cold. */
                #define ghost_cold __attribute__((__cold__))
                #define ghost_has_ghost_cold 1
            #endif
        #else
            #define ghost_cold __attribute__((__cold__))
            #define ghost_has_ghost_cold 1
        #endif
    #endif
#endif

/* This is just a compiler hint. If unsupported, we ignore it. */
#ifndef ghost_has_ghost_cold
    #define ghost_cold /*nothing*/
    #define ghost_has_ghost_cold 1
#endif

#endif
