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

#ifndef GHOST_VSSCANF_H_INCLUDED
#define GHOST_VSSCANF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
int ghost_vsscanf(char* str, const char* restrict format, va_list args);
#endif

#ifndef ghost_has_ghost_vsscanf
    #ifdef ghost_vsscanf
        #define ghost_has_ghost_vsscanf 1
    #endif
#endif

/*
 * Under MSVC 2012 and earlier there is no vsscanf().
 *
 * It's possible to make this wrap sscanf() in various ways but Ghost does not
 * do this yet. It might be worth doing if we have more platforms that have
 * sscanf() but not vsscanf() and if we can do it at least semi-portably.
 */
#ifndef ghost_has_ghost_vsscanf
    #ifdef _MSC_VER
        #if _MSC_VER < 1800
            #define ghost_has_ghost_vsscanf 0
        #endif
    #endif
#endif

/* MSVC 2013 and newer has vsscanf() but it's only allowed if
 * _CRT_SECURE_NO_WARNINGS is defined. We wrap it to silence the warning. */
#ifndef ghost_has_ghost_vsscanf
    #ifdef _MSC_VER
        #if _MSC_VER >= 1800
            #include "ghost/header/c/ghost_stdio_h.h"
            #include "ghost/language/ghost_restrict.h"
            #include "ghost/impl/ghost_impl_always_inline.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            int ghost_vsscanf(
                    const char* ghost_impl_v_buffer,
                    const char* ghost_impl_v_format,
                    va_list ghost_impl_v_args)
            #if !GHOST_EMIT_DEFS
            ;
            #else
            {
                #pragma warning(push)
                #pragma warning(disable:4996)
                /* https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/vsscanf-vswscanf */
                return vsscanf(ghost_impl_v_buffer, ghost_impl_v_format, ghost_impl_v_args);
                #pragma warning(pop)
            }
            #endif
            GHOST_IMPL_FUNCTION_CLOSE
            #define ghost_has_ghost_vsscanf 1
        #endif
    #endif
#endif

/*
 * vsscanf() is in <stdio.h> as of C99.
 *     https://en.cppreference.com/w/c/io/fscanf
 * For now we assume it's backported to older language standards.
 */
#ifndef ghost_has_ghost_vsscanf
    #include "ghost/header/c/ghost_stdio_h.h"
    #if ghost_has(ghost_stdio_h)
        #define ghost_vsscanf vsscanf
        #define ghost_has_ghost_vsscanf 1
    #endif
#endif

/* Otherwise we don't have this. */
#ifndef ghost_has_ghost_vsscanf
    #define ghost_has_ghost_vsscanf 0
#endif

#endif
