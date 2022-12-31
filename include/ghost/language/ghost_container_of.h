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

#ifndef GHOST_CONTAINER_OF_H_INCLUDED
#define GHOST_CONTAINER_OF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_container_of(pointer, container_type, member_name)
 *
 * Gets a pointer to the containing struct of the given member pointer, where
 * the container has the given type and the member has the given name.
 *
 * For example:
 *
 *     typedef struct {
 *         float a;
 *         int b;
 *     } foo_t;
 *
 *     foo_t foo;
 *     int* b_p = &foo.b;
 *
 *     foo_t* foo_p = ghost_container_of(b_p, foo_t, b);
 *     ghost_assert(foo_p == &foo);
 *
 * @warning If the given pointer is null, the behaviour is undefined! If your
 *          pointer might be null you must do a null check before using this.
 */
#endif

#ifndef ghost_has_ghost_container_of
    #ifdef ghost_container_of
        #define ghost_has_ghost_container_of 1
    #endif
#endif

#ifndef ghost_has_ghost_container_of
    #include "ghost/language/ghost_offsetof.h"
    #include "ghost/language/ghost_reinterpret_cast.h"
    #define ghost_container_of(pointer, structure, member) \
            (ghost_reinterpret_cast(structure*, \
                (ghost_reinterpret_cast(char*, pointer) - ghost_offsetof(structure, member))))
    #define ghost_has_ghost_container_of 1
#endif

#endif
