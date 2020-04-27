#pragma once

#include "node.hpp"
#include <functional>

namespace utstl
{

template <class T>
class Queue
{
  Node<T> *front = nullptr, *rear = nullptr;
  int _size = 0;

public:
  Queue();
  Queue(T[], int);
  void enqueue(T);
  T dequeue();
  T peek();
  void forEach(const std::function<void(T)> &);
  int size();
  bool isEmpty();
  void reverse();
  ~Queue();
};

/**
 * Constructor without any arguments
 * */
template <typename T>
Queue<T>::Queue() {}

/**
 * Constructor with array as an argument which can be used to initialise the
 * queue
 * */
template <typename T>
Queue<T>::Queue(T arr[], int size)
{
  for (int i = 0; i < size; ++i)
  {
    enqueue(arr[i]);
  }
}

/**
 * Iterates over each element of the queue
 * */
template <class T>
void Queue<T>::forEach(const std::function<void(T)> &func)
{
  Node<T> *temp = front;
  while (temp)
  {
    func(temp->data);
    temp = temp->next;
  }
}

/**
 * Add element to the end of the queue
 * */
template <typename T>
void Queue<T>::enqueue(T data)
{
  Node<T> *node = new Node<T>(data);

  if (isEmpty())
  {
    front = rear = node;
    ++_size;
    return;
  }

  rear->next = node;
  rear = node;
  ++_size;
}

/**
 * Remove element from the start of the queue
 * */
template <typename T>
T Queue<T>::dequeue()
{
  T data{};

  if (!isEmpty())
  {
    Node<T> *temp = front;
    data = front->data;
    front = front->next;
    --_size;
    delete temp;

    if (isEmpty())
      rear = nullptr;
  }

  return data;
}

/**
 * Get the front element without removing it from the queue
 * */
template <typename T>
T Queue<T>::peek()
{
  T data{};

  if (!isEmpty())
  {
    T value = front->data;
    data = value;
  }

  return data;
}

/**
 * Get the front element without removing it from the queue
 * */
template <typename T>
void Queue<T>::reverse()
{
  int size = _size;
  while (size--)
  {
    enqueue(dequeue());
  }
}

/**
 * get size of the queue
 * */
template <typename T>
int Queue<T>::size()
{
  return _size;
}

/**
 * Return true if array is empty
 * */
template <typename T>
bool Queue<T>::isEmpty()
{
  return !_size;
}

/**
 * Releases all the allocated memeory for the queue
 * */
template <typename T>
Queue<T>::~Queue()
{
  while (front)
  {
    Node<T> *temp = front;
    front = front->next;
    delete temp;
  }
}
} // namespace utstl