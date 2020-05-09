#include <iostream>
#include <vector>

int max(int a, int b)
{
    return a > b ? a : b;
}

int maxSubarraySum(int *arr, int size)
{
    int sum = 0, best = 0;
    for (int i = 0; i < size; ++i)
    {
        sum = max(arr[i], sum + arr[i]);
        best = max(best, sum);
    }

    return best;
}

int main(int argc, char **argv)
{
    int total;
    std::vector<int> arr;
    std::cout << "Enter the total elements: ";
    std::cin >> total;

    // iterate and take inputs
    for (int i = 0; i < total; ++i)
    {
        int temp;
        std::cin >> temp;
        arr.push_back(temp);
    }

    // Call the max sub array func
    std::cout << maxSubarraySum(arr.data(), arr.size()) << "\n";
    return 0;
}