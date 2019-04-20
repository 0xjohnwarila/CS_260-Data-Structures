#include <iostream>

#include "array_list.hpp"
#include "linked_list.hpp"
#include "test_array_list.hpp"

int main() {
  LinkedList<int> intList;
  std::cout << "made list" << std::endl;
  intList.append(2);
  intList.insert(88);
  intList.append(9);
  std::cout << "appended values" << std::endl;
  intList.add(3, 1);

  for (auto v : intList)
    std::cout << v << std::endl;

  std::cout << "Array Testing" << std::endl;
  ArrayList<int> intArr;
  int testArr[4] = {1, 2, 3, 4};
  intArr.fill(testArr, 4);
  std::cout << "0 = " << intArr.get(0) << std::endl;
  intArr.add(testArr[1], 0);
  std::cout << "0 = " << intArr.get(0) << std::endl;
  intArr.add(99, 8);
  std::cout << "8 = " << intArr.get(8) << std::endl;
  std::cout << "7 = " << intArr.get(7) << std::endl;
  return EXIT_SUCCESS;
}
