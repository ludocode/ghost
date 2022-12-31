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

#ifndef GHOST_RINDEX_H_INCLUDED
#define GHOST_RINDEX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches the string in reverse order, returning a pointer to the last
 * instance of the given character or ghost_null if not found.
 *
 * This is identical to strrchr().
 */
char* ghost_rindex(const char* s, int c);
#endif

#ifndef ghost_has_ghost_rindex
    #ifdef ghost_rindex
        #define ghost_has_ghost_rindex 1
    #endif
#endif

#ifndef ghost_has_ghost_rindex
    /* The rindex() function is obsolete. It's identical to strrchr(). */
    #include "ghost/string/ghost_strrchr.h"
    #define ghost_rindex ghost_strrchr
    #define ghost_has_ghost_rindex 1
#endif

#endif
