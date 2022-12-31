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

/**
 * This template generates qsort test functions for a given qsort variant. The
 * test must define one of the following macros:
 *
 * - TEST_GHOST_QSORT_GNU
 * - TEST_GHOST_QSORT_BSD
 * - TEST_GHOST_QSORT_C11
 * - TEST_GHOST_QSORT_WIN
 * - TEST_GHOST_QSORT
 *
 * It can also define TEST_GHOST_QSORT_VARIANT to a string to append to the
 * test name (e.g. "$internal" for the force-internal variants.)
 */

#include "test_common.h"

#include "ghost/language/ghost_array_count.h"
#include "ghost/language/ghost_static_cast.h"
#include "ghost/language/ghost_discard.h"
#include "ghost/string/ghost_memcmp.h"

static int s_context = 7;

#if defined(TEST_GHOST_QSORT_GNU) || defined(TEST_GHOST_QSORT_C11)
static int mycompare(const void* pa, const void* pb, void* context)
#elif defined(TEST_GHOST_QSORT_BSD) || defined(TEST_GHOST_QSORT_WIN)
static int mycompare(void* context, const void* pa, const void* pb)
#elif defined(TEST_GHOST_QSORT)
static int mycompare(const void* pa, const void* pb)
#else
    #error
#endif
{
    int a;
    int b;
    #ifdef TEST_GHOST_QSORT
    ghost_discard(s_context);
    #else
    mirror_check(context == &s_context);
    #endif
    a = *ghost_static_cast(const int*, pa);
    b = *ghost_static_cast(const int*, pb);
    /*printf("comparing %i %i\n", a, b); */
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}

#if defined(TEST_GHOST_QSORT_GNU)
    #define TEST_QSORT(array, count, size) ghost_gnu_qsort_r(array, count, size, &mycompare, &s_context);
#elif defined(TEST_GHOST_QSORT_BSD)
    #define TEST_QSORT(array, count, size) ghost_bsd_qsort_r(array, count, size, &s_context, &mycompare);
#elif defined(TEST_GHOST_QSORT_WIN)
    #define TEST_QSORT(array, count, size) ghost_win_qsort_s(array, count, size, &mycompare, &s_context);
#elif defined(TEST_GHOST_QSORT_C11)
    #define TEST_QSORT(array, count, size) ghost_c11_qsort_s(array, count, size, &mycompare, &s_context);
#elif defined(TEST_GHOST_QSORT)
    #define TEST_QSORT(array, count, size) ghost_qsort(array, count, size, &mycompare);
#endif

#ifndef TEST_GHOST_QSORT_VARIANT
    #define TEST_GHOST_QSORT_VARIANT /*nothing*/
#endif

/*mirror_1(name(MIRROR_NAME TEST_GHOST_QSORT_VARIANT)) { */
mirror() {
    int expected[] = {1, 2, 3, 4, 4, 5, 6};
    int actual[] = {4, 1, 6, 4, 2, 5, 3};
    TEST_QSORT(actual, ghost_array_count(actual), sizeof(*actual));
    /*for (size_t i = 0; i < ghost_array_count(actual); ++i)
     *    printf("%i\n",actual[i]); */
    mirror_eq(0, ghost_memcmp(expected, actual, sizeof(expected)));
}
