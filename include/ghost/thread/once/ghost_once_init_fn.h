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

#ifndef GHOST_ONCE_INIT_FN_H_INCLUDED
#define GHOST_ONCE_INIT_FN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Dynamically initialize a once flag.
 *
 * You are unlikely to need this function. Use GHOST_ONCE_INIT instead.
 *
 * This must be called exactly once for a given once flag, and must complete on
 * one thread before ghost_once() can be called on any threads. It stands to
 * reason therefore that if you have a means of synchronizing threads to
 * perform a single call to ghost_once_init(), you might as well just use that
 * to perform your single initialization.
 *
 * The only real use case for this is if you have a dynamic structure that has
 * a part you want lazily initialized from multiple threads. So you allocate
 * the structure, initialize its once flag, launch a bunch of threads, then
 * some time later the threads concurrently need access to something in the
 * structure that still needs to be initialized so they use the once flag to
 * initialize it. In this unlikely scenario, use ghost_once_init() instead of
 * GHOST_ONCE_INIT to initialize the flag.
 */
void ghost_once_init(ghost_once_t* once);
#endif

#ifndef ghost_has_ghost_once_init
    #ifdef ghost_once_init
        #define ghost_has_ghost_once_init 1
    #endif
#endif

#ifndef ghost_has_ghost_once_init
    #include "ghost/thread/once/ghost_once_t.h"
    #if !ghost_has_ghost_once_t
        #define ghost_has_ghost_once_init 0
    #endif
#endif

/*
 * Windows
 *     https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initonceinitialize
 * The documentation claims that a one-time initialization object cannot be
 * moved or copied (but of course there is no corresponding destroy function
 * so it's pretty limited in what it might do.) To be on the safe side we
 * follow the documentation and use this to initialize it.
 */
#ifndef ghost_has_ghost_once_init
    #ifdef _WIN32
        #define ghost_once_init InitOnceInitialize
        #define ghost_has_ghost_once_init 1
    #endif
#endif

/*
 * Other platforms only provide a static initializer. It is only required to
 * work for static initialization, not as a variable assignment. While some
 * platforms just define these to e.g. 0, others may define them to {0} or some
 * other expression so assignment won't work. Since initialization can't
 * reference the value being initialized, it can't have an internal pointer. We
 * therefore assume an initialized but unused once flag can be moved, so we
 * just memcpy() it.
 */
#ifndef ghost_has_ghost_once_init
    #include "ghost/thread/once/ghost_once_init_s.h"
    #if ghost_has_GHOST_ONCE_INIT
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/string/ghost_memcpy.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        void ghost_once_init(ghost_once_t* once) {
            ghost_once_t initializer = GHOST_ONCE_INIT;
            ghost_memcpy(once, &initializer, sizeof(*once));
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_once_init 1
    #endif
#endif

#ifndef ghost_has_ghost_once_init
    #define ghost_has_ghost_once_init 0
#endif

#endif
