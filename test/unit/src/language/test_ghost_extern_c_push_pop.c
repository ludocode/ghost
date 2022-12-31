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

#include "ghost/language/ghost_extern_c_push_pop.h"

#ifndef ghost_has_GHOST_EXTERN_C_PUSH
    #error "ghost/language/ghost_extern_c_push_pop.h must define ghost_has_GHOST_EXTERN_C_PUSH."
#endif
#ifndef ghost_has_GHOST_EXTERN_C_POP
    #error "ghost/language/ghost_extern_c_push_pop.h must define ghost_has_GHOST_EXTERN_C_POP."
#endif

#include "test_common.h"

#if !ghost_has_GHOST_EXTERN_C_PUSH
    #error "ghost_has_GHOST_EXTERN_C_PUSH must exist."
#endif
#if !ghost_has_GHOST_EXTERN_C_POP
    #error "ghost_has_GHOST_EXTERN_C_POP must exist."
#endif

/* TODO this doesn't work */
#if 0
/* TODO for now we test this only on Linux via dlsym(). Ghost could use some dlsym() wrappers! */
#if defined(__linux__) && defined(__GNUC__)
#include <dlfcn.h>
#include "ghost/language/ghost_null.h"
#include "ghost/language/ghost_bit_cast.h"

GHOST_EXTERN_C_PUSH
__attribute__((visibility("default"), externally_visible))
int test_ghost_extern_c_block_function(void) {
    return 5;
}
GHOST_EXTERN_C_POP

mirror() {
    /* TODO using bit cast instead of reinterpret cast because -Wpedantic doesn't allow converting void* to function pointer */
    typedef int (*fn_t)(void);
    fn_t f = ghost_bit_cast(fn_t, void*, dlsym(ghost_null, "test_ghost_extern_c_block_function"));
    mirror_ne(f, ghost_null);
    mirror_eq(5, f());
}
#endif
#endif
