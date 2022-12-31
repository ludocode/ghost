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

#include "ghost/container/template/ghost_tmap_all.h"

#if !ghost_has_GHOST_TMAP
    #error "GHOST_TMAP must exist."
#endif

#include "ghost/type/uint32_t/ghost_uint32_t.h"
#include "ghost/type/size_t/ghost_size_t.h"
#if ghost_has(ghost_uint32_t) && ghost_has(ghost_size_t)

typedef struct pair_t {
    ghost_uint32_t key;
    ghost_uint32_t value;
    ghost_iwbt_node_t node;
} pair_t;

#define pair_key(pair) pair->key
#if 1
#include "ghost/math/compare/ghost_compare_u32.h"
#define pair_compare ghost_compare_u32
/*#define pair_compare(left, right) ((left < right) ? -1 : ((left > right) ? 1 : 0))*/
#else
#define pair_compare(left, right) (__extension__({\
        printf("comparing %i %i\n",left,right); \
        ((left < right) ? -1 : ((left > right) ? -1 : 0)) \
        }))
#endif

GHOST_TMAP(pair_map, ghost_uint32_t, pair_t, node,
        pair_key, pair_compare)

typedef int ghost_impl_chibicc_unused2; /* chibicc workaround: https://github.com/rui314/chibicc/issues/99 */

#include "mirror/mirror.h"
#include "ghost/malloc/ghost_free.h"
#include "ghost/algorithm/knuth_hash/ghost_knuth_hash_u32.h"
#include "ghost/malloc/ghost_alloc.h"

#if ghost_has(ghost_alloc) && ghost_has(ghost_free)
mirror() {
    /* We use knuth_hash to generate some pseudorandom keys. The total matches
     * the keyspace so that we test some collisions. */
    ghost_size_t key_bits = 12;
    ghost_uint32_t total = 1u << key_bits;

    ghost_uint32_t dups = 0;
    ghost_uint32_t i;

    pair_map_t map;
    pair_map_clear(&map);

    for (i = 0; i < total; ++i) {
        ghost_uint32_t key = ghost_knuth_hash_u32(i, key_bits);
        /*printf("********************************\n"); */
        pair_t* pair = ghost_alloc(pair_t);
        /*printf("key %u\n",key); */
        pair->key = key;
        pair->value = i;
        pair = pair_map_insert(&map, pair);
        if (pair != ghost_null) {
            /* replace duplicate */
            ++dups;
            /*printf("duplicate!\n"); */
            mirror_check(pair->key == key);
            ghost_free(pair);
        }

        /*ghost_iwbt_print(&map.tree); */
    }
    /*printf("dups %i\n", dups);
     *printf("%zi\n",pair_map_count(&map)); */

    /* make sure we didn't accidentally insert duplicated elements */
    mirror_check(pair_map_count(&map) == total - dups);

    /*ghost_iwbt_print(&map.tree); */

    for (i = 0; i < total; ++i) {
        ghost_uint32_t key = ghost_knuth_hash_u32(i, key_bits);
        /*printf("********************************\n"); */
        pair_t* pair = pair_map_find(&map, key);
        if (pair) {
            mirror_check(pair->key == ghost_knuth_hash_u32(pair->value, key_bits));
            pair_map_remove(&map, pair);
            ghost_free(pair);
        } else {
            /*printf("was duplicate\n"); */
        }
    }
}
#endif

#endif
