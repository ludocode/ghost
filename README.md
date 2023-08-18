## Ghost

Ghost is a header-only portability library for C. It's a bit like a "Boost for C".

## Introduction

Ghost is useful for making extremely portable configure-free programs and libraries in C. Ghost wraps the ugly differences between language standards, compilers, operating systems and CPU architectures, and brings platform-specific extensions to all platforms wherever possible.

What behaviour do you need for `realloc(p, 0)`? Ghost has all the variations. Do you want your threads to return `int` or `void*`? Ghost has both. What prototype do you want for `qsort_r()`? Ghost implements them all. Use whichever you like on any platform.

Unlike portable runtimes like [Apache's](https://en.wikipedia.org/wiki/Apache_Portable_Runtime) or [glib](https://en.wikipedia.org/wiki/GLib), there is no runtime component to Ghost. It's composed entirely of macros and small inline functions that disappear at compile-time, delegating as much as possible to the platform to give you the smallest binaries and fastest code.

Ghost is released under a public-domain-equivalent license (MIT-0). You can include it as-is, copy-paste from it at will, use it as documentation or educational materials, or [amalgamate the parts you want](docs/amalgamate.md) into a single header namespaced to your project using the included tool.

Ghost makes C a truly "write once, compile anywhere" language: it's designed to *just work* out-of-the-box on all operating systems, with all compilers, in all language standards, with zero configuration. Ghost is the configure script killer. If you hate the autotools as much as I do, you just might like Ghost.

## Warning!

Ghost is in early development and is still experimental. I'm publishing it under the maxim "If you're not embarrassed when you ship your first version, you've waited too long."

Ghost has plain C fallbacks where possible so it should run on anything but tests are weak and full support is limited to popular or open source compilers and operating systems. A primary goal of Ghost is to work on any platform with a C compiler. I need your help to get it there.

Many parts of Ghost are poorly tested at the moment. I believe it can become very solid but right now it's probably full of bugs. Use it at your own risk.

## Getting Started

[Fetch the code](https://github.com/ludocode/ghost/archive/refs/heads/develop.tar.gz) and put `include/` on your include path. That's it!

To use a feature of Ghost, just include the header file for it. Ghost is broken up into micro-includes so you can use it for only a single feature if you want. Only those parts you actually include get compiled.

Ghost has zero namespace pollution, silences no global warnings, defines no platform configuration macros, and includes the minimum system headers required for only those features you use. It is safe to add to any codebase.

Take a look at the [Quick Tour](#quick-tour) below to see what Ghost can do.

## Supported Platforms

Ghost supports all standard versions of C, C++ and Objective-C. The following implementations have special support in Ghost:

|Compilers|Platforms|CPU Architectures|
|-|-|-|
|GCC (4+)<br>Clang (3.4+, Apple Clang, etc.)<br>Microsoft Visual C/C++ (2012+)<br>NVIDIA HPC (a.k.a. PGI) (22.5+)<br>[TinyCC](https://en.wikipedia.org/wiki/Tiny_C_Compiler) ([mob](https://repo.or.cz/w/tinycc.git) only)<br>[chibicc](https://github.com/rui314/chibicc)<br>[Kefir](https://github.com/protopopov1122/kefir)<br>[lacc](https://github.com/larmel/lacc/)<br>[cproc](https://sr.ht/~mcf/cproc/)<br>[PCC](http://pcc.ludd.ltu.se/)<br>[cparser](https://github.com/libfirm/cparser/) (*partial*)<br>[lcc](https://drh.github.io/lcc/) (*partial*)<br>[Digital Mars C/C++](https://www.digitalmars.com/download/freecompiler.html) (8.57+) (*partial*)|Linux (glibc, musl, etc.)<br>Windows (Vista+)<br>macOS<br>BSDs (FreeBSD, OpenBSD, etc.)<br>Android NDK (Bionic libc)<br>iOS<br>Arduino<br>Emscripten<br>[apε](https://justine.lol/ape.html)/[Cosmopolitan](https://justine.lol/cosmopolitan/index.html)|x86<br>x86\_64<br>ARM 32-bit (v7a)<br>ARM 64-bit (aarch64)<br>RISC-V (32-bit and 64-bit)<br>AVR<br>WebAssembly|

Even if not listed above, Ghost should work on any standard implementation of C. Any features that cannot be detected, worked around, or implemented by Ghost will be disabled, which you can test with the preprocessor.

## Quick Tour

All of Ghost's features are broken up into micro-includes. You can include individual headers to get only the features you want.

```c
#include "ghost/math/popcount/ghost_popcount_u64.h"
// We've included the minimum necessary to get ghost_popcount_u64().
uint64_t x = ghost_popcount_u64(27); // x == 4

#include "ghost/debug/ghost_static_assert.h"
// We've included the minimum necessary to get ghost_static_assert().
ghost_static_assert(sizeof(int) == 4);
```

You can also include large featuresets with Ghost's group headers. (Worried about compile times? No problem! C compiles *fast*. Compiling all >1000 Ghost headers in C takes less time than compiling `#include <iostream>` in C++.)

```c
#include "ghost/ghost_common.h"
// We've included a bunch of normal stuff that is used in typical C code:
// fixed-width types, string/memory functions, language extensions,
// malloc() and friends, a few math functions like ghost_min/max(), etc.

#include "ghost/ghost_thread_all.h"
// We've included all of Ghost's threading wrappers:
// - ghost_mutex_t, GHOST_MUTEX_INIT, ghost_mutex_lock(), etc.
// - ghost_condition_t, ghost_condition_wait(), ghost_condition_signal(), etc.
// - ghost_once_t, ghost_once(), etc.
// - ghost_*thread_create(), ghost_*thread_join(), etc.
```

You can include any Ghost header on any platform. Use `ghost_has(x)` to test whether the symbol or feature `x` exists.

```c
#include "ghost/language/ghost_typeof.h"
#if ghost_has(ghost_typeof)
    // We have ghost_typeof(). Use it as you would typeof().
#endif

#include "ghost/preprocessor/ghost_has_include.h"
#if ghost_has(ghost_has_include)
    // __has_include works (and it's not faked by some namespace-polluting
    // library.) Use __has_include() to see if a header exists.
#endif
```

You don't need to use Ghost's wrappers if you don't want to. You can just use it to help you include standard symbols. Ghost only wraps them in case the underlying types don't exist.

```c
#include "ghost/ghost_header_common.h"
// Ghost tried to include commonly used C headers: <stdlib.h>, <stdio.h>,
// <stdint.h>, <limits.h>, <inttypes.h>, etc. If you don't care about ancient
// platforms, you can just assume things like printf() and int32_t exist. Or,
// you can use Ghost to check:
#if ghost_has(ghost_stdint_h)
    // <stdint.h> was included. int32_t almost certainly exists.
#endif

#include "ghost/header/posix/ghost_pthread_h.h"
#if ghost_has(ghost_pthread_h)
    // <pthread.h> has been included. You can use POSIX threads directly.
#endif
```

Ghost's wrappers can be preferable because they enforce consistent behaviour on all platforms and language standards.

```c
#include "ghost/malloc/ghost_malloc.h"
// malloc() cannot be implicitly cast to a typed pointer in C++, but ghost_malloc() can.
foo_t* p = ghost_malloc(sizeof(foo_t)); // legal C++
// Want your C code to compile as C++?
#define malloc ghost_malloc
```

Where platforms differ, Ghost provides variations for each set of prototypes and behaviours. Use any of them on any platform.

```c
#include "ghost/malloc/ghost_malloc.h"
// malloc(0) varies by platform; ghost_malloc(0) always returns a unique
// allocation unless an error occurred.
void* p = ghost_malloc(...);
// Ghost also provides ghost_malloc_0null() for the opposite behaviour.

#include "ghost/malloc/ghost_realloc.h"
// realloc() with size 0 varies by platform and will be forbidden in C23.
// ghost_realloc() asserts in debug mode that size is not 0.
void* q = ghost_realloc(p, 0); // FATAL ERROR, assertion failed

#include "ghost/malloc/ghost_realloc_0alloc.h"
// This variant, ghost_realloc_0alloc(), always returns an allocated pointer on 0.
void* r = ghost_realloc_0alloc(p, 0); // r != NULL (unless allocation failed)
// Ghost also provides ghost_realloc_0null() and ghost_realloc_0free() for other
// behaviours.
```

Ghost prefers to use the platform. It will translate behavioral differences and mismatched prototypes wherever possible. Most features have plain C fallbacks in case the platform doesn't provide them.

```c
#include "ghost/math/rotl/ghost_rotl_u32.h"
// ghost_rotl_u32() rotates bits left. It compiles down to a single rotate
// instruction on architectures and compilers that support it, but otherwise
// uses ordinary C shifts and masks.
uint32_t x = ghost_rotl_u32(0x08000200U, 5); // returns 0x00004001U

#include "ghost/algorithm/qsort/ghost_gnu_qsort_r.h"
// This works on any platform wrapping any system qsort_r()/qsort_s() function.
// If the platform has none, Ghost implements one.
ghost_gnu_qsort_r(values, count, sizeof(values[0]), my_compare, my_context);
// Here's an easy way to port code!
#define qsort_r ghost_gnu_qsort_r
```

Ghost provides simple math functions and common algorithms.

```c
#include "ghost/algorithm/ghost_fnv1a.h"
// ghost_fnv1a_cstr_u32() computes the 32-bit FNV-1a hash of a null-terminated string.
uint32_t hash = ghost_fnv1a_cstr_u32("Hello world!"); // 0x7a78f512U

#include "ghost/math/ghost_is_pow2_all.h"
// ghost_is_pow2_*() returns true if the argument is a power of two.
bool x = ghost_is_pow2_i(37); // false
bool y = ghost_is_pow2_u(64U); // true
```

Ghost can help you detect implementation details that are tricky to detect.

```c
#include "ghost/detect/ghost_unix.h"
#if GHOST_UNIX
    // This is a UNIX-like, even if it didn't define __unix__.
#endif

#include "ghost/detect/ghost_gcc.h"
#if GHOST_GCC
    // This is really GCC, not some other compiler that defines __GNUC__.
#endif

#include "ghost/detect/ghost_musl_version.h"
#if GHOST_MUSL
    #if GHOST_MUSL_VERSION >= 1002000
        // We're compiling against musl 1.2.0 or later. time_t is 64-bit on all
        // architectures.
    #endif
#endif
```

Ghost is highly customizable. You can set configuration options and override any Ghost symbols before including Ghost. Overridden symbols propagate throughout Ghost.

```c
// Before any Ghost headers...
#define ghost_realloc_0any my_realloc // "0any" for any behaviour on size 0
#define ghost_free my_free

// You've configured a custom allocator! All of Ghost's allocation functions
// will use it: ghost_malloc(), ghost_strdup(), ghost_vasprintf(), etc.

#include "ghost/ghost_format.h"
char* p = ghost_asprintf("%s %s", "Hello", "world!"); // calls my_realloc()
```

You can also disable any Ghost feature. These also propagate: any feature that depends on a disabled feature will be disabled as well.

```c
// Before any Ghost headers...
#define ghost_has_ghost_float 0

// Ghost will assume float does not exist. You can still include any Ghost
// headers; any other features that require float won't exist either.

#include "ghost/math/max/ghost_max_f.h"
#if ghost_has(ghost_max_f)
    // Nope! This code won't be compiled!
#endif
float x = ghost_max_f(3.14f, 2.71f); // Compile error, no such function
```

Ghost's headers can be amalgamated to generate a single-file library or a header that you can incorporate into your project. This lets you use Ghost without needing an external dependency on it.

```sh
tools/amalgamate.py -i- -o foo_ghost.h -p foo <<EOF
#include "ghost/debug/ghost_static_assert.h"
#include "ghost/language/ghost_header_function.h"
#include "ghost/math/ghost_checked_mul.h"
#include "ghost/thread/ghost_mutex.h"
EOF
# We've generated foo_ghost.h, a Ghost platform wrapper namespaced to your
# library "foo". It contains the minimum stuff necessary to provide the
# above features on as many platforms as possible. Ship this with your
# library to remain dependency-free!

echo '#include "ghost/detect/ghost_musl_version.h"' | \
    tools/amalgamate.py -i- -o bar_musl.h -p bar
# We've generated bar_musl.h, a standalone dependency-free header whose sole
# purpose is to detect the version of musl.
```

Explore the [documentation](docs/) and [`include/` tree](include/ghost/) to find out more.
