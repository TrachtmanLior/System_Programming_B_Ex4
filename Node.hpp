// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <stack>
#include <queue>

template<typename T>
class Node {
public:
    T data; // The data stored in the node.
    std::vector<Node<T>*> children; // The children nodes of this node.

    Node(const T& data);
    Node(const Node& other); // Copy constructor
    ~Node();

    // Getter for data
    T get_value() const;

    // Getter for children
    const std::vector<Node<T>*>& get_children() const;

};

// Constructor implementation
template<typename T>
Node<T>::Node(const T& data) : data(data) {}

// Copy constructor implementation
template<typename T>
Node<T>::Node(const Node<T>& other) : data(other.data), children(other.children) {
    for (const Node<T>* child : other.children) {
        children.push_back(new Node<T>(*child));
    }
}

// Destructor
template<typename T>
Node<T>::~Node() {
    for (Node<T>* child : children) {
        delete child;
    }
}

// Getter for node data
template<typename T>
T Node<T>::get_value() const {
    return data;
}


// Getter for children
template<typename T>
const std::vector<Node<T>*>& Node<T>::get_children() const {
    return children;
}



#endif // NODE_HPP
