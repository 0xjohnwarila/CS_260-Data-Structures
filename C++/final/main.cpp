#include <iostream>

#include "test.hpp"

int main() {
  if (testSuite())
    std::cout << "Tests Pass" << std::endl;
  else
    std::cout << "Tests Fail" << std::endl;
  return EXIT_SUCCESS;
}