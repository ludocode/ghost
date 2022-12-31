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

#ifndef GHOST_UINT_LEAST64_ALL_H_INCLUDED
#define GHOST_UINT_LEAST64_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_uint_least64_t and related macros:
 *
 * - GHOST_UINT_LEAST64_C()
 * - GHOST_UINT_LEAST64_MAX
 * - GHOST_UINT_LEAST64_WIDTH
 *
 * If the implementation does not support an unsigned integer at least 64 bits
 * wide, none of these will exist. Check ghost_has() to see whether each type
 * or macro exists.
 */
#endif

#include "ghost/type/uint_least64_t/ghost_uint_least64_t.h"
#include "ghost/type/uint_least64_t/ghost_uint_least64_width.h"
#include "ghost/type/uint_least64_t/ghost_uint_least64_c.h"
#include "ghost/type/uint_least64_t/ghost_uint_least64_max.h"

#endif
