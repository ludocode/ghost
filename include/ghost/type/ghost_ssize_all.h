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

#ifndef GHOST_SSIZE_ALL_H_INCLUDED
#define GHOST_SSIZE_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_ssize_t and related macros:
 *
 * - GHOST_SSIZE_MIN
 * - GHOST_SSIZE_MAX
 * - GHOST_SSIZE_WIDTH
 * - GHOST_SSIZE_C()
 *
 * This also tries to have the platform define the POSIX standard ssize_t or
 * Windows SSIZE_T and related macros. If these exist in the platform, Ghost's
 * definitions are wrappers for them.
 *
 * If you're looking for portable format specifiers for printing and scanning
 * size_t (e.g. GHOST_PRIuZ), see ghost/format/ghost_format_z.h .
 */
#endif

#include "ghost/type/ssize_t/ghost_ssize_t.h"
#include "ghost/type/ssize_t/ghost_ssize_width.h"
#include "ghost/type/ssize_t/ghost_ssize_max.h"
#include "ghost/type/ssize_t/ghost_ssize_min.h"
#include "ghost/type/ssize_t/ghost_ssize_c.h"

#endif
