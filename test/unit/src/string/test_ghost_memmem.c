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

#include "ghost/string/ghost_memmem.h"

#ifndef ghost_has_ghost_memmem
    #error "ghost/string/ghost_memmem.h must define ghost_has_ghost_memmem."
#endif

#include "test_common.h"

#if !ghost_has_ghost_memmem
    #error "ghost_memmem must exist."
#endif

#include "ghost/language/ghost_static_cast.h"

mirror() {
    static const char rose[] = "Rose is a rose is a rose is a rose.";
    mirror_eq_s(rose     , ghost_static_cast(char*, ghost_memmem(rose,      sizeof(rose),      "Rose", 4)));
    mirror_eq_s(rose + 10, ghost_static_cast(char*, ghost_memmem(rose,      sizeof(rose),      "rose", 4)));
    mirror_eq_s(rose + 20, ghost_static_cast(char*, ghost_memmem(rose + 11, sizeof(rose) - 11, "rose", 4)));
}
