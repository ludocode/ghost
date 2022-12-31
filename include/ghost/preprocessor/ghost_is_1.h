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

#ifndef GHOST_IS_1_H_INCLUDED
#define GHOST_IS_1_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_IS_1(text)
 *
 * Expands to 1 if the given text expands to 1, or 0 otherwise.
 *
 * This is the complement of GHOST_NOT() which checks whether a value is 0.
 */
/* TODO move this to experimental */

#ifndef ghost_has_GHOST_IS_1
    #ifdef GHOST_IS_1
        #define ghost_has_GHOST_IS_1 1
    #endif
#endif

/* TODO this isn't working under the MSVC traditional preprocessor yet.
 * TODO or is it? GHOST_NOT should be fixed now... */
#if 0
#ifndef ghost_has_GHOST_IS_1
    #include "ghost/preprocessor/ghost_msvc_traditional.h"
    #if GHOST_MSVC_TRADITIONAL
        #define ghost_has_GHOST_IS_1 0
    #endif
#endif
#endif

#ifndef ghost_has_GHOST_IS_1
    #include "ghost/preprocessor/ghost_not.h"
    #if ghost_has_GHOST_NOT
        #include "ghost/preprocessor/ghost_concat.h"
        #define GHOST_IS_1(text) \
                GHOST_NOT(GHOST_CONCAT(GHOST_IMPL_IS_1_, text))
        #define GHOST_IMPL_IS_1_1 0
        #define ghost_has_GHOST_IS_1 1
    #endif
#endif

#ifndef ghost_has_GHOST_IS_1
    #define ghost_has_GHOST_IS_1 0
#endif

#endif
