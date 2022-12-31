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

#ifndef GHOST_TRUE_H_INCLUDED
#define GHOST_TRUE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def ghost_true (ghost_bool)1
 *
 * `ghost_true` has type `ghost_bool`. Note that this differs from C99 and C11
 * where `true` has type `int`. In C23, `true` will have type `_Bool`; we
 * backport this behaviour to all language standards.
 */
#endif

/* We need bool. */
#ifndef ghost_has_ghost_true
    #include "ghost/type/bool/ghost_bool.h"
    #if !ghost_has(ghost_bool)
        #define ghost_has_ghost_true 0
    #endif
#endif

/* In C++ true and false are keywords. */
#ifndef ghost_has_ghost_true
    #if defined(__cplusplus)
        #define ghost_true true
        #define ghost_has_ghost_true 1
    #endif
#endif

/* We don't use true and false in C23 because they are predefined macros. They
 * could technically be defined by old user code to something else. */

/* We backport the C23 behaviour to C11 and C99 (and wherever we have a _Bool
 * extension) by making ghost_true and ghost_false of type ghost_bool. */
#ifndef ghost_has_ghost_true
    #define ghost_true ((ghost_bool)1)
    #define ghost_has_ghost_true 1
#endif

#endif
