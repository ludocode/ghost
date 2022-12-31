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

#ifndef GHOST_DEFER_MORE_H_INCLUDED
#define GHOST_DEFER_MORE_H_INCLUDED

#include "ghost/ghost_core.h"

#include "ghost/preprocessor/ghost_defer.h"

/* http://jhnet.co.uk/articles/cpp_magic */
/* TODO move to experimental */

/**
 * @def GHOST_DEFER_2(MACRO)(x)
 *
 * Defers the expansion of a function-like macro until two expansion passes
 * later.
 */
#define GHOST_DEFER_2(m) m GHOST_BLANK GHOST_BLANK () ()
#define ghost_has_GHOST_DEFER_2 1 // TODO ghost_has this file

/**
 * @def GHOST_DEFER_3(MACRO)(x)
 *
 * Defers the expansion of a function-like macro until three expansion
 * passes later.
 */
#define GHOST_DEFER_3(m) m GHOST_BLANK GHOST_BLANK GHOST_BLANK () () ()

/**
 * @def GHOST_DEFER_4(MACRO)(x)
 *
 * Defers the expansion of a function-like macro until four expansion
 * passes later.
 */
#define GHOST_DEFER_4(m) m GHOST_BLANK GHOST_BLANK GHOST_BLANK GHOST_BLANK () () () ()

#define GHOST_DEFER_IMPL_BLANK_2 GHOST_BLANK GHOST_BLANK
#define GHOST_DEFER_IMPL_BLANK_4 GHOST_DEFER_IMPL_BLANK_2 GHOST_DEFER_IMPL_BLANK_2
#define GHOST_DEFER_IMPL_BLANK_8 GHOST_DEFER_IMPL_BLANK_4 GHOST_DEFER_IMPL_BLANK_4
#define GHOST_DEFER_IMPL_BLANK_16 GHOST_DEFER_IMPL_BLANK_8 GHOST_DEFER_IMPL_BLANK_8
#define GHOST_DEFER_IMPL_BLANK_32 GHOST_DEFER_IMPL_BLANK_16 GHOST_DEFER_IMPL_BLANK_16
#define GHOST_DEFER_IMPL_BLANK_64 GHOST_DEFER_IMPL_BLANK_32 GHOST_DEFER_IMPL_BLANK_32

#define GHOST_DEFER_IMPL_PARENS_2 () ()
#define GHOST_DEFER_IMPL_PARENS_4 GHOST_DEFER_IMPL_PARENS_2 GHOST_DEFER_IMPL_PARENS_2
#define GHOST_DEFER_IMPL_PARENS_8 GHOST_DEFER_IMPL_PARENS_4 GHOST_DEFER_IMPL_PARENS_4
#define GHOST_DEFER_IMPL_PARENS_16 GHOST_DEFER_IMPL_PARENS_8 GHOST_DEFER_IMPL_PARENS_8
#define GHOST_DEFER_IMPL_PARENS_32 GHOST_DEFER_IMPL_PARENS_16 GHOST_DEFER_IMPL_PARENS_16
#define GHOST_DEFER_IMPL_PARENS_64 GHOST_DEFER_IMPL_PARENS_32 GHOST_DEFER_IMPL_PARENS_32

/**
 * @def GHOST_DEFER_5(MACRO)(x)
 *
 * Defers the expansion of a function-like macro until five expansion
 * passes later.
 */
#define GHOST_DEFER_5(m) m GHOST_DEFER_IMPL_BLANK_4 GHOST_DEFER_IMPL_PARENS_4

/**
 * @def GHOST_DEFER_9(MACRO)(x)
 *
 * Defers the expansion of a function-like macro until nine expansion
 * passes later.
 */
#define GHOST_DEFER_9(m) m GHOST_DEFER_IMPL_BLANK_8 GHOST_DEFER_IMPL_PARENS_8

/**
 * @def GHOST_DEFER_17(MACRO)(x)
 *
 * Defers the expansion of a function-like macro until 17 expansion
 * passes later.
 */
#define GHOST_DEFER_17(m) m GHOST_DEFER_IMPL_BLANK_16 GHOST_DEFER_IMPL_PARENS_16

/**
 * @def GHOST_DEFER_33(MACRO)(x)
 *
 * Defers the expansion of a function-like macro until 33 expansion
 * passes later.
 */
#define GHOST_DEFER_33(m) m GHOST_DEFER_IMPL_BLANK_32 GHOST_DEFER_IMPL_PARENS_32

/**
 * @def GHOST_DEFER_65(MACRO)(x)
 *
 * Defers the expansion of a function-like macro until 65 expansion
 * passes later.
 */
/* TODO looks like this is actually 34 expansion passes? test this all */
#define GHOST_DEFER_65(m) m GHOST_DEFER_IMPL_BLANK_64 GHOST_DEFER_IMPL_PARENS_64

#endif
