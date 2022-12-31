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

#ifndef GHOST_IMPL_EX_REALLOC_0ANY_H_INCLUDED
#define GHOST_IMPL_EX_REALLOC_0ANY_H_INCLUDED

/*
 * @def ghost_impl_ex_realloc_0any()
 *
 * A non-synthetic wrapper for a system or custom realloc() regardless of its
 * behaviour when size is 0.
 *
 * Don't call or override this; use ghost_realloc_0any() instead.
 */

#if defined(ghost_has_ghost_impl_ex_realloc_0any) || defined(ghost_impl_ex_realloc_0any)
    #error "ghost_impl_ex_realloc_0any() cannot be overridden or disabled. Override ghost_realloc_0any() or define GHOST_MALLOC_SYSTEM=0 instead."
#endif

/* ghost_realloc_0any() override is handled in ghost_malloc_system.h. */
#include "ghost/malloc/ghost_malloc_system.h"

/* If ghost_realloc_0any() is overridden, use it for
 * ghost_impl_ex_realloc_0any() so that other malloc functions can be
 * synthesized from it. */
#ifdef ghost_has_ghost_realloc_0any
    #if ghost_has_ghost_realloc_0any
        #define ghost_impl_ex_realloc_0any ghost_realloc_0any
        #define ghost_has_ghost_impl_ex_realloc_0any 1
    #endif
#endif

/* We only wrap system functions if GHOST_MALLOC_SYSTEM is enabled. */
#ifndef ghost_has_ghost_impl_ex_realloc_0any
    #include "ghost/malloc/ghost_malloc_system.h"
    #if !GHOST_MALLOC_SYSTEM
        #define ghost_has_ghost_impl_ex_realloc_0any 0
    #endif
#endif

/* We also require <stdlib.h> in a hosted environment. */
#ifndef ghost_has_ghost_impl_ex_realloc_0any
    #include "ghost/language/ghost_hosted.h"
    #if !GHOST_HOSTED
        #define ghost_has_ghost_impl_ex_realloc_0any 0
    #endif
#endif
#ifndef ghost_has_ghost_impl_ex_realloc_0any
    #include "ghost/header/c/ghost_stdlib_h.h"
    #if !ghost_has(ghost_stdlib_h)
        #define ghost_has_ghost_impl_ex_realloc_0any 0
    #endif
#endif

/* ghost_impl_ex_realloc_0any() wraps any system realloc() regardless of its
 * behaviour. */
#ifndef ghost_has_ghost_impl_ex_realloc_0any
    #ifdef __cplusplus
        #define ghost_impl_ex_realloc_0any ::realloc
    #else
        #define ghost_impl_ex_realloc_0any realloc
    #endif
    #define ghost_has_ghost_impl_ex_realloc_0any 1
#endif

#endif
