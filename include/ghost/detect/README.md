This folder contains macros for detecting parts of the implementation that are otherwise hard to detect.

Ghost doesn't wrap things that are easy to detect. For example MSVC defines `_MSC_VER` and nothing else does. If want to detect that compiler, just use the official macro.

However, some things are harder to detect. Some examples:

GCC first identified itself by defining `__GNUC__`. However, as its many extensions became implemented in other compilers, some of them also came to define `__GNUC__` to activate them. This means it is hard to detect GCC without being mistaken by other compilers that masquerade as GCC. For this reason Ghost provides `GHOST_GCC` which can be used to detect it. This makes it suitable to protect code that doesn't make sense for non-GCC compilers, like working around version-specific compiler bugs. This macro will be maintained to exclude new GCC-like compilers as they appear.

Linux has many different possible libcs. To help code target them properly, almost all of them identify themselves with macros like `__GLIBC__` and `__BIONIC__`. The exception is musl. They have historically refused to identify themselves with the preprocessor. For this reason, Ghost provides `GHOST_MUSL` and `GHOST_MUSL_VERSION` which attempt to detect musl and its version.

On C platforms in general, it can be difficult to know how to detect the libc. On GNU/Linux, if you include only `<stddef.h>`, `__GLIBC__` won't be defined. This is because `<stddef.h>` is provided by the compiler, not the libc. The macro `__GLIBC__` is actually defined in `<features.h>`, but this is problematic because this non-standard header does not exist on all platforms, so you need to know the libc to determine whether it's safe to include! To simplify this, Ghost provides `ghost_libc.h`. This includes whatever headers are necessary to activate those macros that will let you detect the libc.
