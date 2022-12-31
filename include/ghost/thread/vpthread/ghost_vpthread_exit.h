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

#ifndef GHOST_VPTHREAD_EXIT_H_INCLUDED
#define GHOST_VPTHREAD_EXIT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Exits the current Ghost thread returning void*.
 *
 * You should prefer to return from the thread start function instead of using
 * this.
 *
 * @warning This can only be used on threads created by Ghost and only on
 *          threads that were created with the matching return type. Ghost does
 *          not check this. Using this on other threads or with the wrong
 *          return type is undefined behaviour and can lead to crashes and
 *          memory leaks.
 *
 * @warning On most platforms, this is effectively a longjmp() out of the
 *          thread. No user cleanup code is executed which can lead to resource
 *          leaks or worse. In particular, no C++ destructors are called for
 *          objects on the stack. Some platforms may in fact perform stack
 *          unwinding so this is not portable.
 *
 * @see ghost_ithread_exit()
 * @see ghost_vthread_exit()
 */
[[noreturn]] void ghost_vpthread_exit(void* return_value);
#endif

/* Override is handled in the ex wrapper */
#include "ghost/impl/thread/ghost_impl_ex_vpthread_exit.h"

/* A thread type is required */
#ifndef ghost_has_ghost_vpthread_exit
    #include "ghost/thread/vpthread/ghost_vpthread_t.h"
    #if !ghost_has(ghost_vpthread_t)
        #define ghost_has_ghost_vpthread_exit 0
    #endif
#endif

/* If we have a real thread type returning void*, use it */
#ifndef ghost_has_ghost_vpthread_exit
    #if ghost_has_ghost_impl_ex_vpthread_exit
        #define ghost_vpthread_exit ghost_impl_ex_vpthread_exit
        #define ghost_has_ghost_vpthread_exit 1
    #endif
#endif

/* Synthesize it from a thread returning int. */
#ifndef ghost_has_ghost_vpthread_exit
    #include "ghost/impl/thread/ghost_impl_ex_ithread_exit.h"
    #if ghost_has_ghost_impl_ex_ithread_exit
        #include "ghost/language/ghost_noreturn_opt.h"
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_bit_cast.h"
        #include "ghost/language/ghost_static_cast.h"
        #include "ghost/type/intptr_t/ghost_intptr_t.h"
        #include "ghost/type/int/ghost_int_width.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_noreturn_opt
        ghost_impl_inline
        void ghost_vpthread_exit(void* ghost_v_ret) {
            #if GHOST_INT_WIDTH >= GHOST_INTPTR_WIDTH
                /* We're not using auxiliary storage. The return value can be
                 * cast directly. */
                ghost_impl_ex_ithread_exit(ghost_static_cast(int,
                            ghost_bit_cast(ghost_intptr_t, void*, ghost_v_ret)));
            #else
                /* We need to place the return value in auxiliary storage. */
                ghost_impl_thread_aux_exit(ghost_v_ret);
                ghost_impl_ex_ithread_exit(0);
            #endif
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_vpthread_exit 1
    #endif
#endif

#ifndef ghost_has_ghost_vpthread_exit
    #define ghost_has_ghost_vpthread_exit 0
#endif

#endif
