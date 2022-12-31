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

#ifndef GHOST_MIN_UH_H_INCLUDED
#define GHOST_MIN_UH_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Returns the lesser of the arguments.
 */
unsigned short ghost_min_uh(unsigned short left, unsigned short right);
#endif

#ifndef ghost_has_ghost_min_uh
    #ifdef ghost_min_uh
        #define ghost_has_ghost_min_uh 1
    #endif
#endif

#ifndef ghost_has_ghost_min_uh
    #include "ghost/type/ushort/ghost_ushort.h"
    #if ghost_has_ghost_ushort
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        unsigned short ghost_min_uh(unsigned short left, unsigned short right) {
            return ghost_static_cast(unsigned short, (left < right) ? left : right);
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_min_uh 1
    #endif
#endif

#ifndef ghost_has_ghost_min_uh
    #define ghost_has_ghost_min_uh 0
#endif

#endif
