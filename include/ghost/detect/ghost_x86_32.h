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

#ifndef GHOST_X86_32_H_INCLUDED
#define GHOST_X86_32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_X86_32
 *
 * Defined to 1 if the processor is 32-bit x86 (and not 64-bit x86_64) and 0
 * otherwise.
 *
 * Other names for this architecture are IA-32 and i386.
 *
 *     https://en.wikipedia.org/wiki/IA-32
 */
#endif

/* Handle override */
#ifndef ghost_has_GHOST_X86_32
    #ifdef GHOST_X86_32
        #define ghost_has_GHOST_X86_32 1
    #endif
#endif

/* Some compilers define preprocs for both 32-bit and 64-bit x86. If the
 * processor is x86_64, it is not 32-bit x86. */
#ifndef ghost_has_GHOST_X86_32
    #include "ghost/detect/ghost_x86_64.h"
    #if GHOST_X86_64
        #define GHOST_X86_32 0
        #define ghost_has_GHOST_X86_32 1
    #endif
#endif

/* See: https://sourceforge.net/p/predef/wiki/Architectures/ */
#ifndef ghost_has_GHOST_X86_32
    #if defined(i386) || defined(__i386) || defined(__i386__) || \
            defined(__i486__) || defined(__i586__) || defined(__i686__) || \
            defined(__IA32__) || \
            (defined(_M_IX86) && !defined(_M_I86)) || \
            defined(_M_I386) || \
            defined(__THW_INTEL__) || defined(__INTEL__) || \
            defined(__386) || defined(__386__) || \
            defined(__I86__) || \
            defined(__X86_32__) || defined(_X86_32_)
        #define GHOST_X86_32 1
    #else
        #define GHOST_X86_32 0
    #endif
    #define ghost_has_GHOST_X86_32 1
#endif

#endif
