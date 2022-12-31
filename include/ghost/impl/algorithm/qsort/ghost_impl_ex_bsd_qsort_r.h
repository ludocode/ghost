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

#ifndef GHOST_IMPL_EX_BSD_QSORT_R_H_INCLUDED
#define GHOST_IMPL_EX_BSD_QSORT_R_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/impl/algorithm/qsort/ghost_impl_qsort_config.h"

/*
 * ghost_impl_ex_bsd_qsort_r()
 *
 * A wrapper for an external qsort_r() with the FreeBSD/Apple prototype if it has
 * one.
 *
 * Don't call or override this; use ghost_bsd_qsort_r() instead.
 */

#if defined(ghost_has_ghost_impl_ex_bsd_qsort_r) || defined(ghost_impl_ex_bsd_qsort_r)
    #error "ghost_impl_ex_bsd_qsort_r() cannot be overridden. Override ghost_bsd_qsort_r() instead."
#endif

/* Handle ghost_bsd_qsort_r() override here */
#ifndef ghost_has_ghost_bsd_qsort_r
    #ifdef ghost_bsd_qsort_r
        #define ghost_has_ghost_bsd_qsort_r 1
    #endif
#endif

/* If it's overridden, use it for ghost_impl_ex_bsd_qsort_r() so that
 * other qsort functions can use it */
#ifdef ghost_has_ghost_bsd_qsort_r
    #if ghost_has_ghost_bsd_qsort_r
        #if GHOST_QSORT_FORCE_INTERNAL
            #error "Cannot override ghost_bsd_qsort_r() when GHOST_QSORT_FORCE_INTERNAL is set."
        #endif
        #define ghost_impl_ex_bsd_qsort_r ghost_bsd_qsort_r
        #define ghost_has_ghost_impl_ex_bsd_qsort_r 1
    #endif
#endif

/* If we're internal, or disabling system functions, disable this. */
#ifndef ghost_has_ghost_impl_ex_bsd_qsort_r
    #if GHOST_QSORT_FORCE_INTERNAL || GHOST_QSORT_DISABLE_SYSTEM
        #define ghost_has_ghost_impl_ex_bsd_qsort_r 0
    #endif
#endif

/*
 * FreeBSD and DragonFly BSD support the BSD qsort_r(), but only if _BSD_SOURCE
 * is defined.
 *
 * Since we don't know whether they will break the ABI, it's probably not safj
 * to declare it ourselves. Instead we try to detect whether it exists.
 *
 * We'd rather use the real prototype and get a compiler
 * error if it's wrong instead of declaring it ourselves and risking silently
 * compiling to nonsense. For this reason we don't do anything special to
 * future-proof against this.
 */
#ifndef ghost_has_ghost_impl_ex_bsd_qsort_r
    #include "ghost/header/c/ghost_stdlib_h.h"
    #if defined(__FreeBSD__) || defined(__DragonFly__)
        #if ghost_has(ghost_stdlib_h)
            #define ghost_impl_ex_bsd_qsort_r qsort_r
            #define ghost_has_ghost_impl_ex_bsd_qsort_r 1
        #endif
    #endif
#endif

/*
 * Apple platforms (macOS, iOS) define qsort_r() but have some feature test
 * requirements (not _ANSI_SOURCE and some variations of _POSIX_SOURCE and
 * _DARWIN_SOURCE).
 *
 * FreeBSD and DragonFly BSD also support BSD qsort_r(), but only if
 * _BSD_SOURCE is defined.
 *
 * We declare it ourselves to avoid these requirements.
 *
 * Note that there is some effort in FreeBSD to change it over to the GNU
 * prototype:
 *
 *     https://reviews.freebsd.org/D17083
 *     https://austingroupbugs.net/view.php?id=900
 *
 * That plan was put on hold in favor of implementing C11 qsort_s() but they
 * may at some point try again.
 *
 * If they ever actually do this, it's not clear whether they will preserve the
 * old ABI. There are some suggestions that an asm label should be used to
 * preserve the old ABI and call the new function something else, but that's
 * not what the above patches do. They do an ABI break and add some _Generic
 * hacks to the header. For some reason they still preserve the old function
 * but they renamed it instead of using an asm label to rename the new one.
 *
 * In any case, if they ever do decide to change this, the below code will
 * fail at runtime.
 */
#ifndef ghost_has_ghost_impl_ex_bsd_qsort_r
    #if defined(__APPLE__) || defined(__FreeBSD__) || defined(__DragonFly__)
        #include "ghost/language/ghost_extern_c.h"
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/type/size_t/ghost_size_t.h"

        #if GHOST_IMPL_LIBC_ASM
            ghost_extern_c
            ghost_dllimport
            void ghost_impl_ex_bsd_qsort_r(void* first, ghost_size_t count, ghost_size_t element_size,
                    void* context,
                    int (*compare)(void* context, const void* left, const void* right))
                ghost_impl_libc_asm("qsort_r");
        #else
            #include "ghost/impl/ghost_impl_always_inline.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            void ghost_impl_ex_bsd_qsort_r(void* first, ghost_size_t count, ghost_size_t element_size,
                    void* context,
                    int (*compare)(void* context, const void* left, const void* right))
            {
                ghost_dllimport
                extern void qsort_r(void* first, ghost_size_t count, ghost_size_t element_size,
                        void* context,
                        int (*compare)(void* context, const void* left, const void* right));
                qsort_r(first, count, element_size, context, compare);
            }
            GHOST_IMPL_FUNCTION_CLOSE
        #endif

        #define ghost_has_ghost_impl_ex_bsd_qsort_r 1
    #endif
#endif

/*
 * Newlib supports BSD qsort_r() but it may declare it as either qsort_r() or
 * __bsd_qsort_r(). Either way the asm name is __bsd_qsort_r() so we declare
 * that ourselves.
 */
#ifndef ghost_has_ghost_impl_ex_bsd_qsort_r
    #include "ghost/header/c/ghost_stdlib_h.h"
    #ifdef __NEWLIB__
        #include "ghost/impl/ghost_impl_libc_asm.h"
        #include "ghost/language/ghost_extern_c.h"
        #include "ghost/language/ghost_dllimport.h"
        #include "ghost/type/size_t/ghost_size_t.h"

        ghost_extern_c
        ghost_dllimport
        void
        #if GHOST_IMPL_LIBC_ASM
            ghost_impl_ex_bsd_qsort_r(void* first, ghost_size_t count, ghost_size_t element_size,
                    void* context,
                    int (*compare)(void* context, const void* left, const void* right))
                ghost_impl_libc_asm("__bsd_qsort_r");
        #else
            __bsd_qsort_r(void* first, ghost_size_t count, ghost_size_t element_size,
                    void* context,
                    int (*compare)(void* context, const void* left, const void* right));
            #define ghost_impl_ex_bsd_qsort_r __bsd_qsort_r
        #endif
        #define ghost_has_ghost_impl_ex_bsd_qsort_r 1
    #endif
#endif

/* Otherwise we don't have an external BSD qsort_r(). */
#ifndef ghost_has_ghost_impl_ex_bsd_qsort_r
    #define ghost_has_ghost_impl_ex_bsd_qsort_r 0
#endif

#endif
