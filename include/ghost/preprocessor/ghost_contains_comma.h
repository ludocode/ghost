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

#ifndef GHOST_CONTAINS_COMMA_H_INCLUDED
#define GHOST_CONTAINS_COMMA_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @def GHOST_CONTAINS_COMMA(...)
 *
 * Expands to 1 if two or more arguments were passed (i.e. the __VA_ARGS__
 * contains an unparenthesized comma) and 0 otherwise.
 */

#ifndef ghost_has_GHOST_CONTAINS_COMMA
    #ifdef GHOST_CONTAINS_COMMA
        #define ghost_has_GHOST_CONTAINS_COMMA 1
    #endif
#endif

/* This requires variadic macros. */
#ifndef ghost_has_GHOST_CONTAINS_COMMA
    #include "ghost/preprocessor/ghost_pp_va_args.h"
    #if !GHOST_PP_VA_ARGS
        #define ghost_has_GHOST_CONTAINS_COMMA 0
    #endif
#endif

#ifndef ghost_has_GHOST_CONTAINS_COMMA

    /*
     * We implement this by counting arguments. This is limited to 63 arguments
     * for the same reasons as GHOST_COUNT_ARGS() and the implementation is
     * nearly the same.
     *
     * I'd love a way to implement this that doesn't use argument counting so that
     * it can support unlimited arguments (or that at least raises an error when
     * too many arguments are passed.) I'm open to suggestions. Note though
     * that MSVC only supports 127 preprocessor arguments even though C++
     * requires 256 so maybe there's no point.
     *
     * Note that we don't actually want to wrap GHOST_COUNT_ARGS(). This could
     * in theory be implemented as `(GHOST_COUNT_ARGS() >= 2)` but that might
     * only work in the context of an #ifdef, not with token pasting like what
     * GHOST_REST() uses this for.
     *
     * TODO actually we probably could just wrap GHOST_COUNT_ARGS(), figure it out later
     */

    #define GHOST_CONTAINS_COMMA(...) \
                GHOST_CONTAINS_COMMA_IMPL( \
                    __VA_ARGS__, \
                    GHOST_CONTAINS_COMMA_IMPL_SEQUENCE(), \
                    GHOST_CONTAINS_COMMA_IMPL_UNUSED)

    #define GHOST_CONTAINS_COMMA_IMPL(...) GHOST_CONTAINS_COMMA_IMPL_64TH_ARG(__VA_ARGS__)

    #define GHOST_CONTAINS_COMMA_IMPL_SEQUENCE() \
                 1,  1,  1,  1,  1,  1,  1, \
             1,  1,  1,  1,  1,  1,  1,  1, \
             1,  1,  1,  1,  1,  1,  1,  1, \
             1,  1,  1,  1,  1,  1,  1,  1, \
             1,  1,  1,  1,  1,  1,  1,  1, \
             1,  1,  1,  1,  1,  1,  1,  1, \
             1,  1,  1,  1,  1,  1,  1,  1, \
             1,  1,  1,  1,  1,  1,  1, \
                                         0

    #define GHOST_CONTAINS_COMMA_IMPL_64TH_ARG( \
            _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8, \
            _9, _10, _11, _12, _13, _14, _15, _16, \
            _17, _18, _19, _20, _21, _22, _23, _24, \
            _25, _26, _27, _28, _29, _30, _31, _32, \
            _33, _34, _35, _36, _37, _38, _39, _40, \
            _41, _42, _43, _44, _45, _46, _47, _48, \
            _49, _50, _51, _52, _53, _54, _55, _56, \
            _57, _58, _59, _60, _61, _62, _63, \
            x, ...) x

    #define ghost_has_GHOST_CONTAINS_COMMA 1
#endif

#endif
