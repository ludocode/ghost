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

#ifndef GHOST_LDOUBLE_ALL_H_INCLUDED
#define GHOST_LDOUBLE_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
#endif

/* cproc (actually its backend QBE) does not yet support long double.
 * Unfortunately we don't have any way of detecting when it will add it in the
 * future. cproc uses GCC's preprocessor which already defines things like
 * __LDBL_MAX__ so we can't count on those macros to determine that it's been
 * implemented. This will need to be changed if QBE ever implements it. */
#ifndef ghost_has_ghost_ldouble
    #include "ghost/detect/ghost_cproc.h"
    #if GHOST_CPROC
        #define ghost_has_ghost_ldouble 0
    #endif
#endif

/* TODO */
#ifndef ghost_has_ghost_ldouble
    #define ghost_has_ghost_ldouble 1
#endif

#endif
