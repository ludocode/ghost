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

#ifndef GHOST_TYPE_COMMON_H_INCLUDED
#define GHOST_TYPE_COMMON_H_INCLUDED

#include "ghost/ghost_core.h"

/**
 * @file
 *
 * Includes most types in `ghost/type/`, those commonly used in ordinary code.
 *
 * This includes types, widths, limits and constant macros for:
 *
 * - all the basic types (e.g. ghost_bool, ghost_llong, ghost_ldouble, ghost_float, etc.)
 * - all the special character types (e.g. ghost_wchar_t, ghost_char8_t, ghost_char32_t, etc.)
 * - all the standard library types (e.g. ghost_ptrdiff_t, ghost_ssize_t, ghost_intptr_t, etc.)
 * - all the fixed-width types (e.g. ghost_int32_t, ghost_uint64_t, ghost_float64_t, etc.)
 *
 * It does not include less commonly used types like ghost_int_least32_t or
 * ghost_float32_t.
 */

/* basic types */
#include "ghost/type/ghost_bool_all.h"
#include "ghost/type/ghost_char_all.h"
#include "ghost/type/ghost_schar_all.h"
#include "ghost/type/ghost_uchar_all.h"
#include "ghost/type/ghost_short_all.h"
#include "ghost/type/ghost_ushort_all.h"
#include "ghost/type/ghost_int_all.h"
#include "ghost/type/ghost_uint_all.h"
#include "ghost/type/ghost_long_all.h"
#include "ghost/type/ghost_ulong_all.h"
#include "ghost/type/ghost_llong_all.h"
#include "ghost/type/ghost_ullong_all.h"

/* floating point types */
#include "ghost/type/ghost_float_all.h"
#include "ghost/type/ghost_double_all.h"
#include "ghost/type/ghost_ldouble_all.h"

/* standard library types */
#include "ghost/type/ghost_size_all.h"
#include "ghost/type/ghost_ssize_all.h"
#include "ghost/type/ghost_ptrdiff_all.h"
#include "ghost/type/ghost_intptr_all.h"
#include "ghost/type/ghost_uintptr_all.h"

/* fixed-width types */
#include "ghost/type/ghost_int8_all.h"
#include "ghost/type/ghost_int16_all.h"
#include "ghost/type/ghost_int32_all.h"
#include "ghost/type/ghost_int64_all.h"
#include "ghost/type/ghost_uint8_all.h"
#include "ghost/type/ghost_uint16_all.h"
#include "ghost/type/ghost_uint32_all.h"
#include "ghost/type/ghost_uint64_all.h"

/* special character types */
#include "ghost/type/ghost_wchar_all.h"
#include "ghost/type/ghost_char8_all.h"
#include "ghost/type/ghost_char16_all.h"
#include "ghost/type/ghost_char32_all.h"

#endif
