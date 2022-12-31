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

#include "ghost/format/ghost_format_z.h"

#ifndef ghost_has_GHOST_PRIdZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_PRIdZ."
#endif
#ifndef ghost_has_GHOST_PRIiZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_PRIiZ."
#endif
#ifndef ghost_has_GHOST_PRIuZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_PRIuZ."
#endif
#ifndef ghost_has_GHOST_PRIoZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_PRIoZ."
#endif
#ifndef ghost_has_GHOST_PRIxZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_PRIxZ."
#endif
#ifndef ghost_has_GHOST_PRIXZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_PRIXZ."
#endif
#ifndef ghost_has_GHOST_SCNdZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_SCNdZ."
#endif
#ifndef ghost_has_GHOST_SCNiZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_SCNiZ."
#endif
#ifndef ghost_has_GHOST_SCNuZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_SCNuZ."
#endif
#ifndef ghost_has_GHOST_SCNoZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_SCNoZ."
#endif
#ifndef ghost_has_GHOST_SCNxZ
    #error "ghost/format/ghost_format_z.h must define ghost_has_GHOST_SCNxZ."
#endif

#include "test_common.h"

#include "ghost/format/ghost_snprintf.h"
#include "ghost/format/ghost_sscanf.h"
#include "ghost/type/size_t/ghost_size_t.h"
#include "ghost/language/ghost_static_cast.h"

/* We'll do our signed tests with ghost_ssize_t if it's the same width as
 * ghost_size_t; otherwise we won't bother. */
#include "ghost/type/ssize_t/ghost_ssize_t.h"
#include "ghost/type/ssize_t/ghost_ssize_width.h"
#ifdef TEST_GHOST_FORMAT_Z_USE_SSIZE_T
    #error
#endif
#if ghost_has(ghost_ssize_t) && defined(GHOST_SSIZE_WIDTH) && defined(GHOST_SIZE_WIDTH)
    #if GHOST_SSIZE_WIDTH == GHOST_SIZE_WIDTH
        #define TEST_GHOST_FORMAT_Z_USE_SSIZE_T
    #endif
#endif

#if ghost_has(ghost_snprintf)
    #if ghost_has_GHOST_PRIdZ && defined(TEST_GHOST_FORMAT_Z_USE_SSIZE_T)
        mirror(/*suffix("GHOST_PRIdZ")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIdZ, ghost_static_cast(ghost_ssize_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIiZ && defined(TEST_GHOST_FORMAT_Z_USE_SSIZE_T)
        mirror(/*suffix("GHOST_PRIiZ")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIiZ, ghost_static_cast(ghost_ssize_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIuZ
        mirror(/*suffix("GHOST_PRIuZ")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIuZ, ghost_static_cast(ghost_size_t, 1234)));
            mirror_eq_s(buf, "1234");
        }
    #endif

    #if ghost_has_GHOST_PRIoZ
        mirror(/*suffix("GHOST_PRIoZ")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIoZ, ghost_static_cast(ghost_size_t, 1234)));
            mirror_eq_s(buf, "2322");
        }
    #endif

    #if ghost_has_GHOST_PRIxZ
        mirror(/*suffix("GHOST_PRIxZ")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIxZ, ghost_static_cast(ghost_size_t, 1234)));
            mirror_eq_s(buf, "4d2");
        }
    #endif

    #if ghost_has_GHOST_PRIXZ
        mirror(/*suffix("GHOST_PRIXZ")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIXZ, ghost_static_cast(ghost_size_t, 1234)));
            mirror_eq_s(buf, "4D2");
        }
    #endif
#endif

#if ghost_has(ghost_sscanf)
    #if ghost_has_GHOST_SCNdZ && defined(TEST_GHOST_FORMAT_Z_USE_SSIZE_T)
        mirror(/*suffix("GHOST_SCNdZ")*/) {
            ghost_ssize_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNdZ, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_ssize_t, -1234));
        }
    #endif

    #if ghost_has_GHOST_SCNiZ && defined(TEST_GHOST_FORMAT_Z_USE_SSIZE_T)
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiZ")*/) {
            ghost_ssize_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNiZ, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_ssize_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNiZ && defined(TEST_GHOST_FORMAT_Z_USE_SSIZE_T)
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiZ")*/) {
            ghost_ssize_t val;
            mirror_eq_i(1, ghost_sscanf("-02322", "%" GHOST_SCNiZ, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_ssize_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNiZ && defined(TEST_GHOST_FORMAT_Z_USE_SSIZE_T)
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiZ")*/) {
            ghost_ssize_t val;
            mirror_eq_i(1, ghost_sscanf("-0X4D2", "%" GHOST_SCNiZ, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_ssize_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNoZ
        mirror(/*suffix("GHOST_SCNoZ")*/) {
            ghost_size_t val;
            mirror_eq_i(1, ghost_sscanf("2322", "%" GHOST_SCNoZ, &val));
            mirror_eq_z(val, ghost_static_cast(ghost_size_t, 1234u));
        }
    #endif

    #if ghost_has_GHOST_SCNxZ
        mirror(/*suffix("GHOST_SCNxZ")*/) {
            ghost_size_t val;
            mirror_eq_i(1, ghost_sscanf("4d2", "%" GHOST_SCNxZ, &val));
            mirror_eq_z(val, ghost_static_cast(ghost_size_t, 1234u));
        }
    #endif
#endif
