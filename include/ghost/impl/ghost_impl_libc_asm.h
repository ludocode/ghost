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

#ifndef GHOST_IMPL_LIBC_ASM_H_INCLUDED
#define GHOST_IMPL_LIBC_ASM_H_INCLUDED

/*
 * @def ghost_impl_libc_asm(x) ghost_asm_label(x)
 *
 * This expands to an __asm__ label with whatever name mangling is necessary
 * for libc symbols on the platform (if it's possible to do so with the
 * preprocessor.)
 *
 * Ghost often needs to declare libc functions itself. See
 * ghost_impl_libc_noexcept.h for details. Some platforms mangle names even in
 * C and in extern "C" blocks. For example the asm label of C functions on
 * macOS must have a leading underscore.
 *
 * This macro handles the workarounds needed specifically for libc functions.
 */

#ifdef GHOST_IMPL_LIBC_ASM
    #error
#endif
#ifndef ghost_impl_libc_asm
    #include "ghost/language/ghost_asm_label.h"
    #if ghost_has(ghost_asm_label)
        #define GHOST_IMPL_LIBC_ASM 1
        #ifdef __APPLE__
            /* macOS prefixes all names with an underscore. */
            #define ghost_impl_libc_asm(label) ghost_asm_label("_" label)
        #else
            #define ghost_impl_libc_asm(label) ghost_asm_label(label)
        #endif
    #else
        #define GHOST_IMPL_LIBC_ASM 0
    #endif
#endif

#endif
