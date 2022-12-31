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

#include "ghost/malloc/ghost_malloc_system.h"

#ifndef ghost_has_GHOST_MALLOC_SYSTEM
    #error "ghost/malloc/ghost_malloc_system.h must define ghost_has_ghost_malloc_system."
#endif

#include "test_common.h"

#if !ghost_has_GHOST_MALLOC_SYSTEM || !defined(GHOST_MALLOC_SYSTEM)
    #error "GHOST_MALLOC_SYSTEM must be defined."
#endif

#if GHOST_MALLOC_SYSTEM != 0 && GHOST_MALLOC_SYSTEM != 1
    #error "GHOST_MALLOC_SYSTEM must be defined to 0 or 1."
#endif
