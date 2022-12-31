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

#ifndef GHOST_UINTPTR_ALL_H_INCLUDED
#define GHOST_UINTPTR_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Defines ghost_uintptr_t and related macros:
 *
 * - GHOST_UINTPTR_MIN
 * - GHOST_UINTPTR_MAX
 * - GHOST_UINTPTR_WIDTH
 * - GHOST_UINTPTR_C()
 */

/**
 * An alias of uintptr_t (if possible), which is an unsigned integer type large
 * enough to store a pointer.
 */
typedef uintptr_t ghost_uintptr_t;

/**
 * @def GHOST_UINTPTR_C(x) x
 *
 * Defines a preprocessor constant of type ghost_uintptr_t.
 */

/**
 * @def GHOST_UINTPTR_MAX UINTPTR_MAX
 *
 * The maximum value of ghost_uintptr_t.
 */

/**
 * @def GHOST_UINTPTR_WIDTH UINTPTR_WIDTH
 *
 * The width of ghost_uintptr_t in bits.
 */
#endif

/* ghost_intptr_t and ghost_uintptr_t are defined together here. */
#include "ghost/impl/type/ghost_impl_intptr_uintptr.h"

#endif
