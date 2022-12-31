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

#ifndef GHOST_STDC_VERSION_H_INCLUDED
#define GHOST_STDC_VERSION_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_STDC_VERSION __STDC_VERSION__
 *
 * A macro that specifies the C version in the style of __STDC_VERSION__.
 *
 * This is here so we can work around any compilers or old C versions that
 * define __STDC_VERSION__ incorrectly.
 *
 * Here's a table of known C versions and the corresponding value of
 * __STDC_VERSION__:
 *
 * K&R: not defined (see below)
 * C89: not defined
 * C95: 199409L
 * C99: 199901L
 * C11: 201112L
 * C17: 201710L
 * C23: not yet assigned; 202000L in use by some compilers
 *
 * Note that C17 only fixes defects in previous standards so it isn't
 * generally used for feature detection. C95 added very little so it isn't
 * used for feature detection much either.
 *
 * Note that "ANSI C" and C90 are alternate names for what Ghost calls C89.
 *
 * The original pre-standardization version of C is generally known as K&R C.
 * Neither C89 nor K&R C define __STDC_VERSION__ but you can distinguish
 * between them via the macro __STDC__. In K&R C __STDC__ is not defined while
 * in C89 and later it's defined to 1.
 *
 * Ghost does not support K&R C.
 */
#endif

#ifndef ghost_has_GHOST_STDC_VERSION
    #ifdef GHOST_STDC_VERSION
        #define ghost_has_GHOST_STDC_VERSION 1
    #elif defined(__STDC_VERSION__)
        #define GHOST_STDC_VERSION __STDC_VERSION__
        #define ghost_has_GHOST_STDC_VERSION 1
    #else
        #define ghost_has_GHOST_STDC_VERSION 0
    #endif
#endif

#endif
