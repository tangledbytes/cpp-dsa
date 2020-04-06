#pragma once

#include "node.hpp"

namespace utstl {

template <class T>
class Stack {
  Node<T> *top = nullptr;
  unsigned int _size = 0;

 private:
  void deepCopy(const Stack<T> &);

 public:
  Stack();
  Stack(const Stack<T> &);
  Stack(T[], int size);
  T peek();
  T pop();
  void push(T);
  bool isEmpty();
  void forEach(void (*func)(T &data));
  void forEach(void (*func)(T data));
  Stack<T> &operator=(const Stack<T> &);
  ~Stack();
};

template <typename T>
Stack<T>::Stack() {}

template <typename T>
Stack<T>::Stack(T data[], int size) {
  for (int i = 0; i < size; ++i) push(data[i]);
}

template <typename T>
Stack<T>::Stack(const Stack<T> &other) {
  deepCopy(other);
}

template <typename T>
void Stack<T>::deepCopy(const Stack<T> &source) {
  Node<T> *temp = source.top;
  while (!isEmpty()) pop();
  while (temp) {
    push(temp->data);
    temp = temp->next;
  }
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &source) {
  if (this == &source) return *this;
  deepCopy(source);
  return *this;
}

template <typename T>
void Stack<T>::push(T data) {
  Node<T> *node = new Node<T>(data);

  node->next = top;
  top = node;
  ++_size;
}

template <typename T>
T Stack<T>::pop() {
  T data{};

  if (!isEmpty()) {
    Node<T> *temp = top;
    data = top->data;
    temp = top;
    top = top->next;
    --_size;
    delete temp;
  }

  return data;
}

template <typename T>
bool Stack<T>::isEmpty() {
  return !_size;
}

template <typename T>
T Stack<T>::peek() {
  T data{};
  if (!isEmpty()) data = top->data;
  return data;
}

template <typename T>
void Stack<T>::forEach(void (*func)(T data)) {
  Node<T> *temp = top;
  while (temp) {
    func(temp->data);
    temp = temp->next;
  }
}

template <typename T>
void Stack<T>::forEach(void (*func)(T &data)) {
  Node<T> *temp = top;
  while (temp) {
    func(temp->data);
    temp = temp->next;
  }
}

template <typename T>
Stack<T>::~Stack() {
  while (!isEmpty()) pop();
}
}