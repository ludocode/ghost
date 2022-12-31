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

#ifndef GHOST_IF_ELSE_H_INCLUDED
#define GHOST_IF_ELSE_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_IF_ELSE(condition, truetext, falsetext)
 *
 * If the preprocessor condition is 0, the preprocessor expands this to
 * falsetext; otherwise it expands to truetext.
 *
 * Any condition other than 0 is considered true including blank, a
 * parenthesized expression, etc. Only a 0 is considered false.
 *
 * If you want your truetext and falsetext to contain commas, use
 * GHOST_IF_ELSE_BLOCK() instead.
 *
 * Example:
 *
 *     void* p = GHOST_IF_ELSE(ghost_has(ghost_alloca), ghost_alloca, ghost_malloc)(size)
 *     // use p...
 *     GHOST_IF_ELSE(ghost_has(ghost_alloca), , ghost_free(p))
 *
 * @note This isn't supported on compilers with buggy preprocessors (e.g.
 * cparser.) Check ghost_has(GHOST_IF_ELSE) to see if it's available.
 */

#ifndef ghost_has_GHOST_IF_ELSE
    #ifdef GHOST_IF_ELSE
        #define ghost_has_GHOST_IF_ELSE 1
    #endif
#endif

#ifndef ghost_has_GHOST_IF_ELSE
    #include "ghost/preprocessor/ghost_if_else_block.h"
    #if ghost_has(GHOST_IF_ELSE_BLOCK)
        #define GHOST_IF_ELSE(condition, truetext, falsetext) \
                GHOST_IF_ELSE_BLOCK(condition)(truetext)(falsetext)
        #define ghost_has_GHOST_IF_ELSE 1
    #else
        #define ghost_has_GHOST_IF_ELSE 0
    #endif
#endif

#endif
