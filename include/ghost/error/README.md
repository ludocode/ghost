## Configuring errno

Ghost provides the following features for interacting with errno:

- `ghost_errno_h` (in `ghost/header/c/`) -- Includes `<errno.h>` if possible
- `ghost_errno` -- A thread-local l-value that stores errno, by default a wrapper around libc errno
- `ghost_errno_load()` -- Loads the current value of errno
- `ghost_errno_store(value)` -- Stores a value to errno
- `ghost_errno_is(value)` -- An expression that evaluates to 1 if errno is the given error value or 0 otherwise.

Ghost separates the different parts of errno handling so you can configure it however you like. This allows you to implement your own errno (for example if building in a freestanding environment) or to disable any interaction between Ghost and errno.

Ghost internally only uses `ghost_errno_store()` and `ghost_errno_is()` which gives you maximum flexibility for how you want to configure it:

- Define `ghost_errno` to a custom l-value if you have your own global or threadlocal errno variable in freestanding;

- Define `ghost_errno_load()` and `ghost_errno_store()` if you have some special way of handling errno (perhaps you want to log or debugbreak any time errno is set by Ghost);

- Define `ghost_has_ghost_errno` to 0 to disable all Ghost handling of errno;

- Define `ghost_has_ghost_errno_h` to 0 to additionally prevent Ghost from including `<errno.h>`;

- Define `ghost_has_ghost_errno_store` to 0 if you just want to prevent Ghost from setting errno in its synthetic libc wrappers while still allowing it to check errno values normally.
