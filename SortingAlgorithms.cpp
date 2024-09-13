#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "SortingAlgorithms.h"

namespace SortingAlgorithms {

  void insertionSort(int* nums, int numsSize) {
    for (int i = 1; i < numsSize; i++) {
      int j = i;
      
      while (j > 0 && nums[j] < nums[j - 1]) {
        int temp = nums[j];
        nums[j] = nums[j - 1];
        nums[j - 1] = temp;
        j--;
      }
    }
  }

  void selectionSort(int* nums, int numsSize){
    for(int i = 0; i < numsSize; i++){
      int smlIdx = i;

      for(int j = i + 1; j < numsSize; j++){
        if(nums[j] < nums[smlIdx]){
          smlIdx = j;
        }
      }
      int tmp = nums[i];
      nums[i] = nums[smlIdx];
      nums[smlIdx] = tmp;
    }
  }

  void ShellSortKnuth(int* nums, int n) {
    int gap = 1;
    
    while (gap < n/3){
      gap = 3 * gap + 1;
    }

    while (gap > 0) {
      for (int i = gap; i < n; i++) {
        int temp = nums[i];
        int j;
        for (j = i; j >= gap && nums[j - gap] > temp; j -= gap) {
          nums[j] = nums[j - gap];
        }
        nums[j] = temp;
      }
      gap /= 3;
    }
  }

  std::vector<int> genTokudaSeq(int size) {
    std::vector<int> gaps;
    int k = 1;
    int gap;

    while (true) {
      gap = (9 * pow(9, k - 1) - pow(4, k-1)) / (5 * pow(4, k-1));
      if (gap > size) break;
      gaps.push_back(gap);
      k++;
    }

    return gaps;
  }

  void ShellSortTokuda(int* nums, int size) {
    std::vector<int> gaps = genTokudaSeq(size);
    for (int gapIdx = gaps.size() - 1; gapIdx >= 0; gapIdx--) {
      int gap = gaps[gapIdx];

      for (int i = gap; i < size; i++) {
        int tmp = nums[i];
        int j;
        for (j = i; j >= gap && nums[j - gap] > tmp; j -= gap) {
          nums[j] = nums[j - gap];
        }
        nums[j] = tmp;
      }
    }
  }

  int partition(int* nums, int lowIdx, int highIdx) {
    // pick middle element as pivot
    int midpoint = lowIdx + (highIdx - lowIdx) / 2;
    int pivot = nums[midpoint];

    bool done = false;
    while (!done) {
      // increment lowIdx while nums[lowIdx] < pivot
      while (nums[lowIdx] < pivot) {
        lowIdx++;
      }

      // decriment highIdx while pivot < nums[highIdx]
      while (pivot < nums[highIdx]) {
        highIdx--;
      }

      // if zero or one element remain, all numbers are
      // partitioned. return highIdx
      if (lowIdx >= highIdx) {
        done = true;
      } else {
        // swap nums[lowIdx] and nums[highIdx]
        int tmp = nums[lowIdx];
        nums[lowIdx] = nums[highIdx];
        nums[highIdx] = tmp;

        // update lowIdx and highIdx
        lowIdx++;
        highIdx--;
      }
    }

    return highIdx;
  }

  void quickSort(int* nums, int lowIdx, int highIdx) {
    // base case: if partition size is 1 or 0,
    // the partition is already sorted.
    if (lowIdx >= highIdx) {
      return;
    }

    // partition the data within the array. Value lowEndIdx
    // returned from partitioning is the index of the low
    // partitions last index.
    int lowEndIdx = partition(nums, lowIdx, highIdx);

    // Recursivly sort low partition (lowIdx to lowEnxIdx)
    // and high partition (lowEnxIdx to highIdx)
    quickSort(nums, lowIdx, lowEndIdx);
    quickSort(nums, lowEndIdx + 1, highIdx);
  }

  void merge(int* nums, int startIdx, int midIdx, int endIdx) {
    int mergedSize = endIdx - startIdx + 1;               // Size of merged partition
    int mergeIdx = 0;                         // Position to insert merged number
    int leftPos = startIdx;                   // Posision of elements in left part
    int rightPos = midIdx;                    // posision of elements in right part
    int* mergedNumbers = new int[mergedSize];  // Allocate temp array for merged nums

    leftPos = startIdx;                       // Initialize left partition posisiton
    rightPos = midIdx + 1;                    // Initialize right partition position

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= midIdx && rightPos <= endIdx) {
      if (nums[leftPos] <= nums[rightPos]) {
        mergedNumbers[mergeIdx] = nums[leftPos];
        leftPos++;
      } else {
        mergedNumbers[mergeIdx] = nums[rightPos];
        rightPos++;
      }

      mergeIdx++;
    }

    // If left partition is not empty, add remaining elements to merged nums
    while (leftPos <= midIdx) {
      mergedNumbers[mergeIdx] = nums[leftPos];
      leftPos++;
      mergeIdx++;
    }

    // If left partition is not empty, add rmeaining elemtents to merged nums
    while (rightPos <= endIdx) {
      mergedNumbers[mergeIdx] = nums[rightPos];
      rightPos++;
      mergeIdx++;
    }

    // Write merged numbers to nums
    for (mergeIdx = 0; mergeIdx < mergedSize; mergeIdx++) {
      nums[startIdx + mergeIdx] = mergedNumbers[mergeIdx];
    }
  }

  void mergeSort(int* nums, int startIdx, int endIdx) {
    int midIdx = 0;

    if (startIdx < endIdx) {
      midIdx = (startIdx + endIdx) / 2; // Find midIdx

      // Recursivly sort left and right partitions
      mergeSort(nums, startIdx, midIdx);
      mergeSort(nums, midIdx + 1, endIdx);

      // merge left and right partition in sorted order
      merge(nums, startIdx, midIdx, endIdx);
    }
  }

  void countingSort(std::vector<int>& nums, int exp) {
    const int n = nums.size();
    std::vector<int> output(n);
    std::vector<int> count(256, 0);

    for (int i = 0; i < n; i++) {
        count[(nums[i] / exp) & 0xFF]++;
    }

    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(nums[i] / exp) & 0xFF] - 1] = nums[i];
        count[(nums[i] / exp) & 0xFF]--;
    }

    nums = output;
  }

  void radixSort(std::vector<int>& nums) {
    if (nums.empty()) return;

    // Find the minimum and maximum values
    int minVal = *std::min_element(nums.begin(), nums.end());
    int maxVal = *std::max_element(nums.begin(), nums.end());

    // Shift all numbers to be non-negative
    for (int& num : nums) {
        num -= minVal;
    }

    // Now sort the shifted numbers
    for (int exp = 1; maxVal - minVal > 0 && exp <= 0x40000000; exp <<= 8) {
        countingSort(nums, exp);
    }

    // Shift the numbers back
    for (int& num : nums) {
        num += minVal;
    }
  }
}
