# Implementation Details

This document details how Ghost is actually implemented and the rationale for it.

## History

Every portable library in C shares the same problem: how do you abstract away the differences between platforms?

Compared to newer programming languages, C is not actually very portable in practice. The core language (with its standard library) is fairly portable but it doesn't provide enough to write useful programs. Operating systems provide many desirable but non-portable functions. Compilers provide all sorts of desirable but non-portable extensions. These differ between platforms and you'll need fallbacks when they aren't supported. Any non-trivial library will therefore have a decent amount of platform-specific code.

I've released several C libraries as source code. Each of these has a bespoke platform header (e.g. [`mpack-platform.h`](https://github.com/ludocode/mpack/blob/f4b9608ce06a569acf23a2a945fe754472dced75/src/mpack/mpack-platform.h#L941-L1836)) or set of headers (e.g. [`pottery/platform/`](https://github.com/ludocode/pottery/tree/develop/include/pottery/platform)) to paper over the differences between platforms. I hated doing this for every library but I was not willing to add a dependency on some portability library. I needed something I could amalgamate into each library, or at least something I could copy-paste from in order to ease porting.

Ghost is the result of many years of design work to achieve this goal. With Ghost now available, I hope to be able to release many more dependency-free tools and libraries in C, and I hope others will do the same.

## Design Goals

Ghost is designed to scale. Micro-includes maintain a usable organization as Ghost grows to hundreds or thousands of features. The standard header layout (see below) scales each feature to the possibly dozens of different potential implementations.

Ghost is designed to be explicit and strongly typed. Functions like [`ghost_max_*()`](../include/ghost/math/max/) or [`ghost_load_*()`](../include/ghost/serialization/load/) provide huge numbers of typed variations. Macros like [`ghost_alloc()`](../include/ghost/malloc/ghost_alloc.h) provide strongly typed allocations. The weak typing of C is a relic of an ancient era. Just as modern C no longer supports default int or implicit function declarations, Ghost shuns all implicit conversions (even from `void*`, as it isn't portable to C++.) Clear macros like [`ghost_bit_cast()`](../include/ghost/language/ghost_bit_cast.h) provide explicit alternatives to common hacks like strict aliasing violations and union type punning.

Ghost is designed to be amalgamated and embedded directly into source code. It is intended to be able to provide the platform abstraction for small dependency-free source-only libraries. For a header-only library composed of a bunch of include files, all of the library's Ghost usage can be just another header. For single-file libraries, a Ghost amalgamation can be embedded in it directly. A Ghost amalgamation is necessarily quite large, so for smaller libraries, platform abstractions from Ghost can be copy-pasted in, which is why it uses a public-domain-equivalent license.

Ghost is designed to be fixable. Its platform detection is based on heuristics which can sometimes be wrong. It is not expected to be perfect. Instead, Ghost goes to great lengths to let you work around its problems. All Ghost symbols can be overridden. If you are on a platform where Ghost incorrectly detects something, you don't have to patch Ghost. You can just pre-define whatever it got wrong, and Ghost will even use your correction in its other functions. All of its system header inclusions are wrapped so you can even correct it if it tries to `#include` a header that doesn't exist.

Ghost is aggressive in its platform targeting. Ghost targets the true ABI of the platform, not the headers, not the standards, not the compiler flags used, not the documentation nor anything else. It will link against functions like `strdup()` or `flockfile()` where it believes they exist even if the platform doesn't declare them. It will link against extensions like `qsort_r()` even on hostile libcs that give no indication that they exist (like musl.) You no longer need to worry about whether you're compiling with `-std=gnu99` or `-std=c99` or whether you've defined `_GNU_SOURCE` or `_POSIX_C_SOURCE`. You no longer need to even think about test compilation as a means of feature discovery.

Ghost is designed to be a documentation in and of itself, a catalog of the history of the many implementations of C. I hope it becomes almost a wiki of platform behaviour. Ghost is heavily commented; many files have more comments than code.

The best way to understand any particular feature is to just read the code. A good place to start is the headers in [`ghost/language/`](../include/ghost/language/), say [`ghost_alignof.h`](../include/ghost/language/ghost_alignof.h) for example.

## `ghost_has()`

Any symbol or feature declared by Ghost can be tested with `ghost_has()`. Ghost declares support for a feature, say `ghost_foo`, by defining `ghost_has_ghost_foo` to 1 or 0.

`ghost_has()` is implemented like this:

```c
#define ghost_has(x) ghost_has_##x
```

## Ghost implementation details

Any internal symbol defined by Ghost starts with `ghost_impl_` or `GHOST_IMPL_`. These symbols are not meant to be used by users; they may change at any time.

They generally forbid being configured by users. For example, [`ghost_format_i8.h`](../include/ghost/format/ghost_format_i8.h) checks whether `hh` and `ll` format length modifiers are supported like this: (TODO this is out of date)

```c
/* "hh" and "ll" aren't supported in ANSI C. */
#ifdef GHOST_IMPL_FORMAT_8_ALLOW_HH_LL
    #error
#endif
#ifdef __cplusplus
    #define GHOST_IMPL_FORMAT_8_ALLOW_HH_LL
#elif defined(__STDC_VERSION__)
    #include "ghost/language/ghost_stdc_version.h"
    #if GHOST_STDC_VERSION >= 199901L
        #define GHOST_IMPL_FORMAT_8_ALLOW_HH_LL
    #endif
#endif
```

The remaining code then uses `#ifdef GHOST_IMPL_FORMAT_8_ALLOW_HH_LL` to enable the use of `hh` and `ll`.

Function arguments and other internal variables are prefixed with `ghost_impl_v_`. This ensures no conflicts or shadowing warnings will arise with other `impl_` symbols or any user-defined macros.

## Ghost header layout

The typical layout of a Ghost header, say `ghost_foo.h`, starts like this:

```c
#include "ghost/ghost_core.h"

#if GHOST_DOCUMENTATION
#define ghost_has_ghost_foo 1
/**
 * Documentation for ghost_foo
 */
#endif
```

The `GHOST_DOCUMENTATION` block is used by documentation generator tools (e.g. Doxygen.) The line `#define ghost_has_ghost_foo 1` prevents the rest of the file from being parsed when generating documentation. For functions, a modern C prototype of `foo` will be provided within this block, as opposed to the more macro-heavy portable prototypes actually declared in the rest of the file.

What follows is a series of blocks like this:

```c
#ifndef ghost_has_ghost_foo
    #if (some implementation-specific conditions)
        // define ghost_foo as a macro, function, type, etc.
        #define ghost_has_ghost_foo 1
    #endif
#endif
```

All such blocks start with `#ifndef ghost_has_ghost_foo`. Each block attempts to detect platform support that could be used to provide `ghost_foo`. Once a definition is made, `ghost_has_ghost_foo` is defined to either 1 or 0, inhibiting any furthur detection.

The first such block is usually the override check:

```c
/* Allow override */
#ifndef ghost_has_ghost_foo
    #ifdef ghost_foo
        #define ghost_has_ghost_foo 1
    #endif
#endif
```

This allows the user to pre-define `ghost_foo`. We detect this and set `ghost_has_ghost_foo` to 1.

(The user can also define `ghost_foo` as a function or anything else, but if they do, they have to define `ghost_has_ghost_foo` to `1` themselves to tell Ghost not to define it.)

Following this is a series of blocks that test things like the operating system, compiler, language standard, etc. in order to find a platform definition of `ghost_foo`.

Finally, the header ends in one of two ways. If the symbol can be implemented in plain C (in all supported languages including C99, gnu89, C++98, etc.), or if it can be safely defined to nothing (for example if it's just an optimization hint), an unconditional block defines it like this:

```c
#ifndef ghost_has_ghost_foo
    // define ghost_foo in platform-independent C
    #define ghost_has_ghost_foo 1
#endif
```

Alternatively, if it's not possible to make a fallback in plain C, the feature is turned off:

```c
#ifndef ghost_has_ghost_foo
    #define ghost_has_ghost_foo 0
#endif
```

Sometimes separate blocks can be combined to make the code shorter. This is done wherever it does not sacrifice readability.

## Platform Detection

TODO some of this is wrong and needs to be fixed, need to get rid of `ghost_libc.h`

### Operating System (kernel and libc)

Ghost detects the OS kernel and libc by first including `<string.h`> via [`ghost/header/ghost_string_h.h`](../include/ghost/header/ghost_string_h.h). We do this in order to activate macros like `__GLIBC__` and to translate feature-test macros like `_GNU_SOURCE` into `_POSIX_C_SOURCE`.

(Lower-level headers like <stddef.h> are often provided by the compiler rather than the libc so they won't define `__GLIBC__`. `<string.h>` is always from the libc, it's been around since ancient times, and it's not likely to be omitted by a partial embedded libc (for example one that omits locales, datetimes, files, etc.))

Once `<string.h>` is included, we detect the OS and libc via the standard macros, e.g. `__linux__`, `__FreeBSD__`, `_WIN32`, `__APPLE__`, etc. Some libcs like glibc and musl have more complicated detection. Ghost provides these to users in `ghost/detect/`.

### POSIX

Ghost recognizes `__unix__` as well several UNIX-like systems that don't define this (such as macOS) in order to assume POSIX support. It also assumes POSIX support if `__has_include(<unistd.h>)` is true.

`<unistd.h>` may define `_POSIX_VERSION` but often platforms only define this and other POSIX symbols if `_POSIX_C_SOURCE` is defined by the compiler or user. GCC-style compilers don't tend to define this under strict ANSI modes (e.g. `-std=c99`.)

We want Ghost to pick up POSIX functions regardless which is why we try to detect it. We currently don't have much in the way of detecting the POSIX version without the above macros. What we have is wrapped in [`ghost/system/ghost_posix_version.h`](../include/ghost/system/ghost_posix_version.h) but it needs to be expanded. TODO this doesn't exist
