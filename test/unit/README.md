This folder contains Ghost unit tests.

Ghost uses [Mirror](https://github.com/ludocode/mirror) as its unit test library. TODO add it to fetch-dependencies.sh script, make it fetch automatically

## Standard header layout

Every header file in Ghost has at least one corresponding unit test source file. This has the same folder and filename except the filename is prefixed with `test_` and the extension is `.c`.

To test a feature, say `ghost_foo`, a typical test case file starts like this:

```c
#include "ghost/path/to/ghost_foo.h"

#ifndef ghost_has_ghost_foo
    #error "ghost/path/to/ghost_foo.h must define ghost_has_ghost_foo."
#endif

#include "test_common.h"
```

The first header included is always the header to test. This ensures that every Ghost header compiles cleanly on its own.

After that we include `test_common.h`. This verifies a few things in `ghost_foo.h` (in particular that it included `ghost/ghost_core.h`) and it includes `mirror/mirror.h` to define test cases. This also silences warnings about empty translation units in case we don't actually define any tests.

Next we define test cases. If the feature is optional, these will be wrapped in a `ghost_has` check like this:

```
#if ghost_has_ghost_foo
mirror_0() {
    mirror_check(ghost_foo(...));
}
#endif
```

If the feature is mandatory, you'll see this instead:

```c
#if !ghost_has_ghost_foo
    #error "ghost_foo must exist."
#endif

mirror_0() {
    mirror_check(ghost_foo(...));
}
```

In both cases we don't need to specify a name or id to `mirror()`. The unit test defines these automatically. `MIRROR_KEY` is based on the filename of the test file and `MIRROR_NAME` is based on the path of the first header it includes.

## Variant Tests

Suppose `ghost_foo` has an alternative configuration, say, `GHOST_FOO_DISABLE_SYSTEM` to prevent it from using the libc implementation. An variant unit test file for this configuration might look like this:

```
#define GHOST_STATIC_DEFS 1
#define GHOST_FOO_DISABLE_SYSTEM 1
#include "ghost/path/to/ghost_foo.h"

#ifndef ghost_has_ghost_foo
    #error "ghost/path/to/ghost_foo.h must define ghost_has_ghost_foo."
#endif

#include "test_common.h"

#if ghost_has_ghost_foo
mirror(suffix("$nosystem")) {
    mirror_check(ghost_foo(...));
}
#endif
```

These are the main differences:

- `GHOST_STATIC_DEFS` is defined to make all Ghost definitions static. This ensures that single-definition functions (i.e. emit/noemit inline or selectany/weak) will not be used for this file so the functions being tested won't be replaced by those of some other translation unit.

- The configuration is also applied, in this case `GHOST_FOO_DISABLE_SYSTEM`, before including any headers.

- The name of the tests are suffixed with `$` or `@` and the name of the variant.

In some cases the tests are shared between variants with a template. See e.g. the qsort tests for an example.
