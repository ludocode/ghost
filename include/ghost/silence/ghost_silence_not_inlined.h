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

#ifndef GHOST_SILENCE_NOT_INLINED_H_INCLUDED
#define GHOST_SILENCE_NOT_INLINED_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def GHOST_SILENCE_NOT_INLINED
 *
 * Silences warnings about force-inline functions not being inlined.
 */
#endif

#ifndef ghost_has_GHOST_SILENCE_NOT_INLINED
    #ifdef GHOST_SILENCE_NOT_INLINED
        #define ghost_has_GHOST_SILENCE_NOT_INLINED 1
    #endif
#endif

/* MSVC C4714 in /W1 */
#ifndef ghost_has_GHOST_SILENCE_NOT_INLINED
    #ifdef _MSC_VER
        /* C4714: function ... marked as __forceinline not inlined */
        #define GHOST_SILENCE_NOT_INLINED __pragma(warning(disable:4714))
        #define ghost_has_GHOST_SILENCE_NOT_INLINED 1
    #endif
#endif

/*
 * Note: GCC can emit the following warning:
 *
 *     warning: ‘always_inline’ function might not be inlinable [-Wattributes]
 *
 * However, it only does this on functions that are not also declared inline.
 * ghost_always_inline always adds inline under GCC so any code that uses it
 * won't trigger this warning.
 *
 * Silencing -Wattributes would disable a whole lot more warnings than just
 * this, so for this and the above reasons, we don't do anything under GNU C.
 *
 * If you're getting this warning, a better way to silence it is to add inline
 * or use ghost_always_inline.
 */

#ifndef ghost_has_GHOST_SILENCE_NOT_INLINED
    #define GHOST_SILENCE_NOT_INLINED /*nothing*/
    #define ghost_has_GHOST_SILENCE_NOT_INLINED 1
#endif

#endif
