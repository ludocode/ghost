This folder provides wrapped headers that work around platform differences and other problems.

You can include any of these headers on any platform. Ghost will include the real header only if it's available and will declare whether or not it was included.

For example, you can include `ghost/header/windows/ghost_windows_h.h` everywhere, then test whether `<Windows.h>` was actually included using `ghost_has(ghost_windows_h)`. It will be 1 if the header was included and 0 otherwise.

All Ghost header wrappers have a `_h` suffix in their name (in addition to the `.h` file extension), even for C++ headers that don't end in `.h`. This helps prevent conflicts with other Ghost features that have the same name.

## Implementation Notes

### Wrapping headers

Ghost does not wrap all headers here. If some headers are platform-specific and we don't have any other Ghost-specific code to wrap it, we'll just include it directly. For example when Ghost detects MSVC, it includes `<intrin.h>` directly in various places.

The only headers we wrap are those that are on many but not all platforms (like `<unistd.h>`) or that require safety wrapping (like `<Windows.h>`.) Unfortunately these rules mean we need to wrap almost all C standard library headers. Even some of those that are supposed to be available in freestanding are not available everywhere, and we want to wrap C++ support as well (see the section below.)

Moreover, with an amalgamated libc like Cosmopolitan, header files like `<string.h>` don't actually exist. On Cosmopolitan `ghost_has(ghost_string_h)` will still be 1 even though Ghost didn't actually include it because the contents of `<string.h>` are included in the amalgamation.

### `__has_include`

Ghost uses `__has_include` to try to determine whether headers exists.

Ghost has different fallbacks if `__has_include` does not exist. Sometimes it will assume the header exists, sometimes it will not, and sometimes it will use additional checks to try to determine whether it's safe to include it (typically checking `__STDC_HOSTED__` via `GHOST_HOSTED` among other things.)

Ghost checks for `__has_include` support in [`ghost/preprocessor/ghost_has_include.h`](../preprocessor/ghost_has_include.h) in order to exclude libraries that define it as a fallback. See the details in that file.

### C++ alternate headers

C++ has defined alternate header names for all of the C standard library headers. For example `<cstddef>` is defined as a C++ counterpart to `<stddef.h>`. The intention of these was to move all of the C standard library identifiers to the `std` namespace to avoid polluting the global namespace.

This was the rule in C++98. Unfortunately implementers never actually did it correctly (nor could they in many cases) so they eventually relaxed the rules to match reality. Now, the rule is that the C-style headers *must* put identifiers in the global namespace and *may* put identifiers in the `std` namespace, while the C++-style headers *must* put identifiers in the `std` namespace and *may* put identifiers in the global namespace.

For example, in C++11, `<stddef.h>` is guaranteed to define `::size_t` and may or may not define `std::size_t`. `<cstddef>` is the opposite: it is guaranteed to define `std::size_t` and may or may not define `::size_t` (thus defeating the purpose of `<cstddef>`.)

A major goal of Ghost is to maximize portability and consistency and avoid any platform incompatibilities, so we make sure all identifiers are in both namespaces. When compiling as C++, whenever we include a C header that also has a C++ counterpart, we include both.

Some additional discussion is here: https://stackoverflow.com/a/2118718
