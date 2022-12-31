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

#ifndef GHOST_IMPL_EX_WIN_QSORT_S_H_INCLUDED
#define GHOST_IMPL_EX_WIN_QSORT_S_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/impl/algorithm/qsort/ghost_impl_qsort_config.h"

/*
 * ghost_impl_ex_win_qsort_s()
 *
 * A wrapper for an external qsort_s() with the Windows prototype if it has one.
 *
 * Don't call or override this; use ghost_win_qsort_s() instead.
 */

#if defined(ghost_has_ghost_impl_ex_win_qsort_s) || defined(ghost_impl_ex_win_qsort_s)
    #error "ghost_impl_ex_win_qsort_s() cannot be overridden. Override ghost_win_qsort_s() instead."
#endif

/* Handle ghost_win_qsort_s() override here */
#ifndef ghost_has_ghost_win_qsort_s
    #ifdef ghost_win_qsort_s
        #define ghost_has_ghost_win_qsort_s 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_win_qsort_s() so that
 * other qsort functions can use it */
#ifdef ghost_has_ghost_win_qsort_s
    #if ghost_has_ghost_win_qsort_s
        #if GHOST_QSORT_FORCE_INTERNAL
            #error "Cannot override ghost_win_qsort_s() when GHOST_QSORT_FORCE_INTERNAL is set."
        #endif
        #define ghost_impl_ex_win_qsort_s ghost_win_qsort_s
        #define ghost_has_ghost_impl_ex_win_qsort_s 1
    #endif
#endif

/* If we're internal, or disabling system functions, disable this. */
#ifndef ghost_has_ghost_impl_ex_win_qsort_s
    #if GHOST_QSORT_FORCE_INTERNAL || GHOST_QSORT_DISABLE_SYSTEM
        #define ghost_has_ghost_impl_ex_win_qsort_s 0
    #endif
#endif

/* Windows, Wine and ReactOS support this prototype. */
#ifndef ghost_has_ghost_impl_ex_win_qsort_s
    #ifdef _WIN32
        #include "ghost/header/c/ghost_stdlib_h.h"
        /* Don't bother to wrap it; just forward with a macro. */
        #define ghost_impl_ex_win_qsort_s qsort_s
        #define ghost_has_ghost_impl_ex_win_qsort_s 1
    #endif
#endif

/* Otherwise we don't have an external Windows qsort_s(). */
#ifndef ghost_has_ghost_impl_ex_win_qsort_s
    #define ghost_has_ghost_impl_ex_win_qsort_s 0
#endif

#endif
