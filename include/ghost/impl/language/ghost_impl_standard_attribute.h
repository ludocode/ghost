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

#ifndef GHOST_IMPL_STANDARD_ATTRIBUTE_H_INCLUDED
#define GHOST_IMPL_STANDARD_ATTRIBUTE_H_INCLUDED

/*
 * @def GHOST_IMPL_STANDARD_ATTRIBUTE
 *
 * 1 if the standard [[...]] attribute syntax is supported, 0 otherwise.
 *
 * This does not check whether the old-style __attribute__((...)) syntax is
 * supported and there is no wrapper to use whichever is available. The two
 * syntaxes are handled separately by Ghost because they are treated
 * differently by compilers. For example:
 *
 * - PGI/NVidia handles __attribute__((always_inline)) differently from
 *   [[always_inline]]: it has more restrictions on where the latter can be
 *   placed (see ghost_always_inline.)
 *
 * - GCC and PGI/NVidia handle __attribute__((warn_unused_result)) differently
 *   from [[nodiscard]]: the former cannot be silenced by a cast to void (see
 *   ghost_discard.)
 *
 * - Clang complains if an old-style __attribute__((...)) appears between two
 *   standard [[...]] attributes (see ghost_cold.)
 */

#ifdef GHOST_IMPL_STANDARD_ATTRIBUTE
    #error
#endif

/* Standard attributes were only added in GCC 4.8 even though GCC 4.7
 * advertises C++11 support. See "Generalized attributes":
 *     https://gcc.gnu.org/projects/cxx-status.html */
#ifndef GHOST_IMPL_STANDARD_ATTRIBUTE
    #ifdef __GNUC__
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 8)
                #define GHOST_IMPL_STANDARD_ATTRIBUTE 0
            #endif
        #endif
    #endif
#endif

/* C++11 has standard attributes. */
#ifndef GHOST_IMPL_STANDARD_ATTRIBUTE
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 201103L
            #define GHOST_IMPL_STANDARD_ATTRIBUTE 1
        #endif
    #endif
#endif

/* C23 has standard attributes. */
#ifndef GHOST_IMPL_STANDARD_ATTRIBUTE
    #ifdef __STDC_VERSION__
        #include "ghost/language/ghost_stdc_version.h"
        #if GHOST_STDC_VERSION >= 202000L && !GHOST_IMPL_ENABLE_C23
            #define GHOST_IMPL_STANDARD_ATTRIBUTE 1
        #endif
    #endif
#endif

/* Otherwise we don't have it. */
#ifndef GHOST_IMPL_STANDARD_ATTRIBUTE
    #define GHOST_IMPL_STANDARD_ATTRIBUTE 0
#endif

#endif
