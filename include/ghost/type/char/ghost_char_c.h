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

#ifndef GHOST_CHAR_C_H_INCLUDED
#define GHOST_CHAR_C_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CHAR_C(x) x
 *
 * Defines a numerical preprocessor constant of a type convertible to char.
 */
#endif

#ifndef ghost_has_GHOST_CHAR_C
    #ifdef GHOST_CHAR_C
        #define ghost_has_GHOST_CHAR_C 1
    #endif
#endif

#ifndef ghost_has_GHOST_CHAR_C
    #include "ghost/type/char/ghost_char_is_signed.h"
    #if ghost_has_GHOST_CHAR_IS_SIGNED
        #if GHOST_CHAR_IS_SIGNED
            #define GHOST_CHAR_C(x) x
        #else
            #define GHOST_CHAR_C(x) x ## U
        #endif
    #else
        /* We don't know whether it's signed but we'll assume undecorated
         * literals will convert correctly. This could trigger conversion
         * warnings. It could in theory fail due to truncation on machines
         * where char and int are the same size and char is unsigned but this
         * seems pretty unlikely. */
        #define GHOST_CHAR_C(x) x
    #endif
    #define ghost_has_GHOST_CHAR_C 1
#endif

#endif
