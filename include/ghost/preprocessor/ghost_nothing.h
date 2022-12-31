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

#ifndef GHOST_NOTHING_H_INCLUDED
#define GHOST_NOTHING_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_NOTHING //nothing
 *
 * Expands to nothing.
 *
 * In ANSI C and in MSVC's traditional preprocessor, empty macro arguments are
 * undefined behaviour. This can be used to pass a non-blank argument to a
 * macro that becomes blank after expansion.
 */

#ifndef ghost_has_GHOST_NOTHING
    #ifndef GHOST_NOTHING
        #define GHOST_NOTHING /*nothing*/
    #endif
    #define ghost_has_GHOST_NOTHING 1
#endif

#endif
