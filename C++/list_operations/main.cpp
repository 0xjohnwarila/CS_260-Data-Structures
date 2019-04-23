#include <iostream>

#include "array_list.hpp"
#include "linked_list.hpp"
#include "test_array_list.hpp"

int main() {
  LinkedList<int> intList;
  intList.append(2);
  intList.insert(88);
  intList.append(9);
  intList.insert(3, 1);
  intList.insert(55, 90);
  intList.insert(33, 33);
  intList.insert(777, 5);

  for (auto v : intList)
    std::cout << v << std::endl;

  std::cout << std::endl;
  std::cout << intList.remove(1) << " was removed from pos 1" << std::endl
            << std::endl;

  for (auto v : intList)
    std::cout << v << std::endl
              << std::endl;

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
