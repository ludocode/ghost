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

#ifndef GHOST_IMPL_EX_C11_QSORT_S_H_INCLUDED
#define GHOST_IMPL_EX_C11_QSORT_S_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/impl/algorithm/qsort/ghost_impl_qsort_config.h"

/*
 * ghost_impl_ex_c11_qsort_s()
 *
 * A wrapper for an external qsort_s() with the C11 Annex K prototype if it has
 * one.
 *
 * Don't call or override this; use ghost_c11_qsort_s() instead.
 */

#if defined(ghost_has_ghost_impl_ex_c11_qsort_s) || defined(ghost_impl_ex_c11_qsort_s)
    #error "ghost_impl_ex_c11_qsort_s() cannot be overridden. Override ghost_c11_qsort_s() instead."
#endif

/* Handle ghost_c11_qsort_s() override here */
#ifndef ghost_has_ghost_c11_qsort_s
    #ifdef ghost_c11_qsort_s
        #define ghost_has_ghost_c11_qsort_s 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_c11_qsort_s() so that
 * other qsort functions can use it */
#ifdef ghost_has_ghost_c11_qsort_s
    #if ghost_has_ghost_c11_qsort_s
        #if GHOST_QSORT_FORCE_INTERNAL
            #error "Cannot override ghost_c11_qsort_s() when GHOST_QSORT_FORCE_INTERNAL is set."
        #endif
        #define ghost_impl_ex_c11_qsort_s ghost_c11_qsort_s
        #define ghost_has_ghost_impl_ex_c11_qsort_s 1
    #endif
#endif

/* If we're internal, or disabling system functions, disable this. */
#ifndef ghost_has_ghost_impl_ex_c11_qsort_s
    #if GHOST_QSORT_FORCE_INTERNAL || GHOST_QSORT_DISABLE_SYSTEM
        #define ghost_has_ghost_impl_ex_c11_qsort_s 0
    #endif
#endif

/*
 * This function should exist in the libc if __STDC_LIB_EXT1__ is defined by
 * the implementation, but it won't actually be declared unless
 * __STDC_WANT_LIB_EXT1__ is defined by the user.
 *
 * FreeBSD is currently the only platform that I know of that implements this
 * but it doesn't define __STDC_LIB_EXT1__. We therefore detect either
 * __STDC_LIB_EXT1__ or __FreeBSD__.
 *
 * The platform may not properly respect __STDC_WANT_LIB_EXT1__ (and the user
 * may have incorrectly defined it after including headers) so we don't want to
 * rely on it if we don't have to. If we have asm labels, we use that to
 * declare it ourselves, this way we can also avoid potential conflicts with
 * errno_t and rsize_t. If we don't have asm labels, we check
 * __STDC_WANT_LIB_EXT1__ and declare it ourselves (with size_t) if needed.
 */

/* asm label */
#ifndef ghost_has_ghost_impl_ex_c11_qsort_s
    #include "ghost/header/c/ghost_stdlib_h.h"
    #if defined(__STDC_LIB_EXT1__) || defined(__FreeBSD__)
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #if GHOST_IMPL_LIBC_ASM
            #include "ghost/language/ghost_extern_c.h"
            #include "ghost/language/ghost_dllimport.h"
            #include "ghost/error/ghost_errno_t.h"
            #include "ghost/error/ghost_rsize_t.h"
            ghost_extern_c
            ghost_dllimport
            ghost_errno_t ghost_impl_ex_c11_qsort_s(void* first, ghost_rsize_t count, ghost_rsize_t element_size,
                    int (*compare)(const void* left, const void* right, void* context),
                    void* context)
                ghost_impl_libc_asm("qsort_s");
            #define ghost_has_ghost_impl_ex_c11_qsort_s 1
        #endif
    #endif
#endif

/* Check __STDC_WANT_LIB_EXT1__ and RSIZE_MAX. If both of these are defined, it
 * hopefully means <stdlib.h> was included with C11 Annex K support. */
#ifndef ghost_has_ghost_impl_ex_c11_qsort_s
    #if defined(__STDC_LIB_EXT1__) || defined(__FreeBSD__)
        #if defined(__STDC_WANT_LIB_EXT1__)
            #if __STDC_WANT_LIB_EXT1__ && defined(RSIZE_MAX)
                #define ghost_impl_ex_c11_qsort_s qsort_s
                #define ghost_has_ghost_impl_ex_c11_qsort_s 1
            #endif
        #endif
    #endif
#endif

/* no __STDC_WANT_LIB_EXT1__ */
#ifndef ghost_has_ghost_impl_ex_c11_qsort_s
    #if defined(__STDC_LIB_EXT1__) || defined(__FreeBSD__)
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/language/ghost_extern_c.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/error/ghost_errno_t.h"
        #include "ghost/error/ghost_rsize_t.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        ghost_errno_t ghost_impl_ex_c11_qsort_s(void* first, ghost_rsize_t count, ghost_rsize_t element_size,
                int (*compare)(const void* left, const void* right, void* context),
                void* context)
        {
            /* If the platform has declared this despite __STDC_WANT_LIB_EXT1__
             * being off, this may conflict because ghost_errno_t and
             * ghost_rsize_t will be int and size_t, not errno_t and rsize_t. */
            ghost_dllimport
            ghost_errno_t qsort_s(void* first, ghost_rsize_t count, ghost_rsize_t element_size,
                    int (*compare)(const void* left, const void* right, void* context),
                    void* context);
            return qsort_s(first, count, element_size, compare, context);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_impl_ex_c11_qsort_s 1
    #endif
#endif

/* Otherwise we don't have an external C11 qsort_s(). */
#ifndef ghost_has_ghost_impl_ex_c11_qsort_s
    #define ghost_has_ghost_impl_ex_c11_qsort_s 0
#endif

#endif
