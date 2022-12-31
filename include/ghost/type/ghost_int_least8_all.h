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

#ifndef GHOST_INT_LEAST8_ALL_H_INCLUDED
#define GHOST_INT_LEAST8_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_int_least8_t and related macros:
 *
 * - GHOST_INT_LEAST8_C()
 * - GHOST_INT_LEAST8_MAX
 * - GHOST_INT_LEAST8_MIN
 * - GHOST_INT_LEAST8_WIDTH
 *
 * If the implementation does not support a signed integer at least 8 bits
 * wide, none of these will exist. Check ghost_has() to see whether each type
 * or macro exists.
 */
#endif

#include "ghost/type/int_least8_t/ghost_int_least8_t.h"
#include "ghost/type/int_least8_t/ghost_int_least8_width.h"
#include "ghost/type/int_least8_t/ghost_int_least8_c.h"
#include "ghost/type/int_least8_t/ghost_int_least8_max.h"
#include "ghost/type/int_least8_t/ghost_int_least8_min.h"

#endif
