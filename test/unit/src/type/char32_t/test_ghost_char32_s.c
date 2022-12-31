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

#include "ghost/type/char32_t/ghost_char32_s.h"

#ifndef ghost_has_GHOST_CHAR32_S
    #error "ghost/type/char32_t/ghost_char32_s.h must define ghost_has_GHOST_CHAR32_S."
#endif

#include "test_common.h"

#if ghost_has_GHOST_CHAR32_S
#include "ghost/type/char32_t/ghost_char32_t.h"
#include "ghost/language/ghost_discard.h"

mirror() {
    const ghost_char32_t* s = GHOST_CHAR32_S("Hello world!");
    ghost_discard(s);
}
#endif
