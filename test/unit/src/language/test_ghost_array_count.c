/*
 * MIT No Attribution
 *
 * Copyright (c) 2022-2023 Fraser Heavy Software
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

#include "ghost/language/ghost_array_count.h"

#ifndef ghost_has_ghost_array_count
    #error "ghost/language/ghost_array_count.h must define ghost_has_ghost_array_count."
#endif

#include "test_common.h"
#include "ghost/language/ghost_cplusplus.h"

#if !ghost_has_ghost_array_count
    #error "ghost_array_count must exist."
#endif

/* We have to annotate these maybe_unused even though they're used because
 * they're only used in sizeof() so Clang warns about not emitting their
 * definitions. */
#include "ghost/language/ghost_maybe_unused.h"

ghost_maybe_unused
static const int ints[] = {
    1, 2, 3, 4, 5
};

ghost_maybe_unused
static const char* strs[] = {
    "Alice", "Bob", "Carol", "Dave",
};

ghost_maybe_unused
static const struct {
    int x, y;
} points[] = {
    {1, 2}, {3,4}, {5, 6},
};

mirror() {
    mirror_eq(5, ghost_array_count(ints));
    mirror_eq(4, ghost_array_count(strs));
    mirror_eq(3, ghost_array_count(points));
}

#ifdef ghost_cplusplus
struct Foo {
    Foo() : x(4), y(5), z(6) {}
    virtual ~Foo() {}
    int x,y,z;
};

mirror() {
    Foo foos[4];
    mirror_eq(4, ghost_array_count(foos));
}
#endif

/* ghost_array_count() doesn't work on local types in C++98. It does work in
 * all standard versions of C and in C++11 or newer. */
#ifdef ghost_cplusplus
    #if ghost_cplusplus >= 201103L
        #define GHOST_IMPL_TEST_LOCAL_TYPES
    #endif
#else
    #define GHOST_IMPL_TEST_LOCAL_TYPES
#endif
#ifdef GHOST_IMPL_TEST_LOCAL_TYPES
mirror() {
    struct {int x;} array_of_anonymous_type[3];
    mirror_eq(3, ghost_array_count(array_of_anonymous_type));
}
#endif
#undef GHOST_IMPL_TEST_LOCAL_TYPES
