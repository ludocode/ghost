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

#ifndef GHOST_NORETURN_OPT_H_INCLUDED
#define GHOST_NORETURN_OPT_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_noreturn_opt [[noreturn]] or nothing
 *
 * The same as ghost_noreturn, except that if noreturn is not supported, this
 * instead expands to nothing.
 *
 * @see ghost_noreturn
 */
#endif

#ifndef ghost_has_ghost_noreturn_opt
    #ifndef ghost_noreturn_opt
        #include "ghost/language/ghost_noreturn.h"
        #if ghost_has(ghost_noreturn)
            #define ghost_noreturn_opt ghost_noreturn
        #else
            #define ghost_noreturn_opt /*nothing*/
        #endif
    #endif
    #define ghost_has_ghost_noreturn_opt 1
#endif

#endif
