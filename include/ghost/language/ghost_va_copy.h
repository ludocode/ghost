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

#ifndef GHOST_VA_COPY_H_INCLUDED
#define GHOST_VA_COPY_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_va_copy va_copy
 *
 * Copies a variadic argument list.
 */
#endif

/* Always include <stdarg.h> so users can use the real va_copy() if it exists. */
#include "ghost/header/c/ghost_stdarg_h.h"

#ifndef ghost_has_ghost_va_copy
    #ifdef ghost_va_copy
        #define ghost_has_ghost_va_copy 1
    #endif
#endif

/* See if va_copy is a macro. If so use it. */
#ifndef ghost_has_ghost_va_copy
    #ifdef va_copy
        #define ghost_va_copy va_copy
        #define ghost_has_ghost_va_copy 1
    #endif
#endif

/* C has it in <stdarg.h> since C99. */
#ifndef ghost_has_ghost_va_copy
    #ifdef __STDC_VERSION__
        #if __STDC_VERSION__ >= 199901L
            #if ghost_has(ghost_stdarg_h)
                #define ghost_va_copy va_copy
                #define ghost_has_ghost_va_copy 1
            #endif
        #endif
    #endif
#endif

/* C++ has it since C++11. */
#ifndef ghost_has_ghost_va_copy
    #ifdef __cplusplus
        #if ghost_has(ghost_stdarg_h)
            #include "ghost/language/ghost_cplusplus.h"
            #if ghost_cplusplus >= 201103L
                #define ghost_va_copy va_copy
                #define ghost_has_ghost_va_copy 1
            #endif
        #endif
    #endif
#endif

/* GNU C compilers have a builtin. */
#ifndef ghost_has_ghost_va_copy
    #ifdef __GNUC__
        #define ghost_va_copy __builtin_va_copy
        #define ghost_has_ghost_va_copy 1
    #endif
#endif

/*
 * On some platforms we can just memcpy or assign it. We only do this where we
 * know it's safe.
 */

/* MSVC 2012 and earlier doesn't define va_copy() but we can assign it. */
#ifndef ghost_has_ghost_va_copy
    #ifdef _MSC_VER
        #include "ghost/language/ghost_discard.h"
        #define ghost_va_copy(dest, src) ghost_discard((dest) = (src))
        #define ghost_has_ghost_va_copy 1
    #endif
#endif

/* Otherwise we don't have it. */
#ifndef ghost_has_ghost_va_copy
    #define ghost_has_ghost_va_copy 0
#endif

#endif
