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

#ifndef GHOST_MALLOC_ALL_H_INCLUDED
#define GHOST_MALLOC_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes all files in `ghost/malloc/`.
 */

/* Common stuff */
#include "ghost/ghost_malloc_common.h"

/* Alternates */
#include "ghost/malloc/ghost_calloc_0any.h"
#include "ghost/malloc/ghost_calloc_0null.h"
#include "ghost/malloc/ghost_free_nonnull.h"
#include "ghost/malloc/ghost_malloc_0any.h"
#include "ghost/malloc/ghost_malloc_0null.h"
#include "ghost/malloc/ghost_realloc_0alloc.h"
#include "ghost/malloc/ghost_realloc_0any.h"
#include "ghost/malloc/ghost_realloc_0free.h"
#include "ghost/malloc/ghost_realloc_0null.h"

/* Aligned allocations */
#include "ghost/malloc/ghost_aligned_free.h"
#include "ghost/malloc/ghost_aligned_malloc.h"

/* Stack allocations */
#include "ghost/malloc/ghost_alloca.h"
#include "ghost/malloc/ghost_strdupa.h"
#include "ghost/malloc/ghost_strndupa.h"

/* Other */
#include "ghost/malloc/ghost_malloc_system.h"
#include "ghost/malloc/ghost_malloc_size.h"
#include "ghost/malloc/ghost_malloc_good_size.h"

#endif
