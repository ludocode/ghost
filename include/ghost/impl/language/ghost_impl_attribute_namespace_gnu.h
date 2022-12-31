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

#ifndef GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU_H_INCLUDED
#define GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU_H_INCLUDED

/*
 * This is used for the gnu attribute namespace. The safe modern spelling is
 * `__gnu__`, e.g.:
 *
 *     [[__gnu__::__always_inline__]]
 *
 * Older compilers only supported `gnu`:
 *
 *     [[gnu::always_inline]]
 */

/* Clang didn't support __gnu__ until version 8. */
/* TODO this version check won't work on e.g. Apple Clang and other variants */
#ifndef GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU
    #if defined(__clang__)
        #if __clang_major__ < 8
            #define GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU gnu
        #else
            #define GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU __gnu__
        #endif
    #endif
#endif

/* GCC didn't support __gnu__ until also version 8. */
#ifndef GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU
    #include "ghost/detect/ghost_gcc.h"
    #if GHOST_GCC
        #if __GNUC__ < 8
            #define GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU gnu
        #else
            #define GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU __gnu__
        #endif
    #endif
#endif

/* We assume other GNUC compilers support __gnu__. */
#ifndef GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU
    #ifdef __GNUC__
        #define GHOST_IMPL_ATTRIBUTE_NAMESPACE_GNU __gnu__
    #endif
#endif

#endif
