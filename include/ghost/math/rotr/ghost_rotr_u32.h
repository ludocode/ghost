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

#ifndef GHOST_ROTR_U32_H_INCLUDED
#define GHOST_ROTR_U32_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Rotate the bits of the given value from most significant bit to least by the
 * given number of bits modulo 32.
 */
uint32_t ghost_rotr_u32(uint32_t value, unsigned bits);
#endif

#ifndef ghost_has_ghost_rotr_u32
    #ifdef ghost_rotr_u32
        #define ghost_has_ghost_rotr_u32 1
    #endif
#endif

/* We need ghost_uint32_t. */
#ifndef ghost_has_ghost_rotr_u32
    #include "ghost/type/uint32_t/ghost_uint32_t.h"
    #if !ghost_has_ghost_uint32_t
        #define ghost_has_ghost_rotr_u32 0
    #endif
#endif

/* C++20 has std::rotr */
#ifndef ghost_has_ghost_rotr_u32
    #ifdef __cplusplus
        #include "ghost/language/ghost_cplusplus.h"
        #if ghost_cplusplus >= 202002L
            #include "ghost/header/cxx/ghost_cxx_bit_h.h"
            #if ghost_has(ghost_cxx_bit_h)
                #include "ghost/language/ghost_static_cast.h"
                #include "ghost/impl/ghost_impl_always_inline.h"
                GHOST_IMPL_FUNCTION_OPEN
                ghost_impl_always_inline
                ghost_uint32_t ghost_rotr_u32(ghost_uint32_t ghost_impl_v_value, unsigned int ghost_impl_v_bits) {
                    return ::std::rotr(ghost_impl_v_value, ghost_static_cast(int, ghost_impl_v_bits));
                }
                GHOST_IMPL_FUNCTION_CLOSE
                #define ghost_has_ghost_rotr_u32 1
            #endif
        #endif
    #endif
#endif

/* Clang has __builtin_rotateright32(). Other GCC-style compilers may as well but
 * GCC proper apparently does not. We use __has_builtin to check. */
#ifndef ghost_has_ghost_rotr_u32
    #include "ghost/preprocessor/ghost_has_builtin.h"
    #if ghost_has(ghost_has_builtin)
        #if __has_builtin(__builtin_rotateright32)
            #include "ghost/impl/ghost_impl_always_inline.h"
            #include "ghost/language/ghost_static_cast.h"
            GHOST_IMPL_FUNCTION_OPEN
            ghost_impl_always_inline
            ghost_uint32_t ghost_rotr_u32(ghost_uint32_t ghost_impl_v_value, unsigned int ghost_impl_v_bits) {
                return __builtin_rotateright32(ghost_impl_v_value, ghost_static_cast(unsigned char, ghost_impl_v_bits));
            }
            GHOST_IMPL_FUNCTION_CLOSE
            #define ghost_has_ghost_rotr_u32 1
        #endif
    #endif
#endif

/* Microsoft has a _rotr() function in <stdlib.h>. It takes unsigned int as
 * value and not uint32_t, but int is guaranteed to be 32 bits on all
 * architectures supported by MSVC. The bits parameter is also a signed int.
 *     https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rotl-rotl64-rotr-rotr64 */
#ifndef ghost_has_ghost_rotr_u32
    #ifdef _MSC_VER
        #include "ghost/header/c/ghost_stdlib_h.h"
        #include "ghost/impl/ghost_impl_always_inline.h"
        #include "ghost/language/ghost_static_cast.h"
        GHOST_IMPL_FUNCTION_OPEN
        ghost_impl_always_inline
        ghost_uint32_t ghost_rotr_u32(ghost_uint32_t ghost_impl_v_value, unsigned int ghost_impl_v_bits) {
            return _rotr(ghost_impl_v_value, ghost_static_cast(int, ghost_impl_v_bits));
        }
        GHOST_IMPL_FUNCTION_CLOSE
        #define ghost_has_ghost_rotr_u32 1
    #endif
#endif

/*
 * GCC does not support __builtin_rotateright32. Instead GCC recognizes the
 * following code and converts it to a rotate instruction where supported.
 *
 * Other compilers may not optimize this but will at least compile it to
 * correct behaviour. This correctly handles any value for bits without the
 * undefined behaviour of downshifting out of range.
 *
 *     https://blog.regehr.org/archives/1063
 */
#ifndef ghost_has_ghost_rotr_u32
    #include "ghost/impl/ghost_impl_inline.h"
    #include "ghost/language/ghost_static_cast.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_inline
    ghost_uint32_t ghost_rotr_u32(ghost_uint32_t ghost_impl_v_value, unsigned int ghost_impl_v_bits) {
        ghost_impl_v_bits &= (32 - 1);
        return ghost_static_cast(ghost_uint32_t, (ghost_impl_v_value >> ghost_impl_v_bits) |
                (ghost_impl_v_value << ((-ghost_impl_v_bits) & (32 - 1))));
    }
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_rotr_u32 1
#endif

#endif
