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

#ifndef GHOST_UINT32_ALL_H_INCLUDED
#define GHOST_UINT32_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_uint32_t and related macros:
 *
 * - ghost_uint32_t
 * - GHOST_UINT32_C()
 * - GHOST_UINT32_MAX
 * - GHOST_UINT32_WIDTH
 *
 * If the standard uint32_t, UINT32_C(), etc. exist, these are wrappers for
 * them.
 *
 * If the implementation does not support an unsigned integer exactly 32 bits
 * wide with no padding bits, none of these will exist. Check ghost_has() to
 * see whether each type or macro exists.
 */
#endif

#include "ghost/type/uint32_t/ghost_uint32_t.h"
#include "ghost/type/uint32_t/ghost_uint32_width.h"
#include "ghost/type/uint32_t/ghost_uint32_c.h"
#include "ghost/type/uint32_t/ghost_uint32_max.h"

#endif
