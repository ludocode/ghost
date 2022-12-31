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

#ifndef GHOST_MATH_ALL_H_INCLUDED
#define GHOST_MATH_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes all math functions.
 *
 * There are a ton of math functions (in every type permutation) so this is a
 * huge header. It's generally better to include only the math functions you
 * intend to use. Only use this header if you don't care at all about
 * compilation speed.
 *     TODO or not? Ghost compiles super fast anyway, who cares
 */

/* TODO shouldn't need to go into the folders, should be top-level headers for each */
#include "ghost/math/popcount/ghost_popcount_u32.h"

#endif
