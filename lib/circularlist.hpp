#pragma once

#include "node.hpp"

namespace utstl {
template <class T>
class CircularList {
  Node<T> sentinel;
  int length;

 public:
  CircularList() : sentinel(), length(0) {}
  void insert(T data) {
    Node<T> *node = new Node<T>();

    node->next = sentinel.next;
    // If sentinel.next is not null
    if (sentinel.next) sentinel.next->next = node;
    sentinel.next = node;
    // Increment the length
    ++length;
  }
};
}  // namespace utstl