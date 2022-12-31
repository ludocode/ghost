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

#ifndef GHOST_SYS_TYPES_H_H_INCLUDED
#define GHOST_SYS_TYPES_H_H_INCLUDED

#include "ghost/ghost_core.h"

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/*TODO*/

#ifndef ghost_has_ghost_sys_types_h
    #if !defined(_WIN32)
        #include <sys/types.h>
        #define ghost_has_ghost_sys_types_h 1
    #endif
#endif

#ifndef ghost_has_ghost_sys_types_h
    #define ghost_has_ghost_sys_types_h 0
#endif

#endif
