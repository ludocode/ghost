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

#ifndef GHOST_SILENCE_CXX_COMPAT_H_INCLUDED
#define GHOST_SILENCE_CXX_COMPAT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_CXX_COMPAT
 *
 * Silences warnings about C++ compatibility in C.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_CXX_COMPAT
    #ifdef GHOST_SILENCE_CXX_COMPAT
        #define ghost_has_GHOST_SILENCE_CXX_COMPAT 1
    #endif
#endif

/*
 * For GNU C compilers, this silences -Wc++-compat.
 *
 * Under Clang, apparently the only thing it warns about is structs that have
 * different sizes in C and C++.
 *
 * Under GCC it also warns about implicit void pointer casts among other
 * things, so this is needed to make ghost_auto_cast() work without warnings.
 */
#ifndef ghost_has_GHOST_SILENCE_CXX_COMPAT
    #if !defined(__cplusplus) && defined(__GNUC__) && !defined(__CPARSER__)
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            /* _Pragma() wasn't supported until GCC 4.2 */
            #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
                #define GHOST_SILENCE_CXX_COMPAT _Pragma("GCC diagnostic ignored \"-Wc++-compat\"")
                #define ghost_has_GHOST_SILENCE_CXX_COMPAT 1
            #endif
        #else
            #define GHOST_SILENCE_CXX_COMPAT _Pragma("GCC diagnostic ignored \"-Wc++-compat\"")
            #define ghost_has_GHOST_SILENCE_CXX_COMPAT 1
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_CXX_COMPAT
    #define GHOST_SILENCE_CXX_COMPAT /*nothing*/
    #define ghost_has_GHOST_SILENCE_CXX_COMPAT 1
#endif

#endif
