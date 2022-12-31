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

#include "ghost/serialization/load/ghost_load_be_u32.h"

#if !ghost_has_ghost_load_be_u32
    #error "ghost_load_be_u32 must exist"
#endif

#include "mirror/mirror.h"
#include "ghost/language/ghost_alignat.h"

mirror() {

    /* unalign the buffer to make sure it works unaligned
     * (use a long in a struct to align the buffer in case we can't directly
     * specify alignment)
     * TODO don't do this, just use one buffer and load/store at two different alignments in it */
    GHOST_SILENCE_ALIGN_PADDING
    struct {
        long x;
        #if ghost_has_ghost_alignat
        ghost_alignat(16)
        #endif
            unsigned char buffer[5];
    } s;
    unsigned char* p = s.buffer + 1;

    p[0] = 0x01u;
    p[1] = 0x02u;
    p[2] = 0x03u;
    p[3] = 0x04u;
    mirror_eq_u32(0x01020304u, ghost_load_be_u32(p));
}
