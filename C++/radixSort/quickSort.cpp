#include "quickSort.hpp"

#include <iostream>

// Complexity O(n log n)
// Degenerates to O(n^2) when array is already sorted

// Run by calling quickSort(inArr, 0, inArr.length-1)
void quickSort(int inArr[], int lo, int hi) {
  int p = 0;
  if (lo < hi) {
    p = partition(inArr, lo, hi);
    quickSort(inArr, lo, p - 1);
    quickSort(inArr, p + 1, hi);
  }
}

int partition(int inArr[], int lo, int hi) {
  // Choose pivot
  int pivot = inArr[hi];
  int temp = 0;
  int i = lo;
  // Scan through array from lo to hi
  for (int j = lo; j < hi; j++) {
    if (inArr[j] < pivot) {
      // Swap inArr[i] with inArr[j]
      temp = inArr[j];
      inArr[j] = inArr[i];
      inArr[i] = temp;
      // Increment i
      i++;
    }
  }
  // Swap inArr[i] with inArr[hi]
  temp = inArr[hi];
  inArr[hi] = inArr[i];
  inArr[i] = temp;
  return i;
}