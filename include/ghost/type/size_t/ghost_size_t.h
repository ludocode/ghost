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

#ifndef GHOST_SIZE_T_H_INCLUDED
#define GHOST_SIZE_T_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * An alias of size_t (if possible), which is an unsigned integer type the same
 * size as the result type of `sizeof`.
 *
 * If a platform size_t exists (which it essentially always does), ghost_size_t
 * is a typedef of it. In other words, you can include this and simply use
 * size_t everywhere.
 */
typedef size_t ghost_size_t;
#define ghost_has_ghost_size_t 1
#endif

#ifndef ghost_has_ghost_size_t
    #ifdef ghost_size_t
        #define ghost_has_ghost_size_t 1
    #endif
#endif

/* Always include <stddef.h> to make sure the real size_t is defined if
 * possible. */
#include "ghost/header/c/ghost_stddef_h.h"

/*
 * size_t is in <stddef.h> which has been around since ANSI C and is supposed
 * to be available even in freestanding. It's usually provided by the compiler
 * rather than the libc. We therefore assume for now that size_t is always
 * going to be defined and correct even if for some strange reason we don't
 * have <stddef.h>.
 */
#ifndef ghost_has_ghost_size_t
    typedef size_t ghost_size_t;
    #define ghost_has_ghost_size_t 1
#endif

/*
 * GNU C compilers tell us __SIZE_TYPE__. We don't bother with it yet because
 * we assume size_t is available.
 */

/*
 * If we find some esoteric platforms that don't have any of the above we can
 * do something special later (like maybe define it based on __LP64__/__ILP32__
 * or CPU architecture the way we do for everything else.)
 */

#endif
