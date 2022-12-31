This document describes platform-specific information in Ghost.

## Platform Support

### Language Standards

Ghost has special support for the following programming language standards:

- C, any standard version (ANSI C or later, not K&R C)
- C++, any standard version (C++98 or later)
- GNU C and C++ extensions
- Objective-C 2.0
- Objective-C++ 2.0
- Microsoft C++/CLI

## Operating Systems

Ghost has special support for the following operating environments:

- Linux
    - GNU systems (glibc)
    - Android NDK (Bionic libc)
    - musl-based systems (Alpine, PostmarketOS)
    - uClibc
- Windows
    - x86, x86\_64 and ARM
    - Native Win32
    - Common Language Runtime
    - Cygwin (Newlib)
- Apple platforms
    - macOS
    - iOS
    - watchOS
- BSD
    - FreeBSD
    - OpenBSD
    - NetBSD
    - DragonFly BSD
- Misc
    - Emscripten
    - Arduino
    - [Cosmopolitan libc](https://justine.lol/cosmopolitan/index.html)

## Compilers

Ghost has special support for the following compilers:

- GCC version 4+
- Clang (3.4+, Apple Clang, etc.)
- Microsoft Visual C/C++ (MSVC) version 2012+
- NVIDIA HPC (a.k.a. PGI) (22.5+)
- [TinyCC](https://en.wikipedia.org/wiki/Tiny_C_Compiler) ([mob](https://repo.or.cz/w/tinycc.git) only)
- [chibicc](https://github.com/rui314/chibicc) (90d1f7f)
- [Kefir](https://github.com/protopopov1122/kefir)
- [lacc](https://github.com/larmel/lacc/)
- [cproc](https://sr.ht/~mcf/cproc/)
- [PCC](http://pcc.ludd.ltu.se/)
- [cparser](https://github.com/libfirm/cparser/) (*partial*)
- [lcc](https://drh.github.io/lcc/) (*partial*)
- [Digital Mars C/C++](https://www.digitalmars.com/download/freecompiler.html) (8.57+) (*partial*)

Some of these compilers are very old and haven't been updated in years. Obviously I don't expect people to be writing new code with some of these ancient compilers. The idea is just to get Ghost working on them to ensure it supports a wide range of implementations ANSI C.

I'd like to also support the following compilers but I haven't bothered to try getting access to them:

- ICC (Intel C/C++ Compiler)
- IBM's compiler?

## CPU Architectures

Ghost has special support for the following CPU architectures:

- x86
- x86\_64
- armv7a (a.k.a. ARMv7, 32-bit)
- aarch64 (a.k.a ARMv8, 64-bit)
- RISC-V (32-bit and 64-bit)
- AVR
- WebAssembly

In addition, Ghost has support for generic big-endian and little-endian systems, and has generic endian-safe fallbacks if the endianness can't be detected. Most of Ghost should be trivially portable to any architecture with a 32-bit `int` and 8-bit `char`, especially if the compiler provides constants like `__LONG_WIDTH__`. I do also want Ghost to eventually be usable on platforms with a 16-bit `int`.

This needs to be expanded to other popular architectures like MIPS and PowerPC. I don't have a way to test these at the moment.

## C89 and C++98 limitations

Ghost has some minor limitations when being compiled as C89 or C++98.

- C89 and C++98 do not have variadic macros. Any features that require variadic macros (like `GHOST_IF_ELSE()`) will not exist. Use `ghost_has()` to check if a feature exists.

- Some macros have arguments that are optional only when variadic macros are available. An example is `ghost_static_assert(expression, message)`. The message is optional except when compiling under strict C89/C++98.

- Variadic macro definitions still appear in `#define` statements in skipped groups, i.e. the false branches of `#if` blocks. Later C standards relaxed the preprocessor parsing rules for skipped groups (see 6.10.0.4 in C17) but this rule did not appear in the original C89 spec. A C89 compiler may complain about these definitions even in skipped groups.
    - As a workaround, you can delete any line with a variadic macro using a regex like `/#define.*\.\.\./d`. When compiling as C89, such lines are guaranteed to be in skipped groups so deleting them will have no effect. Beware that the resulting code will no longer compile under later versions. As another workaround for this you could use two amalgamations or two copies of Ghost, one with variadic macros and one without.

- Empty macro arguments are undefined behaviour in C89. Each macro argument must have at least one non-whitespace token. If your compiler warns against this, you may need to disable the warning. For GCC this requires disabling `-Wpedantic`. For MSVC you can use `GHOST_SILENCE_INSUFFICIENT_MACRO_ARGS`.

 If using a GNU-style compiler (e.g. GCC, Clang), it's recommended to build with `-std=gnu89` or `-std=gnu++98` (or better yet, a later C or C++ language standard) to avoid some of these limitations.
