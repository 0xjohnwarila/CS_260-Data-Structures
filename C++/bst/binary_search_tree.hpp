#pragma once

#include <iostream>
#include <vector>

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

    T minVal(void) {
      if (leftChild == nullptr)
        return value;
      else
        return leftChild->minVal();
    }
  };

  Node *remove(Node *root, T inVal, Node *parent) {
  }

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

  void inOrder(Node *root) {
    if (root->leftChild != nullptr)
      inOrder(root->leftChild);
    nodeData.push_back(root->value);
    if (root->rightChild != nullptr)
      inOrder(root->rightChild);
  }

  void preOrder(Node *root) {
    nodeData.push_back(root->value);
    if (root->leftChild != nullptr)
      inOrder(root->leftChild);
    if (root->rightChild != nullptr)
      inOrder(root->rightChild);
  }

  void postOrder(Node *root) {
    if (root->leftChild != nullptr)
      inOrder(root->leftChild);
    if (root->rightChild != nullptr)
      inOrder(root->rightChild);
    nodeData.push_back(root->value);
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
check for null root

check for left or right

check for value == inVal
*/
template <class T>
void BinarySearchTree<T>::remove(T inVal) {
  if (root == nullptr)
    return;

  Node *nodeToRemove;

  if (root->value == inVal) {
    Node temp = new Node();
    temp->leftChild = root;
    nodeToRemove = remove(root, inVal, &temp);
    root = temp->left;
  }

  if (nodeToRemove != nullptr)
    delete nodeToRemove;
}

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

template <class T>
void BinarySearchTree<T>::loadDataInOrder(void) {
  if (root == nullptr)
    return;

  inOrder(root);
}

template <class T>
std::vector<T> BinarySearchTree<T>::data(void) {
  return nodeData;
}
