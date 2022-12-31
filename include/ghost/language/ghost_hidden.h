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

#ifndef GHOST_HIDDEN_H_INCLUDED
#define GHOST_HIDDEN_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_hidden
 *
 * Declares a function as being hidden from the dynamic linker.
 *
 * This is the default on Windows. On UNIX systems it is recommended to build
 * with `-fvisibility=hidden` to make this the default. You can use this if you
 * want specific symbols hidden regardless of the compiler's visibility
 * setting.
 *
 * Compiler warnings are issued if a static function is annotated ghost_hidden.
 * If you're not sure whether your function will be static (for example if
 * you're using `ghost_header_*` attributes), using GHOST_HIDDEN_PUSH and
 * GHOST_HIDDEN_POP instead.
 *
 * @see GHOST_HIDDEN_PUSH
 * @see GHOST_HIDDEN_POP
 * @see ghost_dllimport
 * @see ghost_dllexport
 */
#endif

#ifndef ghost_has_ghost_hidden
    #ifdef ghost_hidden
        #define ghost_has_ghost_hidden 1
    #endif
#endif

#ifndef ghost_has_ghost_hidden
    #if defined(__GNUC__)
        #define ghost_hidden __attribute__((__visibility__("hidden")))
    #else
        #define ghost_hidden /*nothing*/
    #endif
    #define ghost_has_ghost_hidden 1
#endif

#endif
