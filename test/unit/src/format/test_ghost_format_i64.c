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

#include "ghost/format/ghost_format_i64.h"

#ifndef ghost_has_GHOST_PRId64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_PRId64."
#endif
#ifndef ghost_has_GHOST_PRIi64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_PRIi64."
#endif
#ifndef ghost_has_GHOST_PRIu64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_PRIu64."
#endif
#ifndef ghost_has_GHOST_PRIo64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_PRIo64."
#endif
#ifndef ghost_has_GHOST_PRIx64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_PRIx64."
#endif
#ifndef ghost_has_GHOST_PRIX64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_PRIX64."
#endif
#ifndef ghost_has_GHOST_SCNd64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_SCNd64."
#endif
#ifndef ghost_has_GHOST_SCNi64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_SCNi64."
#endif
#ifndef ghost_has_GHOST_SCNu64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_SCNu64."
#endif
#ifndef ghost_has_GHOST_SCNo64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_SCNo64."
#endif
#ifndef ghost_has_GHOST_SCNx64
    #error "ghost/format/ghost_format_i64.h must define ghost_has_GHOST_SCNx64."
#endif

#include "test_common.h"

#include "ghost/format/ghost_snprintf.h"
#include "ghost/format/ghost_sscanf.h"
#include "ghost/type/int64_t/ghost_int64_t.h"
#include "ghost/type/uint64_t/ghost_uint64_t.h"
#include "ghost/language/ghost_static_cast.h"

#if ghost_has(ghost_snprintf)
    #if ghost_has_GHOST_PRId64
        mirror(/*suffix("GHOST_PRId64")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRId64, ghost_static_cast(ghost_int64_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIi64
        mirror(/*suffix("GHOST_PRIi64")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIi64, ghost_static_cast(ghost_int64_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIu64
        mirror(/*suffix("GHOST_PRIu64")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIu64, ghost_static_cast(ghost_uint64_t, 1234)));
            mirror_eq_s(buf, "1234");
        }
    #endif

    #if ghost_has_GHOST_PRIo64
        mirror(/*suffix("GHOST_PRIo64")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIo64, ghost_static_cast(ghost_uint64_t, 1234)));
            mirror_eq_s(buf, "2322");
        }
    #endif

    #if ghost_has_GHOST_PRIx64
        mirror(/*suffix("GHOST_PRIx64")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIx64, ghost_static_cast(ghost_uint64_t, 1234)));
            mirror_eq_s(buf, "4d2");
        }
    #endif

    #if ghost_has_GHOST_PRIX64
        mirror(/*suffix("GHOST_PRIX64")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIX64, ghost_static_cast(ghost_uint64_t, 1234)));
            mirror_eq_s(buf, "4D2");
        }
    #endif
#endif

#if ghost_has(ghost_sscanf)
    #if ghost_has_GHOST_SCNd64
        mirror(/*suffix("GHOST_SCNd64")*/) {
            ghost_int64_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNd64, &val));
            mirror_eq_i64(val, ghost_static_cast(ghost_int64_t, -1234));
        }
    #endif

    #if ghost_has_GHOST_SCNi64
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi64")*/) {
            ghost_int64_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNi64, &val));
            mirror_eq_i64(val, ghost_static_cast(ghost_int64_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNi64
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi64")*/) {
            ghost_int64_t val;
            mirror_eq_i(1, ghost_sscanf("-02322", "%" GHOST_SCNi64, &val));
            mirror_eq_i64(val, ghost_static_cast(ghost_int64_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNi64
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi64")*/) {
            ghost_int64_t val;
            mirror_eq_i(1, ghost_sscanf("-0X4D2", "%" GHOST_SCNi64, &val));
            mirror_eq_i64(val, ghost_static_cast(ghost_int64_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNo64
        mirror(/*suffix("GHOST_SCNo64")*/) {
            ghost_uint64_t val;
            mirror_eq_i(1, ghost_sscanf("2322", "%" GHOST_SCNo64, &val));
            mirror_eq_u64(val, ghost_static_cast(ghost_uint64_t, 1234));
        }
    #endif

    #if ghost_has_GHOST_SCNx64
        mirror(/*suffix("GHOST_SCNx64")*/) {
            ghost_uint64_t val;
            mirror_eq_i(1, ghost_sscanf("4d2", "%" GHOST_SCNx64, &val));
            mirror_eq_u64(val, ghost_static_cast(ghost_uint64_t, 1234));
        }
    #endif
#endif
