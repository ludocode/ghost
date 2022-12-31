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

#ifndef GHOST_BOOL_WIDTH_H_INCLUDED
#define GHOST_BOOL_WIDTH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_BOOL_WIDTH
 *
 * The width of ghost_bool in bits.
 */
#endif

#ifndef ghost_has_GHOST_BOOL_WIDTH
    #ifdef GHOST_BOOL_WIDTH
        #define ghost_has_GHOST_BOOL_WIDTH 1
    #endif
#endif

/* C23 adds BOOL_WIDTH to <limits.h>. It might be backported. */
#ifndef ghost_has_GHOST_BOOL_WIDTH
    #include "ghost/header/c/ghost_limits_h.h"
    #ifdef BOOL_WIDTH
        #define GHOST_BOOL_WIDTH BOOL_WIDTH
        #define ghost_has_GHOST_BOOL_WIDTH 1
    #endif
#endif

/* Clang supports __BOOL_WIDTH__ even in C89. */
#ifndef ghost_has_GHOST_BOOL_WIDTH
    #ifdef __BOOL_WIDTH__
        #define GHOST_BOOL_WIDTH BOOL_WIDTH
        #define ghost_has_GHOST_BOOL_WIDTH 1
    #endif
#endif

/* We're currently assuming that sizeof(bool)==1 on all platforms; see the note
 * in ghost_bool_type.h. We check this below with a static assert. */
#ifndef ghost_has_GHOST_BOOL_WIDTH
    #include "ghost/type/char/ghost_char_width.h"
    #define GHOST_BOOL_WIDTH GHOST_CHAR_WIDTH
    #define ghost_has_GHOST_BOOL_WIDTH 1
#endif

#if ghost_has_GHOST_BOOL_WIDTH
    #include "ghost/type/bool/ghost_bool.h"
    #include "ghost/debug/ghost_static_assert.h"
    ghost_static_assert(sizeof(ghost_bool) == 1, "Ghost assumes sizeof(ghost_bool)==1 but this appears to be incorrect. Please file a bug. In the meantime pre-define GHOST_BOOL_WIDTH to the correct size.");
#endif

#endif
