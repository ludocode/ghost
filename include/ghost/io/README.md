### Features intentionally not implemented

Ghost does not implement the `_unlocked` I/O functions. Only `getc_unlocked()`,
`getchar_unlocked()`, `putc_unlocked()` and `putchar_unlocked()` are specified
by POSIX; others are platform-specific extensions. These are rarely supported
and not terribly useful.

Modern locks are fast and unlikely to be a bottleneck in your application. If
you do need these functions, you must be doing highly platform-specific
optimizations so you should just use the real functions directly.

(Ghost provides `flockfile()` on most platforms. If you have a thread that has
exclusive access to a file you could try just keeping it locked throughout to
avoid most of the overhead of locking and unlocking.)
