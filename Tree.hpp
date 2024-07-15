// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "Iterator.hpp"
#include <iostream>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>

template<typename T, int K = 2>
class Tree {
private:
    Node<T>* root;

public:
    Tree();
    Tree(Node<T>* key);
    ~Tree();
    void add_root(Node<T>& node);
    void add_sub_node(Node<T>& parent, Node<T>& child);
    Node<T>* getRoot() const { return root; }

    // Iterator methods
    BFSIterator<T, K> begin_bfs_scan();
    BFSIterator<T, K> end_bfs_scan();
    PreOrderIterator<T, K> begin_pre_order();
    PreOrderIterator<T, K> end_pre_order();
    InOrderIterator<T, K> begin_in_order();
    InOrderIterator<T, K> end_in_order();
    PostOrderIterator<T, K> begin_post_order();
    PostOrderIterator<T, K> end_post_order();
    DFSIterator<T, K> begin_dfs_scan();
    DFSIterator<T, K> end_dfs_scan();
    MinHeapIterator<T, K> begin_heap();
    MinHeapIterator<T, K> end_heap();

    // Default begin and end methods for range-based for loop
    BFSIterator<T, K> begin();
    BFSIterator<T, K> end();

};

template<typename T, int K>
Tree<T, K>::Tree() : root(nullptr) {}

template<typename T, int K>
Tree<T, K>::Tree(Node<T>* key) : root(key) {}

// Destructor

template<typename T, int K>
Tree<T, K>::~Tree() {
   std::function<void(Node<T>*)> del_node = [&](Node<T>* node) {
        if (node) {
            for (auto& child : node->children) {
                del_node(child);
            }
            node->children.clear();
        }
    };
    del_node(root);
    root = nullptr;
}



template<typename T, int K>
void Tree<T, K>::add_root(Node<T>& node) {
    delete root;
    root = new Node<T>(node.get_value());
}

template<typename T, int K>
void Tree<T, K>::add_sub_node(Node<T>& parent, Node<T>& child) {
    if (!root) {
        throw std::runtime_error("Tree is empty, add a root node first!");
    }

    std::stack<Node<T>*> stack;
    stack.push(root);

    while (!stack.empty()) {
        Node<T>* node = stack.top();
        stack.pop();

        if (node->get_value() == parent.get_value()) {
            if (node->children.size() < K) {
                node->children.push_back(new Node<T>(child.get_value()));
                return;
            } else {
                throw std::runtime_error("Parent node has reached maximum children!");
            }
        }

        // Push children onto the stack in reverse order to maintain correct order in DFS
        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
            stack.push(*it);
        }
    }

    throw std::runtime_error("Parent node not found!");
}



template<typename T, int K>
BFSIterator<T, K> Tree<T, K>::begin_bfs_scan() {
    return BFSIterator<T, K>(root);
}

template<typename T, int K>
BFSIterator<T, K> Tree<T, K>::end_bfs_scan() {
    return BFSIterator<T, K>(nullptr);
}

template<typename T, int K>
PreOrderIterator<T, K> Tree<T, K>::begin_pre_order() {
    return PreOrderIterator<T, K>(root);
}

template<typename T, int K>
PreOrderIterator<T, K> Tree<T, K>::end_pre_order() {
    return PreOrderIterator<T, K>(nullptr);
}

template<typename T, int K>
InOrderIterator<T, K> Tree<T, K>::begin_in_order() {
    return InOrderIterator<T, K>(root);
}

template<typename T, int K>
InOrderIterator<T, K> Tree<T, K>::end_in_order() {
    return InOrderIterator<T, K>(nullptr);
}

template<typename T, int K>
PostOrderIterator<T, K> Tree<T, K>::begin_post_order() {
    return PostOrderIterator<T, K>(root);
}

template<typename T, int K>
PostOrderIterator<T, K> Tree<T, K>::end_post_order() {
    return PostOrderIterator<T, K>(nullptr);
}

template<typename T, int K>
DFSIterator<T, K> Tree<T, K>::begin_dfs_scan() {
    return DFSIterator<T, K>(root);
}

template<typename T, int K>
DFSIterator<T, K> Tree<T, K>::end_dfs_scan() {
    return DFSIterator<T, K>(nullptr);
}

template<typename T, int K>
MinHeapIterator<T, K> Tree<T, K>::begin_heap() {
    return MinHeapIterator<T, K>(root);
}

template<typename T, int K>
MinHeapIterator<T, K> Tree<T, K>::end_heap() {
    return MinHeapIterator<T, K>(nullptr);
}

template<typename T, int K>
BFSIterator<T, K> Tree<T, K>::begin() {
    return begin_bfs_scan();
}

template<typename T, int K>
BFSIterator<T, K> Tree<T, K>::end() {
    return end_bfs_scan();
}


#endif // TREE_HPP
