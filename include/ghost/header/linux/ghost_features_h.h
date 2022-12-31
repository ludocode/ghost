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

#ifndef GHOST_FEATURES_H_H_INCLUDED
#define GHOST_FEATURES_H_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes a header containing feature-detection macros from the standard
 * library, usually called <features.h>.
 *
 * This is a special header that is implemented by most (but not all) Linux
 * libcs.
 */

/* Allow the user to override the include path */
#ifndef ghost_has_ghost_features_h
    #ifdef GHOST_FEATURES_H
        #include GHOST_FEATURES_H
        #define ghost_has_ghost_features_h 1
    #endif
#endif

/* Include <features.h> if we can detect directly that it exists. */
#ifndef ghost_has_ghost_features_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<features.h>)
            #include <features.h>
            #define ghost_has_ghost_features_h 1
        #else
            #define ghost_has_ghost_features_h 0
        #endif
    #endif
#endif

/* Non-Linux platforms don't typically have <features.h>. */
#ifndef ghost_has_ghost_features_h
    #ifndef __linux__
        #define ghost_has_ghost_features_h 0
    #endif
#endif

/* See if we can include it based on the libc.
 * TODO we need to combine this with ghost_libc, see ghost_libc.h for details */
#ifndef ghost_has_ghost_features_h
    #include "ghost/detect/ghost_libc.h"
    #include "ghost/header/c/ghost_string_h.h"
    #if !ghost_has(ghost_string_h)
        /* If we fail to include <string.h>, assume we won't have <features.h>
         * either. */
        #define ghost_has_ghost_features_h 0
    #endif
#endif

/* Most Linux libcs provide <features.h> but not all, e.g. Newlib doesn't
 * appear to. We try to list all the libcs we know have it. */
#ifndef ghost_has_ghost_features_h
    #include "ghost/detect/ghost_musl.h"
    #if defined(__GLIBC__) || defined(__UCLIBC__) || GHOST_MUSL || \
            defined(__BIONIC__) || defined(__dietlibc__)
        #include <features.h>
        #define ghost_has_ghost_features_h 1
    #endif
#endif

#ifndef ghost_has_ghost_features_h
    #define ghost_has_ghost_features_h 0
#endif

#endif
