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

#ifndef GHOST_INDEX_H_INCLUDED
#define GHOST_INDEX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches the given string, returning a pointer to the first instance of the
 * given character or ghost_null if not found.
 *
 * This is identical to strchr().
 */
char* ghost_index(const char* s, int c);
#endif

#ifndef ghost_has_ghost_index
    #ifdef ghost_index
        #define ghost_has_ghost_index 1
    #endif
#endif

#ifndef ghost_has_ghost_index
    /* The index() function is obsolete. It's identical to strchr(). */
    #include "ghost/string/ghost_strchr.h"
    #define ghost_index ghost_strchr
    #define ghost_has_ghost_index 1
#endif

#endif
