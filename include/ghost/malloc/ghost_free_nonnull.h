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

#ifndef GHOST_FREE_NONNULL_H_INCLUDED
#define GHOST_FREE_NONNULL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Frees the given pointer, asserting in debug builds that it is not null.
 *
 * This is not how the normal C free() function works. The C standard requires
 * that free(0) is safe and does nothing. All known platforms behave as per the
 * C standard.
 *
 * This function is useful if you want a more strict version of free() that
 * checks that its argument is not null. Since ghost_malloc(0) never returns
 * null (unless an error occurs), you can use this to ensure all your malloc
 * and free calls are properly paired, so you're never unexpectedly freeing
 * something you didn't explicitly allocate.
 */
void ghost_free_nonnull(void* ptr);
#endif

/* Override is handled in ghost_malloc_system.h */
#include "ghost/malloc/ghost_malloc_system.h"

/* Synthesize from ghost_free() */
#ifndef ghost_has_ghost_free_nonnull
    #include "ghost/malloc/ghost_free.h"
    #if ghost_has(ghost_free)
        #include "ghost/debug/ghost_assert.h"
        #if ghost_has(ghost_assert)
            #include "ghost/impl/ghost_impl_inline.h"
            #include "ghost/language/ghost_null.h"
            /* TODO malloc attribs? */
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_inline
            void ghost_free_nonnull(void* ptr) {
                ghost_assert(ptr != ghost_null, "");
                ghost_free(ptr);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #else
            /* We can't assert so just map it directly. */
            #define ghost_free_nonnull ghost_free
        #endif
        #define ghost_has_ghost_free_nonnull 1
    #endif
#endif

#ifndef ghost_has_ghost_free_nonnull
    #define ghost_has_ghost_free_nonnull 0
#endif

#endif
