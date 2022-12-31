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

#ifndef GHOST_CPARSER_PP_H_INCLUDED
#define GHOST_CPARSER_PP_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_CPARSER_PP
 *
 * TODO rename to GHOST_CPARSER_BUGGY_PP, want to be able to set this to 0 if they fix it
 *
 * Expands to 1 if compiling under cparser's preprocessor and 0 otherwise.
 *
 * cparser has a seriously buggy preprocessor. It does not do argumentless
 * macro forwarding correctly among other things:
 *
 *     https://github.com/libfirm/cparser/issues/53
 *
 * We wrap a check for it in this macro. If cparser ever fixes it, this can
 * turn into a version check or whatever.
 */
#endif

#ifndef ghost_has_GHOST_CPARSER_PP
    #ifndef GHOST_CPARSER_PP
        #ifdef __CPARSER__
            #define GHOST_CPARSER_PP 1
        #else
            #define GHOST_CPARSER_PP 0
        #endif
    #endif
    #define ghost_has_GHOST_CPARSER_PP 1
#endif

#endif
