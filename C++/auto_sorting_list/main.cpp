#include <array>
#include <iostream>

#include "auto_sorted_array.hpp"
#include "auto_sorted_list.hpp"

bool testList(void) {
  AutoSortList<int> newAutoList;

  std::array<int, 8> testData = {4, 0, -77, 999, 9, 7, 10, 6};
  std::array<int, 7> expectedData = {-77, 0, 4, 7, 9, 10, 999};
  std::array<int, 7> returnData;

  for (size_t i = 0; i < 8; i++) {
    newAutoList.add(testData[i]);
  }

  newAutoList.remove(3);  // removes 6 from pos 3

  for (size_t i = 0; i < 8; i++) {
    returnData[i] = newAutoList.get(i);
  }

  if (returnData == expectedData)
    return true;
  else
    return false;
}

bool testArray(void) {
  AutoSortArray<int> newAutoArr;
  std::array<int, 6> testData = {1, 3, 5, 4, 6, 0};
  std::array<int, 5> expectedData = {0, 1, 3, 4, 6};
  std::array<int, 5> returnData;
  for (size_t i = 0; i < 6; i++) {
    newAutoArr.add(testData[i]);
  }

  newAutoArr.remove(4);  // remove 5 from pos 4

  for (size_t i = 0; i < 8; i++) {
    returnData[i] = newAutoArr.at(i);
  }

  if (returnData == expectedData)
    return true;
  else
    return false;
}

int main() {
  if (testList())
    std::cout << "Lists Passed Tests" << std::endl;

  if (testArray())
    std::cout << "Arrays Passed Tests" << std::endl;
  return EXIT_SUCCESS;
}