## Internal Implementation Details

`ghost/impl/` contains internal **impl**ementation details of Ghost.

Never directly `#include` any file in this folder.

Never use or define any symbol prefixed with `ghost_impl_`, `GHOST_IMPL_` or `GhostImpl`.

Anything here may change at any time.
