#include <iostream>

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

  return EXIT_SUCCESS;
}