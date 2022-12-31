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

#ifndef GHOST_IMPL_ALWAYS_INLINE_H_INCLUDED
#define GHOST_IMPL_ALWAYS_INLINE_H_INCLUDED

#include "ghost/impl/ghost_impl_function_wrapper.h"

#if GHOST_STATIC_DEFS
    #include "ghost/language/ghost_always_inline.h"
    #if ghost_has_ghost_always_inline
        #define ghost_impl_always_inline ghost_always_inline static
    #else
        #define ghost_impl_always_inline static
    #endif
#elif GHOST_MANUAL_DEFS
    #if GHOST_EMIT_DEFS
        #include "ghost/language/ghost_emit_always_inline.h"
        #define ghost_impl_always_inline ghost_emit_always_inline
    #else
        #include "ghost/language/ghost_noemit_always_inline.h"
        #define ghost_impl_always_inline ghost_noemit_always_inline
    #endif
#else
    #include "ghost/language/ghost_header_always_inline.h"
    #define ghost_impl_always_inline ghost_header_always_inline
#endif

#endif
