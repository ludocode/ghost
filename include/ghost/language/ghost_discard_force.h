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

#ifndef GHOST_DISCARD_FORCE_H_INCLUDED
#define GHOST_DISCARD_FORCE_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_discard_force_force(...)
 *
 * Discards the result by force, silencing warnings even if a called function
 * is marked with compiler extensions stronger than [[nodiscard]].
 *
 * Under GCC, __attribute__((warn_unused_result_)) is stronger than
 * [[nodiscard]] and cannot be silenced by void casting. This does whatever is
 * necessary to silence it.
 *
 * @see ghost_discard_force
 */
#endif

#ifndef ghost_has_ghost_discard_force
    #ifdef ghost_discard_force
        #define ghost_has_ghost_discard_force 1
    #endif
#endif

/*
 * GCC warns even if an __attribute__((warn_unused_result)) expression is
 * explicitly cast to void. This is contrary to the recommendation for the C++
 * standard [[nodiscard]] attribute, so naturally GCC treats them differently.
 * The GCC developers are adamant that they want it to behave this way:
 *
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=25509
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66425
 *
 * The NVidia/PGI compiler emulates this GCC feature so it behaves the same
 * way. We discard even harder under these compilers.
 */
#ifndef ghost_has_ghost_discard_force
    #include "ghost/detect/ghost_gcc.h"
    #if GHOST_GCC || defined(__PGI)

        /* Silencing the warning with diagnostic push/pop doesn't work even in
         * a statement expression. We also can't use e.g. (void)!(x) because
         * that wouldn't work on structs. The below is the best I've got so
         * far. */

        #if defined(__cplusplus)
            /* In C++ we do this template wrapper. We take a const reference to
             * ensure that no copy constructors or assignment operators will
             * run. (Do we need an r-value reference overload?) */
            #include "ghost/impl/ghost_impl_function_wrapper.h"
            #include "ghost/language/ghost_always_inline.h"
            GHOST_IMPL_CXX_FUNCTION_OPEN
            template <typename ghost_T>
            ghost_always_inline
            void ghost_discard_force(const ghost_T&) {}
            GHOST_IMPL_CXX_FUNCTION_CLOSE
            #define ghost_has_ghost_discard_force 1

        #else
            /* In C we have to assign it to a variable to discard it. */
            #include "ghost/language/ghost_typeof.h"
            #if ghost_has_ghost_typeof
                #define ghost_discard_force(x) \
                    ( __extension__ ({ \
                        ghost_typeof(x) ghost_impl_v = (x); \
                        (void)ghost_impl_v; \
                    }))
                #define ghost_has_ghost_discard_force 1
            #endif
        #endif
    #endif
#endif

/* Otherwise we fallback to ghost_discard(). */
#ifndef ghost_has_ghost_discard_force
    #include "ghost/language/ghost_discard.h"
    #define ghost_discard_force(x) ghost_discard(x)
    #define ghost_has_ghost_discard_force 1
#endif

#endif
