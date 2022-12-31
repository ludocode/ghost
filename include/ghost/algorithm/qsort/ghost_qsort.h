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

#ifndef GHOST_QSORT_H_INCLUDED
#define GHOST_QSORT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Sorts an array with a custom callback with a signature matching the standard
 * C qsort() function.
 *
 * This wraps the platform qsort() if available. In freestanding, or if the
 * platform qsort() is disabled, Ghost implements one.
 */
void ghost_qsort(void* first, size_t count, size_t element_size,
        int (*compare)(const void* left, const void* right));
#endif

#include "ghost/impl/algorithm/qsort/ghost_impl_qsort_config.h"

/* Handle override via #define */
#ifndef ghost_has_ghost_qsort
    #ifdef ghost_qsort
        #define ghost_has_ghost_qsort 1
    #endif
#endif

/* Call platform qsort() */
#ifndef ghost_has_ghost_qsort
    #if !GHOST_QSORT_FORCE_INTERNAL
        #include "ghost/header/c/ghost_stdlib_h.h"
        #include "ghost/language/ghost_hosted.h"
        #if GHOST_HOSTED && ghost_has(ghost_stdlib_h)
            #include "ghost/type/size_t/ghost_size_t.h"
            #include "ghost/impl/ghost_impl_always_inline.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            void ghost_qsort(void* first, ghost_size_t count, ghost_size_t element_size,
                    int (*compare)(const void* left, const void* right))
            {
                qsort(first, count, element_size, compare);
            }
            GHOST_IMPL_FUNCTION_CLOSE
            #define ghost_has_ghost_qsort 1
        #endif
    #endif
#endif

/* TODO it's possible to set GHOST_QSORT_DISABLE_SYSTEM and then define an
 * external qsort_r() and not qsort(). We could provide wrappers here for
 * completeness. */

/* Call internal qsort() */
#ifndef ghost_has_ghost_qsort
    #if !GHOST_QSORT_DISABLE_INTERNAL
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/impl/algorithm/qsort/ghost_impl_qsort_internal.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        void ghost_qsort(void* first, ghost_size_t count, ghost_size_t element_size,
                int (*compare)(const void* left, const void* right))
        {
            ghost_impl_qsort_state_t state;
            state.element_size = element_size;
            state.size_class = ghost_impl_qsort_resolve_size_class(first, element_size);
            state.variant = ghost_impl_qsort_variant_nocontext;
            state.compare.nocontext = compare;
            ghost_impl_qsort_internal(&state, first, count);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_qsort 1
    #endif
#endif

#endif
