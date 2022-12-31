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

#ifndef GHOST_STRERROR_H_INCLUDED
#define GHOST_STRERROR_H_INCLUDED

#include "ghost/ghost_core.h"

#ifndef ghost_has_ghost_strerror
    #ifdef ghost_strerror
        #define ghost_has_ghost_strerror 1
    #endif
#endif

#ifndef ghost_has_ghost_strerror
    #include "ghost/language/ghost_hosted.h"
    #if GHOST_HOSTED
        /* TODO */
    #endif
#endif

/* https://en.cppreference.com/w/c/string/byte/strerror */

#ifndef ghost_has_ghost_strerror
    #define ghost_has_ghost_strerror 0
#endif

#endif
