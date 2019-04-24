#include <iostream>

#include "array_list.hpp"
#include "linked_list.hpp"
#include "test_array_list.hpp"

int main() {
  if (array_list_TestSuite())
    std::cout << "Succesfully Tested Array Lists" << std::endl;
  else
    std::cout << "Array List Tests Have Failed" << std::endl;
  return EXIT_SUCCESS;
}
