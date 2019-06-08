#include "quickSort.hpp"

#include <iostream>

// Complexity O(n lowg n)
// Degenerates to O(n^2) when array is already sorted

// Run by calling quickSort(inArr, 0, inArr.length-1)
void quickSort(int inArr[], int low, int high) {
  int p = 0;
  if (low < high) {
    // Get P from the partition
    p = partition(inArr, low, high);
    // Run with low as low, and p - 1 as high
    quickSort(inArr, low, p - 1);
    // Run wiht P + 1 as low, and high as high
    quickSort(inArr, p + 1, high);
  }
}

// The swaps could be made to use no temp var... but I am lazy.
int partition(int inArr[], int low, int high) {
  // Choose pivot
  int pivot = inArr[high];
  int temp = 0;
  int i = low;
  // Scan through array from low to high
  for (int j = low; j < high; j++) {
    // If the index at j is less than our pivot, swap i with j and
    // increment i
    if (inArr[j] < pivot) {
      // Swap inArr[i] with inArr[j]
      temp = inArr[j];
      inArr[j] = inArr[i];
      inArr[i] = temp;
      // Increment i
      i++;
    }
  }
  // Swap inArr[i] with inArr[high]
  temp = inArr[high];
  inArr[high] = inArr[i];
  inArr[i] = temp;
  return i;
}