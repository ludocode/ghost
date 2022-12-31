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

#ifndef GHOST_BCMP_H_INCLUDED
#define GHOST_BCMP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * Compares memory, returning 0 if equal (or if n is 0) and non-zero
 * otherwise (without returning ordering.)
 *
 * Unlike memcmp(), this does not tell you the relative ordering of the
 * arguments.
 *
 * The bcmp() function is considered obsolete. It was originally in POSIX,
 * was deprecated in 2001 and was removed from POSIX in 2008. Despite this,
 * bcmp() can in theory be implemented more efficiently than memcmp() because
 * it doesn't need to compute ordering, so it is still in use:
 *
 * - Some platforms provide a faster bcmp() than memcmp(). For example:
 *       https://reviews.freebsd.org/D34673
 *
 * - Some libraries take advantage of this by calling bcmp() instead of
 *   memcmp() with the expectation that it may be faster.
 *
 * - Some compilers also take advantage of this, for example LLVM optimizes
 *   (0 == memcmp(...)) to (0 == bcmp(...)) where bcmp() exists.
 *
 * There are some efforts at reviving this, either as the original bcmp()
 * or as a new function like memeq(). For the above reasons Ghost does not
 * consider ghost_bcmp() to be deprecated.
 */
int ghost_bcmp(const void* a, const void* b, size_t count);
#endif

#ifndef ghost_has_ghost_bcmp
    #ifdef ghost_bcmp
        #define ghost_has_ghost_bcmp 1
    #endif
#endif

/* If we have a builtin bcmp(), we prefer it to any of our other workarounds.
 * GCC only recognizes bcmp() as a builtin under the -std=gnu* options, not
 * -std=c*. We want the compiler to recognize bcmp() always so it can optimize
 * it properly. */
#ifndef ghost_has_ghost_bcmp
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_bcmp)
            /*
             * Clang lies! Under Clang 8 and earlier, __has_builtin(__builtin_bcmp)
             * is 1, but trying to use it results in:
             *
             *     error: cannot compile this builtin function yet
             *
             * (The broken builtin also takes void*, not const void*, so you may
             * get const warnings before you get the above error.)
             */
            /* TODO this version check won't work on e.g. Apple Clang and
             * other variants, for now we assume it exists on Apple */
            #if defined(__clang__) && !defined(__APPLE__)
                #if __clang_major__ >= 9
                    #define ghost_bcmp __builtin_bcmp
                    #define ghost_has_ghost_bcmp 1
                #endif
            #else
                #define ghost_bcmp __builtin_bcmp
                #define ghost_has_ghost_bcmp 1
            #endif
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define ghost_bcmp __builtin_bcmp
            #define ghost_has_ghost_bcmp 1
        #endif
    #endif
#endif

/*
 * Various platforms have bcmp() but few declare it unconditionally. We could
 * wrap it but that would preclude compilers from recognizing it as a
 * builtin/intrinsic. It's better to just fallback to memcmp().
 */
#ifndef ghost_has_ghost_bcmp
    #include "ghost/string/ghost_memcmp.h"
    #define ghost_bcmp ghost_memcmp
    #define ghost_has_ghost_bcmp 1
#endif

#endif
