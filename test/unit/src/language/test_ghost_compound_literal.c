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

#include "ghost/language/ghost_compound_literal.h"

#ifndef ghost_has_ghost_compound_literal
    #error "ghost/language/ghost_compound_literal.h must define ghost_has_ghost_compound_literal."
#endif

#include "test_common.h"

#if ghost_has_ghost_compound_literal
typedef struct {
    int identifier;
    struct {
        const char* first;
        const char* last;
    } name;
    int age;
} person_t;

mirror() {
    person_t jane = ghost_compound_literal(person_t, 123456, {"Jane", "Doe"}, 47);
    mirror_eq_i(jane.identifier, 123456);
    mirror_eq_s(jane.name.first, "Jane");
    mirror_eq_s(jane.name.last, "Doe");
    mirror_eq_i(jane.age, 47);
}
#endif
