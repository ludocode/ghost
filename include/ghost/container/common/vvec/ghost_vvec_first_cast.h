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

#ifndef GHOST_VVEC_FIRST_CAST_H_INCLUDED
#define GHOST_VVEC_FIRST_CAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_vvec_first_cast(vector, Type) (Type*)ghost_vvec_first(vector)
 *
 * Returns the first element in the vector, casting it to a pointer to the
 * given type.
 *
 * The vector must not be empty.
 *
 * This can be used to avoid implicit void pointer casting (for example if you
 * want your code to compile under -Wc++-compat.)
 */
#endif

#ifndef ghost_has_ghost_vvec_first_cast
    #ifdef ghost_vvec_first_cast
        #define ghost_has_ghost_vvec_first_cast 1
    #endif
#endif

#ifndef ghost_has_ghost_vvec_first_cast
    #include "ghost/container/common/vvec/ghost_vvec_first.h"
    #if !ghost_has(ghost_vvec_first)
        #define ghost_has_ghost_vvec_first_cast 0
    #endif
#endif

#ifndef ghost_has_ghost_vvec_first_cast
    #include "ghost/language/ghost_static_cast.h"
    #define ghost_vvec_first_cast(vector, Type) \
        ghost_static_cast(Type*, ghost_vvec_first(vector))
    #define ghost_has_ghost_vvec_first_cast 1
#endif

#endif
