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

#include "ghost/format/ghost_snprintf.h"

#ifndef ghost_has_ghost_snprintf
    #error "ghost/format/ghost_snprintf.h must define ghost_has_ghost_snprintf."
#endif

#include "test_common.h"

#if ghost_has_ghost_snprintf

#include "ghost/language/ghost_null.h"

#ifdef __GNUC__
    #if __GNUC__ >= 7
        #include "ghost/detect/ghost_gcc.h"
        #if GHOST_GCC
            #pragma GCC diagnostic ignored "-Wformat-truncation"
        #endif
    #endif
#endif

mirror() {
    char buf[6];
    mirror_eq_i(12, ghost_snprintf(buf, sizeof(buf), "%s %s", "Hello", "world!"));
    mirror_eq_s(buf, "Hello");
}

mirror_1(it("shouldn't fail when size is zero")) {
    char buf[1];
    mirror_eq_i(12, ghost_snprintf(buf, 0, "%s %s", "Hello", "world!"));
}

mirror_1(it("shouldn't fail when pointer is null")) {
    mirror_eq_i(12, ghost_snprintf(ghost_null, 0, "%s %s", "Hello", "world!"));
}
#endif
