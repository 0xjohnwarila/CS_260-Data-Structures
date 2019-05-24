#include <iostream>

#include "hashtable.hpp"
#include "person.hpp"
#include "test.hpp"

int main() {
  std::cout << "HashTable" << std::endl;

  if (addGetTest())
    std::cout << "Adding and Getting Pass" << std::endl;
  else
    std::cout << "Adding and Getting Fail" << std::endl;

  if (collisionTest())
    std::cout << "Collision Pass" << std::endl;
  else
    std::cout << "Collision Fail" << std::endl;

  if (removeTest())
    std::cout << "Remove Pass" << std::endl;
  else
    std::cout << "Remove Fail" << std::endl;

  return EXIT_SUCCESS;
}
