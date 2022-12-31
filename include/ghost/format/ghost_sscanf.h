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

#ifndef GHOST_SSCANF_H_INCLUDED
#define GHOST_SSCANF_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 */
int ghost_sscanf(char* str, const char* restrict format, ...);
#endif

#ifndef ghost_has_ghost_sscanf
    #ifdef ghost_sscanf
        #define ghost_has_ghost_sscanf 1
    #endif
#endif

/*
 * sscanf() is in <stdio.h> in ANSI C.
 *
 *     https://en.cppreference.com/w/c/io/fscanf
 *
 * We avoid using this under MSVC because it throws a deprecation warning.
 * Instead we wrap vsscanf() below which will silence it.
 */
#ifndef ghost_has_ghost_sscanf
    #ifndef _MSC_VER
        #include "ghost/header/c/ghost_stdio_h.h"
        #if ghost_has(ghost_stdio_h)
            #define ghost_sscanf sscanf
            #define ghost_has_ghost_sscanf 1
        #endif
    #endif
#endif

/* Wrap vsscanf() if we have it. */
#ifndef ghost_has_ghost_sscanf
    #include "ghost/format/ghost_vsscanf.h"
    #if ghost_has(ghost_vsscanf)
        #include "ghost/impl/ghost_impl_inline.h"
        #include "ghost/header/c/ghost_stdarg_h.h"
        #include "ghost/language/ghost_restrict.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_inline
        int ghost_sscanf(
                const char* ghost_impl_v_buffer,
                const char* ghost_impl_v_format,
                ...) GHOST_IMPL_DEF(
        {
            va_list ghost_impl_v_args;
            int ghost_impl_v_ret;
            va_start(ghost_impl_v_args, ghost_impl_v_format);
            ghost_impl_v_ret = ghost_vsscanf(ghost_impl_v_buffer, ghost_impl_v_format, ghost_impl_v_args);
            va_end(ghost_impl_v_args);
            return ghost_impl_v_ret;
        })
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_sscanf 1
    #endif
#endif

/* Otherwise we don't have this. */
#ifndef ghost_has_ghost_sscanf
    #define ghost_has_ghost_sscanf 0
#endif

#endif
