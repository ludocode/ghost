## Find First Set

portability notes:

Compilers:

- GCC and Clang has builtins for `ffs()`, `ffsl()` and `ffsll()`, but only uses them automatically under non-strict `-std=gnu*`;
- GCC also has `__builtin_ctz()` which could be used to implement ffs;
- MSVC has for `_BitScanForward`;
- Intel has `_bit_scan_forward`;
- NVidia has `__ffs`;
- GHC has `countTrailingZeros`.

Platforms:

- glibc declares `ffs()` in `<strings.h>`, and `ffsl()` and `ffsll()` in `<string.h>`, but only under various conditions (`_DEFAULT_SOURCE` and others);
- musl declares all three of `ffs()`, `ffsl()` and `ffsll()` in `<strings.h>`, but only under various conditions (`_DEFAULT_SOURCE` and others);
- FreeBSD has all three of `ffs()`, `ffsl()` and `ffsll()` in `<strings.h>`, but only under various conditions (`__XSI_VISIBLE`, `__BSD_VISIBLE`)

For the above reasons we never bother to use the ffs() function as declared in the headers.
