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

#ifndef GHOST_SHORT_ALL_H_INCLUDED
#define GHOST_SHORT_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines macros related to signed short:
 *
 * - GHOST_SHORT_C()
 * - GHOST_SHORT_MAX
 * - GHOST_SHORT_MIN
 * - GHOST_SHORT_WIDTH
 *
 * Ghost doesn't omit random vowels. We define GHOST_SHORT_*, not GHOST_SHRT_*.
 *
 * These constants are specifically for signed short. If you want unsigned
 * short, see ghost_ushort.h.
 */
#endif

#include "ghost/type/short/ghost_short.h"
#include "ghost/type/short/ghost_short_width.h"
#include "ghost/type/short/ghost_short_max.h"
#include "ghost/type/short/ghost_short_min.h"
#include "ghost/type/short/ghost_short_c.h"

#endif
