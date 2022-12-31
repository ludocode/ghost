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

/* TODO rename to ghost_debug.h, rename group header to ghost_debug.g.h or ghost_all_debug.h or something */
#ifndef GHOST_DEBUG_H_INCLUDED
#define GHOST_DEBUG_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_DEBUG
 *
 * Defined to 1 if debugging checks are enabled and 0 otherwise.
 *
 * This is used by Ghost to determine whether to enable runtime checks. For
 * example it enables ghost_assert(). You can also use it to enable checks in
 * your own code.
 *
 * You can define GHOST_DEBUG to 1 or 0 before including any Ghost headers to
 * declare whether you want debugging on. Otherwise, GHOST_DEBUG is detected
 * based on DEBUG and _DEBUG. These macros are defined by default in the debug
 * configuration of many projects (DEBUG by possibly CMake and Xcode, _DEBUG by
 * Visual Studio.) If either is defined, debugging is enabled; otherwise we
 * assume a release configuration.
 *
 * We ignore NDEBUG. NDEBUG was originally meant to be able to be undefined and
 * redefined several times throughout a translation unit to re-include
 * <assert.h> with different behaviour (and to this day <assert.h> does not
 * have an include guard for this reason.) Even though it isn't really used
 * this way anymore, it's safer to just stay far away from it. We assume
 * release anyway unless a debug macro is detected so there's no point in
 * detecting NDEBUG.
 */

#ifndef ghost_has_GHOST_DEBUG
    #ifdef GHOST_DEBUG
        #define ghost_has_GHOST_DEBUG 1
    #endif
#endif

#ifndef ghost_has_GHOST_DEBUG
    #if defined(DEBUG) || defined(_DEBUG)
        #define GHOST_DEBUG 1
    #else
        #define GHOST_DEBUG 0
    #endif
    #define ghost_has_GHOST_DEBUG 1
#endif

#endif
