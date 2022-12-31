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

#ifndef GHOST_IMPL_COSMOPOLITAN_H_INCLUDED
#define GHOST_IMPL_COSMOPOLITAN_H_INCLUDED

/*
 * This file implements workarounds for Cosmopolitan libc's amalgamation.
 *
 * When using the amalgamation, headers like <string.h> and <pthread.h> don't
 * exist. Instead the headers have been declared by the amalgamation which,
 * with the recommended build flags, has been force-included.
 *
 * Cosmopolitan allows us to detect it with __COSMOPOLITAN__. However, it
 * currently doesn't provide any way for us to detect whether it's amalgamated.
 * We assume that it is, and so we mark all of these headers as having been
 * already included.
 */

#ifdef __COSMOPOLITAN__

    /* C */
    #ifndef ghost_has_ghost_errno_h
        #define ghost_has_ghost_errno_h 1
    #endif
    #ifndef ghost_has_ghost_inttypes_h
        #define ghost_has_ghost_inttypes_h 1
    #endif
    #ifndef ghost_has_ghost_limits_h
        #define ghost_has_ghost_limits_h 1
    #endif
    #ifndef ghost_has_ghost_math_h
        #define ghost_has_ghost_math_h 1
    #endif
    #ifndef ghost_has_ghost_signal_h
        #define ghost_has_ghost_signal_h 1
    #endif
    #ifndef ghost_has_ghost_stdarg_h
        #define ghost_has_ghost_stdarg_h 1
    #endif
    #ifndef ghost_has_ghost_stdbool_h
        #define ghost_has_ghost_stdbool_h 1
    #endif
    #ifndef ghost_has_ghost_stddef_h
        #define ghost_has_ghost_stddef_h 1
    #endif
    #ifndef ghost_has_ghost_stdint_h
        #define ghost_has_ghost_stdint_h 1
    #endif
    #ifndef ghost_has_ghost_stdio_h
        #define ghost_has_ghost_stdio_h 1
    #endif
    #ifndef ghost_has_ghost_stdlib_h
        #define ghost_has_ghost_stdlib_h 1
    #endif
    #ifndef ghost_has_ghost_string_h
        #define ghost_has_ghost_string_h 1
    #endif
    #ifndef ghost_has_ghost_time_h
        #define ghost_has_ghost_time_h 1
    #endif

    /* POSIX */
    #ifndef ghost_has_ghost_pthread_h
        #define ghost_has_ghost_pthread_h 1
    #endif
    #ifndef ghost_has_ghost_strings_h
        #define ghost_has_ghost_strings_h 1
    #endif
    #ifndef ghost_has_ghost_sys_types_h
        #define ghost_has_ghost_sys_types_h 1
    #endif
    #ifndef ghost_has_ghost_unistd_h
        #define ghost_has_ghost_unistd_h 1
    #endif

#endif

#endif
