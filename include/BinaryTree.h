#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>

template <typename T>
class Node {
public:
    T value;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;

    template <typename U>
    Node(U&& value)
        : value(std::forward<U>(value)) {
    }

    /* setters */
    template <typename U>
    void set_value(U&& new_value) {
        value = std::forward<U>(new_value);
    }

    template <typename U>
    void set_left(U&& new_left) {
        left = std::make_unique<Node<T>>(std::forward<U>(new_left));
    }
    template <typename U>
    void set_right(U&& new_right) {
        right = std::make_unique<Node<T>>(std::forward<U>(new_right));
    }

    /* getters */
    Node<T>* get_left() const {
        return left.get();
    }
    Node<T>* get_right() const {
        return right.get();
    }
};

#endif
