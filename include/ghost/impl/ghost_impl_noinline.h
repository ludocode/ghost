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

#ifndef GHOST_IMPL_NOINLINE_H_INCLUDED
#define GHOST_IMPL_NOINLINE_H_INCLUDED

#include "ghost/impl/ghost_impl_function_wrapper.h"

#if GHOST_STATIC_DEFS
    #include "ghost/language/ghost_maybe_unused.h"
    #include "ghost/language/ghost_noinline.h"
    #define ghost_impl_noinline ghost_maybe_unused ghost_noinline static
#elif GHOST_MANUAL_DEFS
    #include "ghost/language/ghost_noinline.h"
    #define ghost_impl_noinline ghost_noinline
#else
    #include "ghost/language/ghost_header_noinline.h"
    #define ghost_impl_noinline ghost_header_noinline
#endif

#endif
