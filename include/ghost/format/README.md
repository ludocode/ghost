This folder wraps anything to do with `printf()` and `scanf()` format strings. It provides e.g.:

- The standard `<inttypes.h>` identifiers, e.g. `PRIu32`, are wrapped as e.g. `GHOST_PRIu32` in `ghost_format_32.h` and other files;
- Extensions such as `GHOST_PRIuZ` are provided to print `size_t` in `ghost_format_z.h` other files;
- Wrappers for functions like `asprintf()` in their respective files.

Note that some of these functions are considered "allocator functions". They depend on the value of `GHOST_MALLOC_SYSTEM` and may be synthesized if `ghost_malloc` and friends are overridden.

### Future Work

Newlib has a huge number of [`printf()` extensions described here](https://www.intel.com/content/www/us/en/docs/programmable/683282/current/definition-of-asnprintf.html). Eventually it would be nice to wrap many of these, or at least the popular ones. Most libcs, even other libcs for Linux, do not implement `asnprintf()`, `fiprintf()` and many others, but some of these functions like `asnprintf()` are implemented by other libraries like Gnulib.
