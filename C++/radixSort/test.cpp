#include "test.hpp"
#include "quickSort.hpp"

#include <iostream>

bool isSorted(void) {
  int arr[] = {43, 92, 100, 2299, 1, 33};
  int expected[] = {1, 33, 43, 92, 100, 2299};
  int size = 6;
  bool result = true;
  quickSort(arr, 0, 5);
  for (int i = 0; i < 6; i++) {
    std::cout << arr[i] << std::endl;
    if (!(arr[i] == expected[i]))
      result = false;
  }

  return result;
}