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

#ifndef GHOST_STRINGS_H_H_INCLUDED
#define GHOST_STRINGS_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes the POSIX <strings.h> header (not to be confused with <string.h>)
 * if it's available.
 *
 * <strings.h> declares a handful of miscellaneous functions. Many of the
 * functions that used to be declared in it by POSIX have become obsolete (like
 * bcmp().) POSIX only specifies a few functions in this file (like ffs()) but
 * many systems still support all the obsolete functions.
 *
 *     https://man.archlinux.org/man/strings.h.0p
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* Allow the user to override the include path */
#ifndef ghost_has_ghost_strings_h
    #ifdef GHOST_STRINGS_H
        #include GHOST_STRINGS_H
        #define ghost_has_ghost_strings_h 1
    #endif
#endif

/* Try to detect whether it's available */
#ifndef ghost_has_ghost_strings_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<strings.h>)
            #include <strings.h>
            #define ghost_has_ghost_strings_h 1
        #else
            #define ghost_has_ghost_strings_h 0
        #endif
    #endif
#endif

/* Defer platform detection to ghost_unistd_h.h. If we have <unistd.h>, we
 * assume we're on a POSIX system so it should also have <strings.h>. */
#ifndef ghost_has_ghost_strings_h
    #include "ghost/header/posix/ghost_unistd_h.h"
    #if ghost_has(ghost_unistd_h)
        #include <strings.h>
        #define ghost_has_ghost_strings_h 1
    #endif
#endif

/* Otherwise assume we don't have it. */
#ifndef ghost_has_ghost_strings_h
    #define ghost_has_ghost_strings_h 0
#endif

#endif
