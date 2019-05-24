#include <iostream>

#include "hashtable.hpp"
#include "person.hpp"

bool personTesting(void) {
  std::string testName = "Dave";
  float testGPA = 3.6;
  Person* testPerson = new Person(testName, testGPA);

  if (testPerson->key() == testName)
    std::cout << "Key's Match" << std::endl;

  if (testPerson->gradePointAverage() == testGPA)
    std::cout << "GPA's Match" << std::endl;

  return true;
}

int main() {
  std::cout << "HashTable" << std::endl;
  personTesting();

  const std::string collisionHandler = "Linear Probing";

  const Person nullObject = Person(true);

  HashTable<Person> table = HashTable<Person>(8, collisionHandler);

  const Person& dave = Person("Dave", 3.6);
  const Person& dave2 = Person("Evad", 2.5);
  table.add(dave);
  table.add(dave2);

  std::string copykey = "Dave";

  const Person daveCopy = table.get(copykey);

  if (table.get(copykey).isNull())
    std::cout << "NULL" << std::endl;
  else
    std::cout << "Dave's here" << std::endl;

  table.remove(copykey);

  if (table.get(copykey).isNull())
    std::cout << "Dave's not here man" << std::endl;

  return EXIT_SUCCESS;
}
