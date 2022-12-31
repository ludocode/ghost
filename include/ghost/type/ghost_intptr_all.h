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

#ifndef GHOST_INTPTR_ALL_H_INCLUDED
#define GHOST_INTPTR_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_intptr_t and related macros:
 *
 * - GHOST_INTPTR_MIN
 * - GHOST_INTPTR_MAX
 * - GHOST_INTPTR_WIDTH
 * - GHOST_INTPTR_C()
 */

/**
 * @def GHOST_INTPTR_C(x) x
 *
 * Defines a preprocessor constant of type ghost_intptr_t.
 */

/**
 * @def GHOST_INTPTR_MIN INTPTR_MIN
 *
 * The minimum value of ghost_intptr_t.
 */

/**
 * @def GHOST_INTPTR_MAX INTPTR_MAX
 *
 * The maximum value of ghost_intptr_t.
 */

/**
 * @def GHOST_INTPTR_WIDTH INTPTR_WIDTH
 *
 * The width of ghost_intptr_t in bits.
 */
#endif

#include "ghost/type/intptr_t/ghost_intptr_t.h"
#include "ghost/type/intptr_t/ghost_intptr_width.h"
#include "ghost/type/intptr_t/ghost_intptr_min.h"
#include "ghost/type/intptr_t/ghost_intptr_max.h"
#include "ghost/type/intptr_t/ghost_intptr_c.h"

#endif
