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

#ifndef GHOST_SILENCE_MISSING_DECLARATIONS_H_INCLUDED
#define GHOST_SILENCE_MISSING_DECLARATIONS_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_MISSING_DECLARATIONS
 *
 * Silences warnings about functions and variables defined without a previous
 * declaration.
 *
 * @see GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS
 * @see GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_MISSING_DECLARATIONS
    #ifdef GHOST_SILENCE_MISSING_DECLARATIONS
        #define ghost_has_GHOST_SILENCE_MISSING_DECLARATIONS 1
    #endif
#endif

#ifndef ghost_has_GHOST_SILENCE_MISSING_DECLARATIONS
    #include "ghost/silence/ghost_silence_missing_function_declarations.h"
    #include "ghost/silence/ghost_silence_missing_variable_declarations.h"
    #define GHOST_SILENCE_MISSING_DECLARATIONS \
        GHOST_SILENCE_MISSING_FUNCTION_DECLARATIONS \
        GHOST_SILENCE_MISSING_VARIABLE_DECLARATIONS
    #define ghost_has_GHOST_SILENCE_MISSING_DECLARATIONS 1
#endif

#endif
