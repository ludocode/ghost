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

#ifndef GHOST_IMPL_EX_CALLOC_0NULL_H_INCLUDED
#define GHOST_IMPL_EX_CALLOC_0NULL_H_INCLUDED

/*
 * @def ghost_impl_ex_calloc_0null()
 *
 * A non-synthetic wrapper for a system or custom calloc() that returns null
 * when either argument is 0.
 *
 * Don't call or override this; use ghost_calloc_0null() instead.
 */

#if defined(ghost_has_ghost_impl_ex_calloc_0null) || defined(ghost_impl_ex_calloc_0null)
    #error "ghost_impl_ex_calloc_0null() cannot be overridden or disabled. Override ghost_calloc_0null() or define GHOST_MALLOC_SYSTEM to 0 instead."
#endif

/* ghost_calloc_0null() override is handled in ghost_malloc_system.h. */
#include "ghost/malloc/ghost_malloc_system.h"

/* If ghost_calloc_0null() is overridden, use it for
 * ghost_impl_ex_calloc_0null() so that other malloc functions can be
 * synthesized from it. */
#ifdef ghost_has_ghost_calloc_0null
    #if ghost_has_ghost_calloc_0null
        #define ghost_impl_ex_calloc_0null ghost_calloc_0null
        #define ghost_has_ghost_impl_ex_calloc_0null 1
    #endif
#endif

/* We don't yet detect any platforms where calloc() with size 0 returns null.
 * This is still here to support overriding by the user. */

#ifndef ghost_has_ghost_impl_ex_calloc_0null
    #define ghost_has_ghost_impl_ex_calloc_0null 0
#endif

#endif
