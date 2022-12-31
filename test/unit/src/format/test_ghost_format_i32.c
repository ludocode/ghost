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

#include "ghost/format/ghost_format_i32.h"

#ifndef ghost_has_GHOST_PRId32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_PRId32."
#endif
#ifndef ghost_has_GHOST_PRIi32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_PRIi32."
#endif
#ifndef ghost_has_GHOST_PRIu32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_PRIu32."
#endif
#ifndef ghost_has_GHOST_PRIo32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_PRIo32."
#endif
#ifndef ghost_has_GHOST_PRIx32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_PRIx32."
#endif
#ifndef ghost_has_GHOST_PRIX32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_PRIX32."
#endif
#ifndef ghost_has_GHOST_SCNd32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_SCNd32."
#endif
#ifndef ghost_has_GHOST_SCNi32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_SCNi32."
#endif
#ifndef ghost_has_GHOST_SCNu32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_SCNu32."
#endif
#ifndef ghost_has_GHOST_SCNo32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_SCNo32."
#endif
#ifndef ghost_has_GHOST_SCNx32
    #error "ghost/format/ghost_format_i32.h must define ghost_has_GHOST_SCNx32."
#endif

#include "test_common.h"

#include "ghost/format/ghost_snprintf.h"
#include "ghost/format/ghost_sscanf.h"
#include "ghost/type/int32_t/ghost_int32_t.h"
#include "ghost/type/uint32_t/ghost_uint32_t.h"
#include "ghost/language/ghost_static_cast.h"

#if ghost_has(ghost_snprintf)
    #if ghost_has_GHOST_PRId32
        mirror(/*suffix("GHOST_PRId32")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRId32, ghost_static_cast(ghost_int32_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIi32
        mirror(/*suffix("GHOST_PRIi32")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIi32, ghost_static_cast(ghost_int32_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIu32
        mirror(/*suffix("GHOST_PRIu32")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIu32, ghost_static_cast(ghost_uint32_t, 1234)));
            mirror_eq_s(buf, "1234");
        }
    #endif

    #if ghost_has_GHOST_PRIo32
        mirror(/*suffix("GHOST_PRIo32")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIo32, ghost_static_cast(ghost_uint32_t, 1234)));
            mirror_eq_s(buf, "2322");
        }
    #endif

    #if ghost_has_GHOST_PRIx32
        mirror(/*suffix("GHOST_PRIx32")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIx32, ghost_static_cast(ghost_uint32_t, 1234)));
            mirror_eq_s(buf, "4d2");
        }
    #endif

    #if ghost_has_GHOST_PRIX32
        mirror(/*suffix("GHOST_PRIX32")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIX32, ghost_static_cast(ghost_uint32_t, 1234)));
            mirror_eq_s(buf, "4D2");
        }
    #endif
#endif

#if ghost_has(ghost_sscanf)
    #if ghost_has_GHOST_SCNd32
        mirror(/*suffix("GHOST_SCNd32")*/) {
            ghost_int32_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNd32, &val));
            mirror_eq_i32(val, ghost_static_cast(ghost_int32_t, -1234));
        }
    #endif

    #if ghost_has_GHOST_SCNi32
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi32")*/) {
            ghost_int32_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNi32, &val));
            mirror_eq_i32(val, ghost_static_cast(ghost_int32_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNi32
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi32")*/) {
            ghost_int32_t val;
            mirror_eq_i(1, ghost_sscanf("-02322", "%" GHOST_SCNi32, &val));
            mirror_eq_i32(val, ghost_static_cast(ghost_int32_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNi32
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi32")*/) {
            ghost_int32_t val;
            mirror_eq_i(1, ghost_sscanf("-0X4D2", "%" GHOST_SCNi32, &val));
            mirror_eq_i32(val, ghost_static_cast(ghost_int32_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNo32
        mirror(/*suffix("GHOST_SCNo32")*/) {
            ghost_uint32_t val;
            mirror_eq_i(1, ghost_sscanf("2322", "%" GHOST_SCNo32, &val));
            mirror_eq_u32(val, ghost_static_cast(ghost_uint32_t, 1234));
        }
    #endif

    #if ghost_has_GHOST_SCNx32
        mirror(/*suffix("GHOST_SCNx32")*/) {
            ghost_uint32_t val;
            mirror_eq_i(1, ghost_sscanf("4d2", "%" GHOST_SCNx32, &val));
            mirror_eq_u32(val, ghost_static_cast(ghost_uint32_t, 1234));
        }
    #endif
#endif
