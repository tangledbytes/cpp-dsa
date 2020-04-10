#pragma once

namespace utstl {
template <typename T>
class Node {
 public:
  T data;
  Node *next;

 public:
  Node() : data(T()), next(nullptr) {}
  Node(T data) {
    this->data = data;
    next = nullptr;
  }
};
}  // namespace utstl