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

#ifndef GHOST_ULLONG_C_H_INCLUDED
#define GHOST_ULLONG_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_ULLONG_C(x) x ## ULL
 *
 * Defines a preprocessor constant convertible to signed long long.
 *
 * This may cause a -Wlong-long warning on GNU C compilers in older language
 * standards where `long long` is an extension. You should probably disable or
 * silence this warning if you intend to use this in older language standards.
 *
 * @see GHOST_SILENCE_LONG_LONG
 */
#endif

#ifndef ghost_has_GHOST_ULLONG_C
    #ifdef GHOST_ULLONG_C
        #define ghost_has_GHOST_ULLONG_C 1
    #endif
#endif

#ifndef ghost_has_GHOST_ULLONG_C
    #include "ghost/type/ullong/ghost_ullong.h"
    #if ghost_has(ghost_ullong)
        #define GHOST_ULLONG_C(x) x ## ULL
        #define ghost_has_GHOST_ULLONG_C 1
    #endif
#endif

#ifndef ghost_has_GHOST_ULLONG_C
    #define ghost_has_GHOST_ULLONG_C 0
#endif

#endif
