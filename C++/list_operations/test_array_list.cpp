#include "test_array_list.hpp"
#include "array_list.hpp"

bool addTest(void) {
  ArrayList<int> newArray;
  int testData[5] = {15, 2, 32, 45, 51};
  for (int i = 0; i < 5; i++) {
    newArray.add(testData[i], i);
  }
  return false;
}

bool removeTest(void) {
  return true;
}

bool getTest(void) {
  return true;
}

bool array_list_TestSuite(void) {
  return (addTest() && removeTest() && getTest());
}
