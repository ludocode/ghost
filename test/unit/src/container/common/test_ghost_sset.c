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

#include "ghost/container/common/ghost_sset.h"

#ifndef ghost_has_ghost_sset
    #error "ghost/container/common/ghost_sset.h must define ghost_has_ghost_sset."
#endif

#include "test_common.h"

#if ghost_has_ghost_sset
/*
 * A very basic test that the string set works
 */
mirror() {
    ghost_sset_t sset;
    ghost_sset_it_t it;

    ghost_sset_init(&sset);

    ghost_sset_insert(&sset, "Carol");
    ghost_sset_insert(&sset, "Dave");
    ghost_sset_insert(&sset, "Bob");
    ghost_sset_insert(&sset, "Alice");

    mirror_check(!ghost_sset_remove(&sset, "Eve"));
    mirror_eq(ghost_null, ghost_sset_find(&sset, "Eve"));

    mirror_check(ghost_sset_contains(&sset, "Alice"));
    mirror_check(ghost_sset_contains(&sset, "Bob"));
    mirror_check(ghost_sset_contains(&sset, "Carol"));
    mirror_check(ghost_sset_contains(&sset, "Dave"));

    /*
    for (ghost_sset_it_t it = ghost_sset_first(&sset); it; it = ghost_sset_next(&sset, it)) {
        printf("%s\n", ghost_sset_it_string(it));
    }
    */

    /* make sure we can iterate in order */
    it = ghost_sset_first(&sset);
    mirror_nn(it);
    mirror_eq_s("Alice", ghost_sset_it_string(it));
    it = ghost_sset_next(&sset, it);
    mirror_nn(it);
    mirror_eq_s("Bob", ghost_sset_it_string(it));
    it = ghost_sset_next(&sset, it);
    mirror_nn(it);
    mirror_eq_s("Carol", ghost_sset_it_string(it));
    it = ghost_sset_next(&sset, it);
    mirror_nn(it);
    mirror_eq_s("Dave", ghost_sset_it_string(it));

    /* make sure backing up works */
    it = ghost_sset_previous(&sset, it);
    mirror_nn(it);
    mirror_eq_s("Carol", ghost_sset_it_string(it));
    it = ghost_sset_next(&sset, it);
    mirror_nn(it);
    it = ghost_sset_next(&sset, it);
    mirror_eq(ghost_null, it);

    /* remove some elements */
    mirror_check(ghost_sset_remove(&sset, "Bob"));
    ghost_sset_remove_it(&sset, ghost_sset_find(&sset, "Carol"));

    /* check what's left */
    it = ghost_sset_first(&sset);
    mirror_nn(it);
    mirror_eq_s("Alice", ghost_sset_it_string(it));
    it = ghost_sset_last(&sset);
    mirror_nn(it);
    mirror_eq_s("Dave", ghost_sset_it_string(it));

    ghost_sset_destroy(&sset);
}
#endif
