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

#ifndef GHOST_IF_ELSE_BLOCK_H_INCLUDED
#define GHOST_IF_ELSE_BLOCK_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_IF_ELSE_BLOCK(condition)(truetext)(falsetext)
 *
 * If the preprocessor condition is 0, the preprocessor expands this to
 * falsetext; otherwise it expands to truetext.
 *
 * Any condition other than 0 is considered true including blank, a
 * parenthesized expression, etc. Only a 0 is considered false.
 *
 * This is useful if your truetext and falsetext contain commas. For a simpler
 * syntax, see GHOST_IF_ELSE.
 *
 * @note This isn't supported on compilers with buggy preprocessors (e.g.
 * cparser.) Check ghost_has(GHOST_IF_ELSE_BLOCK) to see if it's available.
 */

#ifndef ghost_has_GHOST_IF_ELSE_BLOCK
    #ifdef GHOST_IF_ELSE_BLOCK
        #define ghost_has_GHOST_IF_ELSE_BLOCK 1
    #endif
#endif

/* cparser's preprocessor is too buggy to make this work. */
#ifndef ghost_has_GHOST_IF_ELSE_BLOCK
    #include "ghost/preprocessor/ghost_cparser_pp.h"
    #if GHOST_CPARSER_PP
        #define ghost_has_GHOST_IF_ELSE_BLOCK 0
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_IF_ELSE_BLOCK
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_IF_ELSE_BLOCK 0
    #endif
#endif

#ifndef ghost_has_GHOST_IF_ELSE_BLOCK
    #include "ghost/preprocessor/ghost_concat.h"
    #include "ghost/preprocessor/ghost_bool_pp.h"
    #if ghost_has(GHOST_BOOL)
        #define GHOST_IF_ELSE_BLOCK(condition) GHOST_CONCAT(GHOST_IF_ELSE_BLOCK_IMPL_, GHOST_BOOL(condition))
        #define GHOST_IF_ELSE_BLOCK_IMPL_1(...) __VA_ARGS__ GHOST_IF_ELSE_BLOCK_IMPL_1_ELSE
        #define GHOST_IF_ELSE_BLOCK_IMPL_0(...) GHOST_IF_ELSE_BLOCK_IMPL_0_ELSE
        #define GHOST_IF_ELSE_BLOCK_IMPL_1_ELSE(...)
        #define GHOST_IF_ELSE_BLOCK_IMPL_0_ELSE(...) __VA_ARGS__
        #define ghost_has_GHOST_IF_ELSE_BLOCK 1
    #else
        #define ghost_has_GHOST_IF_ELSE_BLOCK 0
    #endif
#endif

#endif
