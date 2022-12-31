# Math

This folder contains typical math functions you might expect to always be available as part of the runtime.

## Suffixes

All functions have type suffixes with a leading underscore. For example `_f` for `float`, `_i32` for `int32_t`, and `_z` for `size_t`.

Valid suffixes and associated type are:

Basic types:

- `c` - `char`
- `sc` - `signed char`
- `h` - `short`
- `i` - `int`
- `l` - `long`
- `ll` - `long long`
- `uc` - `unsigned char`
- `uh` - `unsigned short`
- `u` - `unsigned` (`int`)
- `ul` - `unsigned long`
- `ull` - `unsigned long long`

Library types:

- `z` - `size_t`
- `sz` - `ssize_t`
- `ip` - `intptr_t`
- `up` - `uintptr_t`
- `pd` - `ptrdiff_t`
- `iN` - `intN_t` (for N bits)
- `uN` - `uintN_t` (for N bits)
- `ilN` - `int_leastN_t` (for N bits)
- `ulN` - `uint_leastN_t` (for N bits)
- `im` - `intmax_t`
- `um` - `uintmax_t`

Floating-point types:

- `f` - `float`
- `d` - `double`
- `ld` - `long double`
- `fN` - `floatN_t` (for N bits)
- `cf` - `complex float`
- `cd` - `complex double`
- `cld` - `complex long double`
- `cfN` - `complex floatN_t` (for N bits)

Note that to avoid ambiguity between `size_t` and `short`, neither use `s`. Instead `s` is used in a few places for `signed`, always with another type character after it.
