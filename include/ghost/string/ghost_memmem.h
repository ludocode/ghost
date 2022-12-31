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

#ifndef GHOST_MEMMEM_H_INCLUDED
#define GHOST_MEMMEM_H_INCLUDED

#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
/**
 * Searches for needle in haystack, returning the first instance of it or null
 * if none is found.
 *
 * If the needle length is zero, haystack is returned.
 */
void* ghost_memmem(const void* haystack, size_t haystack_length,
        const void *needle, size_t needle_length);
#endif

#ifndef ghost_has_ghost_memmem
    #ifdef ghost_memmem
        #define ghost_has_ghost_memmem 1
    #endif
#endif

/* Linux libcs implement this. No other platforms seem to support it. */
#ifndef ghost_has_ghost_memmem
    #ifdef __linux__
        #include "ghost/header/c/ghost_string_h.h"
        #if ghost_has(ghost_string_h)
            #include "ghost/detect/ghost_libc.h"
            #if defined(__GLIBC__) || defined(__UCLIBC__) || defined(__NEWLIB__) || \
                    defined(__BIONIC__) || defined(__dietlibc__) || GHOST_MUSL

                /* It's only declared under _GNU_SOURCE so we need to declare
                 * it ourselves. */

                #include "ghost/type/size_t/ghost_size_t.h"
                #include "ghost/language/ghost_asm_label.h"
                #include "ghost/language/ghost_extern_c.h"
                #include "ghost/language/ghost_dllimport.h"
                #include "ghost/impl/ghost_impl_libc_asm.h"
                #include "ghost/impl/ghost_impl_libc_noexcept.h"

                #if GHOST_IMPL_LIBC_ASM
                    ghost_extern_c
                    ghost_dllimport
                    void* ghost_memmem(const void* vhaystack, ghost_size_t haystack_length,
                            const void *vneedle, ghost_size_t needle_length)
                        ghost_impl_libc_noexcept(ghost_impl_libc_asm("memmem"));
                #else
                    #include "ghost/impl/ghost_impl_always_inline.h"
                    #include "ghost/preprocessor/ghost_nothing.h"
                    GHOST_IMPL_FUNCTION_OPEN
                    ghost_impl_always_inline
                    void* ghost_memmem(const void* vhaystack, ghost_size_t haystack_length,
                        const void *vneedle, ghost_size_t needle_length)
                    {
                        ghost_dllimport
                        void* memmem(const void* vhaystack, ghost_size_t haystack_length,
                                const void *vneedle, ghost_size_t needle_length)
                            ghost_impl_libc_noexcept(GHOST_NOTHING);
                        return memmem(vhaystack, haystack_length, vneedle, needle_length);
                    }
                    GHOST_IMPL_FUNCTION_CLOSE
                #endif
                #define ghost_has_ghost_memmem 1
            #endif
        #endif
    #endif
#endif

/* Otherwise fallback to a plain C implementation. */
#ifndef ghost_has_ghost_memmem
    #include "ghost/impl/ghost_impl_function.h"
    #include "ghost/language/ghost_const_cast.h"
    #include "ghost/language/ghost_null.h"
    #include "ghost/language/ghost_static_cast.h"
    #include "ghost/math/min/ghost_min_z.h"
    #include "ghost/debug/ghost_assert.h"
    #include "ghost/string/ghost_bcmp.h"
    #include "ghost/string/ghost_memchr.h"
    #include "ghost/string/ghost_memset.h"
    #include "ghost/type/size_t/ghost_size_t.h"
    #include "ghost/type/uint8_t/ghost_uint8_t.h"
    GHOST_IMPL_FUNCTION_OPEN
    ghost_impl_function
    void* ghost_memmem(const void* vhaystack, ghost_size_t haystack_length,
        const void *vneedle, ghost_size_t needle_length)
    #if !GHOST_EMIT_DEFS
    ;
    #else
    {
        const ghost_uint8_t* haystack = ghost_static_cast(const ghost_uint8_t*, vhaystack);
        const ghost_uint8_t* needle = ghost_static_cast(const ghost_uint8_t*, vneedle);
        size_t i;

        /* Special cases */
        if (needle_length > haystack_length)
            return ghost_null;
        if (needle_length == 0)
            return ghost_const_cast(void*, vhaystack);
        if (needle_length == 1)
            return ghost_const_cast(void*, ghost_memchr(haystack, needle[0], haystack_length));

        /* This is a very simple Boyer-Moore-Horspool (BMH):
         *     https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm */

        /*
         * BMH may skip up to needle_length beyond the end of the haystack. We
         * make sure it won't overflow. This has a limitation that you can't
         * just blindly pass SIZE_MAX as the haystack_length if you're sure
         * the needle will be found.
         *
         * TODO is this right? doesn't look like it skips that way, and even if
         * it did, it's fine if not used in a comparison... can maybe pull out
         * this assert completely
         */
        ghost_assert(haystack_length + needle_length >= haystack_length, "haystack overflow");

        /* Compute skip table. We use a single byte for each skip entry so the
         * max skip is limited to 255 bytes. This uses relatively little stack
         * space. */
        {
            ghost_uint8_t max_skip = ghost_static_cast(ghost_uint8_t, ghost_min_z(255, needle_length));
            ghost_uint8_t skip[256];
            ghost_memset(skip, max_skip, sizeof(skip));
            for (i = 0; i < needle_length - 1; ++i)
                skip[needle[i]] = ghost_static_cast(ghost_uint8_t, ghost_min_z(255, needle_length - i - 1));

            /* Do the search */
            for (i = 0; i < haystack_length - needle_length + 1;) {
                if (ghost_bcmp(haystack + i, needle, needle_length) == 0)
                    return ghost_const_cast(ghost_uint8_t*, haystack + i);

                /* Jump ahead based on the skip value of the last character. */
                i += skip[haystack[i + needle_length - 1]];
            }
        }

        return ghost_null;
    }
    #endif
    GHOST_IMPL_FUNCTION_CLOSE
    #define ghost_has_ghost_memmem 1
#endif

/* TODO move this to a fuzz test */
#ifdef GHOST_IMPL_MEMMEM_FUZZ
#include <time.h>
#include <stdlib.h>
#include "ghost/debug/ghost_ensure.h"
int main(void) {
    extern void *memmem(const void *haystack, size_t haystacklen,
                    const void *needle, size_t needlelen);
    srand(1);
    for (size_t i = 0; i < 1000000; ++i) {
        uint8_t haystack[10000];
        uint8_t needle[10];
        size_t haystack_len = ((size_t)rand() % sizeof(haystack) + 1);
        size_t needle_len = ((size_t)rand() % sizeof(needle) + 1);
        size_t limit = 1 + ((size_t)rand() % 256);
        if (i % 10000 == 0) printf("step %i\n",i);
        for (size_t j = 0; j < haystack_len; ++j)
            haystack[j] = (uint8_t)((size_t)rand() % limit);
        for (size_t j = 0; j < needle_len; ++j)
            needle[j] = (uint8_t)((size_t)rand() % limit);
        void* p = memmem(haystack, haystack_len, needle, needle_len);
        void* q = ghost_memmem(haystack, haystack_len, needle, needle_len);
        #if 0
        if(p) printf("%zi\n",(size_t)((uint8_t*)p-haystack)); else printf("null\n");
        if(q) printf("%zi\n",(size_t)((uint8_t*)q-haystack)); else printf("null\n");
        #endif
        ghost_ensure(p == q);
    }
    printf("pass\n");
    return 0;
}
#endif

#endif
