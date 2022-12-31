#!/bin/bash

# MIT No Attribution
#
# Copyright (c) 2022 Fraser Heavy Software
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

# Given a size_t implementation of a math function, generates all other math
# functions via search and replace.
#
# Note that this is just to generate the starting points. Math functions need
# to be customized per-type:
#
# - Compiler intrinsics can be used where possible which can require
#   significant per-type customization
#
# - For functions with plain C fallbacks that involve a lot of bit twiddling,
#   basic type functions sometimes wrap fixed-width functions

#set -x

f=$1

if [ "$f" = "" ]; then
    echo "no file!"
    exit 1
fi

gen() {
    local normal_type="$1"
    local ghost_type="$2"
    local ghost_file="$3"
    local suffix="$4"
    local ghost_upper_prefix="$5"
    local uppersuffix="$(echo $suffix | tr [:lower:] [:upper:])"

    local d=$(echo $f|sed "s/_z\>/_$suffix/")
    if [ -e "$d" ]; then
        echo "Skipping $d"
        return
    fi

    echo "Generating $d"
    cp $f $d
    sed -i "s/ghost_size_t\.h/$ghost_file.h/g" $d
    sed -i "s/GHOST_SIZE_/${ghost_upper_prefix}_/g" $d
    #cat $d
    # for `ghost_has_##type` we use the filename, not the ghost type (they
    # sometimes differ.)
    sed -i "s/ghost_has_ghost_size_t/ghost_has_$ghost_file/g" $d
    sed -i "s/ghost_has(ghost_size_t)/ghost_has_$ghost_file/g" $d
    #cat $d
    sed -i "s/ghost_size_t/$ghost_type/g" $d
    #cat $d
    sed -i "s/\<size_t/$normal_type/g" $d
    #cat $d
    sed -i "s/_z\>/_$suffix/g" $d
    #cat $d
    sed -i "s/_Z_/_${uppersuffix}_/g" $d
    #cat $d
}

gen char char ghost_char c GHOST_CHAR
gen short short ghost_short h GHOST_SHORT
gen int int ghost_int i GHOST_INT
gen long long ghost_long l GHOST_LONG
gen "long long" ghost_llong ghost_llong ll GHOST_LLONG
gen "signed char" "signed char" ghost_schar sc GHOST_SCHAR
gen "unsigned char" "unsigned char" ghost_uchar uc GHOST_UCHAR
gen "unsigned short" "unsigned short" ghost_ushort uh GHOST_USHORT
gen "unsigned" "unsigned" ghost_uint u GHOST_UINT
gen "unsigned long" "unsigned long" ghost_ulong ul GHOST_ULONG
gen "unsigned long long" ghost_ullong ghost_ullong ull GHOST_ULLONG

gen ssize_t ghost_ssize_t ghost_ssize_t sz GHOST_SSIZE
gen intptr_t ghost_intptr_t ghost_intptr_t ip GHOST_INTPTR
gen uintptr_t ghost_uintptr_t ghost_uintptr_t up GHOST_UINTPTR
gen ptrdiff_t ghost_ptrdiff_t ghost_ptrdiff_t pd GHOST_PTRDIFF

gen int8_t ghost_int8_t ghost_int8_t i8 GHOST_INT8
gen int16_t ghost_int16_t ghost_int16_t i16 GHOST_INT16
gen int32_t ghost_int32_t ghost_int32_t i32 GHOST_INT32
gen int64_t ghost_int64_t ghost_int64_t i64 GHOST_INT64
#gen int128_t ghost_int128_t ghost_int128_t i128 GHOST_INT128
gen uint8_t ghost_uint8_t ghost_uint8_t u8 GHOST_UINT8
gen uint16_t ghost_uint16_t ghost_uint16_t u16 GHOST_UINT16
gen uint32_t ghost_uint32_t ghost_uint32_t u32 GHOST_UINT32
gen uint64_t ghost_uint64_t ghost_uint64_t u64 GHOST_UINT64
#gen uint128_t ghost_uint128_t ghost_uint128_t u128 GHOST_UINT128

gen int_least8_t ghost_int_least8_t ghost_int_least8_t il8 GHOST_INT_LEAST8
gen int_least16_t ghost_int_least16_t ghost_int_least16_t il16 GHOST_INT_LEAST16
gen int_least32_t ghost_int_least32_t ghost_int_least32_t il32 GHOST_INT_LEAST32
gen int_least64_t ghost_int_least64_t ghost_int_least64_t il64 GHOST_INT_LEAST64
#gen int_least128_t ghost_int_least128_t ghost_int_least128_t il128 GHOST_INT_LEAST128
gen uint_least8_t ghost_uint_least8_t ghost_uint_least8_t ul8 GHOST_UINT_LEAST8
gen uint_least16_t ghost_uint_least16_t ghost_uint_least16_t ul16 GHOST_UINT_LEAST16
gen uint_least32_t ghost_uint_least32_t ghost_uint_least32_t ul32 GHOST_UINT_LEAST32
gen uint_least64_t ghost_uint_least64_t ghost_uint_least64_t ul64 GHOST_UINT_LEAST64
#gen uint_least128_t ghost_uint_least128_t ghost_uint_least128_t ul128 GHOST_UINT_LEAST128

gen float float ghost_float f GHOST_FLOAT
gen double double ghost_double d GHOST_DOUBLE
gen "long double" "long double" ghost_ldouble ld GHOST_LDOUBLE
gen float32_t ghost_float32_t ghost_float32_t f32 GHOST_FLOAT32
gen float64_t ghost_float64_t ghost_float64_t f64 GHOST_FLOAT64

gen char8_t ghost_char8_t ghost_char8_t c8 GHOST_CHAR8
gen char16_t ghost_char16_t ghost_char16_t c16 GHOST_CHAR16
gen char32_t ghost_char32_t ghost_char32_t c32 GHOST_CHAR32

# complex numbers and decimals are not implemented yet
#gen "ghost_cfloat_t" "ghost_cfloat_t" ghost_cfloat cf
#gen "ghost_cdouble_t" "ghost_cdouble_t" ghost_cdouble cd
#gen "ghost_cldouble_t" "ghost_cldouble_t" ghost_cldouble cld
#gen "ghost_cfloat32_t" "ghost_cfloat32_t" ghost_float32_t f32
#gen "ghost_cfloat64_t" "ghost_cfloat64_t" ghost_float64_t f64

