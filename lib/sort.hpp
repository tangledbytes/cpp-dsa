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

	// partition function partitions an array into 3
	// parts. It uses a slower variant of partition algorithm
	// called Lomuto's partition
	int lomuto_partition(int *arr, int l, int r)
	{
		int pivot = arr[r];
		int j = l - 1;

		for (int i = l; i < r; ++i)
		{
			if (arr[i] <= pivot)
			{
				utstl::utils::swap<int>(&arr[i], &arr[++j]);
			}
		}

		utstl::utils::swap<int>(&arr[++j], &arr[r]);

		return j;
	}

	// hoare_partition function uses the original hoare's
	// partition algorithm to partition the arrays
	int hoare_partition(int arr[], int l, int r)
	{
		int pivot = arr[l];
		int i = l - 1;
		int j = r + 1;

		while (true)
		{
			while (arr[++i] < pivot)
				;
			while (arr[--j] > pivot)
				;

			if (i >= j)
				return j;

			utstl::utils::swap<int>(&arr[i], &arr[j]);
		}
	}

	// medianOf3 returns the index of median of the three
	// value corresponding to the indices in the array
	int medianOf3(int arr[], int i1, int i2, int i3)
	{
		return (
			(arr[i1] > arr[i2]) ? (arr[i2] > arr[i3]) ? i2 : (arr[i1] > arr[i3]) ? i3 : i1 : (arr[i3] < arr[i1]) ? i1 : (arr[i3] > arr[i2]) ? i2 : i3);
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
			Heap<int, Heap_Type::MIN> heap(arr, size, size);
			int *heapArr = new int[size];
			int *tempArr = heap.get_heap();

			// Store the heap into the array
			for (int i = 0; i < size; ++i)
				heapArr[i] = tempArr[i];

			for (int i = size - 1; i > 0; --i)
			{
				// Exchange first and ith element
				utils::swap<int>(heapArr[0], heapArr[i]);

				// Decrement heap size
				size--;

				// Heapify the remaining array
				Heap<int, Heap_Type::MIN>::heapify(heapArr, size, 0);
			}

			return heapArr;
		}

		void lomuto_quick(int arr[], int l, int r)
		{
			if (l >= r)
				return;

			int pivot = lomuto_partition(arr, l, r);
			lomuto_quick(arr, l, pivot - 1);
			lomuto_quick(arr, pivot + 1, r);
		}

		void hoare_quick(int arr[], int l, int r)
		{
			if (l < r)
			{
				int pivot = hoare_partition(arr, l, r);
				hoare_quick(arr, l, pivot);
				hoare_quick(arr, pivot + 1, r);
			}
		}

		// quick function usses optimised bentley-mcilroy
		// quicksort algorithm to sort the provided array
		// in place. These optimisations were suggested by Robert
		// Sedgewick in his paper "Analysis of Quick Sort" in 1976
		void quick(int arr[], int l, int r)
		{
			constexpr int INSERTION_SORT_THRESHOLD = 8;
			constexpr int MEDIAN_OF_3_THRESHOLD = 40;

			int size = r - l + 1;

			// Perfrom insertion sort if the size is below the
			// insertion sort threshold
			if (size <= INSERTION_SORT_THRESHOLD)
			{
				return insertion(arr, size);
			}

			// Median of 3 has better constant than the randomised
			// quicksort approach. The time complexities of the two are as
			// follows:
			// Randomised Quicksort ~ 1.386nlogn
			// Median of 3 Quicksort ~ 1.188nlogn
			if (size <= MEDIAN_OF_3_THRESHOLD)
			{
				int med = medianOf3(arr, l, l + size / 2, r);

				// Swap the median with the median
				utils::swap<int>(arr[med], arr[l]);
			}
			else
			{
				// If the array size is too big then use the ninther
				int eps = size / 8;
				int mid = l + size / 2;
				int m1 = medianOf3(arr, l, l + eps, l + eps + eps);
				int m2 = medianOf3(arr, mid - eps, mid, mid + eps);
				int m3 = medianOf3(arr, r - eps - eps, r - eps, r);

				int ninther = medianOf3(arr, m1, m2, m3);
				utils::swap<int>(arr[ninther], arr[l]);
			}

			// Bentley-McIlroy Procedure
			int i = l, j = r + 1;
			int p = l, q = r + 1;

			int pivot = arr[l];
			while (true)
			{
				while (arr[++i] < pivot)
					if (i == r)
						break;

				while (arr[--j] > pivot)
					if (j == l)
						break;

				if (i == j && (arr[i] == pivot))
					utils::swap<int>(arr[++p], arr[i]);
				if (i >= j)
					break;

				utils::swap<int>(arr[i], arr[j]);
				if (arr[i] == pivot)
					utils::swap<int>(arr[++p], arr[i]);
				if (arr[j] == pivot)
					utils::swap<int>(arr[--q], arr[j]);
			}

			i = j + 1;
			for (int k = l; k <= p; ++k)
				utils::swap<int>(arr[k], arr[j--]);
			for (int k = r; k >= q; --k)
				utils::swap<int>(arr[k], arr[i++]);

			quick(arr, l, j);
			quick(arr, i, r);
		}

	} // namespace Sort
} // namespace utstl