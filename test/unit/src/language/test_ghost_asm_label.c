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

#include "ghost/language/ghost_asm_label.h"

#ifndef ghost_has_ghost_asm_label
    #error "ghost/language/ghost_asm_label.h must define ghost_has_ghost_asm_label."
#endif

#include "test_common.h"

/* TODO this test doesn't work */
#if 0

#if ghost_has_ghost_asm_label
#include "ghost/language/ghost_null.h"
#include "ghost/language/ghost_bit_cast.h"

#if defined(__linux__) && defined(__GNUC__)
/* TODO for now we test dlsym only on Linux. Ghost could use some dlsym()
 * wrappers! */
#include <dlfcn.h>
#endif


/* Note we don't extern "C" this. The asm label should override C++ name
 * mangling. */
int test_ghost_asm_label_before(void);
__attribute__((visibility("default"), externally_visible))
int test_ghost_asm_label_before(void) {
    return 7;
} ghost_asm_label("test_ghost_asm_label_after");

extern int test_ghost_asm_label_after(void);

mirror() {
    mirror_eq(7, test_ghost_asm_label_after());

    #if defined(__linux__) && defined(__GNUC__)
    /* TODO using bit cast instead of reinterpret cast because -Wpedantic doesn't allow converting void* to function pointer */
    typedef int (*fn_t)(void);
    fn_t f = ghost_bit_cast(fn_t, void*, dlsym(ghost_null, "test_ghost_asm_label_after"));
    mirror_ne(f, ghost_null);
    mirror_eq(7, f());
    #endif
}
#endif

#endif
