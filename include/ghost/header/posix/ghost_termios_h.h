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

#ifndef GHOST_TERMIOS_H_H_INCLUDED
#define GHOST_TERMIOS_H_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @file
 *
 * Includes <termios.h> if possible, which contains POSIX terminal functions.
 *
 * Check `#if ghost_has(ghost_termios_h)` to see whether it was actually included.
 *
 *     https://man.archlinux.org/man/termios.h.0p
 */
#endif

/* Global header workarounds */
#include "ghost/impl/header/ghost_impl_headers.h"

/* If we can check whether <termios.h> exists, prefer that. */
#ifndef ghost_has_ghost_termios_h
    #include "ghost/preprocessor/ghost_has_include.h"
    #if ghost_has(ghost_has_include)
        #if __has_include(<termios.h>)
            #include <termios.h>
            #define ghost_has_ghost_termios_h 1
        #else
            #define ghost_has_ghost_termios_h 0
        #endif
    #endif
#endif

/* If we have <unistd.h>, assume we're a POSIX system. */
#ifndef ghost_has_ghost_termios_h
    #include "ghost/header/posix/ghost_unistd_h.h"
    #if ghost_has(ghost_unistd_h)
        #include <termios.h>
        #define ghost_has_ghost_termios_h 1
    #endif
#endif

/* Otherwise we make no assumptions. */
#ifndef ghost_has_ghost_termios_h
    #define ghost_has_ghost_termios_h 0
#endif

#endif
