# `ghost/malloc/`

This folder includes Ghost's memory allocation functions.

## Standard C allocation functions and extensions

The standard C allocation functions (for non-extended alignment) are:

- `malloc(size)` -- Allocates uninitialized memory
- `calloc(count, stride)` -- Allocates an array of zeroed memory
- `realloc(ptr, size)` -- Re-allocates a pointer, leaving the new space uninitialized

Some platforms provide extensions. For example:

- glibc, OpenBSD, Solaris and others have `reallocarray()` to reallocate with an overflow check.
- NetBSD has the same thing but calls it `reallocarr()`.
- OpenBSD has `recallocarray()` for reallocating with zeroing.
- FreeBSD has `mallocx()` and `rallocx()` from jemalloc with flags to configure zeroing and other behaviour.
- FreeBSD, DragonflyBSD and Solaris have `reallocf()` to free the given pointer on memory allocation failure.

Ghost currently does not implement many of these extensions. `ghost_reallocarray()` is likely to be implemented soon (TODO).

## Behavioural variants

### `malloc()`, `calloc()` and friends

Implementations vary in the behaviour of `malloc()`, `calloc()` and friends when the size is zero. On some platforms they return a unique allocation; on other platforms they return null and set errno to EINVAL; on others still they may return null and not set errno at all; and on others the behaviour is explicitly undefined, and may crash or worse.

Ghost standardizes on returning a unique allocation when the size is zero. For many of these functions, an alternative with the suffix `_0null` is provided, which returns null (usually without setting errno, though this is currently implementation-defined) if the size is zero.

### `realloc()`

The standard C `realloc()` function has the following signature. As long as the size is not zero, it either resizes the given allocation or allocates a new one if it's null.

```
void* realloc(void* p, size_t size);
```

The behaviour when size is 0 is more complicated.

As of C23, calling `realloc()` with a non-null pointer and size of 0 invokes undefined behaviour. In practice, [implementations vary](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2396.htm#dr_400). They may free the given pointer and return a new allocation (e.g. the BSDs, macOS), or they may free or ignore the given pointer and return null, possibly setting errno. Moreover, calling `realloc()` with a null pointer and size of 0 must behave as `malloc(0)`, which is itself implementation-defined. This creates even more possibilities.

Ghost implements many (but not all) of these variations. The behaviour is described in the following table:

| Ghost `realloc()` variation    | `ptr != null`, `size == 0`       | `ptr == null`, `size == 0`         | Platforms          |
|--------------------------------|----------------------------------|------------------------------------|--------------------|
| `ghost_realloc()`              | undefined (abort in debug)       | return new minimum-size allocation | Ghost              |
| `ghost_realloc_0alloc()`       | resize ptr to minimum and return | return new minimum-size allocation | BSDs, macOS        |
| `ghost_realloc_0free()`        | free ptr, return null            | return new minimum-size allocation | glibc, Windows     |
| `ghost_realloc_0null()`        | free ptr, return null            | return null                        | AIX probably?      |
| `ghost_realloc_0any()`         | implementation-defined           | implementation-defined             | (any platform)     |

On allocation failure, all of these set errno to `ENOMEM`, leave the given pointer untouched, and return null. (Several platforms have a `reallocf()` extension that frees the given pointer on allocation failure. Ghost does not implement this yet.)

For those Ghost functions that can return null instead of allocating, they may or may not set errno to `EINVAL` or some other error. This is still implementation-defined. It's recommended to only check errno for `ENOMEM` to determine whether an allocation failure occurred.

Ghost provides all of these functions not because they're necessarily that useful but because it makes it easy to override the allocator in Ghost. You can override whichever one specifically matches the behaviour of your custom `realloc()`. If you don't know the behaviour of your custom `realloc()` function, just define `ghost_realloc_0any` to it and let Ghost do the rest. It will guarantee correct behaviour for all other `ghost_realloc_*()` functions.

## Querying Allocation Sizes

Some platforms provide ways to query the size of an allocation, and to query the size that an allocation should be to avoid wasting allocator padding.

The macOS man page for [`malloc_size()` and `malloc_good_size()`](https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/malloc_good_size.3.html) has a good description of these functions.

Ghost provides the following which are modeled on the macOS functions:

- `ghost_malloc_size()` -- Returns the storage size of the given allocation
- `ghost_malloc_good_size()` -- Rounds up the given size to a value that minimizes allocator waste

Note that many platforms, in particular Windows, do not provide such functions.

## Typed allocation macros

Ghost defines typed allocation macros. These are simple `#define` wrappers around the standard C API that perform `sizeof` automatically on the given type. This is a common macro in many projects, which is why Ghost calls it simply "alloc".

- `ghost_alloc(T)` -- Allocate memory for a value of type T
- `ghost_alloc_zero(T)` -- Allocate zeroed memory for a value of type T
- `ghost_alloc_array(T, size_t)` -- Allocate memory for an array of values of type T
- `ghost_alloc_array_zero(T, size_t)` -- Allocate zeroed memory for an array of values of type T

In table form:

|Function|Parameters|New Memory State|
|-|-|-|
|`ghost_alloc(T)`|type|uninitialized|
|`ghost_alloc_array(T, n)`|type and count|uninitialized|
|`ghost_alloc_zero(T)`|type|zeroed|
|`ghost_alloc_array_zero(T, n)`|type and count|zeroed|

These are useful as a replacement for the typical pattern of allocating a struct in C, which is:

```c
/* Idiomatic C style */
foo_t* foo = malloc(sizeof(foo_t))

/* C++-compatible style */
foo_t* foo = (foo_t*) malloc(sizeof(foo_t))
```

Instead, write this:

```c
foo_t* foo = ghost_alloc(foo_t);
```

This performs `sizeof` and a cast for you. These have several advantages over calling `malloc()` or `calloc()` directly:

- `ghost_alloc()` returns a typed pointer instead of `void*`. This is less error-prone than calling `malloc()` because you could pass the wrong size. Passing the wrong type to `ghost_alloc()` will cause a compiler error when you attempt to assign it to a typed pointer.

- The code can be compiled as C++ without requiring a manual cast. In fact this casts via `ghost_bless()` which is meant to avoid strict aliasing problems among other things. In C++ it indicates to the compiler that it should start the lifetime of the allocated memory as an object of the correct type.

- The code is shorter and extremely clear, especially if you were previously casting manually for compatibility with C++, or having to pass 1 to `calloc()` to get zeroed memory.

You can free the allocated pointer with `ghost_free()` as normal.

You can mix and match these with `ghost_malloc()`, `ghost_free()` and so on. You don't have to use these everywhere or convert your code to them. You can simply use them wherever you find them convenient.

These macros do not handle extended alignment requirements. They assume `malloc()` will sufficiently align memory for the given type.

## Overriding the allocator

Ghost allows you to override the underlying allocator it uses to provide its allocation functions.

The macro `GHOST_MALLOC_SYSTEM` defines whether Ghost will use the system `malloc()`, `realloc()`, `free()`, and so on. It defaults to 1 if a system allocator is available (i.e. the implementation is hosted) and no allocator functions are overridden. If any allocation function is overridden, `GHOST_MALLOC_SYSTEM` defaults to 0.

Currently the following Ghost functions are considered allocation functions:

- `ghost/malloc/` functions:
    - `ghost_aligned_free`
    - `ghost_aligned_malloc`
    - `ghost_calloc`
    - `ghost_calloc_0any`
    - `ghost_calloc_0null`
    - `ghost_free`
    - `ghost_free_nonnull`
    - `ghost_malloc`
    - `ghost_malloc_0any`
    - `ghost_malloc_0null`
    - `ghost_malloc_good_size`
    - `ghost_malloc_size`
    - `ghost_memdup`
    - `ghost_realloc`
    - `ghost_realloc_0alloc`
    - `ghost_realloc_0any`
    - `ghost_realloc_0free`
    - `ghost_realloc_0null`
    - `ghost_strdup`
    - `ghost_strndup`
- `ghost/format/` functions:
    - `ghost_asprintf`
    - `ghost_vasprintf`

When this is 0, Ghost allocator functions won't exist unless you define some yourself. You can define this to 0 to make Ghost wrap a custom allocator, to customize or correct Ghost's usage of the system allocator, or to disable Ghost's allocator entirely.

When providing a custom allocation function, you need to override the variant that correctly matches its behaviour. For example if you override `ghost_malloc()`, your function must return a minimum-size allocation when size is 0, as Ghost and user code expects.

If you're unsure of the behaviour of your function when the size is 0, override `ghost_malloc_0any()` instead, which accepts any behaviour on size 0. `ghost_malloc()` will automatically wrap it and ensure the correct behaviour.

In other words, to use a custom allocator, just do this:

```c
#define ghost_malloc_0any my_malloc
#define ghost_realloc_0any my_realloc
#define ghost_calloc_0any my_calloc
#define ghost_free my_free
```

When the system allocator is disabled, Ghost will implement all allocation functions in terms of others as much as possible. For example with the above overrides, `ghost_strdup()` will automatically call `my_malloc()`. Similarly, if you were to define only `ghost_malloc()`, Ghost would define a `ghost_calloc()` that calls your `ghost_malloc()` and zeroes the memory.

On the other hand, if you define `ghost_malloc()` and also define `GHOST_MALLOC_SYSTEM` to 1, `ghost_calloc()` will still use the system `calloc()`.

This is useful if you want to use, say, a third-party `asprintf()` implementation. You could do this:

```
#define ghost_asprintf my_asprintf
#define ghost_vasprintf my_vasprintf
#define GHOST_MALLOC_SYSTEM 1
```

In this case `ghost_malloc()`, `ghost_free()` and so on will still wrap the system allocator. Only your custom `asprintf()` function will be used which presumably uses the system `malloc()` so it can be freed with `free()` or `ghost_free()`.
