#pragma once

#include <iostream>

using std::cout;
using std::endl;

template <class T>
class BinarySearchTree {
 private:
  class Node {
   public:
    T value;
    Node *parent;
    Node *leftChild;
    Node *rightChild;

    Node() : Node(T()) {}
    Node(T value) : Node(value, nullptr, nullptr, nullptr) {}
    Node(T value, Node *parent) : value(value), parent(parent) {}
    Node(T value, Node *parent, Node *leftChild, Node *rightChild) : value(value),
                                                                     parent(parent),
                                                                     leftChild(leftChild),
                                                                     rightChild(rightChild) {}

    Node *minVal(void) {
      if (leftChild == nullptr)
        return this;
      else
        return leftChild->minVal();
    }
  };

  // PRIVATE add method
  // O(n)
  void add(T inVal, Node *parent, Node *root) {
    if (root == nullptr) {
      root = new Node(inVal, parent);
      if (parent->value > root->value)
        parent->leftChild = root;
      else
        parent->rightChild = root;
      return;
    }
    if (root->value > inVal)
      add(inVal, root, root->leftChild);
    else
      add(inVal, root, root->rightChild);
  }

  // In Order loading
  // O(n)
  void inOrder(Node *root) {
    if (root == nullptr)
      return;
    inOrder(root->leftChild);
    nodeData.push_back(root->value);
    inOrder(root->rightChild);
  }

  // Pre Order loading
  // O(n)
  void preOrder(Node *root) {
    if (root == nullptr)
      return;
    nodeData.push_back(root->value);
    preOrder(root->leftChild);
    preOrder(root->rightChild);
  }

  // Post Order loading
  // O(n)
  void postOrder(Node *root) {
    if (root == nullptr)
      return;
    postOrder(root->leftChild);
    postOrder(root->rightChild);
    nodeData.push_back(root->value);
  }

  // Checks if a member is in the tree
  // O(n)
  bool inTree(T inVal, Node *currentRoot) {
    if (currentRoot == nullptr)
      return false;
    if (currentRoot->value == inVal)
      return true;
    if (currentRoot->value > inVal)
      inTree(inVal, currentRoot->leftChild);
    else
      inTree(inVal, currentRoot->rightChild);
  }

  // Returns pointer to node with inVal
  // O(n)
  Node *search(T inVal, Node *root) {
    if (root->value == inVal)
      return root;
    if (root->value > inVal)
      return search(inVal, root->leftChild);
    else
      return search(inVal, root->rightChild);
  }

  // Removes with no subtree
  // O(1)
  void removeNoSubtree(Node *parent) {
    if (parent->parent->leftChild == parent)
      parent->parent->leftChild = nullptr;
    else
      parent->parent->rightChild = nullptr;
    delete parent;
  }

  // Removes with one subtree
  // O(1)
  void removeOneSubtree(Node *parent) {
    if (parent->leftChild != nullptr)
      parent->parent->leftChild = parent->leftChild;
    else
      parent->parent->rightChild = parent->rightChild;

    delete parent;
  }

  // Removes with two subtrees
  // O(1)
  void removeTwoSubtree(Node *parent) {
    if (parent == root) {
      T tempValue = parent->leftChild->value;
      remove(tempValue);
      parent->value = tempValue;
      return;
    }
    Node *successor = parent->minVal();

    parent->value = successor->value;
    successor->parent->leftChild = nullptr;
    delete successor;
  }

  size_t depth;
  size_t numberOfNodes;

  std::vector<T> nodeData;

  Node *root;

 public:
  BinarySearchTree();

  void add(T inVal);
  void remove(T inVal);
  void loadDataInOrder(void);
  void loadDataPreOrder(void);
  void loadDataPostOrder(void);

  std::vector<T> data(void);
};

template <class T>
BinarySearchTree<T>::BinarySearchTree() {
  root = nullptr;
}

/*
See doc file for full explanation of remove method.
O(n)
*/
template <class T>
void BinarySearchTree<T>::remove(T inVal) {
  // Check if the BST doesn't exist
  if (root == nullptr)
    return;

  // Check if the value is not in the BST
  if (!inTree(inVal, root))
    return;

  // Check if the parent has no subtree
  Node *parent = search(inVal, root);
  if ((parent->leftChild == nullptr) && (parent->rightChild == nullptr)) {
    removeNoSubtree(parent);
    return;
  }

  // Check if the parent has one subtree
  if ((parent->leftChild != nullptr || parent->rightChild != nullptr) && !(parent->leftChild != nullptr && parent->rightChild != nullptr)) {
    removeOneSubtree(parent);
    return;
  }

  // Check if the parent has two subtree
  if ((parent->leftChild != nullptr) && (parent->rightChild != nullptr)) {
    removeTwoSubtree(parent);
    return;
  }
}

// Add a new object to the BST recursively
// O(n)
template <class T>
void BinarySearchTree<T>::add(T inVal) {
  if (root == nullptr) {
    root = new Node(inVal);
    return;
  }

  if (root->value > inVal)
    add(inVal, root, root->leftChild);
  else
    add(inVal, root, root->rightChild);
}

// Load node data with In Order
// O(n)
template <class T>
void BinarySearchTree<T>::loadDataInOrder(void) {
  nodeData.clear();
  inOrder(root);
}

// Load node data with Pre Order
// O(n)
template <class T>
void BinarySearchTree<T>::loadDataPreOrder(void) {
  nodeData.clear();
  preOrder(root);
}

// Load node data with Post Order
// O(n)
template <class T>
void BinarySearchTree<T>::loadDataPostOrder(void) {
  nodeData.clear();
  postOrder(root);
}

// Return node data that was previously loaded
template <class T>
std::vector<T> BinarySearchTree<T>::data(void) {
  return nodeData;
}
