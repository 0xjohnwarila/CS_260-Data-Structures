#include <iostream>
#include "person.hpp"

bool personTesting(void) {
  std::string testName = "Dave";
  float testGPA = 3.6;
  Person *testPerson = new Person(testName, testGPA);

  if (testPerson->key() == testName)
    std::cout << "Key's Match" << std::endl;

  if (testPerson->gradePointAverage() == testGPA)
    std::cout << "GPA's Match" << std::endl;

  return true;
}

int main() {
  std::cout << "HashTable" << std::endl;
  personTesting();
  return EXIT_SUCCESS;
}
