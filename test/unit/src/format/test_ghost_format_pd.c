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

#include "ghost/format/ghost_format_pd.h"

#ifndef ghost_has_GHOST_PRIdPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_PRIdPD."
#endif
#ifndef ghost_has_GHOST_PRIiPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_PRIiPD."
#endif
#ifndef ghost_has_GHOST_PRIuPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_PRIuPD."
#endif
#ifndef ghost_has_GHOST_PRIoPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_PRIoPD."
#endif
#ifndef ghost_has_GHOST_PRIxPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_PRIxPD."
#endif
#ifndef ghost_has_GHOST_PRIXPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_PRIXPD."
#endif
#ifndef ghost_has_GHOST_SCNdPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_SCNdPD."
#endif
#ifndef ghost_has_GHOST_SCNiPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_SCNiPD."
#endif
#ifndef ghost_has_GHOST_SCNuPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_SCNuPD."
#endif
#ifndef ghost_has_GHOST_SCNoPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_SCNoPD."
#endif
#ifndef ghost_has_GHOST_SCNxPD
    #error "ghost/format/ghost_format_pd.h must define ghost_has_GHOST_SCNxPD."
#endif

#include "test_common.h"

#include "ghost/format/ghost_snprintf.h"
#include "ghost/format/ghost_sscanf.h"
#include "ghost/type/ptrdiff_t/ghost_ptrdiff_t.h"
#include "ghost/language/ghost_static_cast.h"

/* TODO we don't have such a thing as ghost_uptrdiff_t (yet?) For now we just
 * hack it in where we know it matches size_t. */
/*#include "ghost/type/ghost_uptrdiff_t.h"*/
#include "ghost/detect/ghost_x86_32.h"
#include "ghost/detect/ghost_x86_64.h"
#if GHOST_X86_32 || GHOST_X86_64
    #include "ghost/type/size_t/ghost_size_t.h"
    typedef ghost_size_t ghost_uptrdiff_t;
    #define ghost_has_ghost_uptrdiff_t 1
#else
    #define ghost_has_ghost_uptrdiff_t 0
#endif

#if ghost_has(ghost_snprintf)
    #if ghost_has_GHOST_PRIdPD
        mirror(/*suffix("GHOST_PRIdPD")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIdPD, ghost_static_cast(ghost_ptrdiff_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIiPD
        mirror(/*suffix("GHOST_PRIiPD")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIiPD, ghost_static_cast(ghost_ptrdiff_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has(ghost_uptrdiff_t)
    #if ghost_has_GHOST_PRIuPD
        mirror(/*suffix("GHOST_PRIuPD")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIuPD, ghost_static_cast(ghost_uptrdiff_t, 1234)));
            mirror_eq_s(buf, "1234");
        }
    #endif

    #if ghost_has_GHOST_PRIoPD
        mirror(/*suffix("GHOST_PRIoPD")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIoPD, ghost_static_cast(ghost_uptrdiff_t, 1234)));
            mirror_eq_s(buf, "2322");
        }
    #endif

    #if ghost_has_GHOST_PRIxPD
        mirror(/*suffix("GHOST_PRIxPD")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIxPD, ghost_static_cast(ghost_uptrdiff_t, 1234)));
            mirror_eq_s(buf, "4d2");
        }
    #endif

    #if ghost_has_GHOST_PRIXPD
        mirror(/*suffix("GHOST_PRIXPD")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIXPD, ghost_static_cast(ghost_uptrdiff_t, 1234)));
            mirror_eq_s(buf, "4D2");
        }
    #endif
    #endif
#endif

#if ghost_has(ghost_sscanf)
    #if ghost_has_GHOST_SCNdPD
        mirror(/*suffix("GHOST_SCNdPD")*/) {
            ghost_ptrdiff_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNdPD, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_ptrdiff_t, -1234));
        }
    #endif

    #if ghost_has_GHOST_SCNiPD
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiPD")*/) {
            ghost_ptrdiff_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNiPD, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_ptrdiff_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNiPD
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiPD")*/) {
            ghost_ptrdiff_t val;
            mirror_eq_i(1, ghost_sscanf("-02322", "%" GHOST_SCNiPD, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_ptrdiff_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNiPD
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiPD")*/) {
            ghost_ptrdiff_t val;
            mirror_eq_i(1, ghost_sscanf("-0X4D2", "%" GHOST_SCNiPD, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_ptrdiff_t, -1234));
        }
        #endif
    #endif

    #if ghost_has(ghost_uptrdiff_t)
    #if ghost_has_GHOST_SCNoPD
        mirror(/*suffix("GHOST_SCNoPD")*/) {
            ghost_uptrdiff_t val;
            mirror_eq_i(1, ghost_sscanf("2322", "%" GHOST_SCNoPD, &val));
            mirror_eq_z(val, ghost_static_cast(ghost_ptrdiff_t, 1234));
        }
    #endif

    #if ghost_has_GHOST_SCNxPD
        mirror(/*suffix("GHOST_SCNxPD")*/) {
            ghost_uptrdiff_t val;
            mirror_eq_i(1, ghost_sscanf("4d2", "%" GHOST_SCNxPD, &val));
            mirror_eq_z(val, ghost_static_cast(ghost_ptrdiff_t, 1234));
        }
    #endif
    #endif
#endif
