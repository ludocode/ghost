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

#ifndef GHOST_C11_QSORT_S_H_INCLUDED
#define GHOST_C11_QSORT_S_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Sorts an array with a custom callback and context with a signature matching
 * C11 Annex K qsort_r().
 *
 * This wraps the closest matching platform qsort_r()/qsort_s() function if one
 * is available. If not, Ghost implements one.
 *
 * This mainly exists as a portable drop-in replacement for C11 Annex K
 * qsort_r() wherever it's already being used. If you're writing new code
 * you should probably use ghost_gnu_qsort_r() instead.
 */
errno_t ghost_c11_qsort_s(void* first, rsize_t count, rsize_t element_size,
        int (*user_compare)(const void* left, const void* right, void* user_context),
        void* user_context);
#endif

/* Override is handled in the ex wrapper */
#include "ghost/impl/algorithm/qsort/ghost_impl_ex_c11_qsort_s.h"

/* If we have a real C11 qsort_r(), we call it directly. */
#ifndef ghost_has_ghost_c11_qsort_s
    #if ghost_has_ghost_impl_ex_c11_qsort_s
        #include "ghost/error/ghost_errno_t.h"
        #include "ghost/error/ghost_rsize_t.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/language/ghost_discard.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        ghost_errno_t ghost_c11_qsort_s(void* first, ghost_rsize_t count, ghost_rsize_t element_size,
                int (*user_compare)(const void* left, const void* right, void* user_context),
                void* user_context)
        {
            return ghost_impl_ex_c11_qsort_s(first, count, element_size, user_compare, user_context);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_c11_qsort_s 1
    #endif
#endif

/* Otherwise, since GNU qsort_r() uses the same callback, we wrap our GNU
 * qsort_r() wrapper (not the system function) with our constraint checks. This
 * will handle all the alternate qsorts including the internal implementation. */
#ifndef ghost_has_ghost_c11_qsort_s
    #include "ghost/algorithm/qsort/ghost_gnu_qsort_r.h"
    #if ghost_has(ghost_gnu_qsort_r)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_expect_false.h"
        #include "ghost/language/ghost_null.h"
        #include "ghost/debug/ghost_fatal.h"
        #include "ghost/error/ghost_errno_t.h"
        #include "ghost/error/ghost_rsize_t.h"

        GHOST_IMPL_FUNCTION_OPEN

        ghost_impl_inline
        ghost_errno_t ghost_c11_qsort_s(void* first, ghost_rsize_t count, ghost_rsize_t element_size,
                int (*user_compare)(const void* left, const void* right, void* user_context),
                void* user_context)
        {
            if (ghost_expect_false(count > GHOST_RSIZE_BOUNDS ||
                    element_size > GHOST_RSIZE_BOUNDS ||
                    (count > 0 && (first == ghost_null || user_context == ghost_null))))
                ghost_fatal("constraint violation");

            ghost_gnu_qsort_r(first, count, element_size, user_compare, user_context);
            return 0;
        }

        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_c11_qsort_s 1
    #endif
#endif

#ifndef ghost_has_ghost_c11_qsort_s
    #define ghost_has_ghost_c11_qsort_s 0
#endif

#endif
