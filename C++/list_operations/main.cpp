#include <iostream>

#include "array_list.hpp"
#include "linked_list.hpp"
#include "test_array_list.hpp"
#include "test_linked_list.hpp"

int main() {
  std::cout << std::endl
            << "Running Array List Tests" << std::endl
            << std::endl;
  if (array_list_TestSuite())
    std::cout << "Succesfully Tested Array Lists!" << std::endl;
  else
    std::cout << "Array List Tests Have Failed!" << std::endl;

  std::cout << std::endl
            << std::endl
            << "Running Linked List Tests" << std::endl
            << std::endl;
  if (linked_list_TestSuite())
    std::cout << "Succesfully Tested Linked Lists!" << std::endl;
  else
    std::cout << "Linked List Tests Have Failed!" << std::endl;
  return EXIT_SUCCESS;
}
