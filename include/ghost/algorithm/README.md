This contains useful non-cryptographic algorithms like hashing, sorting, random number generation, etc.

Some of these wrap standard C or POSIX functions like `qsort()`. Others are pure C like the FNV-1a hash algorithms.

This needs to be expanded a lot. At the very least we need:

- The POSIX algorithms in `<search.h>`, in particular `bsearch()`, `lsearch()`
    - The `hsearch()`, `twalk()` and `insque()` algorithms also need to be wrapped and implemented but they will probably go in `container/legacy/`
- Random number genereration, e.g. xoshiro, with helpers for uniform ranges, floats, etc.
- Modern hash algorithms, e.g. MurmurHash and some of its many derivatives (implemented in C and with a public-domain-equivalent license of course)
- CRC algorithms, in particular CRC-32 and Adler-32
