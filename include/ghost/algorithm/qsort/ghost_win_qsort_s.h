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

#ifndef GHOST_WIN_QSORT_S_H_INCLUDED
#define GHOST_WIN_QSORT_S_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Sorts an array with a custom callback and context with a signature matching
 * Windows, Wine and ReactOS qsort_s().
 *
 * This wraps the closest matching platform qsort_r()/qsort_s() function if one
 * is available. If not, Ghost implements one.
 */
void ghost_win_qsort_s(void* first, size_t count, size_t element_size,
        int (__cdecl *compare)(void* context, const void* left, const void* right),
        void* context)
#endif

/* Override is handled in the ex wrapper */
#include "ghost/impl/algorithm/qsort/ghost_impl_ex_win_qsort_s.h"

/* If we have a real Windows qsort_s(), call it directly. If we have a BSD
 * qsort_r() and we're not using __cdecl, we can pass the callback through
 * directly so we can wrap it without overhead. We use a wrapper function to
 * give clean compiler errors. */
#ifndef ghost_has_ghost_win_qsort_s
    #include "ghost/impl/algorithm/qsort/ghost_impl_ex_bsd_qsort_r.h"
    #if ghost_has(ghost_impl_ex_win_qsort_s) || \
            (ghost_has(ghost_impl_ex_bsd_qsort_r) && !GHOST_WIN_QSORT_S_USE_CDECL)
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        void ghost_win_qsort_s(void* first, ghost_size_t count, ghost_size_t element_size,
                int (GHOST_WIN_QSORT_S_CDECL *user_compare)(void* user_context, const void* left, const void* right),
                void* user_context)
        {
            #if ghost_has(ghost_impl_ex_win_qsort_s)
                ghost_impl_ex_win_qsort_s(first, count, element_size, user_compare, user_context);
            #elif (ghost_has(ghost_impl_ex_bsd_qsort_r) && !GHOST_WIN_QSORT_S_USE_CDECL)
                ghost_impl_ex_bsd_qsort_r(first, count, element_size, user_context, user_compare);
            #else
                #error
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_win_qsort_s 1
    #endif
#endif

/* Wrap any of the other qsort_r() functions. */
#ifndef ghost_has_ghost_win_qsort_s
    #include "ghost/impl/algorithm/qsort/ghost_impl_ex_gnu_qsort_r.h"
    #include "ghost/impl/algorithm/qsort/ghost_impl_ex_c11_qsort_s.h"
    #if ghost_has_ghost_impl_ex_gnu_qsort_r || \
            ghost_has(ghost_impl_ex_bsd_qsort_r) || \
            ghost_has_ghost_impl_ex_c11_qsort_s

        #include "ghost/impl/ghost_impl_function.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_discard.h"
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/language/ghost_static_cast.h"

        GHOST_IMPL_FUNCTION_OPEN

        typedef struct ghost_win_qsort_s_context_t {
            int (GHOST_WIN_QSORT_S_CDECL *user_compare)(void* user_context, const void* left, const void* right);
            void* user_context;
        } ghost_win_qsort_s_context_t;

        #if ghost_has(ghost_impl_ex_bsd_qsort_r)

            /* Wrap BSD */

            ghost_impl_function
            int
            ghost_win_qsort_s_compare_bsd(void* vcontext, const void* left, const void* right) GHOST_IMPL_DEF({
                ghost_win_qsort_s_context_t* context = ghost_static_cast(ghost_win_qsort_s_context_t*, vcontext);
                return context->user_compare(context->user_context, left, right);
            })

            ghost_impl_inline
            void ghost_win_qsort_s(void* first, ghost_size_t count, ghost_size_t element_size,
                    int (GHOST_WIN_QSORT_S_CDECL *user_compare)(void* user_context, const void* left, const void* right),
                    void* user_context)
            {
                ghost_win_qsort_s_context_t context = {user_compare, user_context};
                ghost_impl_ex_bsd_qsort_r(first, count, element_size, &context, &ghost_win_qsort_s_compare_bsd);
            }

        #else

            /* Wrap GNU or C11. They use the same compare callback. */

            ghost_impl_function
            int ghost_win_qsort_s_compare_gnu_c11(const void* left, const void* right, void* vcontext) GHOST_IMPL_DEF({
                ghost_win_qsort_s_context_t* context = ghost_static_cast(ghost_win_qsort_s_context_t*, vcontext);
                return context->user_compare(context->user_context, left, right);
            })

            ghost_impl_inline
            void ghost_win_qsort_s(void* first, ghost_size_t count, ghost_size_t element_size,
                    int (GHOST_WIN_QSORT_S_CDECL *user_compare)(void* user_context, const void* left, const void* right),
                    void* user_context)
            {
                ghost_win_qsort_s_context_t context;
                context.user_compare = user_compare;
                context.user_context = user_context;

                #if ghost_has_ghost_impl_ex_gnu_qsort_r
                    ghost_impl_ex_gnu_qsort_r(first, count, element_size,
                            &ghost_win_qsort_s_compare_gnu_c11, &context);
                #elif ghost_has_ghost_impl_ex_c11_qsort_s
                    ghost_discard(ghost_impl_ex_c11_qsort_s(first, count, element_size,
                                &ghost_win_qsort_s_compare_gnu_c11, &context));
                #else
                    #error
                #endif
            }

        #endif

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_win_qsort_s 1
    #endif
#endif

/* Use the internal implementation */
#ifndef ghost_has_ghost_win_qsort_s
    #if !GHOST_QSORT_DISABLE_INTERNAL
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/impl/algorithm/qsort/ghost_impl_qsort_internal.h"
        #include "ghost/type/size_t/ghost_size_t.h"

        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_inline
        void ghost_win_qsort_s(void* first, ghost_size_t count, ghost_size_t element_size,
                int (GHOST_WIN_QSORT_S_CDECL *user_compare)(void* user_context, const void* left, const void* right),
                void* user_context)
        {
            ghost_impl_qsort_state_t state;
            state.element_size = element_size;
            state.size_class = ghost_impl_qsort_resolve_size_class(first, element_size);
            #if GHOST_WIN_QSORT_S_USE_CDECL
                state.variant = ghost_impl_qsort_variant_windows;
                state.compare.windows = user_compare;
            #else
                state.variant = ghost_impl_qsort_variant_bsd;
                state.compare.bsd = user_compare;
            #endif
            state.user_context = user_context;
            ghost_impl_qsort_internal(&state, first, count);
        }

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_win_qsort_s 1
    #endif
#endif

#ifndef ghost_has_ghost_win_qsort_s
    #define ghost_has_ghost_win_qsort_s 0
#endif

#endif
