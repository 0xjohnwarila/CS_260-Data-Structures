#include <array>
#include <iostream>

#include "array_list.hpp"
#include "test_array_list.hpp"

bool addTest(void) {
  std::cout << "*** Add Test ***" << std::endl;
  ArrayList<int> newArray;
  std::array<int, 5> testData = {15, 2, 32, 45, 51};
  std::cout << std::endl
            << "Test array: ";
  for (int i = 0; i < 5; i++) {
    std::cout << testData[i] << " ";
  }
  std::cout << std::endl
            << std::endl;
  std::array<int, 5> returnData = {};
  for (int i = 0; i < 5; i++) {
    std::cout << "Adding " << testData[i] << ". ";
    newArray.add(testData[i], i);
    returnData[i] = newArray.at(i);
    std::cout << "Got back " << returnData[i] << std::endl;
  }
  if (returnData == testData) {
    std::cout << "Add Test Passed" << std::endl;
    return true;
  } else {
    std::cout << "Add Test Failed" << std::endl;
    return false;
  }
}

bool removeTest(void) {
  return false;
}

bool atTest(void) {
  return true;
}

bool array_list_TestSuite(void) {
  return (addTest() && removeTest() && atTest());
}
