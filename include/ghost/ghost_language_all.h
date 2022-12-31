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

#ifndef GHOST_LANGUAGE_ALL_H_INCLUDED
#define GHOST_LANGUAGE_ALL_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes everything in `ghost/language/`.
 *
 * This is all of Ghost's wrappers for common compiler extensions to the C
 * language, as well as wrappers for compatibility with other C-compatible
 * languages (C++, Objective-C.)
 */

/*
 * These language extension features are essentially all simple macros. It is
 * trivial for the compiler to parse this so there is no reason to not just
 * include them all (and they are almost all included by other parts of Ghost
 * anyway.) If you really don't want them all, just don't include this header
 * (or any header that includes it like `ghost_common.h`).
 */

#include "ghost/language/ghost_alignas.h"
#include "ghost/language/ghost_alignat.h"
#include "ghost/language/ghost_alignof.h"
#include "ghost/language/ghost_always_inline.h"
#include "ghost/language/ghost_always_inline_opt.h"
#include "ghost/language/ghost_always_inline_stmt.h"
#include "ghost/language/ghost_array_count.h"
#include "ghost/language/ghost_asm_label.h"
#include "ghost/language/ghost_assume.h"
#include "ghost/language/ghost_auto_cast.h"
#include "ghost/language/ghost_auto.h"
#include "ghost/language/ghost_bit_cast.h"
#include "ghost/language/ghost_bless.h"
#include "ghost/language/ghost_cast.h"
#include "ghost/language/ghost_cold.h"
#include "ghost/language/ghost_complex.h"
#include "ghost/language/ghost_compound_literal.h"
#include "ghost/language/ghost_const_cast.h"
#include "ghost/language/ghost_container_of.h"
#include "ghost/language/ghost_cplusplus.h"
#include "ghost/language/ghost_cxx_exceptions.h"
#include "ghost/language/ghost_deprecated.h"
#include "ghost/language/ghost_deprecated_reason.h"
#include "ghost/language/ghost_discard_force.h"
#include "ghost/language/ghost_discard.h"
#include "ghost/language/ghost_dllexport.h"
#include "ghost/language/ghost_dllimport.h"
#include "ghost/language/ghost_emit_always_inline.h"
#include "ghost/language/ghost_emit_inline.h"
#include "ghost/language/ghost_expect_false.h"
#include "ghost/language/ghost_expect.h"
#include "ghost/language/ghost_expect_true.h"
#include "ghost/language/ghost_extern_c.h"
#include "ghost/language/ghost_extern_c_push_pop.h"
#include "ghost/language/ghost_fallthrough.h"
#include "ghost/language/ghost_generic.h"
#include "ghost/language/ghost_header_always_inline.h"
#include "ghost/language/ghost_header_function.h"
#include "ghost/language/ghost_header_inline.h"
#include "ghost/language/ghost_header_noinline.h"
#include "ghost/language/ghost_hidden.h"
#include "ghost/language/ghost_hidden_push_pop.h"
#include "ghost/language/ghost_hosted.h"
#include "ghost/language/ghost_hot.h"
#include "ghost/language/ghost_inline.h"
#include "ghost/language/ghost_inline_opt.h"
#include "ghost/language/ghost_is_aligned.h"
#include "ghost/language/ghost_max_align.h"
#include "ghost/language/ghost_may_alias.h"
#include "ghost/language/ghost_maybe_unused.h"
#include "ghost/language/ghost_nodiscard.h"
#include "ghost/language/ghost_nodiscard_reason.h"
#include "ghost/language/ghost_noemit_always_inline.h"
#include "ghost/language/ghost_noemit_inline.h"
#include "ghost/language/ghost_noinline.h"
#include "ghost/language/ghost_noreturn.h"
#include "ghost/language/ghost_noreturn_opt.h"
#include "ghost/language/ghost_null.h"
#include "ghost/language/ghost_offsetof.h"
#include "ghost/language/ghost_optimize_for_size.h"
#include "ghost/language/ghost_optimize_for_size_opt.h"
#include "ghost/language/ghost_reinterpret_cast.h"
#include "ghost/language/ghost_remove_quals.h"
#include "ghost/language/ghost_restrict.h"
#include "ghost/language/ghost_selectany_var.h"
#include "ghost/language/ghost_static_cast.h"
#include "ghost/language/ghost_static_init.h"
#include "ghost/language/ghost_stdc_version.h"
#include "ghost/language/ghost_struct_hack_access.h"
#include "ghost/language/ghost_struct_hack.h"
#include "ghost/language/ghost_struct_hack_sizeof.h"
#include "ghost/language/ghost_thread_local.h"
#include "ghost/language/ghost_typeof.h"
#include "ghost/language/ghost_unreachable.h"
#include "ghost/language/ghost_va_copy.h"
#include "ghost/language/ghost_weak.h"
#include "ghost/language/ghost_zero_init.h"

#endif
