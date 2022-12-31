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

#ifndef GHOST_THREAD_ID_COMPARE_H_INCLUDED
#define GHOST_THREAD_ID_COMPARE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Performs a three-way comparison of the given thread ids, returning their
 * relative ordering.
 *
 * This function may not exist. Several of the backends (pthreads, C11) do not
 * require that thread IDs support comparisons. This is only enabled on platforms
 * where we've checked that it's safe. Use ghost_has(ghost_thread_id_compare) to
 * see if this function exists.
 *
 * @return 0 if the thread ids are equal; less than 0 if the first thread id is
 *         less than the second; and greater than 0 if the first thread id is
 *         greater than the second.
 */
int ghost_thread_id_compare(ghost_thread_id_t first, ghost_thread_id_t second);
#endif

#include "ghost/thread/ghost_thread_config.h"

#ifndef ghost_has_ghost_thread_id_compare
    #ifdef ghost_thread_id_compare
        #define ghost_has_ghost_thread_id_compare 0
    #endif
#endif

/* We need thread id */
#ifndef ghost_has_ghost_thread_id_compare
    #include "ghost/thread/thread_id/ghost_thread_id_t.h"
    #if !ghost_has(ghost_thread_id_t)
        #define ghost_has_ghost_thread_id_compare 0
    #endif
#endif

/*
 * On Windows, thread ids are just a DWORD. We can compare them directly.
 */
#ifndef ghost_has_ghost_thread_id_compare
    #if GHOST_THREAD_WINDOWS
        #include "ghost/math/compare/ghost_compare_i.h"
        #define ghost_thread_id_compare ghost_compare_i
        #define ghost_has_ghost_thread_id_compare 1
    #endif
#endif

/*
 * pthreads and C11 do not require integer types for pthread_t and thrd_t. They
 * may not be comparable with ==, not bitwise comparable, not ordered, etc. We
 * do not assume that three-way comparison is possible in general but we can do
 * it on some platforms where we know it's safe.
 */

/* Under glibc (and uClibc), pthread_t is an unsigned long, internally a
 * pointer to a struct pthread. We can do math on the pointer value. */
#ifndef ghost_has_ghost_thread_id_compare
    #ifdef __GLIBC__
        #include "ghost/math/compare/ghost_compare_ul.h"
        #define ghost_thread_id_compare ghost_compare_ul
        #define ghost_has_ghost_thread_id_compare 1
    #endif
#endif

/* Under musl, pthread_t and thrd_t are both opaque pointers to a struct
 * __pthread. Unsigned long is used in C++ presumably to avoid problems with
 * the undefined struct. We'll cast it to intptr_t to do math on it. */
#ifndef ghost_has_ghost_thread_id_compare
    #include "ghost/detect/ghost_musl.h"
    #if GHOST_MUSL
        #include "ghost/math/compare/ghost_compare_ip.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/impl/ghost_impl_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        int ghost_thread_id_compare(ghost_thread_id_t ghost_impl_v_left, ghost_thread_id_t ghost_impl_v_right) {
            return ghost_compare_ip(
                    ghost_static_cast(intptr_t, ghost_impl_v_left),
                    ghost_static_cast(intptr_t, ghost_impl_v_right));
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_thread_id_compare 1
    #endif
#endif

/* We don't know of any safe way to three-way compare the thread id on this
 * platform. */
#ifndef ghost_has_ghost_thread_id_compare
    #define ghost_has_ghost_thread_id_compare 0
#endif

#endif
