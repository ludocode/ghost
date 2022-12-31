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

#ifndef GHOST_INLINE_OPT_H_INCLUDED
#define GHOST_INLINE_OPT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_inline_opt inline
 *
 * Defines `ghost_inline_opt` as `inline` or equivalent, or nothing if `inline`
 * is not supported.
 *
 * Use this if you intend to declare static inline functions and you don't care
 * whether inline is actually supported.
 *
 * @see ghost_inline
 */
#endif

#ifndef ghost_has_ghost_inline_opt
    #ifndef ghost_inline_opt
        #include "ghost/language/ghost_inline.h"
        #if ghost_has(ghost_inline)
            #define ghost_inline_opt ghost_inline
        #else
            #define ghost_inline_opt /*nothing*/
        #endif
    #endif
    #define ghost_has_ghost_inline_opt 1
#endif

#endif
