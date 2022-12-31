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

#include "ghost/format/ghost_format_ip.h"

#ifndef ghost_has_GHOST_PRIdP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_PRIdP."
#endif
#ifndef ghost_has_GHOST_PRIiP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_PRIiP."
#endif
#ifndef ghost_has_GHOST_PRIuP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_PRIuP."
#endif
#ifndef ghost_has_GHOST_PRIoP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_PRIoP."
#endif
#ifndef ghost_has_GHOST_PRIxP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_PRIxP."
#endif
#ifndef ghost_has_GHOST_PRIXP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_PRIXP."
#endif
#ifndef ghost_has_GHOST_SCNdP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_SCNdP."
#endif
#ifndef ghost_has_GHOST_SCNiP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_SCNiP."
#endif
#ifndef ghost_has_GHOST_SCNuP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_SCNuP."
#endif
#ifndef ghost_has_GHOST_SCNoP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_SCNoP."
#endif
#ifndef ghost_has_GHOST_SCNxP
    #error "ghost/format/ghost_format_ip.h must define ghost_has_GHOST_SCNxP."
#endif

#include "test_common.h"

#include "ghost/format/ghost_snprintf.h"
#include "ghost/format/ghost_sscanf.h"
#include "ghost/type/intptr_t/ghost_intptr_t.h"
#include "ghost/type/uintptr_t/ghost_uintptr_t.h"
#include "ghost/language/ghost_static_cast.h"

#if ghost_has(ghost_snprintf)
    #if ghost_has_GHOST_PRIdP
        mirror(/*suffix("GHOST_PRIdP")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIdP, ghost_static_cast(ghost_intptr_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIiP
        mirror(/*suffix("GHOST_PRIiP")*/) {
            char buf[128];
            mirror_eq_i(5, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIiP, ghost_static_cast(ghost_intptr_t, -1234)));
            mirror_eq_s(buf, "-1234");
        }
    #endif

    #if ghost_has_GHOST_PRIuP
        mirror(/*suffix("GHOST_PRIuP")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIuP, ghost_static_cast(ghost_uintptr_t, 1234)));
            mirror_eq_s(buf, "1234");
        }
    #endif

    #if ghost_has_GHOST_PRIoP
        mirror(/*suffix("GHOST_PRIoP")*/) {
            char buf[128];
            mirror_eq_i(4, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIoP, ghost_static_cast(ghost_uintptr_t, 1234)));
            mirror_eq_s(buf, "2322");
        }
    #endif

    #if ghost_has_GHOST_PRIxP
        mirror(/*suffix("GHOST_PRIxP")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIxP, ghost_static_cast(ghost_uintptr_t, 1234)));
            mirror_eq_s(buf, "4d2");
        }
    #endif

    #if ghost_has_GHOST_PRIXP
        mirror(/*suffix("GHOST_PRIXP")*/) {
            char buf[128];
            mirror_eq_i(3, ghost_snprintf(buf, sizeof(buf), "%" GHOST_PRIXP, ghost_static_cast(ghost_uintptr_t, 1234)));
            mirror_eq_s(buf, "4D2");
        }
    #endif
#endif

#if ghost_has(ghost_sscanf)
    #if ghost_has_GHOST_SCNdP
        mirror(/*suffix("GHOST_SCNdP")*/) {
            ghost_intptr_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNdP, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_intptr_t, -1234));
        }
    #endif

    #if ghost_has_GHOST_SCNiP
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiP")*/) {
            ghost_intptr_t val;
            mirror_eq_i(1, ghost_sscanf("-1234", "%" GHOST_SCNiP, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_intptr_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNiP
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiP")*/) {
            ghost_intptr_t val;
            mirror_eq_i(1, ghost_sscanf("-02322", "%" GHOST_SCNiP, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_intptr_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNiP
        /* For some reason "i" scanning doesn't seem to work on Cosmopolitan at the moment */
        #ifndef __COSMOPOLITAN__
        mirror(/*suffix("GHOST_SCNiP")*/) {
            ghost_intptr_t val;
            mirror_eq_i(1, ghost_sscanf("-0X4D2", "%" GHOST_SCNiP, &val));
            mirror_eq_sz(val, ghost_static_cast(ghost_intptr_t, -1234));
        }
        #endif
    #endif

    #if ghost_has_GHOST_SCNoP
        mirror(/*suffix("GHOST_SCNoP")*/) {
            ghost_uintptr_t val;
            mirror_eq_i(1, ghost_sscanf("2322", "%" GHOST_SCNoP, &val));
            mirror_eq_z(val, ghost_static_cast(ghost_intptr_t, 1234));
        }
    #endif

    #if ghost_has_GHOST_SCNxP
        mirror(/*suffix("GHOST_SCNxP")*/) {
            ghost_uintptr_t val;
            mirror_eq_i(1, ghost_sscanf("4d2", "%" GHOST_SCNxP, &val));
            mirror_eq_z(val, ghost_static_cast(ghost_intptr_t, 1234));
        }
    #endif
#endif
