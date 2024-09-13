#include <iostream>
#include <ctime>
#include <chrono>
#include <cassert>
#include <vector>
#include <random>
#include <limits>

#include "SortingAlgorithms.h"

bool sorted(int* nums, int size) {
  for (int i = 1; i < size; i++) {
    if (nums[i - 1] > nums[i]) {
      return false;
    }
  }

  return true;
}

bool sorted(std::vector<int>& nums) {
  if (nums.empty()) return true;
  for (auto i = nums.begin() + 1; i < nums.end(); i++) {
    if (*i < *i - 1) {
      return false;
    }
  }

  return true;
}

int genRandInt() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(std::numeric_limits<int>::min(), 
                                           std::numeric_limits<int>::max());
    return dis(gen);
}

void timeFunction(int* a, int b, void (*func)(int*, int)) {
  auto start = std::chrono::high_resolution_clock::now();

  func(a, b);
  assert(sorted(a, b));

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
}

void timeFunction(int* nums, int lowIdx, int highIdx, void (*func)(int*, int, int)) {
  auto start = std::chrono::high_resolution_clock::now();

  func(nums, lowIdx, highIdx);
  assert(sorted(nums, highIdx + 1));

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
}

void timeFunction(std::vector<int>& nums, void (*func)(std::vector<int>&)) {

  auto start = std::chrono::high_resolution_clock::now();

  func(nums);
  assert(sorted(nums));

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
}

using namespace SortingAlgorithms;

int main() {
  srand(static_cast<unsigned>(time(0)));

  const int SIZE_NUMS = 1000000;
  int nums[SIZE_NUMS];
  int numsSorted[SIZE_NUMS];

  for (int i = 0; i < SIZE_NUMS; i++) {
    nums[i] = genRandInt();
  }

  std::vector<int> numsVec(nums, nums + SIZE_NUMS);
  std::vector<int> numsVecSorted(numsVec);

  std::copy(nums, nums + SIZE_NUMS, numsSorted);
  

  std::cout << "shellSort knuths: ";
  timeFunction(numsSorted, SIZE_NUMS, ShellSortKnuth);


  std::copy(nums, nums + SIZE_NUMS, numsSorted);
  
  std::cout << "shellSort tokuda: ";
  timeFunction(numsSorted, SIZE_NUMS, ShellSortTokuda);


  std::copy(nums, nums + SIZE_NUMS, numsSorted);

  std::cout << "quickSort: ";
  timeFunction(numsSorted, 0, SIZE_NUMS - 1, quickSort);

  std::copy(nums, nums + SIZE_NUMS, numsSorted);

  std::cout << "mergeSort: ";
  timeFunction(numsSorted, 0, SIZE_NUMS - 1, mergeSort);


  std::copy(nums, nums + SIZE_NUMS, numsSorted);

  std::cout << "radixSort: ";
  timeFunction(numsVecSorted, radixSort);
  // These test the implementation of slower sorting Sorting algorithms.
  // commented out to test larger sets.

  /*std::copy(nums, nums + SIZE_NUMS, numsSorted);*/
  /**/
  /*std::cout << "insertionSort: ";*/
  /*timeFunction(numsSorted, SIZE_NUMS, insertionSort);*/
  /**/
  /**/
  /*std::copy(nums, nums + SIZE_NUMS, numsSorted);*/
  /**/
  /**/
  /*std::cout << "selectionSort: ";*/
  /*timeFunction(numsSorted, SIZE_NUMS, selectionSort);*/


  // for (int i = 0; i < SIZE_NUMS; i++) {
  //  std::cout << numsSorted[i] << std::endl;
  // }

  return 0;
}
