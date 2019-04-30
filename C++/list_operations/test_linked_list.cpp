#include <array>
#include <iostream>

#include "linked_list.hpp"
#include "test_linked_list.hpp"

using std::cout;
using std::endl;

bool insertGetLinkedListTest(void) {
  cout << "*** Insert Test ***" << endl
       << endl;
  std::array<int, 5> testData = {15, 2, 32, 45, 51};
  std::array<int, 7> expectedData = {51, 45, 42, 32, 2, 15, 88};
  std::array<int, 7> returnData;
  LinkedList<int> newIntList;

  for (int i = 0; i < 5; i++) {
    newIntList.insert(testData[i]);
  }

  newIntList.insert(42, 2);
  newIntList.insert(88, 6);

  for (int i = 0; i < 7; i++) {
    returnData[i] = newIntList.get(i);
  }

  if (returnData == expectedData) {
    cout << "Insert Test Passed!" << endl
         << endl;
    return true;
  } else {
    cout << "Insert Test Failed!" << endl
         << endl;
    return false;
  }
}

bool removeLinkedListTest(void) {
  cout << "*** Remove Test ***" << endl
       << endl;
  std::array<int, 5> testData = {15, 2, 32, 45, 51};
  std::array<int, 4> expectedData = {15, 2, 32, 51};
  std::array<int, 4> returnData;
  LinkedList<int> newIntList;

  for (int i = 5 - 1; i >= 0; i--) {
    newIntList.insert(testData[i]);
  }

  newIntList.remove(3);

  for (int i = 0; i < 4; i++) {
    returnData[i] = newIntList.get(i);
  }

  if (returnData == expectedData) {
    cout << "Remove Test Passed!" << endl
         << endl;
    return true;
  } else {
    cout << "Remove Test Failed!" << endl
         << endl;
    return false;
  }
}

bool linked_list_TestSuite(void) {
  return (insertGetLinkedListTest() && removeLinkedListTest());
}