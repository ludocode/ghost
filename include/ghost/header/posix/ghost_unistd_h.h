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

#ifndef GHOST_UNISTD_H_H_INCLUDED
#define GHOST_UNISTD_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes <unistd.h> if possible, which declares basic POSIX functions and
 * macros.
 *
 * Check `#if ghost_has(ghost_unistd_h)` to see whether it was actually included.
 *
 *     https://en.wikipedia.org/wiki/Unistd.h
 *     https://man.archlinux.org/man/unistd.h.0p
 *
 * Internally, Ghost tends to use this to detect POSIX support rather than
 * checking _POSIX_VERSION. The latter macro is not always defined unless the
 * user requested it with e.g. _POSIX_C_SOURCE.
 */

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* Allow the user to override the include path */
#ifndef ghost_has_ghost_unistd_h
    #ifdef GHOST_UNISTD_H
        #include GHOST_UNISTD_H
        #define ghost_has_ghost_unistd_h 1
    #endif
#endif

/* If we can check whether <unistd.h> exists, prefer that. */
#ifndef ghost_has_ghost_unistd_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<unistd.h>)
            #include <unistd.h>
            #define ghost_has_ghost_unistd_h 1
        #else
            #define ghost_has_ghost_unistd_h 0
        #endif
    #endif
#endif

/* <unistd.h> is required by the Single Unix Specification. If this is a
 * UNIX-like system, assume it exists. */
#ifndef ghost_has_ghost_unistd_h
    #include "ghost/detect/ghost_unix.h"
    #if GHOST_UNIX
        #include <unistd.h>
        #define ghost_has_ghost_unistd_h 1
    #endif
#endif

/*
 * If a relevant feature test macro is defined, we'll include it. We try to
 * include a libc header first in case the libc wants to translate a macro like
 * _GNU_SOURCE into _POSIX_C_SOURCE.
 *
 * We're assuming that a user or compiler would only request POSIX on a system
 * that is actually POSIX. This may or may not turn out to be a safe
 * assumption.
 *
 *     https://man.archlinux.org/man/core/man-pages/feature_test_macros.7.en
 */
#ifndef ghost_has_ghost_unistd_h
    #include "ghost/header/c/ghost_string_h.h"
    #if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE)
        #include <unistd.h>
        #define ghost_has_ghost_unistd_h 1
    #endif
#endif

/* Otherwise we make no assumptions. */
#ifndef ghost_has_ghost_unistd_h
    #define ghost_has_ghost_unistd_h 0
#endif

#endif
