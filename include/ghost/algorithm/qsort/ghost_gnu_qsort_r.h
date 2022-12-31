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

#ifndef GHOST_GNU_QSORT_R_H_INCLUDED
#define GHOST_GNU_QSORT_R_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Sorts an array with a custom callback and context with a signature matching
 * GNU (and future POSIX) qsort_r().
 *
 * This wraps the closest matching platform qsort_r()/qsort_s() function if one
 * is available. If not, Ghost implements one.
 */
void ghost_gnu_qsort_r(void* first, size_t count, size_t element_size,
        int (*compare)(const void* left, const void* right, void* context),
        void* context);
#endif

/* Override is handled in the ex wrapper */
#include "ghost/impl/algorithm/qsort/ghost_impl_ex_gnu_qsort_r.h"

/* If we have a real GNU qsort_r(), we call it directly. If we have a C11
 * qsort_s(), the callback matches so we also call it directly. We use a
 * wrapper function to give clean compiler errors. */
#ifndef ghost_has_ghost_gnu_qsort_r
    #include "ghost/impl/algorithm/qsort/ghost_impl_ex_c11_qsort_s.h"
    #if ghost_has_ghost_impl_ex_gnu_qsort_r || ghost_has_ghost_impl_ex_c11_qsort_s
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/language/ghost_discard.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        void ghost_gnu_qsort_r(void* first, ghost_size_t count, ghost_size_t element_size,
                int (*user_compare)(const void* left, const void* right, void* user_context),
                void* user_context)
        {
            #if ghost_has_ghost_impl_ex_gnu_qsort_r
                ghost_impl_ex_gnu_qsort_r(first, count, element_size, user_compare, user_context);
            #elif ghost_has_ghost_impl_ex_c11_qsort_s
                ghost_discard(ghost_impl_ex_c11_qsort_s(first, count, element_size, user_compare, user_context));
            #else
                #error
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_gnu_qsort_r 1
    #endif
#endif

/* Convert BSD qsort_r() or Windows qsort_s(). These are nearly identical; the
 * only difference is that the compare callback on Windows may be declared
 * __cdecl. The compare callback prototype in these is different so we need a
 * thunk to convert it. */
#ifndef ghost_has_ghost_gnu_qsort_r
    #include "ghost/impl/algorithm/qsort/ghost_impl_ex_bsd_qsort_r.h"
    #include "ghost/impl/algorithm/qsort/ghost_impl_ex_win_qsort_s.h"
    #if ghost_has_ghost_impl_ex_bsd_qsort_r || ghost_has_ghost_impl_ex_win_qsort_s
        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_static_cast.h"

        GHOST_IMPL_FUNCTION_OPEN

        typedef struct {
            int (*user_compare)(const void* left, const void* right, void* user_context);
            void* user_context;
        } ghost_gnu_qsort_r_context_t;

        /* We give these functions different names to avoid possible linker errors. */
        ghost_impl_function
        int
        #if ghost_has_ghost_impl_ex_bsd_qsort_r
            ghost_gnu_qsort_r_compare_bsd
        #elif ghost_has_ghost_impl_ex_win_qsort_s
            GHOST_WIN_QSORT_S_CDECL ghost_gnu_qsort_r_compare_win
        #else
            #error
        #endif
                (void* vcontext, const void* left, const void* right) GHOST_IMPL_DEF(
        {
            ghost_gnu_qsort_r_context_t* context = ghost_static_cast(ghost_gnu_qsort_r_context_t*, vcontext);
            return context->user_compare(left, right, context->user_context);
        })

        ghost_impl_inline
        void ghost_gnu_qsort_r(void* first, ghost_size_t count, ghost_size_t element_size,
                int (*user_compare)(const void* left, const void* right, void* user_context),
                void* user_context)
        {
            ghost_gnu_qsort_r_context_t context;
            context.user_compare = user_compare;
            context.user_context = user_context;
            #if ghost_has_ghost_impl_ex_bsd_qsort_r
                ghost_impl_ex_bsd_qsort_r(first, count, element_size, &context, &ghost_gnu_qsort_r_compare_bsd);
            #elif ghost_has_ghost_impl_ex_win_qsort_s
                ghost_impl_ex_win_qsort_s(first, count, element_size, &ghost_gnu_qsort_r_compare_win, &context);
            #else
                #error
            #endif
        }

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_gnu_qsort_r 1
    #endif
#endif

/* Use the internal implementation */
#ifndef ghost_has_ghost_gnu_qsort_r
    #if !GHOST_QSORT_DISABLE_INTERNAL
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/impl/algorithm/qsort/ghost_impl_qsort_internal.h"
        #include "ghost/type/size_t/ghost_size_t.h"

        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_inline
        void ghost_gnu_qsort_r(void* first, size_t count, size_t element_size,
                int (*user_compare)(const void* left, const void* right, void* user_context),
                void* user_context)
        {
            ghost_impl_qsort_state_t state;
            state.element_size = element_size;
            state.size_class = ghost_impl_qsort_resolve_size_class(first, element_size);
            state.variant = ghost_impl_qsort_variant_gnu;
            state.compare.gnu = user_compare;
            state.user_context = user_context;
            ghost_impl_qsort_internal(&state, first, count);
        }

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_gnu_qsort_r 1
    #endif
#endif

#ifndef ghost_has_ghost_gnu_qsort_r
    #define ghost_has_ghost_gnu_qsort_r 0
#endif

#endif
