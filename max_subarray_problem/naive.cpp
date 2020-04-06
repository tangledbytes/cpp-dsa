#include <chrono>
#include <iostream>
#include <vector>

std::vector<int> maxSubarray(std::vector<int>& arr) {
  int size = arr.size();
  int max_sum = 0, min_index = 0, max_index = size - 1;

  for (auto val : arr) {
    max_sum += val;
  }

  for (int i = 0; i < size - 1; ++i) {
    int local_sum = 0;
    for (int j = i; j < size; ++j) {
      local_sum += arr[j];
      if (local_sum > max_sum) {
        min_index = i;
        max_index = j;
        max_sum = local_sum;
      }
    }
  }

  std::vector<int> result = {min_index, max_index, max_sum};

  return result;
}

int main(int argc, char** argv) {
  std::vector<int> arr = {-13, -3,  -25, -20, -3, -16, -23, 18,  20,  -7, 12,
                          -5,  -22, 15,  -4,  7,  -13, -3,  -25, -20, -3, -16,
                          -23, 18,  20,  -7,  12, -5,  -22, 15,  -4,  7};
  std::vector<int> arr1 = {-1, -100, 200, 56, -2};

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> res = maxSubarray(arr1);
  auto stop = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

  std::cout << duration.count() << std::endl;

  for (auto val : res) {
    std::cout << val << std::endl;
  }

  return 0;
}