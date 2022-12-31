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

#ifndef GHOST_USHORT_ALL_H_INCLUDED
#define GHOST_USHORT_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines macros related to unsigned short:
 *
 * - GHOST_USHORT_C()
 * - GHOST_USHORT_MAX
 * - GHOST_USHORT_WIDTH
 *
 * Ghost doesn't omit random vowels. We define GHOST_USHORT_*, not
 * GHOST_USHRT_*.
 *
 * These constants are specifically for unsigned short. If you want signed
 * short, see ghost_short.h.
 */
#endif

#include "ghost/type/ushort/ghost_ushort.h"
#include "ghost/type/ushort/ghost_ushort_max.h"
#include "ghost/type/ushort/ghost_ushort_width.h"
#include "ghost/type/ushort/ghost_ushort_c.h"

#endif
