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

#ifndef GHOST_DISCARD_H_INCLUDED
#define GHOST_DISCARD_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_discard(...) (void)(...)
 *
 * Evaluates the given expression and explicitly discards the result, silencing
 * warnings even if a called function is marked nodiscard.
 *
 * This is useful to silence nodiscard warnings. It's also useful in macros to
 * generate a void expression (e.g. `ghost_discard(0)`), to prevent the return
 * values of functions or expressions with side effects from being used (e.g.
 * `ghost_discard(x = y)`), or in combination with the comma operator to
 * evaluate and ignore arguments:
 *
 *     #define FOO(x, y) (ghost_discard(y), (x))
 *
 * Ghost uses this everywhere as an alternative to void casting simply to
 * better document what's going on.
 *
 * Note that this doesn't silence GCC's __attribute__((warn_unused_result)).
 * For that use ghost_discard_force().
 *
 * @see ghost_discard_force()
 */
#endif

/* TODO revert the split, ghost_nodiscard is warn_unused_result wherever
 * [[nodiscard]] doesn't exist, it doesn't make sense to require
 * ghost_discard_force() only on newer language standards */

/* The the C++ (and probably C) standards intend for a nodiscard value to
 * be discarded by void casting. There is some discussion on it here:
 *     https://stackoverflow.com/a/53581957 */
#ifndef ghost_has_ghost_discard
    #ifndef ghost_discard
        #include "ghost/language/ghost_static_cast.h"
        #define ghost_discard(x) ghost_static_cast(void, (x))
    #endif
    #define ghost_has_ghost_discard 1
#endif

#endif
