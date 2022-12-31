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

#ifndef GHOST_ABORT_H_INCLUDED
#define GHOST_ABORT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_abort() abort()
 *
 * Aborts the program.
 *
 * This immediately stops execution. It does not attempt to report any reason
 * for the error or its source location and it does not flush any streams or
 * open files. It simply stops as soon as possible.
 *
 * If you want to abort due to a fatal error, consider calling ghost_fatal()
 * instead, or check for error conditions with ghost_ensure(). These call
 * Ghost's fatal error handler ghost_assert_fail() which ultimately calls this,
 * but there are many advantages to the fatal error handler:
 *
 * - ghost_fatal() accepts an optional message describing the failure;
 * - ghost_ensure() additionally performs a check and includes the condition as part of the error message;
 * - ghost_assert_fail() can be overridden to customize fatal error handling (for example to log fatal errors);
 * - ghost_assert_fail() contains details of the failure (including source location), by default printing to stderr;
 * - ghost_assert_fail() by default attempts to cause a debugger to break;
 * - ghost_assert_fail() provides better error messages from debugging tools like Valgrind and Address Sanitizer
 *
 * @see ghost_fatal()
 */
#endif

#ifndef ghost_has_ghost_abort
    #ifdef ghost_abort
        #define ghost_has_ghost_abort 1
    #endif
#endif

/* On hosted platforms, use abort(). */
#ifndef ghost_has_ghost_abort
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        #include "ghost/header/c/ghost_stdlib_h.h"
        #if ghost_has(ghost_stdlib_h)
            #ifdef __cplusplus
                #define ghost_abort() ::abort()
            #else
                #define ghost_abort() abort()
            #endif
            #define ghost_has_ghost_abort 1
        #endif
    #endif
#endif

/* Use __builtin_trap(). */
#ifndef ghost_has_ghost_abort
    /* GCC has supported __builtin_trap long before it supported __has_builtin.
     * If we have __has_builtin we'll check but we otherwise assume it's
     * available. */
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_trap)
            #define ghost_abort __builtin_trap
            #define ghost_has_ghost_abort 1
        #endif
    #else
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #define ghost_abort __builtin_trap
            #define ghost_has_ghost_abort 1
        #endif
    #endif
#endif

/*
 * Without any of the above, we don't have a way to abort so we don't define
 * ghost_abort().
 *
 * If you're on a microcontroller you could in theory define ghost_abort() to
 * an infinite loop, e.g. `for(;;){}`. This is how some ancient
 * microcontrollers used to be halted. We could consider making ghost_abort()
 * do that automatically on some microcontroller architectures. Alternatively,
 * if there are specific instructions that can cause a CPU to halt, we could do
 * some inline assembly.
 */
#ifndef ghost_has_ghost_abort
    #define ghost_has_ghost_abort 0
#endif

#endif
