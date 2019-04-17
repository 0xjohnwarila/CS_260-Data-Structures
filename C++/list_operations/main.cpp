#include <iostream>

#include "linked_list.hpp"
#include "test_array_list.hpp"

int main() {
  LinkedList<int> intList;
  std::cout << "made list" << std::endl;
  intList.append(2);
  intList.append(9);
  std::cout << "appended values" << std::endl;
  intList.add(3, 1);

  for (int i = 0; i < 3; i++) {
    std::cout << intList.get(i) << std::endl;
  }

  return EXIT_SUCCESS;
}
