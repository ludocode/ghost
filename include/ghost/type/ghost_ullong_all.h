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

#ifndef GHOST_ULLONG_ALL_H_INCLUDED
#define GHOST_ULLONG_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines macros related to unsigned long long:
 *
 * - GHOST_ULLONG_C()
 * - GHOST_ULLONG_MAX
 * - GHOST_ULLONG_WIDTH
 *
 * This also defines ghost_has(ghost_ullong). Check this to see if the platform
 * supports `unsigned long long`.
 *
 * The type `ghost_ullong` is a typedef to `unsigned long long` if supported.
 * This may silence pedantic warnings about using a `unsigned long long`
 * extension in older language standards.
 *
 * These constants are specifically for unsigned long long. If you want signed
 * long long, see ghost_llong.h.
 */
#endif

#include "ghost/type/ullong/ghost_ullong.h"
#include "ghost/type/ullong/ghost_ullong_width.h"
#include "ghost/type/ullong/ghost_ullong_max.h"
#include "ghost/type/ullong/ghost_ullong_c.h"

#endif
