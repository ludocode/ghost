# String

This folder implements string and memory manipulation functions typically found in `<string.h>`, `<strings.h>` and similar headers.

Some functions in `<string.h>` and `<strings.h>` are elsewhere in Ghost. For example `strdup()` is with the allocator functions and `ffs()` is with the math functions.

This also doesn't contain string formatting functions (which are typically in `<stdio.h>`.) Functions like `printf()` and `scanf()` are in `ghost/format/` along with format specifiers and everything else related to string formatting.


## Unimplemented functions

The following functions are not implemented:

- `strcasecmp()`, `strcasecmp_l()`, `strcasestr()`, `strncasecmp()`, `strncasecmp_l()`

Case-insensitive string functions are not yet implemented in Ghost. It's not trivial to do locale-specific things in a platform-independent way. If these were to be implemented they may end up in a top-level `locale/` folder to abstract out `locale_t` and all locale-related functions. Wide string functions are also not yet implemented for similar reasons.

- glibc `strfry()`, `memfrob()`.

[glibc maintainers consider `strfry()` to be a joke](https://sourceware.org/bugzilla/show_bug.cgi?id=4403) and `memfrob()` obviously is as well. Don't use these functions.
