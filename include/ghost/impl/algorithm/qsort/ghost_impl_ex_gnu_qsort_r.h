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

#ifndef GHOST_IMPL_EX_GNU_QSORT_R_H_INCLUDED
#define GHOST_IMPL_EX_GNU_QSORT_R_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/impl/algorithm/qsort/ghost_impl_qsort_config.h"

/*
 * ghost_impl_ex_gnu_qsort_r()
 *
 * A wrapper for an external qsort_r() with the GNU (and future POSIX) prototype
 * if it has one.
 *
 * Don't call or override this; use ghost_gnu_qsort_r().
 */

#if defined(ghost_has_ghost_impl_ex_gnu_qsort_r) || defined(ghost_impl_ex_gnu_qsort_r)
    #error "ghost_impl_ex_gnu_qsort_r() cannot be overridden. Override ghost_gnu_qsort_r() instead."
#endif

/* Handle ghost_gnu_qsort_r() override here */
#ifndef ghost_has_ghost_gnu_qsort_r
    #ifdef ghost_gnu_qsort_r
        #define ghost_has_ghost_gnu_qsort_r 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_gnu_qsort_r() so that
 * other qsort functions can use it */
#ifdef ghost_has_ghost_gnu_qsort_r
    #if ghost_has_ghost_gnu_qsort_r
        #if GHOST_QSORT_FORCE_INTERNAL
            #error "Cannot override ghost_gnu_qsort_r() when GHOST_QSORT_FORCE_INTERNAL is set."
        #endif
        #if GHOST_DISABLE_EXTERNAL_GNU_QSORT_R
            #error "Cannot override ghost_bsd_qsort_r() when GHOST_DISABLE_EXTERNAL_GNU_QSORT_R is set."
        #endif
        #define ghost_impl_ex_gnu_qsort_r ghost_gnu_qsort_r
        #define ghost_has_ghost_impl_ex_gnu_qsort_r 1
    #endif
#endif

/* If we're internal, or disabling system functions, disable this. */
#ifndef ghost_has_ghost_impl_ex_gnu_qsort_r
    #if GHOST_QSORT_FORCE_INTERNAL || GHOST_QSORT_DISABLE_SYSTEM
        #define ghost_has_ghost_impl_ex_gnu_qsort_r 0
    #endif
#endif

/* Linux libcs */
#ifndef ghost_has_ghost_impl_ex_gnu_qsort_r

    /*
     * glibc, uClibc, musl and Newlib all have GNU qsort_r(), but they all
     * declare it only under certain conditions (e.g. _GNU_SOURCE.) We need to
     * declare it ourselves and possibly wrap it.
     *
     * musl was the latest to implement it; it was added to musl 1.2.3 which
     * was released on 2022-04-07 so this is our test for GHOST_GLIBC_COMPAT.
     * For other libcs, we assume they've supported it long enough that we
     * don't need to check.
     *
     * uClibc defines __GLIBC__ under various conditions, not necessarily
     * always. We check __UCLIBC__ just in case.
     *
     * We also check musl with our hacks. This won't detect where qsort_r() was
     * backported (e.g. Alpine backported it to musl 1.2.2) but it's close
     * enough. musl still does not support any means to detect qsort_r() with
     * the preprocessor.
     */

    #include "ghost/detect/ghost_libc.h"
    #include "ghost/impl/ghost_impl_glibc_compat.h"

    #ifdef GHOST_IMPL_LINUX_HAS_GNU_QSORT_R
        #error
    #endif
    #if defined(__GLIBC__) && (GHOST_GLIBC_COMPAT == 0 || GHOST_GLIBC_COMPAT >= 20220407L)
        #define GHOST_IMPL_LINUX_HAS_GNU_QSORT_R
    #elif defined(__UCLIBC__) || defined(__NEWLIB__)
        #define GHOST_IMPL_LINUX_HAS_GNU_QSORT_R
    #else
        #include "ghost/detect/ghost_musl.h"
        #if GHOST_MUSL
            #include "ghost/detect/ghost_musl_version.h"
            #if GHOST_MUSL_VERSION >= 1002003L
                #define GHOST_IMPL_LINUX_HAS_GNU_QSORT_R
            #endif
        #endif
    #endif

    #ifdef GHOST_IMPL_LINUX_HAS_GNU_QSORT_R
        #undef GHOST_IMPL_LINUX_HAS_GNU_QSORT_R

        /*
         * glibc uses various attributes that might cause incompatible
         * declarations and Newlib can declare qsort_r() with the BSD
         * prototype instead (e.g. under _BSD_SOURCE.) In all cases, the
         * true function in the ABI is called qsort_r().
         *
         * If we can rename it directly to the system function with asm
         * labels, we do so; otherwise we wrap it with our own declaration
         * and hope it doesn't conflict.
         */

        #include "ghost/language/ghost_extern_c.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/language/ghost_dllimport.h"

        /* asm label */
        #if GHOST_IMPL_LIBC_ASM
            ghost_extern_c
            ghost_dllimport
            void ghost_impl_ex_gnu_qsort_r(void* first, size_t count, size_t element_size,
                    int (*compare)(const void* left, const void* right, void* context),
                    void* context)
                ghost_impl_libc_asm("qsort_r");

        /* local declaration */
        #else
            #include "ghost/impl/ghost_impl_always_inline.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            void ghost_impl_ex_gnu_qsort_r(void* first, size_t count, size_t element_size,
                    int (*compare)(const void* left, const void* right, void* context),
                    void* context)
            {
                ghost_dllimport
                extern void qsort_r(void* first, size_t count, size_t element_size,
                        int (*compare)(const void* left, const void* right, void* context),
                        void* context);
                qsort_r(first, count, element_size, compare, context);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #endif

        #define ghost_has_ghost_impl_ex_gnu_qsort_r 1
    #endif
#endif

/* No other systems that we know of define GNU qsort_r(). This may grow in the
 * future since GNU qsort_r() has apparently been added to the next version of
 * POSIX. Once it's ratified we can detect _POSIX_VERSION. */
#ifndef ghost_has_ghost_impl_ex_gnu_qsort_r
    #define ghost_has_ghost_impl_ex_gnu_qsort_r 0
#endif

#endif
