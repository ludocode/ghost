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

#ifndef GHOST_HAS_H_INCLUDED
#define GHOST_HAS_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def ghost_has(identifier)
 *
 * Expands to 1 if Ghost has defined the given identifier or if Ghost or the
 * platform supports the given feature and 0 otherwise.
 *
 * The identifier may be a macro, a function, a type, a global variable, the
 * name of a header, or anything else.
 *
 * Examples:
 *
 *     #include "ghost/thread/ghost_mutex_t.h"
 *     #if ghost_has(ghost_mutex_t)
 *         // ghost_mutex_t is available
 *     #endif
 *
 *     #include "ghost/preprocessor/ghost_has_include.h"
 *     #if ghost_has(ghost_has_include)
 *         // __has_include is available (and works)
 *     #endif
 *
 *     #include "ghost/header/c/ghost_stdio_h.h"
 *     #if ghost_has(ghost_stdio_h)
 *         // <stdio.h> was included
 *     #endif
 */

/*
 * Ghost defines ghost_has_x to 1 for any identifier x that it defines.
 *
 * Using 1 and 0 instead of defined and undefined lets users of Ghost
 * pre-define ghost_has_x to 0 to disable any identifier x (for example if
 * Ghost's platform detection is incorrect and causes compiler errors.)
 */

#ifndef ghost_has_ghost_has
    #ifdef ghost_has
        #define ghost_has_ghost_has 1
    #endif
#endif

#ifndef ghost_has_ghost_has
    #define ghost_has(identifier) ghost_has_##identifier
    #define ghost_has_ghost_has 1
#endif

#endif
