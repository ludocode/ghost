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

#ifndef GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS_H_INCLUDED
#define GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS
 *
 * Silences warnings about variables defined without a previous declaration.
 *
 * A valid reason to silence this warning is to define non-inline selectany or
 * weak variables in header-only libraries. Clang in particular warns even when
 * defining a selectany variable in a header file.
 *
 * @see GHOST_SILENCE_MISSING_DECLARATIONS
 * @see GHOST_SILENCE_MISSING_FUCNTION_DECLARATIONS
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS
    #ifdef GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS
        #define ghost_has_GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS 1
    #endif
#endif

/* Clang has -Wmissing-variable-declarations. GCC has no equivalent. */
#ifndef ghost_has_GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS
    #if defined(__clang__)
        #define GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS \
                _Pragma("GCC diagnostic ignored \"-Wmissing-variable-declarations\"")
        #define ghost_has_GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS
    #define GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS /*nothing*/
    #define ghost_has_GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS 1
#endif

#endif
