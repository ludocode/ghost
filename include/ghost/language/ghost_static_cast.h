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

#ifndef GHOST_STATIC_CAST_H_INCLUDED
#define GHOST_STATIC_CAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def ghost_static_cast(Type, value) (Type)(value)
 *
 * Casts value to Type. If the type is a different numerical width or format,
 * the value will be converted. In C++, if the cast can convert between base
 * and derived class pointers, the pointer will be shifted appropriately.
 *
 * @see ghost_cast
 * @see ghost_reinterpret_cast
 * @see ghost_const_cast
 */
#endif

#ifndef ghost_has_ghost_static_cast
    #ifdef ghost_static_cast
        #define ghost_has_ghost_static_cast 1
    #endif
#endif

#ifndef ghost_has_ghost_static_cast
    #ifdef __cplusplus
        #define ghost_static_cast(Type, value) (static_cast<Type>(value))
    #else
        #define ghost_static_cast(Type, value) ((Type)(value))
    #endif
    #define ghost_has_ghost_static_cast 1
#endif

#endif
