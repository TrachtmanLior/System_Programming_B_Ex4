// written by Lior Trachtman: 211791041
// EMAIL: lior16122000@gmail.com
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Node.hpp"
#include <queue>
#include <stack>
#include <vector>
#include <algorithm> // For std::sort
#include <functional> // For std::greater

// Base class for all iterators
template<typename T>
class Iterator {
protected:
    Node<T>* current;  // Pointer to the current node

public:
    Iterator() : current(nullptr) {}  // Constructor initializes current to nullptr
    Node<T>* operator*() { return current; }  // Dereference operator
    Node<T>* operator->() { return current; }  // Arrow operator
    bool operator!=(const Iterator<T>& other) const { return current != other.current; }  // Inequality operator
    bool operator==(const Iterator<T>& other) const { return current == other.current; }  // Equality operator
};

//==============BFS ITERATOR IMPLEMENTATION==================================
template<typename T, size_t k = 2>
class BFSIterator : public Iterator<T> {
private:
    std::queue<Node<T>*> nodeQueue;  // Queue to manage the nodes for traversal

public:
    // Constructor initializes the iterator with the root node
    explicit BFSIterator(Node<T>* root) {
        if (root) {
            nodeQueue.push(root);  // Push the root node onto the queue
            this->current = root;  // Initialize current to root
        } else {
            this->current = nullptr;
        }
    }

    // Pre-increment operator to advance the iterator
    BFSIterator<T, k>& operator++() {
        if (!nodeQueue.empty()) {
            Node<T>* currentNode = nodeQueue.front();
            nodeQueue.pop();

            // Enqueue all the children of the current node
            for (Node<T>* child : currentNode->get_children()) {
                if (child) {
                    nodeQueue.push(child);
                }
            }

            // Set current to the next node in the queue or nullptr if the queue is empty
            this->current = nodeQueue.empty() ? nullptr : nodeQueue.front();
        } else {
            this->current = nullptr;  // If the queue is empty, set current to nullptr
        }
        return *this;
    }
};

//==============DFS ITERATOR IMPLEMENTATION==================================
template<typename T, size_t k>
class DFSIterator : public Iterator<T> {
private:
    std::stack<Node<T>*> nodeStack;

public:
    explicit DFSIterator(Node<T>* root) {
        if (root) nodeStack.push(root);
        ++(*this);
    }

    DFSIterator<T, k>& operator++() {
        if (!nodeStack.empty()) {
            this->current = nodeStack.top();
            nodeStack.pop();

            for (auto it = this->current->get_children().rbegin(); it != this->current->get_children().rend(); ++it) {
                if (*it) nodeStack.push(*it);
            }
        } else {
            this->current = nullptr;
        }
        return *this;
    }
};

//==============IN ORDER ITERATOR IMPLEMENTATION==================================
template<typename T, size_t k>
class InOrderIterator : public Iterator<T> {
private:
    std::stack<Node<T>*> nodeStack;

    void pushLeftChildren(Node<T>* node) {
        while (node) {
            nodeStack.push(node);
            // Push all left children first
            if (!node->get_children().empty()) {
                node = node->get_children()[0]; // Move to the leftmost child
            } else {
                break;
            }
        }
    }

public:
    explicit InOrderIterator(Node<T>* root) {
        if (root) {
            if (k != 2) {
                nodeStack.push(root);  // Treat it as a DFS traversal for k != 2
            } else {
                pushLeftChildren(root);
            }
            ++(*this); // Move to the first valid node
        } else {
            this->current = nullptr;
        }
    }

    InOrderIterator<T, k>& operator++() {
        if (k != 2) {
            if (!nodeStack.empty()) {
                this->current = nodeStack.top();
                nodeStack.pop();

                for (auto it = this->current->get_children().rbegin(); it != this->current->get_children().rend(); ++it) {
                    if (*it) nodeStack.push(*it);
                }
            } else {
                this->current = nullptr;
            }
        } else {
            if (!nodeStack.empty()) {
                this->current = nodeStack.top();
                nodeStack.pop();
                Node<T>* node = this->current->get_children().size() > 1 ? this->current->get_children()[1] : nullptr;
                if (node) {
                    pushLeftChildren(node);
                }
            } else {
                this->current = nullptr;
            }
        }
        return *this;
    }
};
//==============POST ORDER ITERATOR IMPLEMENTATION==================================
template<typename T, size_t k>
class PostOrderIterator : public Iterator<T> {
private:
    std::stack<Node<T>*> nodeStack;
    std::stack<Node<T>*> outputStack;

    void fillOutputStack(Node<T>* root) {
        if (!root) return;
        nodeStack.push(root);
        while (!nodeStack.empty()) {
            Node<T>* node = nodeStack.top();
            nodeStack.pop();
            outputStack.push(node); // Push the node onto outputStack first
            // Push all children onto nodeStack
            for (auto& child : node->get_children()) {
                if (child) {
                    nodeStack.push(child);
                }
            }
        }
    }

    void dfs(Node<T>* root) {
        if (!root) return;
        std::stack<Node<T>*> tempStack;
        tempStack.push(root);
        while (!tempStack.empty()) {
            Node<T>* node = tempStack.top();
            tempStack.pop();
            outputStack.push(node);
            // Push children onto tempStack in reverse order
            for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) {
                if (*it) {
                    tempStack.push(*it);
                }
            }
        }
        // Reverse the order in the output stack
        std::stack<Node<T>*> reversedOutputStack;
        while (!outputStack.empty()) {
            reversedOutputStack.push(outputStack.top());
            outputStack.pop();
        }
        outputStack = std::move(reversedOutputStack);
    }

public:
    explicit PostOrderIterator(Node<T>* root) {
        if (root) {
            if (k == 2) {
                fillOutputStack(root);
            } else {
                dfs(root);
            }
            ++(*this); // Advance to the first element
        }
    }

    PostOrderIterator<T, k>& operator++() {
        if (!outputStack.empty()) {
            this->current = outputStack.top();
            outputStack.pop();
        } else {
            this->current = nullptr;
        }
        return *this;
    }
};



//==============PRE ORDER ITERATOR IMPLEMENTATION==================================
template<typename T, size_t k>
class PreOrderIterator : public Iterator<T> {
private:
    std::stack<Node<T>*> nodeStack;

public:
    explicit PreOrderIterator(Node<T>* root) {
        if (root) nodeStack.push(root);
        ++(*this);
    }

    PreOrderIterator<T, k>& operator++() {
        if (!nodeStack.empty()) {
            this->current = nodeStack.top();
            nodeStack.pop();

            for (auto it = this->current->get_children().rbegin(); it != this->current->get_children().rend(); ++it) {
                if (*it) nodeStack.push(*it);
            }
        } else {
            this->current = nullptr;
        }
        return *this;
    }
};

//==============MIN HEAP ITERATOR IMPLEMENTATION==================================
template<typename T, size_t k = 2>
class MinHeapIterator : public Iterator<T> {
private:
    std::vector<Node<T>*> heap;
    size_t index;
    bool is_end;

    struct CompareNodes {
        bool operator()(Node<T>* a, Node<T>* b) const {
            return a->get_value() > b->get_value();
        }
    };

    void traverse(Node<T>* node) {
        if (node) {
            heap.push_back(node);
            for (Node<T>* child : node->get_children()) traverse(child);
        }
    }

public:
    explicit MinHeapIterator(Node<T>* root) : index(0), is_end(false) {
        traverse(root);
        std::make_heap(heap.begin(), heap.end(), CompareNodes());
        if (heap.empty()) is_end = true;
    }

    MinHeapIterator<T, k>& operator++() {
        if (!is_end) {
            std::pop_heap(heap.begin(), heap.end(), CompareNodes());
            heap.pop_back();
            if (heap.empty()) is_end = true;
        }
        return *this;
    }

    Node<T>* operator*() {
        return is_end ? nullptr : heap.front();
    }

    Node<T>* operator->() {
        return is_end ? nullptr : heap.front();
    }

    bool operator!=(const MinHeapIterator<T, k>& other) const {
        return index != other.index || is_end != other.is_end;
    }

    bool operator==(const MinHeapIterator<T, k>& other) const {
        return index == other.index && is_end == other.is_end;
    }
};

#endif // ITERATOR_HPP
