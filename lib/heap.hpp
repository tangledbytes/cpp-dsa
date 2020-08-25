#pragma once
#include <stdexcept>

#include "utils/utils.hpp"

namespace utstl
{
	enum class Heap_Type
	{
		MIN,
		MAX
	};

	template <typename T = int, Heap_Type t = Heap_Type::MAX>
	class Heap
	{
		T *arr;
		int size;
		int capacity;

	private:
		static constexpr int DEFAULT_CAPACITY = 10;
		static constexpr int RESIZE_DOUBLE_THRESHOLD = 100;

	private:
		static void max_heapify(T arr[], int size, int index)
		{
			int preferred_index;
			while (true)
			{
				int left = (2 * index) + 1;
				int right = (2 * index) + 2;

				if (left < size && arr[left] > arr[index])
					preferred_index = left;
				else
					preferred_index = index;

				if (right < size && arr[right] > arr[preferred_index])
					preferred_index = right;

				if (preferred_index != index)
				{
					utils::swap<T>(arr[preferred_index], arr[index]);
					index = preferred_index;
					continue;
				}

				return;
			}
		}

		static void min_heapify(T arr[], int size, int index)
		{
			int preferred_index;
			while (true)
			{
				int left = (2 * index) + 1;
				int right = (2 * index) + 2;

				if (left < size && arr[left] < arr[index])
					preferred_index = left;
				else
					preferred_index = index;

				if (right < size && arr[right] < arr[preferred_index])
					preferred_index = right;

				if (preferred_index != index)
				{
					utils::swap<T>(arr[preferred_index], arr[index]);
					index = preferred_index;
					continue;
				}

				return;
			}
		}

		void max_insert(T data)
		{
			// Resize the heap if the it is full
			if (size == capacity)
				resize();

			arr[size] = data;

			for (int i = size; i != 0 && arr[parent(i)] < arr[i];)
			{
				utils::swap<T>(arr[i], arr[parent(i)]);
				i = parent(i);
			}

			++size;
		}

		void min_insert(T data)
		{
			// Resize the heap if the it is full
			if (size == capacity)
				resize();

			arr[size] = data;

			for (int i = size; i != 0 && arr[parent(i)] > arr[i];)
			{
				utils::swap<T>(arr[i], arr[parent(i)]);
				i = parent(i);
			}

			++size;
		}

	public:
		explicit Heap(int capacity = DEFAULT_CAPACITY) : size(0), capacity(capacity)
		{
			arr = new T[capacity];
		}

		explicit Heap(T arr[], int size, int capacity) : size(size), capacity(capacity)
		{
			this->arr = new T[capacity];
			// Copy the array to the internal array
			for (int i = 0; i < size; ++i)
				this->arr[i] = arr[i];

			// Heapify entire array
			for (int i = (size / 2) - 1; i > -1; --i)
			{
				heapify(this->arr, size, i);
			}
		}

		static void heapify(T arr[], int size, int index = 0)
		{
			if (t == Heap_Type::MAX)
				return max_heapify(arr, size, index);
			if (t == Heap_Type::MIN)
				return min_heapify(arr, size, index);
		}

		T *get_heap() const
		{
			return arr;
		}

		int get_size() const
		{
			return size;
		}

		int get_capacity() const
		{
			return capacity;
		}

		void resize(int cap)
		{
			// Don't resize if the requested capacity
			// is lower than the size of the array
			if (cap < size)
				return;

			T *newArr = new int[cap];
			for (int i = 0; i < size; ++i)
				newArr[i] = arr[i];

			T *temp = arr;
			delete[] temp;
			arr = newArr;
			capacity = cap;
		}

		void resize()
		{
			// If the capacity of the heap is lesser than the
			// threshold then double the size of the internal array
			if (capacity <= RESIZE_DOUBLE_THRESHOLD)
				return resize(capacity * 2);

			return resize(capacity * 1.5);
		}

		T top() const { return arr[0]; }

		size_t parent(size_t index) const
		{
			// TODO add proper index validation
			return (index - 1) / 2;
		}

		Heap<T, t> &insert(T data)
		{
			if (t == Heap_Type::MAX)
				max_insert(data);
			else
				min_insert(data);

			return *this;
		}

		T remove(int index)
		{
			if (size == 0)
				return T{};

			T value = arr[index];
			arr[index] = arr[--size];

			heapify(arr, size, index);

			return value;
		}

		~Heap() { delete[] arr; }
	};

} // namespace utstl