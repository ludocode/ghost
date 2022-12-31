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

#ifndef GHOST_IS_BLANK_H_INCLUDED
#define GHOST_IS_BLANK_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_IS_BLANK(...)
 *
 * Expands to 1 if the argument list expands to nothing (i.e. contains only
 * whitespace) or 0 otherwise.
 *
 * TODO rename to GHOST_IS_NOTHING() to match GHOST_NOTHING, add a unit test
 * for GHOST_IS_NOTHING(GHOST_NOTHING)
 */

#ifndef ghost_has_GHOST_IS_BLANK
    #ifdef GHOST_IS_BLANK
        #define ghost_has_GHOST_IS_BLANK 1
    #endif
#endif

#ifndef ghost_has_GHOST_IS_BLANK
    #include "ghost/preprocessor/ghost_not.h"
    #include "ghost/preprocessor/ghost_first.h"
    #if ghost_has(GHOST_NOT) && ghost_has(GHOST_FIRST)
        #include "ghost/preprocessor/ghost_expand.h"
        #define GHOST_IS_BLANK(...) \
            GHOST_NOT(GHOST_FIRST(GHOST_EXPAND(GHOST_IS_BLANK_IMPL __VA_ARGS__ ())))
        #define GHOST_IS_BLANK_IMPL(...) 0
        #define ghost_has_GHOST_IS_BLANK 1
    #endif
#endif

#ifndef ghost_has_GHOST_IS_BLANK
    #define ghost_has_GHOST_IS_BLANK 0
#endif

#endif
