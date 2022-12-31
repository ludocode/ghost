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

#ifndef TEST_COMMON_H
#define TEST_COMMON_H

/* All Ghost headers should include ghost/ghost_core.h at least indirectly. */
#if !defined(GHOST_VERSION) || !defined(ghost_has) || !defined(GHOST_DOCUMENTATION)
    #error "ghost/ghost_core.h was not included."
#endif

/* Include mirror for testing. Most files define mirro test but even if they
 * don't this at least prevents warnings for empty translation units. */
#include "mirror/mirror.h"

/* The MSVC traditional preprocessor warns under /W4 if a single-parameter
 * macro is given a blank argument (which it interprets as 0 arguments.)
 * This interferes with some of our macros that take one optional parameter
 * (e.g. ghost_unreachable(), ghost_deprecated(), etc.) */
#include "ghost/preprocessor/ghost_msvc_traditional.h"
#if GHOST_MSVC_TRADITIONAL
    GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS
#endif

/* Old versions of Clang (3.7 and earlier) don't properly strip CV qualifiers
 * from _Generic type arguments. We use this to disable some unit tests. */
#if defined(__clang__) && !defined(__APPLE__)
    #if __clang_major__ < 3 || __clang_major__ == 3 && __clang_minor__ <= 7
        #define GHOST_IMPL_GENERIC_NO_CV
    #endif
#endif

#endif
