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

#ifndef GHOST_IMPL_EX_REALLOC_H_INCLUDED
#define GHOST_IMPL_EX_REALLOC_H_INCLUDED

/*
 * @def ghost_impl_ex_realloc()
 *
 * A non-synthetic wrapper for a system or custom realloc() that checks in
 * debug that ptr is null when size is zero and returns a new minimum-size
 * allocation.
 *
 * Don't call or override this; use ghost_realloc() instead.
 */

#if defined(ghost_has_ghost_impl_ex_realloc) || defined(ghost_impl_ex_realloc)
    #error "ghost_impl_ex_realloc() cannot be overridden or disabled. Override ghost_realloc() or define GHOST_MALLOC_SYSTEM=0 instead."
#endif

/* ghost_realloc() override is handled in ghost_malloc_system.h. */
#include "ghost/malloc/ghost_malloc_system.h"

/* If ghost_realloc() is overridden, use it for ghost_impl_ex_realloc() so
 * that other malloc functions can be synthesized from it. */
#ifdef ghost_has_ghost_realloc
    #if ghost_has_ghost_realloc
        #define ghost_impl_ex_realloc ghost_realloc
        #define ghost_has_ghost_impl_ex_realloc 1
    #endif
#endif

/*
 * In debug, no platform could possibly implement this because it depends on
 * ghost's fatal error handler.
 *
 * In non-debug builds, any of the platforms that provide
 * ghost_impl_ex_realloc_0alloc() or ghost_impl_ex_realloc_0free()
 * can provide this as well, but we don't bother to implement them here because
 * this will map directly to those functions anyway.
 */

#ifndef ghost_has_ghost_impl_ex_realloc
    #define ghost_has_ghost_impl_ex_realloc 0
#endif

#endif
