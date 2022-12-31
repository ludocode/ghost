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

#ifndef GHOST_PRETTY_FUNCTION_OPT_H_INCLUDED
#define GHOST_PRETTY_FUNCTION_OPT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_PRETTY_FUNCTION_OPT
 *
 * Evaluates to a `const char*` string containing the name of the containing
 * function, ideally human-readable; or evaluates to null if the function name
 * cannot be determined.
 *
 * See GHOST_PRETTY_FUNCTION for more info.
 *
 * @see GHOST_PRETTY_FUNCTION
 */
#endif

#ifndef ghost_has_GHOST_PRETTY_FUNCTION_OPT
    #ifndef GHOST_PRETTY_FUNCTION_OPT
        #include "ghost/debug/ghost_pretty_function.h"
        #if ghost_has(GHOST_PRETTY_FUNCTION)
            #define GHOST_PRETTY_FUNCTION_OPT GHOST_PRETTY_FUNCTION
        #else
            #include "ghost/language/ghost_null.h"
            #define GHOST_PRETTY_FUNCTION_OPT ghost_null
        #endif
    #endif
    #define ghost_has_GHOST_PRETTY_FUNCTION_OPT 1
#endif

#endif
