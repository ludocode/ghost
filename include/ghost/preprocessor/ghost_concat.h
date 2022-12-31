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

#ifndef GHOST_CONCAT_H_INCLUDED
#define GHOST_CONCAT_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_CONCAT(x, y) x##y (expanded first)
 *
 * Concatenates the arguments, expanding them first.
 *
 * The preprocessor token concatenation operator ## inhibits expansion of macro
 * arguments before concatenation. If you do want them expanded first, use this
 * instead.
 */

#ifndef ghost_has_GHOST_CONCAT
    #ifndef GHOST_CONCAT
        #define GHOST_CONCAT(x, y) GHOST_CONCAT_IMPL(x, y)
        #define GHOST_CONCAT_IMPL(x, y) x##y
    #endif
    #define ghost_has_GHOST_CONCAT 1
#endif

#endif
