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

#ifndef GHOST_CPROC_H_INCLUDED
#define GHOST_CPROC_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def GHOST_CPROC
 *
 * Defined to 1 if the compiler is cproc and 0 otherwise.
 *
 * cproc does not currently define a macro like __cproc__ or __CPROC__. This
 * means there is no straightforward way to detect it.
 *
 * We attempt to detect cproc here. If you want to make it explicit, define
 * __cproc__ or __CPROC__ (or simply GHOST_CPROC) yourself.
 */
#endif

#ifndef ghost_has_GHOST_CPROC
    #ifdef GHOST_CPROC
        #define ghost_has_GHOST_CPROC 1
    #endif
#endif

/* Hopefully cproc will define this soon. */
#ifndef ghost_has_GHOST_CPROC
    #if defined(__cproc__) || defined(__CPROC__)
        #define GHOST_CPROC 1
        #define ghost_has_GHOST_CPROC 1
    #endif
#endif

/*
 * cproc does not yet have its own preprocessor. It currently wraps the system
 * preprocessor which is GCC or Clang.
 *
 * cproc undefines __GNUC__ and __GNUC_MINOR__ but it doesn't undefine several
 * other GNUC macros. It also defines __extension__ as a macro. We detect it
 * via these oddities.
 */
#ifndef ghost_has_GHOST_CPROC
    #if !defined(__GNUC__) && !defined(__GNUC_MINOR__) && defined(__extension__) && \
            (defined(__GNUC_PATCHLEVEL__) || defined(__GNUC_STDC_INLINE__) || defined(__GNUC_GNU_INLINE__))
        #define GHOST_CPROC 1
        #define ghost_has_GHOST_CPROC 1
    #endif
#endif

/* We're probably not cproc. */
#ifndef ghost_has_GHOST_CPROC
    #define GHOST_CPROC 0
    #define ghost_has_GHOST_CPROC 1
#endif

#endif
