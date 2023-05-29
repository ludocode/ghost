/*
 * MIT No Attribution
 *
 * Copyright (c) 2022-2023 Fraser Heavy Software
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

#ifndef GHOST_IMPL_SSET_ELEMENT_NEW_H_INCLUDED
#define GHOST_IMPL_SSET_ELEMENT_NEW_H_INCLUDED

#include "ghost/container/common/sset/ghost_sset_t.h"

#if ghost_has(ghost_sset_t)
    #include "ghost/impl/container/common/sset/ghost_impl_sset_element_t.h"
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/string/ghost_memcpy.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/language/ghost_struct_hack_sizeof.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    ghost_impl_sset_element_t* ghost_impl_sset_element_new(const char* ghost_impl_v_string,
            size_t ghost_impl_v_length) GHOST_IMPL_DEF(
    {
        /* string is stored after the end of the struct as a "manual struct hack". */
        /* TODO undo this, this is supposed to be ghost_struct_hack_sizeof() */
        ghost_impl_sset_element_t* element = ghost_static_cast(ghost_impl_sset_element_t*,
                ghost_malloc(sizeof(ghost_impl_sset_element_t) + ghost_impl_v_length + 1));
        ghost_ensure(element != ghost_null, "malloc() failed allocating string set element");

        /* TODO use ghost_struct_hack_access() */
        element->length = ghost_impl_v_length;
        ghost_memcpy(element->cstring, ghost_impl_v_string, ghost_impl_v_length);
        element->cstring[element->length] = '\000';

        return element;
    })
    GHOST_IMPL_FUNCTION_CLOSE
#endif

#endif
