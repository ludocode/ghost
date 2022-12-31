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

#ifndef GHOST_HOSTED_H_INCLUDED
#define GHOST_HOSTED_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_HOSTED
 *
 * Defined to 1 if the implementation is hosted (i.e. has the standard
 * library) or 0 if the implementation is freestanding.
 *
 * This is always defined. If Ghost cannot determine whether the implementation
 * is hosted, it will assume it is hosted. We should add explicit detection of
 * all freestanding platforms that can't be detected by other means. In the
 * meantime, if Ghost isn't properly detecting your freestanding platform, you
 * can add -DGHOST_HOSTED=0 to your command-line.
 */
#endif

#ifndef ghost_has_GHOST_HOSTED
    #ifdef GHOST_HOSTED
        #define ghost_has_GHOST_HOSTED 1
    #endif
#endif

/* For some reason under Digital Mars __STDC_HOSTED__ is 0. */
#ifndef ghost_has_GHOST_HOSTED
    #ifdef __DMC__
        #define GHOST_HOSTED 1
        #define ghost_has_GHOST_HOSTED 1
    #endif
#endif

/* If the compiler tells us directly, use it. */
#ifndef ghost_has_GHOST_HOSTED
    #ifdef __STDC_HOSTED__
        #if __STDC_HOSTED__
            #define GHOST_HOSTED 1
        #else
            #define GHOST_HOSTED 0
        #endif
        #define ghost_has_GHOST_HOSTED 1
    #endif
#endif

/* Esoteric freestanding platforms that don't define __STDC_HOSTED__ can be
 * checked here. */

/* Guess based on whether we have <stdio.h>. This header is technically allowed
 * to exist in freestanding so this isn't a great test. If you're freestanding,
 * yet <stdio.h> exists and __STDC_HOSTED__ is not defined, you have a rather
 * confusing environment. In this case you should define either GHOST_HOSTED or
 * __STDC_HOSTED__ to 0 explicitly. */
#ifndef ghost_has_GHOST_HOSTED
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<stdio.h>)
            #define GHOST_HOSTED 1
        #else
            #define GHOST_HOSTED 0
        #endif
        #define ghost_has_GHOST_HOSTED 1
    #endif
#endif

/* Assume we're hosted. */
#ifndef ghost_has_GHOST_HOSTED
    #define GHOST_HOSTED 1
    #define ghost_has_GHOST_HOSTED 1
#endif

#endif
