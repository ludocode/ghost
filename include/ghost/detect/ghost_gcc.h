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

#ifndef GHOST_GCC_H_INCLUDED
#define GHOST_GCC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def GHOST_GCC
 *
 * 1 if the compiler is GCC (and not some other compiler that defines
 * __GNUC__), and 0 otherwise.
 */
#endif

#ifndef ghost_has_GHOST_GCC
    #ifdef GHOST_GCC
        #define ghost_has_GHOST_GCC 1
    #endif
#endif

#ifndef ghost_has_GHOST_GCC
    /*
     * chibicc doesn't define __GNUC__ yet but the developer has suggested it
     * might at some point. It's almost inconceivable that MSVC would define
     * __GNUC__ but someone might try to define it themselves. Just to be safe
     * we list every C compiler we've ever heard of in alphabetical order.
     */

    #include "ghost/detect/ghost_cproc.h"

    #if defined(__GNUC__) && \
            !defined(_MSC_VER) /* Microsoft Visual C/C++ */ && \
            !defined(__CPARSER__) && \
            !GHOST_CPROC && \
            !defined(__DMC__) /* Digital Mars C/C++ */ && \
            !defined(__INTEL_COMPILER) && \
            !defined(__KEFIRCC__) && \
            !defined(__LCC__) && \
            !defined(__PCC__) /* Portable C Compiler */ && \
            !defined(__PGI) && !defined(__NVCOMPILER) /* NVIDIA HPC (formerly PGI) */ && \
            !defined(__chibicc__) && \
            !defined(__clang__) && \
            !defined(__lacc__)
        #define GHOST_GCC 1
    #else
        #define GHOST_GCC 0
    #endif
    #define ghost_has_GHOST_GCC 1
#endif

#endif
