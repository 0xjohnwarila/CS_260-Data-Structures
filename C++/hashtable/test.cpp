#include "test.hpp"
#include "advancedhashtable.hpp"
#include "hashtable.hpp"
#include "person.hpp"

#include <iostream>

bool addGetTest(void) {
  const Person testPerson1 = Person("Dave", 3.6);
  const Person testPerson2 = Person("Mike", 2.8);
  const Person testPerson3 = Person("Jill", 3.9);

  size_t size = 10;

  AdvancedHashTable<Person> table = AdvancedHashTable<Person>(size);
  //HashTable<Person> table = HashTable<Person>(size);
  table.add(testPerson1);
  table.add(testPerson2);
  table.add(testPerson3);
  std::vector<Person> returnData;

  if (!table.get("Dave").isNull())
    returnData.push_back(table.get("Dave"));
  if (!table.get("Mike").isNull())
    returnData.push_back(table.get("Mike"));
  if (!table.get("Jill").isNull())
    returnData.push_back(table.get("Jill"));

  bool passing = true;

  // Lambda's are pretty neat
  auto keysMissMatch = [](std::string key1, std::string key2) { return !(key1 == key2); };
  auto gpaMissMatch = [](float gpa1, float gpa2) { return !(gpa1 == gpa2); };

  if (keysMissMatch(returnData.at(0).key(), testPerson1.key()))
    passing = false;
  if (gpaMissMatch(returnData.at(0).gradePointAverage(), testPerson1.gradePointAverage()))
    passing = false;
  if (keysMissMatch(returnData.at(1).key(), testPerson2.key()))
    passing = false;
  if (gpaMissMatch(returnData.at(1).gradePointAverage(), testPerson2.gradePointAverage()))
    passing = false;
  if (keysMissMatch(returnData.at(2).key(), testPerson3.key()))
    passing = false;
  if (gpaMissMatch(returnData.at(2).gradePointAverage(), testPerson3.gradePointAverage()))
    passing = false;
  if (!(table.get("Not In Table").isNull()))
    passing = false;

  return passing;
}

bool collisionTest(void) {
  const Person testPerson1 = Person("This", 3.6);
  const Person testPerson2 = Person("Hits", 2.8);
  const Person testPerson3 = Person("Tish", 3.9);

  size_t size = 10;

  AdvancedHashTable<Person> table = AdvancedHashTable<Person>(size);
  //HashTable<Person> table = HashTable<Person>(size);
  table.add(testPerson1);
  table.add(testPerson2);
  table.add(testPerson3);

  bool passing = true;

  if (table.get("This").isNull())
    passing = false;
  if (table.get("Hits").isNull())
    passing = false;
  if (table.get("Tish").isNull())
    passing = false;

  return passing;
}

bool removeTest(void) {
  const Person testPerson1 = Person("Dave", 3.6);
  const Person testPerson2 = Person("Mike", 2.8);
  const Person testPerson3 = Person("Jill", 3.9);

  size_t size = 10;

  AdvancedHashTable<Person> table = AdvancedHashTable<Person>(size);
  //HashTable<Person> table = HashTable<Person>(size);

  table.add(testPerson1);
  table.add(testPerson2);
  table.add(testPerson3);

  table.remove("Dave");
  table.remove("Not in Table");

  bool passing = true;

  if (!table.get("Dave").isNull())
    passing = false;

  return passing;
}
