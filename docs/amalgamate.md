# Amalgamating Ghost

Suppose you'd like to use Ghost for your library but you don't want a hard dependency on it. Ghost provides a way for you to amalgamate all of the Ghost headers you use and prefix all of the identifiers in order to generate a namespaced platform header for your library.

This relies on a novel property of Ghost: any header can be included on any platform. If the platform doesn't have the required features to implement a feature in Ghost, that feature (and any dependent features) will simply be disabled.

## Simple Amalgamation

Let's say you want to use `strdup()` in your library. It's been in POSIX since 2008 and it'll be in C23 so this should be easy, right? Haha, no. This function can be annoying to port, especially if you don't control the compiler flags of whoever will be including your library.

Linux libcs won't declare `strdup()` when compiling with `-std=c11` without a defined feature flag like `_POSIX_C_SOURCE` or `_GNU_SOURCE`. Windows supports `strdup()` but throws a deprecation warning because it wants you to use `_strdup()`. Many esoteric C platforms won't support it at all. The BSDs and macOS support it natively, so that's nice... unless you want your library to have a customizable `malloc()`, in which case you need `strdup()` to use it. If you intend to support any platforms that don't define `strdup()` you need a fallback implementation in plain C.

All of this is a huge pain, and this is just one function! Just about every C feature you can imagine has its own unique platform-specific annoyances. (This is in fact why I created Ghost, because I was tired of reinventing this crap in every library.)

Luckily, Ghost provides [`ghost_strdup()`](../include/ghost/malloc/ghost_strdup.h) to handle all of this for you. Perfect! Except, you probably don't want your library to depend on some other library just to give you this one function.

Ghost provides a way to generate your own header that contains this function. Say your library is called "foo". Write a file called `foo_generate_ghost.c` containing this line:

```c
#include "ghost/malloc/ghost_strdup.h"
```

Next, run Ghost's amalgamate script on it:

```sh
tools/amalgamate.py -i foo_generate_ghost.c -o foo_ghost.h -p foo
```

Take a look at the resulting `foo_ghost.h`. It contains all of the parts of Ghost necessary to define `foo_ghost_strdup()`.

This will be a lot more than you might expect! Scroll to the bottom to find `ghost/malloc/ghost_strdup.h`. Starting from the bottom and working our way up:

- There is a fallback implementation in plain C used if the platform doesn't have `strdup()` or if you're using a custom allocator.

- There is boilerplate to link against Linux libc `strdup()` even if `_POSIX_C_SOURCE` or `_GNU_SOURCE` isn't defined.

- There are wrappers for Windows `_strdup()` and the GNU compiler intrinsic `__builtin_strdup()`.

- There are wrappers for `foo_ghost_strlen()` and `foo_ghost_memcpy()` required to implement a fallback `foo_ghost_strdup()`. These also have C fallbacks in case you're freestanding and don't have compiler builtins.

- There is what Ghost calls "header linkage", i.e. `foo_ghost_header_function`, a way to portably define non-static functions in header files in most compilers. This avoids bloating the resulting binaries with duplicate functions.

- There is support for `extern inline` and for manual emission of function definitions. You can optionally explicitly emit standalone definitions of all functions (inline and not) in exactly one translation unit, ensuring there is no code bloat even on non-optimizing C compilers.

- There are pedantic things like `foo_ghost_static_cast()` to make the code compile cleanly as C++ under `-Wold-style-cast` and other extreme warning flags. This is important if you're going to be using it in header files where you don't control how it will be compiled.

- There is all the scaffolding necessary to allow you to override `foo_ghost_malloc()` with a custom allocator and have `foo_ghost_strdup()` automatically use it.

- If there's no `malloc()`, `foo_ghost_strdup()` can't be implemented. As in normal Ghost, there is support for `#if foo_ghost_has(foo_ghost_strdup)` to see if it exists.

In other words, it is portable to the extreme: `foo_ghost_strdup()` will work automatically out-of-the-box on any wristwatch or toaster oven in the universe.

All Ghost identifiers are prefixed with `foo_ghost_` or `FOO_GHOST_` to avoid any namespace pollution. You can `#include` this header in your library and then `#define foo_strdup foo_ghost_strdup` to make it easier to use.

The amalgamated header has quite a lot of code, but most of this is shared across Ghost so it will grow less than linearly as you add more Ghost headers. Try adding more includes to `foo_generate_ghost.c` to see how it affects the result. For example, try adding `#include "ghost/malloc/ghost_free.h"` to complete the malloc configurability.

The amalgamation generator is currently unoptimized so the code is a lot longer than it could be. The script will eventually have an optimization pass to allow you to define assumptions (like "assume hosted" or "assume C99") and strip out unnecessary stuff. This is not implemented yet so for now amalgamations are pretty big. Modern C preprocessors are extremely fast so optimizing it is not yet a priority.

Ghost is released under a public-domain-equivalent license. You can ship this header with your library without attributing Ghost. You can even remove the license if you want. You can drop its contents in whole or in part into your own source file to make a single-file library.

## Optional Ghost Dependency

The above amalgamation strategy eliminates any dependency on Ghost but it makes your code use a fixed version of it internally. Ideally, the dependency on Ghost would be optional, this way it can automatically take advantage of future improvements in Ghost. You can instead include Ghost directly if possible and only fallback to the included amalgamation if the real Ghost is missing or too old.

I recommend checking if Ghost exists in two ways. One is if the user has defined `GHOST_AVAILABLE=1`, and the other is via `__has_include("ghost/core/ghost_version.h")`. If either of these pass, you can include the version header and check `GHOST_VERSION` to see if Ghost is new enough.

Here's an example platform header called `foo_platform.h`. We've added a few more `#include`s to show how it works.

```c
#ifndef FOO_PLATFORM_H
#define FOO_PLATFORM_H

// See if Ghost is available
#ifndef FOO_GHOST_AVAILABLE
    #ifdef GHOST_AVAILABLE
        #if GHOST_AVAILABLE
            #define FOO_GHOST_AVAILABLE 1
        #endif
    #else
        #ifdef __has_include
            #if __has_include("ghost/core/ghost_version.h")
                #define FOO_GHOST_AVAILABLE 1
            #endif
        #endif
    #endif
#endif
#ifndef FOO_GHOST_AVAILABLE
    #define FOO_GHOST_AVAILABLE 0
#endif

// If so, see if the version is new enough
#ifndef FOO_USE_GHOST
    #if FOO_GHOST_AVAILABLE
        #include "ghost/core/ghost_version.h"
        #if GHOST_VERSION >= 1 // or whatever version you need
            #define FOO_USE_GHOST 1
        #endif
    #endif
#endif
#ifndef FOO_USE_GHOST
    #define FOO_USE_GHOST 0
#endif

#if FOO_USE_GHOST
    // Use real Ghost
    #include "ghost/malloc/ghost_strdup.h"
    #include "ghost/string/ghost_strlcpy.h"
    #include "ghost/language/ghost_always_inline.h"
    #include "ghost/math/max/ghost_max_z.h"
    #define foo_strdup ghost_strdup
    #define foo_strlcpy ghost_strlcpy
    #define foo_always_inline ghost_always_inline
    #define foo_max_s ghost_max_z
#else
    // Use our amalgamated Ghost
    #include "foo_ghost.h"
    #define foo_strdup foo_ghost_strdup
    #define foo_strlcpy foo_ghost_strlcpy
    #define foo_always_inline foo_ghost_always_inline
    #define foo_max_s foo_ghost_max_z
#endif

#endif
```

You can pass this same header to Ghost's amalgamate script to generate your amalgamation. It only cares about the lines that start with `#include "ghost/`.

```
tools/amalgamate.py -i foo_platform.h -o foo_ghost.h -p foo
```

This is the strategy used by several of my other libraries, in particular [MPack](https://github.com/ludocode/mpack) and [Pottery](https://github.com/ludocode/pottery). (TODO branches not published yet, fix up above once complete)
