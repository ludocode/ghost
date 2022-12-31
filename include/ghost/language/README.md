# Language

The `language/` folder is for things that could be considered language extensions, for porting language features across versions or between languages (C/C++), or for working around language differences between C, C++, Objective-C and potentially other compatible languages.

## Alignment

Ghost provides the following features for alignment:

- `ghost_alignas`
- `ghost_alignat`
- `ghost_alignof`
- `ghost_is_aligned`
- `ghost_max_align`

## Casts

Ghost provides many cast macros for compatibility with C++:

- `ghost_static_cast()` -- A wrapper for C++ `static_cast<>()`
- `ghost_reinterpret_cast()` -- A wrapper for C++ `reinterpret_cast<>()`
- `ghost_const_cast()` -- A wrapper for C++ `const_cast<>()` (but only for `const`, not other CV-qualifiers)
- `ghost_cast()` -- An alias for `ghost_static_cast()`, since that's usually what you want
- `ghost_auto_cast()` -- Allows implicit casting of `void*` to a typed pointer
- `ghost_bit_cast()` -- Performs a safe bitwise conversion from one type to another.
- `ghost_bless()` -- Used to "start the lifetime" of memory as a given type

The wrappers for C++-style casts can be used to make your code compile cleanly as C++ under GCC/Clang `-Wold-style-cast`. `ghost_const_cast()` also makes it easy to cast away const in C, which can otherwise be difficult to silence warnings.. `ghost_bit_cast()` brings C++ `std::bit_cast<>()` to C, while `ghost_auto_cast()` brings C-style implicit `void*` conversion to C++. `ghost_bless()` is a pedantic and probably useless C++-ism that Ghost uses internally for correctness.

Except for `ghost_bit_cast()`, these are all plain casts or no-ops in C. They exist only for compatibility with C++. If you don't care about C++, you don't need to use them.

## Header linkage

Ghost provides the following function attributes for declaring functions in header files. We call this "header linkage". They are ideal for writing a simple header-only library. The important ones are:

- `ghost_header_inline`
- `ghost_header_function`

Use them like this:

```c
ghost_header_inline
bool foo(...) {
    /* a small function */
}

ghost_header_function
int bar(...) {
    /* ... */
    /* ... */
    /* a large function */
    /* ... */
    /* ... */
}
```

These will automatically use the best function declarators and compiler extensions available to reduce code bloat and eliminate redundant definitions. They use `[[selectany]]` or C++-style `inline` where possible; the non-inline attributes use `weak` otherwise; and all of them fallback to `static inline` or just `static`. These attributes always exist on all platforms. Use them anywhere; they "just work".

Some care is recommended in choosing the correct attribute. You should prefer `ghost_header_inline` for small functions and `ghost_header_function` for all others. `ghost_header_inline` allows profile-guided optimization, link-time identical code folding and other compiler heuristics to do their job, but may cause duplication between translation units which leads to code bloat if used on large functions. Conversely, `ghost_header_function` will reliably prevent code bloat on most platforms but it often does so by inhibiting inlining.

Ghost additionally provides the following attributes for overriding the compiler's heuristics:

- `ghost_header_always_inline`
- `ghost_header_noinline`

## Manual inline emission

Ghost provides the following attributes to control the emission of inline function definitions:

- `ghost_emit_inline`
- `ghost_noemit_inline`
- `ghost_emit_always_inline`
- `ghost_noemit_always_inline`

These declare a function `inline` or `always_inline`. The `emit` variants cause a non-inline definition to be emitted in the current translation unit. The `noemit` variants do not emit a definition in the current translation unit. This allows you to use inline functions while guaranteeing that only one non-inline definition exists in the final link.

These are supported everywhere except strict ANSI C. Even in ANSI C, some compilers provide extensions to make this work. You can check `ghost_has(ghost_emit_inline)` to see whether it's supported.

Suppose you are writing an app or library called "foo". In a common header file, do this:

```c
#include "ghost/language/ghost_emit_inline.h"
#ifdef FOO_EMIT_DEFS
    #define foo_inline ghost_emit_inline
#else
    #define foo_inline ghost_noemit_inline
#endif
```

Declare all your inline functions `foo_inline` (without `static` or any other linkage specifier.) In exactly one translation unit, define `FOO_EMIT_DEFS` (or have the users of your libary define it) and include all headers with inline functions. The standalone functions will then be emitted in only that translation unit.

There are more involved uses for these as well. For example if you are making a header-only library, it's possible to default to "header linkage" (see above), while supporting an optional configuration to use emit/noemit instead, where users specify their own translation unit in which to emit definitions. Ghost does exactly this for its own functions; see `GHOST_MANUAL_DEFS` and `GHOST_EMIT_DEFS`.
