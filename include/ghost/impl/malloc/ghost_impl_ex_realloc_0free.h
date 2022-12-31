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

#ifndef GHOST_IMPL_EX_REALLOC_0FREE_H_INCLUDED
#define GHOST_IMPL_EX_REALLOC_0FREE_H_INCLUDED

/*
 * @def ghost_impl_ex_realloc_0free()
 *
 * A non-synthetic wrapper for a system or custom realloc() function that has
 * the behaviour of glibc/musl and Windows: when the given size is zero, it
 * frees the given pointer and returns null, or allocates if the given pointer
 * is null.
 *
 * Don't call or override this; use ghost_realloc_0free() instead.
 */

#if defined(ghost_has_ghost_impl_ex_realloc_0free) || defined(ghost_impl_ex_realloc_0free)
    #error "ghost_impl_ex_realloc_0free() cannot be overridden or disabled. Override ghost_realloc_0free() or define GHOST_MALLOC_SYSTEM=0 instead."
#endif

/* ghost_realloc_0free() override is handled in ghost_malloc_system.h. */
#include "ghost/malloc/ghost_malloc_system.h"

/* If ghost_realloc_0free() is overridden, use it for ghost_impl_ex_realloc_0free()
 * so that other malloc functions can be synthesized from it. */
#ifdef ghost_has_ghost_realloc_0free
    #if ghost_has_ghost_realloc_0free
        #define ghost_impl_ex_realloc_0free ghost_realloc_0free
        #define ghost_has_ghost_impl_ex_realloc_0free 1
    #endif
#endif

/* We only wrap system functions if GHOST_MALLOC_SYSTEM is enabled. */
#ifndef ghost_has_ghost_impl_ex_realloc_0free
    #include "ghost/malloc/ghost_malloc_system.h"
    #if !GHOST_MALLOC_SYSTEM
        #define ghost_has_ghost_impl_ex_realloc_0free 0
    #endif
#endif

/* We require <stdlib.h> in a hosted environment. */
#ifndef ghost_has_ghost_impl_ex_realloc_0free
    #include "ghost/language/ghost_hosted.h"
    #if !GHOST_HOSTED
        #define ghost_has_ghost_impl_ex_realloc_0free 0
    #endif
#endif
#ifndef ghost_has_ghost_impl_ex_realloc_0free
    #include "ghost/header/c/ghost_stdlib_h.h"
    #if !ghost_has(ghost_stdlib_h)
        #define ghost_has_ghost_impl_ex_realloc_0free 0
    #endif
#endif

/* Windows */
#ifndef ghost_has_ghost_impl_ex_realloc_0free
    #ifdef _WIN32
        #ifdef __cplusplus
            #define ghost_impl_ex_realloc_0free ::realloc
        #else
            #define ghost_impl_ex_realloc_0free realloc
        #endif
        #define ghost_has_ghost_impl_ex_realloc_0free 1
    #endif
#endif

/* glibc */
#ifndef ghost_has_ghost_impl_ex_realloc_0free
    #ifdef __linux__
        #include "ghost/detect/ghost_glibc.h"
        #if GHOST_GLIBC
            #ifdef __cplusplus
                #define ghost_impl_ex_realloc_0free ::realloc
            #else
                #define ghost_impl_ex_realloc_0free realloc
            #endif
            #define ghost_has_ghost_impl_ex_realloc_0free 1
        #endif
    #endif
#endif

/* No system ghost_realloc_0free(). */
#ifndef ghost_has_ghost_impl_ex_realloc_0free
    #define ghost_has_ghost_impl_ex_realloc_0free 0
#endif

#endif
