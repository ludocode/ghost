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

#ifndef GHOST_LLONG_ALL_H_INCLUDED
#define GHOST_LLONG_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines macros related to signed long long:
 *
 * - GHOST_LLONG_C()
 * - GHOST_LLONG_MAX
 * - GHOST_LLONG_MIN
 * - GHOST_LLONG_WIDTH
 *
 * This also defines ghost_has(ghost_llong). Check this to see if the platform
 * supports `long long`.
 *
 * The type `ghost_llong` is a typedef to `long long` if supported. This may
 * silence pedantic warnings about using a `long long` extension in older
 * language standards.
 *
 * These constants are specifically for signed long long. If you want unsigned
 * long long, see ghost_ullong.h.
 */
#endif

#include "ghost/type/llong/ghost_llong.h"
#include "ghost/type/llong/ghost_llong_width.h"
#include "ghost/type/llong/ghost_llong_max.h"
#include "ghost/type/llong/ghost_llong_min.h"
#include "ghost/type/llong/ghost_llong_c.h"

#endif
