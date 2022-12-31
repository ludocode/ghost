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

#ifndef GHOST_ASM_LABEL_H_INCLUDED
#define GHOST_ASM_LABEL_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * @def ghost_asm_label(name) __asm__(name)
 *
 * Specifies a different name to be used in the assembler code as the name of
 * the annotated symbol.
 *
 * This is used by Ghost to wrap system functions that may or may not be
 * declared normally. For example:
 *
 *     extern void* my_malloc_wrapper(size_t size) ghost_asm_label("malloc");
 *
 * You can also use this to define your own functions and variables with
 * different assembler names.
 *
 * https://gcc.gnu.org/onlinedocs/gcc/Asm-Labels.html
 */
#endif

#ifndef ghost_has_ghost_asm_label
    #ifdef ghost_asm_label
        #define ghost_has_ghost_asm_label 1
    #endif
#endif

/* GNUC compilers (GCC, Clang, etc.) should support asm labels.
 *
 * TinyCC supports asm label. It doesn't appear to behave properly under 9.27
 * but it's fixed in mob. Ghost only supports mob. */
#ifndef ghost_has_ghost_asm_label
    #if defined(__GNUC__) || defined(__TINYC__)
        #define ghost_asm_label(name) __asm__(name)
        #define ghost_has_ghost_asm_label 1
    #endif
#endif

/* cproc supports asm labels. */
#ifndef ghost_has_ghost_asm_label
    #include "ghost/detect/ghost_cproc.h"
    #if GHOST_CPROC
        #define ghost_asm_label(name) __asm__(name)
        #define ghost_has_ghost_asm_label 1
    #endif
#endif

#ifndef ghost_has_ghost_asm_label
    #define ghost_has_ghost_asm_label 0
#endif

#endif
