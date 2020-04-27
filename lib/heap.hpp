#pragma once
#include <stdexcept>

#include "utils/utils.hpp"

namespace utstl
{
class Heap
{
protected:
  int *internal_arr;
  int heap_size;
  int max_size;

private:
  void construct_heap(int size)
  {
    internal_arr = new int[size];
    if (!internal_arr)
    {
      std::overflow_error("Couldn't allocate the memory!");
    }
    heap_size = 0;
    max_size = size;
  }

public:
  explicit Heap(int size) { construct_heap(size); }

  int *get_heap() const { return internal_arr; }
  int get_size() const { return heap_size; }
  void set_size(int size)
  {
    if (size > -1)
      heap_size = size;
  }

  static void max_heapify(int *arr, int size, int index);
  static void max_heapify_iterative(int *arr, int size, int index);
  static void min_heapify(int *arr, int size, int index);
  static void min_heapify_iterative(int *arr, int size, int index);

  ~Heap() { delete[] internal_arr; }
};

void Heap::max_heapify(int *arr, int size, int index)
{
  int left = (2 * index) + 1;
  int right = (2 * index) + 2;
  int largest = 0;

  if (left < size && arr[left] > arr[index])
    largest = left;
  else
    largest = index;

  if (right < size && arr[right] > arr[largest])
    largest = right;

  if (largest != index)
  {
    utstl::utils::swap<int>(&arr[largest], &arr[index]);
    max_heapify(arr, size, largest);
  }
}

void Heap::max_heapify_iterative(int *arr, int size, int index)
{
  int i = index;
  int largest = 0;
  while (true)
  {
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (left < size && arr[left] > arr[i])
      largest = left;
    else
      largest = i;

    if (right < size && arr[right] > arr[largest])
      largest = right;

    if (largest != i)
    {
      utstl::utils::swap<int>(&arr[largest], &arr[i]);
      i = largest;
      continue;
    }

    return;
  }
}

void Heap::min_heapify(int *arr, int size, int index)
{
  int left = (2 * index) + 1;
  int right = (2 * index) + 2;
  int smallest = 0;

  if (left < size && arr[left] < arr[index])
    smallest = left;
  else
    smallest = index;

  if (right < size && arr[right] < arr[smallest])
    smallest = right;

  if (smallest != index)
  {
    utstl::utils::swap<int>(&arr[smallest], &arr[index]);
    min_heapify(arr, size, smallest);
  }
}

void Heap::min_heapify_iterative(int *arr, int size, int index)
{
  int i = index;
  while (true)
  {
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    int smallest = 0;

    if (left < size && arr[left] < arr[i])
      smallest = left;
    else
      smallest = i;

    if (right < size && arr[right] < arr[smallest])
      smallest = right;

    if (smallest != i)
    {
      utstl::utils::swap<int>(&arr[smallest], &arr[i]);
      i = smallest;
      continue;
    }

    return;
  }
}

// //////////////////////////// CLASS MAXHEAP //////////////////////////////////
// MaxHeap class encapsulates the max-heap

class MaxHeap : public Heap
{
private:
  void construct_from_array(int *arr, int size)
  {
    heap_size = size;
    for (int i = 0; i < size; ++i)
      internal_arr[i] = arr[i];
    for (int i = (size / 2) - 1; i > -1; --i)
    {
      max_heapify_iterative(internal_arr, heap_size, i);
    }
  }

public:
  MaxHeap(int size) : Heap(size) {}
  MaxHeap(int *arr, int size) : Heap(size) { construct_from_array(arr, size); }

  int get_max();
  int extract_max();
  void increase_key(int index, int key);
  void insert(int key);
  int remove(int index);
};

int MaxHeap::get_max() { return internal_arr[0]; }

int MaxHeap::extract_max()
{
  if (heap_size < 1)
    return -1;

  int max = get_max();
  internal_arr[0] = internal_arr[--heap_size];
  max_heapify_iterative(internal_arr, heap_size, 0);

  return max;
}

void MaxHeap::increase_key(int index, int key)
{
  if (internal_arr[index] > key)
    return;

  internal_arr[index] = key;

  while (index > 0 && internal_arr[(index - 1) / 2] < internal_arr[index])
  {
    utils::swap<int>(&internal_arr[(index - 1) / 2], &internal_arr[index]);

    index = (index - 1) / 2;
  }
}

void MaxHeap::insert(int key)
{
  if (heap_size > max_size - 1)
    return;

  internal_arr[heap_size] = INT8_MIN;

  increase_key(heap_size++, key);
}

int MaxHeap::remove(int index)
{
  if (heap_size < 1 || index > heap_size)
    return -1;

  int value = internal_arr[index];
  internal_arr[index] = internal_arr[--heap_size];

  max_heapify_iterative(internal_arr, heap_size, index);

  return value;
}

// //////////////////////////// CLASS MINHEAP //////////////////////////////////
// MinHeap class encapsulates the min-heap

class MinHeap : public Heap
{
private:
  void construct_from_array(int *arr, int size)
  {
    heap_size = size;
    for (int i = 0; i < size; ++i)
      internal_arr[i] = arr[i];
    for (int i = (size / 2) - 1; i > -1; --i)
    {
      min_heapify_iterative(internal_arr, heap_size, i);
    }
  }

public:
  MinHeap(int size) : Heap(size) {}
  MinHeap(int *arr, int size) : Heap(size) { construct_from_array(arr, size); }
  MinHeap(int *arr, int size, int max_size) : Heap(max_size)
  {
    construct_from_array(arr, size);
  }

  int get_min();
  int extract_min();
  void decrease_key(int index, int key);
  void insert(int key);
  int remove(int index);
};

int MinHeap::get_min() { return internal_arr[0]; }
int MinHeap::extract_min()
{
  if (heap_size < 1)
    return -1;

  int min = get_min();

  internal_arr[0] = internal_arr[--heap_size];
  min_heapify_iterative(internal_arr, heap_size, 0);

  return min;
}

void MinHeap::decrease_key(int index, int key)
{
  if (internal_arr[index] < key)
    return;

  internal_arr[index] = key;

  while (index > 0 && internal_arr[(index - 1) / 2] > internal_arr[index])
  {
    utils::swap<int>(&internal_arr[(index - 1) / 2], &internal_arr[index]);
    index = (index - 1) / 2;
  }
}

void MinHeap::insert(int key)
{
  if (heap_size > max_size - 1)
    return;

  internal_arr[heap_size] = INT8_MAX;

  decrease_key(heap_size++, key);
}

int MinHeap::remove(int index)
{
  if (heap_size < 1 || index > heap_size)
    return -1;

  int value = internal_arr[index];
  internal_arr[index] = internal_arr[--heap_size];

  min_heapify_iterative(internal_arr, heap_size, index);

  return value;
}

} // namespace utstl