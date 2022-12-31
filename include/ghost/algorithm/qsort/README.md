# `qsort()` with context extension functions

The standard C `qsort()` function does not support passing a context into the comparison callback. Support for a context is provided by platforms as a common extension called `qsort_r()` or `qsort_s()`. Unfortunately, GNU/Linux, Windows, FreeBSD+macOS and C11 Annex K have all defined their own and they are all incompatible.

Ghost can convert between the `qsort_r()` and `qsort_s()` functions of various platforms. All of these functions are implemented using whichever context-extended qsort functions are provided by the platform. The comparison callback is either passed through or wrapped in a thunk as needed. If no platform function exists, Ghost implements a fallback (introsort normally, or shellsort if optimizing for size.)

Ghost's qsort functions should "just work" on any platform. You shouldn't need to configure anything, but read the Limitations and Configuration sections if you want to understand how it works and customize it.

### Simple Usage

Suppose you'd like to sort an array with GNU-style `qsort_r()` but you want your app to be portable to non-GNU platforms. Just do this:

```c
#include "ghost/functions/qsort/ghost_gnu_qsort_r.h"
```

Now you can use `ghost_gnu_qsort_r()` instead of `qsort_r()` to sort your array. Ghost will do whatever is necessary to make it work.

If you want to still use `qsort_r()`, or you're porting an existing app that already uses `qsort_r()`, you can do this instead:

```c
#include "ghost/functions/qsort/ghost_gnu_qsort_r.h"
#define qsort_r ghost_gnu_qsort_r
```

Now you can use GNU-style `qsort_r()` normally on any platform. This is the easiest way to port existing code.

### API Reference

- [Standard C `qsort()`](https://man.archlinux.org/man/qsort.3)

```c
#include "ghost/functions/qsort/ghost_qsort.h"

void ghost_qsort(void* first, size_t count, size_t element_size,
        int (*compare)(const void* left, const void* right));
```

- [GNU/Linux `qsort_r()` (glibc, uClibc, musl, future POSIX)](https://man.archlinux.org/man/qsort_r.3)

```c
#include "ghost/functions/qsort/ghost_gnu_qsort_r.h"

void ghost_gnu_qsort_r(void* first, size_t count, size_t element_size,
        int (*compare)(const void* left, const void* right, void* user_context),
        void* user_context);
```

- [macOS, Free/Net/DragonFly BSD `qsort_r()`](http://www.ipnom.com/FreeBSD-Man-Pages/qsort_r.3.html)

```c
#include "ghost/functions/qsort/ghost_bsd_qsort_r.h"

void ghost_bsd_qsort_r(void* first, size_t count, size_t element_size,
        void* user_context,
        int (*compare)(void* user_context, const void* left, const void* right));
```

- [Windows `qsort_s()`](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/qsort-s)

```c
#include "ghost/functions/qsort/ghost_win_qsort_s.h"

void ghost_win_qsort_s(void* first, size_t count, size_t element_size,
        int (__cdecl *compare)(void* user_context, const void* left, const void* right),
        void* user_context);
```

- [C11 Annex K `qsort_s()`](https://en.cppreference.com/w/c/algorithm/qsort)

```c
#include "ghost/functions/qsort/ghost_c11_qsort_s.h"

errno_t ghost_c11_qsort_s(void* first, rsize_t count, rsize_t element_size,
        int (*user_compare)(const void* left, const void* right, void* user_context),
        void* user_context);
```

### Limitations

Ghost converts between callback prototypes using a "thunk" callback that performs the conversion. These may have an impact on performance since each comparison may incur an additional function pointer indirection. Some platforms, currently FreeBSD and Newlib, implement multiple `qsort_r()`/`qsort_s()` functions supporting each callback prototype. On such platforms, all qsort variants can be implemented without any overhead. Most platforms however only implement one function so Ghost wrappers without matching callback prototypes will incur this overhead.

On platforms that don't provide any usable `qsort_r()` or `qsort_s()` at all, or when manually configured as such, Ghost provides one. This is by default a full implementation of introsort. This can be fairly large in terms of compiled code size.

When Ghost detects that the compiler is optimizing for size, a small shellsort is used instead. Shellsort compiles to significantly smaller code but its worse case guarantee is somewhat worse than O(nlogn). Ghost prefers to use the platform, and there are no guarantees that the platform provides safe worst-case performance (in particular Bionic libc (TODO check this?) also uses shellsort) so this is no worse that what you can expect from a true platform `qsort_r()`.

If you want worst-case performance guarantees, you can make Ghost prefer its internal introsort. If you want the smallest code size, you can also make Ghost prefer its internal shellsort. See the Configuration section below.

On some compilers, in particular Microsoft's, Ghost cannot detect whether the compiler is optimizing for size. On such compilers it assumes that it isn't (see `GHOST_OPTIMIZE_FOR_SIZE`.)

If two separate translation units rely on Ghost's internal qsort but only one is optimized for size, both the shellsort and introsort implementations may be linked into the binary. If you want to optimize for size, it's recommended to optimize all translation units (or at least all those that use Ghost's internal qsort) for size.

musl libc had historically refused to provide any `qsort_r()` function (and [musl's `qsort()` isn't very fast either](https://github.com/ludocode/pottery/tree/develop/examples/pottery/qsort_fast).) GNU-style `qsort_r()` has been added and appears in musl 1.2.3, but of course in typical musl style, they've given us [no way for the preprocessor to detect it](https://www.openwall.com/lists/musl/2022/04/16/1). The musl developers intentionally obfuscate their library's features so Ghost doesn't always do a great job of detecting what's available. The simplest way to force Ghost to use it is by predefining `ghost_gnu_qsort_r` to `qsort_r`, but note that musl only declares it under `_GNU_SOURCE`.

C11 Annex K does not provide a way to query the current constraint handler. It is therefore not possible for code outside of libc to call it. If a constraint violation occurs, Ghost calls `ghost_fatal()` (which ultimately aborts the program) instead of the constraint handler. Therefore when `ghost_c11_qsort_s()` does return, it always returns 0. If C11 Annex K is not available, Ghost declares `ghost_c11_qsort_s()` using `int` and `size_t` in place of `errno_t` and `rsize_t` respectively, and uses a reasonable alternative to `RSIZE_MAX` (see `GHOST_RSIZE_BOUNDS`.)

For best performance consider porting code away from `qsort()` and its variants altogether. You can use modern sort templates like [Pottery](https://github.com/ludocode/pottery) or [swensort/sort](https://github.com/swenson/sort) to avoid function pointer indirections. This can give you performance comparable to C++ `std::sort<>()` and you can choose a specific sort algorithm appropriate for your dataset.

### Configuration

Ghost's internal qsort implementation can be fairly large (see Limitations above.) If you want to make sure Ghost doesn't use it you can explicitly disable it by defining `GHOST_QSORT_DISABLE_INTERNAL` to 1. If the internal implementation is disabled, including a Ghost qsort header that can't be mapped to a platform qsort will result in a compiler error.

You can also force Ghost to use its internal implementation regardless of what platform qsort functions are available by defining `GHOST_QSORT_FORCE_INTERNAL` to 1. Ghost will then use the internal implementation even for ordinary `ghost_qsort()`.

Ghost declares inline functions as `static inline` in C in order to make it as easy as possible to use. It can however be configured to declare its functions as `inline` and `extern inline` instead. This ensures that only one non-inline implementation of each function will exist in the final link. In order to do this in C, you need to instantiate the inline definitions in exactly one translation unit to prevent duplicate symbols. This is possible by defining `GHOST_EMIT_DEFS` appropriately; see the documentation here. TODO LINK

If Ghost fails to detect a system qsort function, you can define it yourself. For example if it has the BSD prototype but it's only available under `_BSD_SOURCE`, you could pre-define it like this:

```c
#define _BSD_SOURCE
#include <stdlib.h>
#define ghost_bsd_qsort_r qsort_r
```

If a qsort function is overridden, Ghost will use it to implement other qsort functions.

If Ghost incorrectly detects system qsort functions, you can disable its detection by pre-defining `GHOST_QSORT_DISABLE_SYSTEM` to 1. You can combine this with a definition of the correct system function in order to override Ghost's detection. For example:

```c
#define _GNU_SOURCE
#include <stdlib.h>
#define GHOST_QSORT_DISABLE_SYSTEM 1
#define ghost_gnu_qsort_r qsort_r
```
