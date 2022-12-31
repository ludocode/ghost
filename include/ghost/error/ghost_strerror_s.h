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

#ifndef GHOST_STRERROR_S_H_INCLUDED
#define GHOST_STRERROR_S_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Writes a human-readable description of the given error in the current locale
 * into the given buffer.
 *
 * This should be the same string returned from strerror() or printed by
 * perror() (although it may differ on some platforms.)
 *
 * This matches the Windows and C11 Annex K strerror_s() function. For the
 */
int ghost_strerror_s(char* buffer, size_t buffer_size, int error);
#endif

/* this is basically only on windows, it might be simpler if we make it wrap
 * ghost_strerror_r() (or maybe we do that on all non-windows.) */

/* https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s
 * TODO */

#ifndef ghost_has_ghost_strerror_s
    #ifdef ghost_strerror_s
        #define ghost_has_ghost_strerror_s 1
    #endif
#endif

/* Windows has this function.
 *     https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s */
#ifndef ghost_has_ghost_strerror_s
    #ifdef _WIN32
        /*TODO*/
    #endif
#endif

/* C11 Annex K has this but detecting it is not reliable. We ignore it. */

/* Otherwise wrap strerror_r(). */
#ifndef ghost_has_ghost_strerror_s
    #include "ghost/error/ghost_strerror_r.h"
    /* TODO */
#endif

#ifndef ghost_has_ghost_strerror_s
    #define ghost_has_ghost_strerror_s 0
#endif

#endif
