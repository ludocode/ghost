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

#ifndef GHOST_REINTERPRET_CAST_H_INCLUDED
#define GHOST_REINTERPRET_CAST_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/*
 * @def ghost_reinterpret_cast(Type, value) (Type)(value)
 *
 * Casts value to Type even if the types are incompatible.
 *
 * This won't necessarily compile, for example if the types are different
 * sizes. If it does compile though, it will generally do so without warnings.
 * If you want to cast away a `const` modifier you should use
 * `ghost_const_cast()` instead.
 *
 * For converting types bitwise, you probably want ghost_bit_cast() instead.
 *
 * @see ghost_static_cast
 * @see ghost_const_cast
 * @see ghost_bit_cast
 */
#endif

/* TODO explain how some casts that are valid in C++ may cause warnings in C,
 * example void* to function pointer with dlsym(). Recommend ghost_bit_cast()
 * for those instead. Or maybe we need to do something else to silence those
 * warnings in C. */

#ifndef ghost_has_ghost_reinterpret_cast
    #ifdef __cplusplus
        #define ghost_reinterpret_cast(Type, value) (reinterpret_cast<Type>(value))
    #else
        #define ghost_reinterpret_cast(Type, value) ((Type)(value))
    #endif
    #define ghost_has_ghost_reinterpret_cast 1
#endif

#endif
