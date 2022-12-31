# Intrusive Weight-Balanced Tree

This folder implements a type-erased intrusive weight-balanced order-statistic binary tree.

The [weight-balanced tree](https://en.wikipedia.org/wiki/Weight-balanced_tree) is a sort of "universal" data structure. It's able to implement lists, queues, stacks, arrays, maps, sets, priority queues and more with O(log n) performance for all operations.

Ghost implements maps and sets using a weight-balanced tree instead of the more common red-black tree in order to provide the features of an order statistic tree with minimal additional overhead. This means it supports the functionality of `rank()` and `select()` (i.e. `index()` and `at()`); it can be used as an array with functions such as `insert_at()`; and it can be used to implement maps and sets in a way that minimizes the amount of type-erased or templated code.

This tree is implemented here in Ghost. It includes functions for balancing the tree, inserting and removing nodes, and performing certain kinds of lookups and navigation. These functions are shared between all template instantiations of all weight-balanced tree containers. By using the same underlying type-erased data structure for all, the volume of templated code is significantly reduced, leading to smaller binaries and faster programs.

To use this, you need a struct that represents your key-value pairs. Put a `ghost_iwbt_node_t` field in that struct. You then interact with the tree by using pointers to the node field in your structs. To convert the node pointers back to a pointer to your structure, use `ghost_container_of()`.
