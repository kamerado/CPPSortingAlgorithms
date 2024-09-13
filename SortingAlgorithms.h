#ifndef SORTINGALGORITHMS_H

#include <iostream>
#include <vector>
#include <cmath>

namespace SortingAlgorithms {

  void insertionSort(int* nums, int numsSize); 

  void selectionSort(int* nums, int numsSize);

  void ShellSortKnuth(int* nums, int n); 

  void ShellSortTokuda(int* nums, int size);

  void quickSort(int*, int, int);

  void mergeSort(int* nums, int startIdx, int endIdx);

  void radixSort(std::vector<int>& nums);
}

#endif
