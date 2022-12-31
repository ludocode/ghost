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

#ifndef GHOST_IMPL_QSORT_INTERNAL_DECLARE_H_INCLUDED
#define GHOST_IMPL_QSORT_INTERNAL_DECLARE_H_INCLUDED

#include "ghost/ghost_core.h"

/*
 * Declares Ghost's internal qsort_r().
 */

#include "ghost/language/ghost_alignof.h"
#include "ghost/language/ghost_optimize_for_size_opt.h"
#include "ghost/language/ghost_is_aligned.h"
#include "ghost/impl/ghost_impl_inline.h"
#include "ghost/impl/ghost_impl_noinline.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/type/char/ghost_char_width.h"
#include "ghost/type/uint32_t/ghost_uint32_t.h"
#include "ghost/type/uint64_t/ghost_uint64_t.h"

GHOST_IMPL_FUNCTION_OPEN

typedef enum ghost_impl_qsort_variant_t {
    ghost_impl_qsort_variant_nocontext,
    ghost_impl_qsort_variant_gnu,
    ghost_impl_qsort_variant_bsd
    #if GHOST_WIN_QSORT_S_USE_CDECL
    , ghost_impl_qsort_variant_windows
    #endif
} ghost_impl_qsort_variant_t;

typedef enum ghost_impl_qsort_size_class_t {
    ghost_impl_qsort_size_class_4,
    ghost_impl_qsort_size_class_8,
    ghost_impl_qsort_size_class_any
} ghost_impl_qsort_size_class_t;

ghost_impl_inline
ghost_impl_qsort_size_class_t ghost_impl_qsort_resolve_size_class(void* first, ghost_size_t element_size) {
    if (element_size == sizeof(ghost_uint32_t) && ghost_is_aligned((first),
                #if ghost_has_ghost_alignof
                    ghost_alignof(ghost_uint32_t)
                #elif defined(GHOST_CHAR_WIDTH)
                    32 / GHOST_CHAR_WIDTH
                #else
                    #error "Unknown uint32_t alignment??"
                #endif
                ))
        return ghost_impl_qsort_size_class_4;
    if (element_size == sizeof(ghost_uint64_t) && ghost_is_aligned((first),
                #if ghost_has_ghost_alignof
                    ghost_alignof(ghost_uint64_t)
                #elif defined(GHOST_CHAR_WIDTH)
                    /* Assume the required alignment is the full width. This
                     * may be an overestimate: on some 32-bit systems, 64 bit
                     * values only need to be aligned to a 32 bit boundary.
                     * This is still safe; it just results in minor performance
                     * loss. */
                    64 / GHOST_CHAR_WIDTH
                #else
                    #error "Unknown uint64_t alignment??"
                #endif
                ))
        return ghost_impl_qsort_size_class_8;
    return ghost_impl_qsort_size_class_any;
}

typedef struct ghost_impl_qsort_state_t {
    ghost_size_t element_size;
    ghost_impl_qsort_size_class_t size_class;

    ghost_impl_qsort_variant_t variant;
    union {
        int (*nocontext)(const void* left, const void* right);
        int (*gnu)(const void* left, const void* right, void* user_context);
        int (*bsd)(void* user_context, const void* left, const void* right);
        #if GHOST_WIN_QSORT_S_USE_CDECL
        int (GHOST_WIN_QSORT_S_CDECL *windows)(void* user_context, const void* left, const void* right);
        #endif
    } compare;

    void* user_context;
} ghost_impl_qsort_state_t;

#if GHOST_OPTIMIZE_FOR_SIZE_OPT
    ghost_impl_noinline
    void ghost_impl_qsort_shellsort(ghost_impl_qsort_state_t* state, void* base, ghost_size_t count);
    #define ghost_impl_qsort_internal ghost_impl_qsort_shellsort
#else
    ghost_impl_noinline
    void ghost_impl_qsort_introsort(ghost_impl_qsort_state_t* state, void* base, ghost_size_t count);
    #define ghost_impl_qsort_internal ghost_impl_qsort_introsort
#endif

GHOST_IMPL_FUNCTION_CLOSE

#endif
