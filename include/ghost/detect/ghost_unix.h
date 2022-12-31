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

#ifndef GHOST_UNIX_H_INCLUDED
#define GHOST_UNIX_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_UNIX
 *
 * Defined to 1 if this is a UNIX or UNIX-like system and 0 otherwise.
 */
#endif

#ifndef ghost_has_GHOST_UNIX
    #ifdef GHOST_UNIX
        #define ghost_has_GHOST_UNIX 1
    #endif
#endif

/*
 * __unix__ is defined on most UNIX-like systems including Linux, the BSDs and
 * Cygwin. It may not be defined in proprietary UNIX systems that have their
 * own compilers though (macOS, HP-UX and Solaris) so we check those
 * separately.
 *
 *     http://web.archive.org/web/20160306052035/http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
 */
#ifndef ghost_has_GHOST_UNIX
    #if defined(__unix__) || defined (__unix) || \
            (defined(__APPLE__) && defined(__MACH__)) || \
            defined(__hpux) || \
            (defined(__sun) && defined(__SVR4))
        #define GHOST_UNIX 1
    #else
        #define GHOST_UNIX 0
    #endif
    #define ghost_has_GHOST_UNIX 1
#endif

#endif
