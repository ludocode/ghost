# Containers

## Type Prefixes

The following names are used for containers:

- `vec` -- A vector (i.e. dynamic growable array.)
- `list` -- A doubly-linked list.
- `tlist` -- A tree list.
- `map` -- A tree map (i.e. associative array.)
- `mmap` -- A tree multimap.
- `hmap` -- A hash map.
- `set` -- A tree set.
- `hset` -- A hash set.

Each container has a type prefix indicating what types it stores. Maps have two prefixes, the key followed by the value. (These differ from the suffixes used by Ghost math and serialization functions.)

The following type prefixes are used for containers in `common/`:

- `i` -- `int`;
- `l` -- `int64_t` (which is either `long` or `long long` on virtually all modern platforms)
- `f` -- `float32_t`
- `d` -- `float64_t`
- `z` -- `size_t`
- `s` -- `const char*` strings (null-terminated and length-delimited, copied into the container)
- `v` -- `void*`, used for storing arbitrary heap-allocated objects

Additionally, the following prefixes are used for containers in `generic/` and `template/`:

- `g` -- A type-erased generic container of dynamic element size.
- `t` -- A templated container instantiated by macro.

For example:

- `ghost_ivec` -- a vector of `int`.
- `ghost_sset` -- a set of strings.
- `ghost_lvmap` -- a map of `int64_t` to `void*`, a useful map for storing objects keyed by id.
