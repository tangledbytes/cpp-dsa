#pragma once

#include "node.hpp"

namespace utstl {

template <class T>
class LinkedList {
  Node<T> *Head;

 public:
  int length;

 public:
  LinkedList() : Head(nullptr), length(0) {}
  void insert(T data);
  T remove(T key);
  bool exists(T key);
  void forEach(void (*func)(T &data));
  void forEach(void (*func)(T data));

  ~LinkedList() {
    while (Head) {
      Node<T> *temp = Head;
      Head = Head->next;
      delete temp;
      --length;
    }
  }
};

/**
 * Iterates over each element of the queue
 * */
template <class T>
void LinkedList<T>::forEach(void (*func)(T &data)) {
  Node<T> *temp = Head;
  while (temp) {
    func(temp->data);
    temp = temp->next;
  }
}

/**
 * Iterates over each element of the queue
 * */
template <class T>
void LinkedList<T>::forEach(void (*func)(T data)) {
  Node<T> *temp = Head;
  while (temp) {
    func(temp->data);
    temp = temp->next;
  }
}

template <typename T>
void LinkedList<T>::insert(T data) {
  // Create a new node
  Node<T> *node = new Node<T>(data);

  node->next = Head;
  Head = node;

  ++length;
}

template <typename T>
T LinkedList<T>::remove(T key) {
  Node<T> *temp = Head, *tail = nullptr;
  T data = T();

  while (temp && temp->data != key) {
    tail = temp;
    temp = temp->next;
  }

  if (temp) {
    if (tail) tail->next = temp->next;
    data = temp->data;
    if (temp == Head) Head = temp->next;
    delete temp;
    --length;
  }

  return data;
}

template <typename T>
bool LinkedList<T>::exists(T key) {
  Node<T> *temp = Head;

  while (temp && temp->data != key) {
    temp = temp->next;
  }

  return !!temp;
}

}  // namespace utstl