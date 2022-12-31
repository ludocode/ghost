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

#include "ghost/format/ghost_format_i8.h"

#ifndef ghost_has_GHOST_PRId8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_PRId8."
#endif
#ifndef ghost_has_GHOST_PRIi8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_PRIi8."
#endif
#ifndef ghost_has_GHOST_PRIu8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_PRIu8."
#endif
#ifndef ghost_has_GHOST_PRIo8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_PRIo8."
#endif
#ifndef ghost_has_GHOST_PRIx8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_PRIx8."
#endif
#ifndef ghost_has_GHOST_PRIX8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_PRIX8."
#endif
#ifndef ghost_has_GHOST_SCNd8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_SCNd8."
#endif
#ifndef ghost_has_GHOST_SCNi8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_SCNi8."
#endif
#ifndef ghost_has_GHOST_SCNu8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_SCNu8."
#endif
#ifndef ghost_has_GHOST_SCNo8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_SCNo8."
#endif
#ifndef ghost_has_GHOST_SCNx8
    #error "ghost/format/ghost_format_i8.h must define ghost_has_GHOST_SCNx8."
#endif

#include "test_common.h"

#include "ghost/format/ghost_snprintf.h"
#include "ghost/format/ghost_sscanf.h"
#include "ghost/type/int8_t/ghost_int8_t.h"
#include "ghost/type/uint8_t/ghost_uint8_t.h"
#include "ghost/language/ghost_static_cast.h"

#if ghost_has(ghost_snprintf)
    #if ghost_has_GHOST_PRId8
        mirror(/*suffix("GHOST_PRId8")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRId8, ghost_static_cast(ghost_int8_t, -123)));
            mirror_eq_s(buf, "-123");
        }
    #endif

    #if ghost_has_GHOST_PRIi8
        mirror(/*suffix("GHOST_PRIi8")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIi8, ghost_static_cast(ghost_int8_t, -123)));
            mirror_eq_s(buf, "-123");
        }
    #endif

    #if ghost_has_GHOST_PRIu8
        mirror(/*suffix("GHOST_PRIu8")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIu8, ghost_static_cast(ghost_uint8_t, 123)));
            mirror_eq_s(buf, "123");
        }
    #endif

    #if ghost_has_GHOST_PRIo8
        mirror(/*suffix("GHOST_PRIo8")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIo8, ghost_static_cast(ghost_uint8_t, 123)));
            mirror_eq_s(buf, "173");
        }
    #endif

    #if ghost_has_GHOST_PRIx8
        mirror(/*suffix("GHOST_PRIx8")*/) {
            char buf[128];
            mirror_eq_i(2, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIx8, ghost_static_cast(ghost_uint8_t, 123)));
            mirror_eq_s(buf, "7b");
        }
    #endif

    #if ghost_has_GHOST_PRIX8
        mirror(/*suffix("GHOST_PRIX8")*/) {
            char buf[128];
            mirror_eq_i(2, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIX8, ghost_static_cast(ghost_uint8_t, 123)));
            mirror_eq_s(buf, "7B");
        }
    #endif
#endif

#if ghost_has(ghost_sscanf)
    #if ghost_has_GHOST_SCNd8
        mirror(/*suffix("GHOST_SCNd8")*/) {
            ghost_int8_t val;
            mirror_eq_i(1, ghost_sscanf("-123", "%" GHOST_SCNd8, &val));
            mirror_eq_i8(val, ghost_static_cast(ghost_int8_t, -123));
        }
    #endif

    #if ghost_has_GHOST_SCNi8
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi8")*/) {
            ghost_int8_t val;
            mirror_eq_i(1, ghost_sscanf("-123", "%" GHOST_SCNi8, &val));
            mirror_eq_i8(val, ghost_static_cast(ghost_int8_t, -123));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNi8
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi8")*/) {
            ghost_int8_t val;
            mirror_eq_i(1, ghost_sscanf("-0173", "%" GHOST_SCNi8, &val));
            mirror_eq_i8(val, ghost_static_cast(ghost_int8_t, -123));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNi8
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi8")*/) {
            ghost_int8_t val;
            mirror_eq_i(1, ghost_sscanf("-0X7B", "%" GHOST_SCNi8, &val));
            mirror_eq_i8(val, ghost_static_cast(ghost_int8_t, -123));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNo8
        mirror(/*suffix("GHOST_SCNo8")*/) {
            ghost_uint8_t val;
            mirror_eq_i(1, ghost_sscanf("173", "%" GHOST_SCNo8, &val));
            mirror_eq_u8(val, ghost_static_cast(ghost_uint8_t, 123));
        }
    #endif

    #if ghost_has_GHOST_SCNx8
        mirror(/*suffix("GHOST_SCNx8")*/) {
            ghost_uint8_t val;
            mirror_eq_i(1, ghost_sscanf("7b", "%" GHOST_SCNx8, &val));
            mirror_eq_u8(val, ghost_static_cast(ghost_uint8_t, 123));
        }
    #endif
#endif
