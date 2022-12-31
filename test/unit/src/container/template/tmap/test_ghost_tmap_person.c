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

#include "ghost/string/ghost_strcmp.h"

typedef struct person_t {
    const char* name;
    int age;
    ghost_iwbt_node_t node;
} person_t;

#define person_key(person) person->name
#if 1
#define person_compare ghost_strcmp
#else
#define person_compare(left, right, map) (__extension__({\
        printf("comparing %s %s\n",left,right); \
        ghost_strcmp(left, right);\
        }))
#endif

GHOST_TMAP(person_map, const char*, person_t, node,
        person_key, person_compare)

typedef int ghost_impl_chibicc_unused1; /* chibicc workaround: https://github.com/rui314/chibicc/issues/99 */

#include "mirror/mirror.h"
#include "ghost/language/ghost_zero_init.h"

mirror() {
    person_map_t map;

    person_t alice = {"Alice", 31, GHOST_ZERO_INIT};
    person_t bob = {"Bob", 28, GHOST_ZERO_INIT};
    person_t carol = {"Carol", 42, GHOST_ZERO_INIT};
    person_t dave = {"Dave", 71, GHOST_ZERO_INIT};
    person_t eve = {"Eve", 8, GHOST_ZERO_INIT};

    person_map_clear(&map);

    person_map_insert(&map, &alice);
    person_map_insert(&map, &dave);
    person_map_insert(&map, &bob);
    person_map_insert(&map, &eve);
    person_map_insert(&map, &carol);

    /*ghost_iwbt_print(&map.tree); */

    mirror_check(person_map_find(&map, "Alice") != ghost_null);
    mirror_check(person_map_find(&map, "Bob") != ghost_null);
    mirror_check(person_map_find(&map, "Carol") != ghost_null);
    mirror_check(person_map_find(&map, "Dave") != ghost_null);
    mirror_check(person_map_find(&map, "Eve") != ghost_null);
    mirror_check(person_map_count(&map) == 5);

    person_map_remove_key(&map, "Bob");

    mirror_check(person_map_find(&map, "Alice") != ghost_null);
    mirror_check(person_map_find(&map, "Bob") == ghost_null);
    mirror_check(person_map_find(&map, "Carol") != ghost_null);
    mirror_check(person_map_find(&map, "Dave") != ghost_null);
    mirror_check(person_map_find(&map, "Eve") != ghost_null);
    mirror_check(person_map_count(&map) == 4);

    person_map_remove(&map, &eve);

    mirror_check(person_map_find(&map, "Alice") != ghost_null);
    mirror_check(person_map_find(&map, "Bob") == ghost_null);
    mirror_check(person_map_find(&map, "Carol") != ghost_null);
    mirror_check(person_map_find(&map, "Dave") != ghost_null);
    mirror_check(person_map_find(&map, "Eve") == ghost_null);
    mirror_check(person_map_count(&map) == 3);

    person_map_remove(&map, &carol);
    person_map_remove(&map, &dave);
    person_map_remove(&map, &alice);
    mirror_check(person_map_count(&map) == 0);
    mirror_check(person_map_is_empty(&map));
}
