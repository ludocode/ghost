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

#ifndef GHOST_SIZE_ALL_H_INCLUDED
#define GHOST_SIZE_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_size_t and related macros:
 *
 * - GHOST_SIZE_MAX
 * - GHOST_SIZE_WIDTH
 * - GHOST_SIZE_C()
 *
 * This also tries to include platform headers that define the standards:
 * size_t, SIZE_MAX, etc. If these exist in the platform, Ghost's definitions
 * are wrappers for them.
 *
 * If you're looking for portable format specifiers for printing and scanning
 * size_t (e.g. GHOST_PRIuZ), see ghost/format/ghost_format_z.h .
 */
#endif

#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/type/size_t/ghost_size_width.h"
#include "ghost/type/size_t/ghost_size_max.h"
#include "ghost/type/size_t/ghost_size_c.h"

#endif
