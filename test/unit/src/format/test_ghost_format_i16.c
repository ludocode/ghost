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

#include "ghost/format/ghost_format_i16.h"

#ifndef ghost_has_GHOST_PRId16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_PRId16."
#endif
#ifndef ghost_has_GHOST_PRIi16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_PRIi16."
#endif
#ifndef ghost_has_GHOST_PRIu16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_PRIu16."
#endif
#ifndef ghost_has_GHOST_PRIo16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_PRIo16."
#endif
#ifndef ghost_has_GHOST_PRIx16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_PRIx16."
#endif
#ifndef ghost_has_GHOST_PRIX16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_PRIX16."
#endif
#ifndef ghost_has_GHOST_SCNd16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_SCNd16."
#endif
#ifndef ghost_has_GHOST_SCNi16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_SCNi16."
#endif
#ifndef ghost_has_GHOST_SCNu16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_SCNu16."
#endif
#ifndef ghost_has_GHOST_SCNo16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_SCNo16."
#endif
#ifndef ghost_has_GHOST_SCNx16
    #error "ghost/format/ghost_format_i16.h must define ghost_has_GHOST_SCNx16."
#endif

#include "test_common.h"

#include "ghost/format/ghost_snprintf.h"
#include "ghost/format/ghost_sscanf.h"
#include "ghost/type/int16_t/ghost_int16_t.h"
#include "ghost/type/uint16_t/ghost_uint16_t.h"
#include "ghost/language/ghost_static_cast.h"

#if ghost_has(ghost_snprintf)
    #if ghost_has_GHOST_PRId16
        mirror(/*suffix("GHOST_PRId16")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRId16, ghost_static_cast(ghost_int16_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIi16
        mirror(/*suffix("GHOST_PRIi16")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIi16, ghost_static_cast(ghost_int16_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIu16
        mirror(/*suffix("GHOST_PRIu16")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIu16, ghost_static_cast(ghost_uint16_t, 1234)));
            mirror_eq_s(buf, "1234");
        }
    #endif

    #if ghost_has_GHOST_PRIo16
        mirror(/*suffix("GHOST_PRIo16")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIo16, ghost_static_cast(ghost_uint16_t, 1234)));
            mirror_eq_s(buf, "2322");
        }
    #endif

    #if ghost_has_GHOST_PRIx16
        mirror(/*suffix("GHOST_PRIx16")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIx16, ghost_static_cast(ghost_uint16_t, 1234)));
            mirror_eq_s(buf, "4d2");
        }
    #endif

    #if ghost_has_GHOST_PRIX16
        mirror(/*suffix("GHOST_PRIX16")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIX16, ghost_static_cast(ghost_uint16_t, 1234)));
            mirror_eq_s(buf, "4D2");
        }
    #endif
#endif

#if ghost_has(ghost_sscanf)
    #if ghost_has_GHOST_SCNd16
        mirror(/*suffix("GHOST_SCNd16")*/) {
            ghost_int16_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNd16, &val));
            mirror_eq_i16(val, ghost_static_cast(ghost_int16_t, -1234));
        }
    #endif

    #if ghost_has_GHOST_SCNi16
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi16")*/) {
            ghost_int16_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNi16, &val));
            mirror_eq_i16(val, ghost_static_cast(ghost_int16_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNi16
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi16")*/) {
            ghost_int16_t val;
            mirror_eq_i(1, ghost_sscanf("-02322", "%" GHOST_SCNi16, &val));
            mirror_eq_i16(val, ghost_static_cast(ghost_int16_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNi16
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNi16")*/) {
            ghost_int16_t val;
            mirror_eq_i(1, ghost_sscanf("-0X4D2", "%" GHOST_SCNi16, &val));
            mirror_eq_i16(val, ghost_static_cast(ghost_int16_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNo16
        mirror(/*suffix("GHOST_SCNo16")*/) {
            ghost_uint16_t val;
            mirror_eq_i(1, ghost_sscanf("2322", "%" GHOST_SCNo16, &val));
            mirror_eq_u16(val, ghost_static_cast(ghost_uint16_t, 1234));
        }
    #endif

    #if ghost_has_GHOST_SCNx16
        mirror(/*suffix("GHOST_SCNx16")*/) {
            ghost_uint16_t val;
            mirror_eq_i(1, ghost_sscanf("4d2", "%" GHOST_SCNx16, &val));
            mirror_eq_u16(val, ghost_static_cast(ghost_uint16_t, 1234));
        }
    #endif
#endif
