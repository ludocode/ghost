This folder contains Ghost's serialization functions.

# Low-level data serialization

- `hswap/` -- host to network/big/little byte-swapping functions

The traditional functions like `htonl()` and `ntohs()`, as well as modern extensions like `htobe16()` and `le32toh()` are included in `hswap/` (for "host swap".) We suffix them explicitly by their fixed-width type (e.g. `_u16`, `_u32` rather than `htonl()` or `ntohs()`.

These were used back when serialization was done with structs. Traditionally, you would define a struct for a frame of the protocol, then simply cast your stream pointer to it to read or write. Of course this turns out to be a pretty terrible way of doing serialization. Workarounds accumulated to make this portable:

- Differing endianness made these host-based byte-swapping functions necessary. You have to go through each field in your struct and swap the bytes after reading or before writing, e.g. `p->x = htonl(p->x)`.
- Struct packing rules varied. `#pragma pack` became necessary to force struct layouts to match the protocol.
- RISC processors did not implement unaligned loads or implemented them inefficiently. You would have to `memcpy()` from the stream to the struct to read from it and vice versa.

All of this turns out to be way more work than just directly using unaligned load/store functions. If you're writing modern serialization code, you probably want the functions in `load/` and `store/` instead.

- `load/`, `store/` -- unaligned fixed-width endian-specific load/store

These are Ghost's modern serialization functions.
