#pragma once

#include "node.hpp"

namespace utstl {

template <class T>
class LinkedList {
  Node<T> Head;  // Kind of a sentinel

 public:
  int length;

 public:
  LinkedList() : Head(), length(0) {}
  void insert(T data);
  T remove(T key);
  bool exists(T key);
  void forEach(void (*func)(T &data));
  void forEach(void (*func)(T data));

  ~LinkedList() {
    Node<T> *localHead = Head.next;
    while (localHead) {
      Node<T> *temp = localHead;
      localHead = localHead->next;
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
  Node<T> *temp = Head.next;
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
  Node<T> *temp = Head.next;
  while (temp) {
    func(temp->data);
    temp = temp->next;
  }
}

template <typename T>
void LinkedList<T>::insert(T data) {
  // Create a new node
  Node<T> *node = new Node<T>(data);

  node->next = Head.next;
  Head.next = node;

  ++length;
}

template <typename T>
T LinkedList<T>::remove(T key) {
  Node<T> *temp = Head.next, *tail = &Head;
  T data = T();

  while (temp && temp->data != key) {
    tail = temp;
    temp = temp->next;
  }

  if (temp) {
    tail->next = temp->next;
    data = temp->data;
    delete temp;
    --length;
  }

  return data;
}

template <typename T>
bool LinkedList<T>::exists(T key) {
  Node<T> *temp = Head.next;

  while (temp && temp->data != key) {
    temp = temp->next;
  }

  return !!temp;
}

}  // namespace utstl