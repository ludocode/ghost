This folder contains container templates. Use these to instantiate strongly-typed containers.

Container templates define many functions for completeness. It is likely that you will use only a subset of them for a given template instantiation. Consider using compiler flags that eliminate unused functions, for example `-fvisibility=hidden`, `-ffunction-sections` and `-Wl,--gc-sections`. (Unfortunately it is not currently possible to instantiate only some functions and not others. This is partly because functions depend on others and they cannot instantiate their dependencies automatically.)

These container templates are focused on simplicity and versatility. If you need more advanced containers, try [Pottery](https://github.com/ludocode/pottery).

# Example

Suppose you'd like to store an intrusive map of people keyed by name, like this:

```c
typedef struct person_t {
    char* name;
    // ...
} person_t;
```

Add a `ghost_iwbt_node_t` field to the struct, define key and compare functions or macros, then define the map with `GHOST_TMAP()`. Like this:

```c
#include "ghost/container/template/tmap/ghost_tmap.h"

typedef struct person_t {
    const char* name;
    // ...
    ghost_iwbt_node_t node;
} person_t;

static inline const char* person_name(person_t* person) {
    return person->name;
}

GHOST_TMAP(
    person_map,    /* name for the map */
    const char*,   /* key type */
    person_t,      /* value type */
    node,          /* name of the field containing the node metadata */
    person_name,   /* function or macro to access the key */
    strcmp         /* function or macro to compare two keys */
)
```

You can then use it like this:

```c
person_map_t map;
person_map_clear(&map);

person_t alice = {"Alice", 31, GHOST_ZERO_INIT};
person_t bob = {"Bob", 28, GHOST_ZERO_INIT};
person_t eve = {"Eve", 8, GHOST_ZERO_INIT};

/* insert some persons */
person_map_insert(&map, &alice);
person_map_insert(&map, &bob);
person_map_insert(&map, &eve);
assert(person_map_count(&map) == 3);

/* iterate over the map */
person_t* person;
for (person = person_map_first(&map);
        person != NULL;
        person = person_map_next(&map, person))
{
    printf("Name: %s\n", person->name); // prints names in order
}

/* find a value by key */
person = person_map_find(&map, "Eve");
assert(person == &alice);

/* remove by key or value */
person_map_remove(&map, person); // removes Eve
person_map_remove_key(&map, "Eve"); // also removes Eve
```
