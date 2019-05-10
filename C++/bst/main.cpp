#include <iostream>
#include <vector>

#include "binary_search_tree.hpp"

int main() {
  using std::cout;
  using std::endl;

  BinarySearchTree<int> intBST;
  intBST.add(5);
  intBST.add(9);
  intBST.add(8);
  intBST.add(3);
  intBST.add(1);
  intBST.add(23);
  intBST.loadDataInOrder();

  std::vector<int> returnData = intBST.data();

  for (auto &&i : returnData) {
    cout << i << endl;
  }
  cout << endl;
  intBST.loadDataPreOrder();
  returnData = intBST.data();
  for (auto &&i : returnData) {
    cout << i << endl;
  }
  cout << endl;
  intBST.loadDataPostOrder();
  returnData = intBST.data();
  for (auto &&i : returnData) {
    cout << i << endl;
  }

  return EXIT_SUCCESS;
}