#include <iostream>

#include "auto_sorted_array.hpp"
#include "auto_sorted_list.hpp"

int main() {
  AutoSortList<int> newAutoList;

  newAutoList.add(7);
  newAutoList.add(6);
  newAutoList.add(4);
  newAutoList.add(10);
  newAutoList.add(9);
  newAutoList.add(999);
  newAutoList.add(0);
  newAutoList.add(-77);
  for (auto &&i : newAutoList) {
    std::cout << i << std::endl;
  }

  AutoSortArray<int> newAutoArr;
  int test[5] = {1, 3, 4, 5, 6};
  newAutoArr.fill(test, 5);
  newAutoArr.add(0);

  for (int i = 0; i < 6; i++)
    std::cout << newAutoArr.at(i) << std::endl;

  return EXIT_SUCCESS;
}