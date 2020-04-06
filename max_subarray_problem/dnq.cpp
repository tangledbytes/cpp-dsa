#include <chrono>
#include <iostream>
#include <vector>

void print(std::vector<int> &arr) {
  for (int val : arr) {
    std::cout << val << " ";
  }

  std::cout << std::endl;
}

// The solution is of two parts
// First part concerns with finding the maximum subaray which crosses the mid
// point Second part concerns with finding the subarray which is either in left
// or the right side of the mid point

// Function to find the subarray which crosses the mid point
std::vector<int> find_cross_subarray(std::vector<int> &arr, int low, int mid,
                                     int high) {
  int left, right, sum = 0;
  int left_sum = INT32_MIN;

  for (int i = mid; i >= low; --i) {
    sum += arr[i];
    if (sum > left_sum) {
      left = i;
      left_sum = sum;
    }
  }

  int right_sum = INT32_MIN;
  sum = 0;

  for (int i = mid + 1; i <= high; ++i) {
    sum += arr[i];
    if (sum > right_sum) {
      right = i;
      right_sum = sum;
    }
  }

  std::vector<int> result = {left, right, left_sum + right_sum};

  return result;
}

// Function to recursively divide and solve the problem
std::vector<int> max_subarray(std::vector<int> &arr, int low, int high) {
  std::vector<int> result;

  // Define the base case
  if (low == high) {
    result.push_back(low);
    result.push_back(high);
    result.push_back(arr[low]);

    return result;
  }

  int mid = (low + high) / 2;

  std::vector<int> left_array = max_subarray(arr, low, mid);
  std::vector<int> cross_array = find_cross_subarray(arr, low, mid, high);
  std::vector<int> right_array = max_subarray(arr, mid + 1, high);

  // std::cout << "=============================" << std::endl;
  // print(left_array);
  // print(cross_array);
  // print(right_array);
  // std::cout << "=============================" << std::endl;

  if (left_array[2] >= right_array[2] && left_array[2] >= cross_array[2]) {
    return left_array;
  } else if (right_array[2] >= left_array[2] &&
             right_array[2] >= cross_array[2]) {
    return right_array;
  } else
    return cross_array;
}

// Main function
int main(int argc, char **argv) {
  std::vector<int> arr = {-13, -3,  -25, -20, -3, -16, -23, 18,  20,  -7, 12,
                          -5,  -22, 15,  -4,  7,  -13, -3,  -25, -20, -3, -16,
                          -23, 18,  20,  -7,  12, -5,  -22, 15,  -4,  7};

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> res = max_subarray(arr, 0, 29);
  auto stop = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

  std::cout << duration.count() << std::endl;

  std::cout << res[0] << " " << res[1] << " " << res[2] << std::endl;
  return 0;
}