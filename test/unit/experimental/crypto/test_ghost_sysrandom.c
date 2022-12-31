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

#include "ghost/crypto/ghost_sysrandom.h"

#include "test_common.h"

#include "ghost/language/ghost_zero_init.h"
#include "ghost/string/ghost_memset.h"
#include "ghost/string/ghost_memcmp.h"

#if ghost_has_ghost_sysrandom
mirror_1(it("should not result in zeroes")) {
    char a[16] = GHOST_ZERO_INIT;
    char b[16] = GHOST_ZERO_INIT;
    ghost_sysrandom(b, sizeof(b));
    mirror_ne_i(0, ghost_memcmp(a, b, sizeof(a)));
}

mirror_1(it("should give different results each time")) {
    char a[16] = GHOST_ZERO_INIT;
    char b[16] = GHOST_ZERO_INIT;
    ghost_sysrandom(a, sizeof(a));
    ghost_sysrandom(b, sizeof(b));
    mirror_ne_i(0, ghost_memcmp(a, b, sizeof(a)));
}

mirror_1(it("should provide lots of random data")) {
    size_t i;

    /* make sure we can generate a huge buffer. RSA keys for example can be
     * pretty big. This also tests looping for those systems that can only
     * provide 256 bytes at a time (e.g. OpenBSD.) */
    static char buf[8192];
    ghost_memset(buf, 0, sizeof(buf));
    ghost_sysrandom(buf, sizeof(buf));

    /* make sure each chunk of 8 bytes differs from the last */
    for (i = 8; i < sizeof(buf); i += 8) {
        mirror_ne_i(0, ghost_memcmp(buf + i, buf + i - 8, 8));
    }

    #if 0
    /* print bytes */
    for (i = 0; i < sizeof(buf); i+=16)
        printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
                (unsigned char)buf[i+0], (unsigned char)buf[i+1], (unsigned char)buf[i+2], (unsigned char)buf[i+3],
                (unsigned char)buf[i+4], (unsigned char)buf[i+5], (unsigned char)buf[i+6], (unsigned char)buf[i+7],
                (unsigned char)buf[i+8], (unsigned char)buf[i+9], (unsigned char)buf[i+10], (unsigned char)buf[i+11],
                (unsigned char)buf[i+12], (unsigned char)buf[i+13], (unsigned char)buf[i+14], (unsigned char)buf[i+15]);
    #endif
}
#endif
