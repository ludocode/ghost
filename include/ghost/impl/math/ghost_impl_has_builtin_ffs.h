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

#ifndef GHOST_IMPL_HAS_BUILTIN_FFS_H_INCLUDED
#define GHOST_IMPL_HAS_BUILTIN_FFS_H_INCLUDED

#ifdef GHOST_IMPL_HAS_BUILTIN_FFS
    #error "You cannot pre-define GHOST_IMPL_ macros."
#endif

/* If __has_builtin() is available, use it. */
#ifndef GHOST_IMPL_HAS_BUILTIN_FFS
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_ffs)
            #define GHOST_IMPL_HAS_BUILTIN_FFS 1
        #endif
    #endif
#endif

/* Otherwise assume only that GCC has it. */
#ifndef GHOST_IMPL_HAS_BUILTIN_FFS
    #include "ghost/detect/ghost_gcc.h"
    #if GHOST_GCC
        #define GHOST_IMPL_HAS_BUILTIN_FFS 1
    #endif
#endif

#ifndef GHOST_IMPL_HAS_BUILTIN_FFS
    #define GHOST_IMPL_HAS_BUILTIN_FFS 0
#endif

#endif
