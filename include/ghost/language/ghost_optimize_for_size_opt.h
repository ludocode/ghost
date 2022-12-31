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

#ifndef GHOST_OPTIMIZE_FOR_SIZE_OPT_H_INCLUDED
#define GHOST_OPTIMIZE_FOR_SIZE_OPT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_OPTIMIZE_FOR_SIZE_OPT
 *
 * Expands to 1 if the compiler is optimizing for size (e.g. with a `-Os`
 * command-line option) or 0 if it might not be.
 *
 * This detects -Os with GCC/Clang. Unfortunately there doesn't seem to be a
 * macro defined for /Os under MSVC.
 *
 * If Ghost can't determine whether the compiler is optimizing for size, this
 * is 0. Use GHOST_OPTIMIZE_FOR_SIZE instead if you want to be sure whether the
 * compiler is optimizing for size.
 *
 * @see GHOST_OPTIMIZE_FOR_SIZE
 */
#endif

#ifndef ghost_has_GHOST_OPTIMIZE_FOR_SIZE_OPT
    #ifndef GHOST_OPTIMIZE_FOR_SIZE_OPT
        #include "ghost/language/ghost_optimize_for_size.h"
        #if ghost_has(GHOST_OPTIMIZE_FOR_SIZE)
            #define GHOST_OPTIMIZE_FOR_SIZE_OPT GHOST_OPTIMIZE_FOR_SIZE
        #else
            /* We can't tell; assume it's off. */
            #define GHOST_OPTIMIZE_FOR_SIZE_OPT 0
        #endif
    #endif
    #define ghost_has_GHOST_OPTIMIZE_FOR_SIZE_OPT 1
#endif

#endif
