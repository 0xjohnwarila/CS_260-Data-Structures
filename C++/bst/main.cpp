#include <iostream>
#include <vector>

#include "binary_search_tree.hpp"

bool addInOrderTest(BinarySearchTree<int> testBST) {
  testBST.loadDataInOrder();
  std::vector<int> expectedData = {1, 2, 6, 8, 9, 11, 13, 15, 18};
  return expectedData == testBST.data();
}

bool preOrderTest(BinarySearchTree<int> testBST) {
  testBST.loadDataPreOrder();
  std::vector<int> expectedData = {6, 2, 1, 9, 8, 15, 13, 11, 18};
  return expectedData == testBST.data();
}

bool postOrderTest(BinarySearchTree<int> testBST) {
  testBST.loadDataPostOrder();
  std::vector<int> expectedData = {1, 2, 8, 11, 13, 18, 15, 9, 6};
  return expectedData == testBST.data();
}

bool removeTest(BinarySearchTree<int> testBST) {
  testBST.remove(1);   // No subtree
  testBST.remove(13);  // 1 subtree
  testBST.remove(9);   // 2 subtree
  testBST.remove(6);   // root
  testBST.remove(42);  // not in bst
  testBST.loadDataPreOrder();
  std::vector<int> expectedData = {2, 8, 15, 11, 18};
  return expectedData == testBST.data();
}

int main() {
  using std::cout;
  using std::endl;

  BinarySearchTree<int> intBST;
  intBST.add(6);
  intBST.add(2);
  intBST.add(1);
  intBST.add(9);
  intBST.add(8);
  intBST.add(15);
  intBST.add(13);
  intBST.add(11);
  intBST.add(18);
  if (addInOrderTest(intBST)) {
    cout << "Add / in order test passed" << endl;
  }

  if (preOrderTest(intBST)) {
    cout << "Preorder test passed" << endl;
  }

  if (postOrderTest(intBST)) {
    cout << "Postorder test passed" << endl;
  }

  if (removeTest(intBST)) {
    cout << "Remove test passed" << endl;
  }

  return EXIT_SUCCESS;
}
