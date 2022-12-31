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

#ifndef GHOST_DEFER_H_INCLUDED
#define GHOST_DEFER_H_INCLUDED

#include "ghost/ghost_core.h"

/* http://jhnet.co.uk/articles/cpp_magic */

#include "ghost/preprocessor/ghost_blank.h"

/**
 * @def GHOST_DEFER(MACRO)(x) MACRO(x)
 *
 * Defers the expansion of a function-like macro to the next expansion
 * pass.
 *
 * You must place the arguments to the macro following the call to defer. For
 * example:
 *
 *     GHOST_DEFER(FOO)(x)
 *
 * This expands to the literal text FOO(x); it does not actually expand FOO(x).
 * Add another expansion pass to expand it. For example:
 *
 *     GHOST_EXPAND(GHOST_DEFER(FOO)(x))
 */

#ifndef ghost_has_GHOST_DEFER
    #ifndef GHOST_DEFER
        #define GHOST_DEFER(m) m GHOST_BLANK()
    #endif
    #define ghost_has_GHOST_DEFER 1
#endif

#endif
