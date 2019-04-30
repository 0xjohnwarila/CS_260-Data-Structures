#include <iostream>

#include "test_linked_list.hpp"

using std::cout;
using std::endl;

bool insertLinkedListTest(void) {
  cout << "*** Insert Test ***" << endl
       << endl;
  cout << "Insert Test Failed!" << endl
       << endl;
  return false;
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