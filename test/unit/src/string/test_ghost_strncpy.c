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

#include "ghost/string/ghost_strncpy.h"

#ifndef ghost_has_ghost_strncpy
    #error "ghost/string/ghost_strncpy.h must define ghost_has_ghost_strncpy."
#endif

#include "test_common.h"

#if !ghost_has_ghost_strncpy
    #error "ghost_strncpy must exist."
#endif

#include "ghost/silence/ghost_silence_stringop_truncation.h"

mirror() {
    char buf[6];

    mirror_check(buf == ghost_strncpy(buf, "hello", 6));
    mirror_eq_s(buf, "hello");

    GHOST_SILENCE_STRINGOP_TRUNCATION
    mirror_check(buf == ghost_strncpy(buf, "goodbye", 3));
    mirror_eq_s(buf, "goolo"); /* buffer wasn't null terminated */

    mirror_check(buf == ghost_strncpy(buf, "hi", 6));
    mirror_eq_s(buf, "hi");
    /* strncpy pads with zeroes */
    mirror_eq_c(buf[3], '\0');
    mirror_eq_c(buf[4], '\0');
    mirror_eq_c(buf[5], '\0');
}
