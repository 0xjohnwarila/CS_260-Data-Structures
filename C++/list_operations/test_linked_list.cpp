#include <array>
#include <iostream>

#include "linked_list.hpp"
#include "test_linked_list.hpp"

using std::cout;
using std::endl;

bool insertLinkedListTest(void) {
  cout << "*** Insert Test ***" << endl
       << endl;
  std::array<int, 5> testData = {15, 2, 32, 45, 51};
  std::array<int, 6> expectedData = {51, 45, 42, 32, 2, 15};
  std::array<int, 6> returnData;
  LinkedList<int> newIntList;

  for (int i = 0; i < 5; i++) {
    newIntList.insert(testData[i]);
  }

  newIntList.insert(42, 2);

  for (int i = 0; i < 6; i++) {
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

bool appendLinkedListTest(void) {
  cout << "*** Append Test ***" << endl
       << endl;
  cout << "Append Test Failed!" << endl
       << endl;
  return false;
}

bool getLinkedListTest(void) {
  cout << "*** Get Test ***" << endl
       << endl;
  cout << "Get Test Failed!" << endl
       << endl;
  return false;
}

bool removeLinkedListTest(void) {
  cout << "*** Remove Test ***" << endl
       << endl;
  cout << "Remove Test Failed!" << endl
       << endl;
  return false;
}

bool iteratorLinkedListTest(void) {
  cout << "*** Iterator Test ***" << endl
       << endl;
  cout << "Iterator Test Failed!" << endl
       << endl;
  return false;
}

bool edgeCaseLinkedListTest(void) {
  cout << "*** Edge Case Test ***" << endl
       << endl;
  cout << "Edge Case Test Failed!" << endl
       << endl;
  return false;
}

bool linked_list_TestSuite(void) {
  return (insertLinkedListTest() && appendLinkedListTest() && getLinkedListTest() && removeLinkedListTest() && iteratorLinkedListTest() && edgeCaseLinkedListTest());
}