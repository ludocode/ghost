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

#ifndef GHOST_MALLOC_COMMON_H_INCLUDED
#define GHOST_MALLOC_COMMON_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes the commonly used parts of `ghost/malloc/`.
 *
 * We include things that don't cause too much unnecessary compilation and
 * things you are likely to use in any non-trivial code. In particular you get:
 *
 * - the standard allocators: `ghost_malloc()`, `ghost_calloc()`, `ghost_realloc()`, `ghost_free()`;
 * - the typed macros `ghost_alloc()` and friends;
 * - helper functions like `ghost_strdup()` and `ghost_memdup()`.
 *
 * We exclude:
 *
 * - rarely used things like `ghost_aligned_malloc()`;
 * - things that require more care to use correctly like `ghost_alloca()`;
 * - unportable things like `ghost_strdupa()` and `ghost_malloc_size()`;
 * - non-standard variations: ghost_malloc_0null(), ghost_realloc_0free(), etc.
 *
 * If you want any of these things you can include their headers directly or
 * include "ghost/malloc/ghost_malloc_all.h" to get all of them.
 */

/* Standard allocation functions */
#include "ghost/malloc/ghost_malloc.h"
#include "ghost/malloc/ghost_calloc.h"
#include "ghost/malloc/ghost_realloc.h"
#include "ghost/malloc/ghost_free.h"

/* Other allocation helpers */
#include "ghost/malloc/ghost_memdup.h"
#include "ghost/malloc/ghost_strdup.h"
#include "ghost/malloc/ghost_strndup.h"

/* Ghost's allocation helpers */
#include "ghost/malloc/ghost_alloc_array.h"
#include "ghost/malloc/ghost_alloc_array_zero.h"
#include "ghost/malloc/ghost_alloc.h"
#include "ghost/malloc/ghost_alloc_zero.h"

#endif
