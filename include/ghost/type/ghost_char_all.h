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

#ifndef GHOST_CHAR_ALL_H_INCLUDED
#define GHOST_CHAR_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines macros related to char:
 *
 * - GHOST_CHAR_IS_SIGNED
 * - GHOST_CHAR_WIDTH
 * - GHOST_CHAR_MAX
 * - GHOST_CHAR_MIN
 * - GHOST_CHAR_C()
 *
 * char may be signed or unsigned. See ghost_schar.h and ghost_uchar.h if you
 * want signed char or unsigned char.
 */
#endif

#include "ghost/type/char/ghost_char.h"
#include "ghost/type/char/ghost_char_width.h"
#include "ghost/type/char/ghost_char_is_signed.h"
#include "ghost/type/char/ghost_char_max.h"
#include "ghost/type/char/ghost_char_min.h"
#include "ghost/type/char/ghost_char_c.h"

#endif
