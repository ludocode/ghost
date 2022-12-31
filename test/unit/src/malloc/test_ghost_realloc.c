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

#include "ghost/malloc/ghost_realloc.h"

#ifndef ghost_has_ghost_realloc
    #error "ghost/malloc/ghost_realloc.h must define ghost_has_ghost_realloc."
#endif

#include "test_common.h"

#if ghost_has_ghost_realloc
#define TEST_GHOST_REALLOC_FN ghost_realloc
#include "test_ghost_realloc.t.h"

mirror_1(it("should allocate with null and size 0")) {
    void* x = ghost_realloc(ghost_null, 0);
    mirror_nn(x);
    #if ghost_has(ghost_free)
    ghost_free(x);
    #endif
}

#include "ghost/debug/ghost_assert.h"
#if ghost_has(ghost_assert) && GHOST_DEBUG
/* TODO death tests are not working yet */
#if 0
mirror_2(death, it("should assert against non-null with size 0 in debug builds")) {
    void* p = ghost_realloc(ghost_null, 1);

    /* This may trigger static analysis tools since realloc(p,0) is no longer
     * allowed as of C23. */
    p = ghost_realloc(p, 0); /* should fail ghost_assert() */

    /* This should be unreachable. We put in this call to free anyway to
     * prevent static analysis from complaining about leaks. */
    ghost_free(p);
}
#endif
#endif

#endif
