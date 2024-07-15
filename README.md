# Trees - STL, Templates, and Iterators

Author: Lior Trachtman  
Email: lior16122000@gmail.com

## Overview

This library provides implementations for various operations on trees, including adding root and sub-nodes, and performing different traversal methods such as BFS, DFS, Pre-order, In-order, and Post-order. The library also supports visualization using SFML.

## Features

- **Node Management**: Create nodes, add children, and access node values easily.
- **Tree Operations**: Add root and sub-nodes, perform traversal using BFS, DFS, Pre-order, In-order, and Post-order methods.
- **Iterator Support**: Iterators provided for BFS, DFS, Pre-order, In-order, and Post-order traversal.

## Traversal Methods

### Breadth-First Search (BFS)

- Iterates through nodes level by level, using a queue.
- Implemented in `Tree.hpp` and `Iterator.hpp`.

### Depth-First Search (DFS)

- Traverses deep into the tree structure, using a stack.
- Implemented in `Tree.hpp` and `Iterator.hpp`.

### Pre-order Traversal

- Visits the root node first, followed by the left subtree, and then the right subtree.
- Implemented in `Tree.hpp` and `Iterator.hpp`.

### In-order Traversal

- Visits the left subtree first, then the root node, and finally the right subtree.
- Implemented in `Tree.hpp` and `Iterator.hpp`.

### Post-order Traversal

- Visits the left and right subtrees first, and then the root node.
- Implemented in `Tree.hpp` and `Iterator.hpp`.

## Code Structure

The library is structured into the following main files:

1. **Node.hpp**
   - Implements the `Node` class for tree nodes.
   - Provides methods for node creation, child management, and value access.

2. **Tree.hpp**
   - Implements the `Tree` class for tree operations.
   - Provides methods for adding root and sub-nodes, managing traversal, and iterating over the tree.

3. **Iterator.hpp**
   - Contains `iterator` implementations for different tree traversal methods.
   - Supports BFS, DFS, Pre-order, In-order, and Post-order traversal.

4. **Complex.hpp**
   - Implements the `Complex` class for complex number operations.
   - Provides arithmetic operations (+, -, *) and comparison operators (==, !=, <, >, <=, >=).
   - Supports output stream operator for printing complex numbers.

5. **TreeDrawer.hpp**
   - Implements functions for visualizing trees using SFML graphics.
   - Provides functions to draw nodes and calculate tree dimensions.
   - Supports customizing node appearance, spacing, and layout.

## Usage

1. Clone the repository.

- `make tree` - compiles the project, creating exec file `tree` to run the program.
- `./tree` - runs the program.

### Tests

Tests:
- `make test` -     run using `./test`  (advanced doctest)
- `make tidy` -     makes sure the code is clean
- `make valgrind` - makes sure there are no memory leaks/problems.


#### clang-tidy and valgrind
Before submitting we ran clang-tidy to make sure the code is written well, and valgrind to make sure there are no memory errors or leaks.

#### Test.cpp
This file includes tests on everything implemented in the Tree class. It tests the methods, the iterators, and the operators.

### Example

To use this library, include the `Tree.hpp` and `Node.hpp` headers in your C++ project:

```cpp
#include "Tree.hpp"
#include "Node.hpp"
#include <iostream>

int main() {
    // Create nodes
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    
    // Create tree and add nodes
    Tree<int> tree;
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    
    // Perform BFS traversal
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        std::cout << it->get_value() << " ";
    }
    std::cout << std::endl;

    // Other traversal methods work similarly...

    return 0;
}
