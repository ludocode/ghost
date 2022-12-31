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

#ifndef GHOST_THREAD_ID_EQUAL_H_INCLUDED
#define GHOST_THREAD_ID_EQUAL_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

#if GHOST_DOCUMENTATION
/*
 * Returns true if two thread ids refer to the same thread and false otherwise.
 */
bool ghost_thread_id_equal(void);
#endif

/* We need thread id */
#ifndef ghost_has_ghost_thread_id_equal
    #include "ghost/thread/thread_id/ghost_thread_id_t.h"
    #if !ghost_has(ghost_thread_id_t)
        #define ghost_has_ghost_thread_id_equal 0
    #endif
#endif

#ifndef ghost_has_ghost_thread_id_equal
    #ifdef ghost_thread_id_equal
        #define ghost_has_ghost_thread_id_equal 1
    #endif
#endif

/*
 * Windows
 *
 * On Windows, thread IDs are just a DWORD. We can compare them with ==.
 */
#ifndef ghost_has_ghost_thread_id_equal
    #if GHOST_THREAD_WINDOWS
        #define ghost_thread_id_equal(x, y) ((x) == (y))
        #define ghost_has_ghost_thread_id_equal 1
    #endif
#endif

/* pthreads or C11. We need to wrap it to cast the return value to bool. */
#ifndef ghost_has_ghost_thread_id_equal
    #if GHOST_THREAD_PTHREADS || GHOST_THREAD_C11
        #include "ghost/type/size_t/ghost_size_t.h"
        #include "ghost/type/bool/ghost_bool.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        ghost_bool ghost_thread_id_equal(ghost_thread_id_t ghost_impl_v_a, ghost_thread_id_t ghost_impl_v_b) {
            #if GHOST_THREAD_PTHREADS
                return ghost_static_cast(ghost_bool, pthread_equal(ghost_impl_v_a, ghost_impl_v_b));
            #elif GHOST_THREAD_C11
                return ghost_static_cast(ghost_bool, thrd_equal(ghost_impl_v_a, ghost_impl_v_b));
            #else
                #error
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_thread_id_equal 1
    #endif
#endif

#ifndef ghost_has_ghost_thread_id_equal
    #define ghost_has_ghost_thread_id_equal 0
#endif

#endif
