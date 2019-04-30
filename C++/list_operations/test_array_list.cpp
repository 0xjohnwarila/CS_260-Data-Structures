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
  std::cout << std::endl;
  if (returnData == testData) {
    std::cout << "Add Test Passed!" << std::endl
              << std::endl;
    return true;
  } else {
    std::cout << "Add Test Failed!" << std::endl
              << std::endl;
    return false;
  }
}

bool removeTest(void) {
  std::cout << "*** Remove Test ***" << std::endl
            << std::endl;
  ArrayList<int> newArray;
  std::array<int, 5> testData = {15, 2, 32, 45, 51};
  std::array<int, 5> expectedData = {15, 2, 32, 0, 51};
  std::array<int, 5> returnData = {};
  for (int i = 0; i < 5; i++) {
    std::cout << "Adding " << testData[i] << ". " << std::endl;
    newArray.add(testData[i], i);
  }
  std::cout << std::endl
            << "Removing " << testData[3] << " from pos 3" << std::endl;
  newArray.remove(3);
  std::cout << "Data is now: ";
  for (int i = 0; i < 5; i++) {
    std::cout << newArray.at(i) << " ";
    returnData[i] = newArray.at(i);
  }
  std::cout << std::endl
            << std::endl;

  if (returnData == expectedData) {
    std::cout << "Remove Test Passed!" << std::endl
              << std::endl;
    return true;
  } else {
    std::cout << "Remove Test Failed!" << std::endl
              << std::endl;
    return false;
  }
}

bool fillTest(void) {
  std::cout << "*** Fill Test ***" << std::endl
            << std::endl;
  ArrayList<int> newArray;
  int testData[] = {15, 2, 32, 45, 51};
  std::cout << "Filling with array: { ";
  for (int i = 0; i < 5; i++) {
    std::cout << testData[i] << " ";
  }
  std::cout << "}" << std::endl;
  std::array<int, 5> expectedData = {15, 2, 32, 45, 51};
  std::array<int, 5> returnData = {};
  newArray.fill(testData, 5);
  std::cout << "Array stored : { ";
  for (int i = 0; i < 5; i++) {
    std::cout << newArray.at(i) << " ";
    returnData[i] = newArray.at(i);
  }
  std::cout << "}" << std::endl
            << std::endl;

  if (returnData == expectedData) {
    std::cout << "Fill Test Passed!" << std::endl
              << std::endl;
    return true;
  } else {
    std::cout << "Fill Test Failed!" << std::endl
              << std::endl;
    return false;
  }
}

bool edgeCaseTest(void) {
  std::cout << "*** Edge Case Tests ***" << std::endl;

  std::cout << std::endl
            << "Adding beyond bounds" << std::endl;
  ArrayList<int> newArray;
  int testData[] = {15, 2, 32, 45, 51};
  newArray.fill(testData, 5);
  std::cout << "Filling with ";
  for (int i = 0; i < 5; i++) {
    std::cout << testData[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl
            << "Adding 89 to position 7" << std::endl;
  newArray.add(89, 7);
  std::cout << "List is now ";
  for (int i = 0; i < 8; i++) {
    std::cout << newArray.at(i) << " ";
  }
  std::cout << std::endl
            << std::endl;

  std::cout << "Removing from position 66 (out of bounds) : got back " << newArray.remove(66)
            << ". Expected 0." << std::endl;

  return true;
}

bool array_list_TestSuite(void) {
  return (addTest() && removeTest() && fillTest() && edgeCaseTest());
}
