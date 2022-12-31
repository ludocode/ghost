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

#ifndef GHOST_COUNTER_H_INCLUDED
#define GHOST_COUNTER_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_COUNTER
 *
 * Expands to an integer that is incremented every time this macro is expanded,
 * or to the current line if a counter is unsupported.
 *
 * This can be used to make macros that define unique names each time they are
 * used. A good way to use this is to pass it as a parameter to a secondary
 * macro to force it to be expanded first, that way it will expand to the same
 * value each time it is used in the secondary macro. Like this:
 *
 *     // TODO does this actually work?
 *     #define FOO() FOO2(GHOST_COUNTER)
 *     #define FOO2(counter) \
 *         struct foo_##counter; \
 *         void foo_##counter##_init(struct foo_##counter); \
 *         // etc.
 *
 *     // TODO probably need to do this instead
 *     #define FOO() GHOST_EXPAND(GHOST_DEFER(FOO2)(GHOST_COUNTER))
 *
 * This uses __LINE__ as a fallback in case __COUNTER__ is not supported.
 * __LINE__ is prone to collisions if the macro is used multiple times on the
 * same line (even if in different included files.) If you don't want __LINE__
 * as a fallback, just use __COUNTER__ directly.
 */

#ifndef ghost_has_GHOST_COUNTER
    #ifdef GHOST_COUNTER
        #define ghost_has_GHOST_COUNTER 1
    #endif
#endif

#ifndef ghost_has_GHOST_COUNTER
    /* GCC has supported __COUNTER__ since GCC 4.9.3.
     * TinyCC also supports this even though it doesn't document it.
     * We assume other compilers that define __GNUC__ also support it unless we
     * know otherwise (e.g. PCC.) */
    #if defined(__GNUC__) && !defined(__PCC__)
        #if defined(__clang__) || defined(__TINYC__)
            #define GHOST_COUNTER __COUNTER__
            #define ghost_has_GHOST_COUNTER 1
        #elif __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
            #define GHOST_COUNTER __COUNTER__
            #define ghost_has_GHOST_COUNTER 1
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_COUNTER
    /* MSVC has supported __COUNTER__ since at least VS 2015. */
    #ifdef _MSC_VER
        #if _MSC_VER >= 1900
            #define GHOST_COUNTER __COUNTER__
            #define ghost_has_GHOST_COUNTER 1
        #endif
    #endif
#endif

#ifndef ghost_has_GHOST_COUNTER
    /* Use __LINE__ as a fallback. */
    #define GHOST_COUNTER __LINE__
    #define ghost_has_GHOST_COUNTER 1
#endif

#endif
