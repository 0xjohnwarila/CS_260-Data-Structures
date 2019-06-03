#include "test.hpp"
#include "radixSort.hpp"

#include <iostream>

bool isSorted(void) {
  int arr[] = {43, 92, 100, 2299, 1, 33};
  int expected[] = {1, 33, 43, 92, 100, 2299};
  int size = 6;
  bool result = true;
  sort(arr, size);

  for (int i = 0; i < 6; i++) {
    if (!(arr[i] == expected[i]))
      result = false;
  }

  return result;
}