#pragma once
#include "heap.hpp"
#include "utils/utils.hpp"

namespace
{
	int *merge_into_one(int *arr1, int *arr2, int size1, int size2)
	{
		int *res = new int[size1 + size2];
		int index1 = 0;
		int index2 = 0;
		int i = 0;

		while (index1 < size1 && index2 < size2)
		{
			if (arr1[index1] <= arr2[index2])
			{
				res[i++] = arr1[index1++];
			}
			else
			{
				res[i++] = arr2[index2++];
			}
		}

		while (index1 < size1)
		{
			res[i++] = arr1[index1++];
		}

		while (index2 < size2)
		{
			res[i++] = arr2[index2++];
		}

		return res;
	}

	int partition(int *arr, int l, int r)
	{
		int pivot = arr[l];
		int j = l;

		for (int i = l + 1; i <= r; ++i)
		{
			if (arr[i] <= pivot)
			{
				utstl::utils::swap<int>(&arr[i], &arr[++j]);
			}
		}

		utstl::utils::swap<int>(&arr[j], &arr[l]);

		return j;
	}
} // namespace

namespace utstl
{

	namespace Sort
	{

		// Performs merge sort on the given array
		// Returns sorted array
		int *merge(int arr[], int start, int end)
		{
			if (start == end)
			{
				int *res = new int[1];
				res[0] = arr[start];
				return res;
			}

			int mid = (start + end) / 2;
			int *arr1 = merge(arr, start, mid);
			int *arr2 = merge(arr, mid + 1, end);

			int *res = merge_into_one(arr1, arr2, mid - start + 1, end - (mid + 1) + 1);

			// Delete the arrays
			delete[] arr1;
			delete[] arr2;

			return res;
		}

		// Performs insertion sort on the given array
		void insertion(int arr[], int size)
		{
			for (int i = 0; i < size - 1; ++i)
			{
				int j = i;
				int key = i + 1;
				while (j > -1 && arr[j] > arr[key])
				{
					utstl::utils::swap<int>(&arr[j--], &arr[key--]);
				}
			}
		}

		// Performs heap sort on the given array
		int *heap(int arr[], int size)
		{
			MaxHeap heap(arr, size);
			int *heapArr = new int[size];
			int *tempArr = heap.get_heap();

			// Store the heap into the array
			for (int i = 0; i < size; ++i)
				heapArr[i] = tempArr[i];

			for (int i = size - 1; i > 0; --i)
			{
				// Exchange first and ith element
				utils::swap<int>(&heapArr[0], &heapArr[i]);

				// Decrement heap size
				size--;

				// Heapify the remaining array
				Heap::max_heapify(heapArr, size, 0);
			}

			return heapArr;
		}

		void quick(int *arr, int l, int r)
		{
			if (l < r)
			{
				int pivot = partition(arr, l, r);
				quick(arr, l, pivot - 1);
				quick(arr, pivot + 1, r);
			}
		}

	} // namespace Sort
} // namespace utstl