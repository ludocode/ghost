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

#ifndef GHOST_MSVC_TRADITIONAL_H_INCLUDED
#define GHOST_MSVC_TRADITIONAL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_MSVC_TRADITIONAL
 *
 * Expands to 1 if compiling under MSVC with the traditional preprocessor or 0
 * otherwise.
 *
 * This is 0 on any compiler other than MSVC, and 0 under MSVC with the new
 * /Zc:preprocessor switch (which will hopefully at some point become the
 * default.)
 *
 * The traditional MSVC preprocessor has many non-conforming behaviours.
 * Several are listed in this link:
 *
 *     https://web.archive.org/web/20190227232400/https://devblogs.microsoft.com/cppblog/msvc-preprocessor-progress-towards-conformance/
 *
 * Behaviour 5, __VA_ARGS__ forwarding, is a particular problem for Ghost (and
 * related libraries like Mirror.) You will occasionally see extra
 * GHOST_EXPAND() under the MSVC traditional preprocessor in order to force
 * __VA_ARGS__ to be expanded properly.
 *
 * Here are some links detailing the new conforming preprocessor:
 *
 *     https://devblogs.microsoft.com/cppblog/announcing-full-support-for-a-c-c-conformant-preprocessor-in-msvc/
 *     https://docs.microsoft.com/en-us/cpp/preprocessor/preprocessor-experimental-overview
 */
#endif

#ifndef ghost_has_GHOST_MSVC_TRADITIONAL
    #ifdef GHOST_MSVC_TRADITIONAL
        #define ghost_has_GHOST_MSVC_TRADITIONAL 1
    #endif
#endif

#ifndef ghost_has_GHOST_MSVC_TRADITIONAL
    #ifdef _MSC_VER
        #ifdef _MSVC_TRADITIONAL
            #if _MSVC_TRADITIONAL
                #define GHOST_MSVC_TRADITIONAL 1
            #else
                #define GHOST_MSVC_TRADITIONAL 0
            #endif
        #else
            #define GHOST_MSVC_TRADITIONAL 1
        #endif
        #define ghost_has_GHOST_MSVC_TRADITIONAL 1
    #endif
#endif

#ifndef ghost_has_GHOST_MSVC_TRADITIONAL
    #define GHOST_MSVC_TRADITIONAL 0
    #define ghost_has_GHOST_MSVC_TRADITIONAL 1
#endif

#endif
