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

/* Some weird bug in PCC 1.1.0 is causing it to not exit cleanly. For now we
 * just exit without cleanup. */
#ifdef __PCC__
    #include <stdio.h>
    #include <stdlib.h>
/*
        stdin = fdopen(0, "w");
        stdout = fdopen(1, "r");
        stderr = fdopen(2, "r");
        fprintf(stderr,"MAIN\n");
    }
    */

#if 0
    int fake_main(void);
    int main(void) {
        fprintf(stderr,"MAIN\n");
        fake_main();
        printf("Exiting\n");
        fflush(stdout);
        fflush(stderr);
        _Exit(EXIT_SUCCESS);
    }
    #define main fake_main
#endif
#endif

#include "mirror/runner/mirror_runner_internal.h"
