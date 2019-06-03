#include <iostream>

#include "test.hpp"

int main() {
  if (isSorted())
    std::cout << "Passed Test" << std::endl;
  else
    std::cout << "Failed Test" << std::endl;

  return EXIT_SUCCESS;
}