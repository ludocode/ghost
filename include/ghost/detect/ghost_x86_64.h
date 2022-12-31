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

#ifndef GHOST_X86_64_H_INCLUDED
#define GHOST_X86_64_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_X86_64
 *
 * Defined to 1 if the processor is x86-64 and 0 otherwise.
 *
 * Another name for this architecture is AMD64.
 *
 *     https://en.wikipedia.org/wiki/X86-64
 */
#endif

/* Handle override */
#ifndef ghost_has_GHOST_X86_64
    #ifdef GHOST_X86_64
        #define ghost_has_GHOST_X86_64 1
    #endif
#endif

/* See: https://sourceforge.net/p/predef/wiki/Architectures/ */
#ifndef ghost_has_GHOST_X86_64
    #if defined(__amd64__) || defined(__amd64) || \
            defined(__x86_64__) || defined(__x86_64) || \
            defined(_M_X64) || defined(_M_AMD64)
        #define GHOST_X86_64 1
    #else
        #define GHOST_X86_64 0
    #endif
    #define ghost_has_GHOST_X86_64 1
#endif

#endif
