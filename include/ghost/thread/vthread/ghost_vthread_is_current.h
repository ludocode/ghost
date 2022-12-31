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

#ifndef GHOST_VTHREAD_IS_CURRENT_H_INCLUDED
#define GHOST_VTHREAD_IS_CURRENT_H_INCLUDED

#include "ghost/ghost_core.h"
#include "ghost/thread/ghost_thread_config.h"

#if GHOST_DOCUMENTATION
/*
 * Returns true if the given thread handle (of a Ghost thread returning void)
 * is the current thread or false otherwise.
 */
bool ghost_vthread_is_current(ghost_vthread_t thread_id);
#endif

#ifndef ghost_has_ghost_vthread_is_current
    #ifdef ghost_vthread_is_current
        #define ghost_has_ghost_vthread_is_current 1
    #endif
#endif

/* We need thread id */
#ifndef ghost_has_ghost_vthread_is_current
    #include "ghost/thread/vthread/ghost_vthread_t.h"
    #if !ghost_has(ghost_vthread_t)
        #define ghost_has_ghost_vthread_is_current 0
    #endif
#endif

#ifndef ghost_has_ghost_vthread_is_current
    #include "ghost/type/bool/ghost_bool.h"
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/thread/vthread/ghost_vthread_id.h"
    #include "ghost/thread/thread_id/ghost_thread_id_equal.h"
    #include "ghost/thread/thread_id/ghost_thread_id_current.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_bool ghost_vthread_is_current(ghost_vthread_t* ghost_impl_v_thread_v) {
        return ghost_thread_id_equal(
                ghost_vthread_id(ghost_impl_v_thread_v),
                ghost_thread_id_current());
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_vthread_is_current 1
#endif

#endif
