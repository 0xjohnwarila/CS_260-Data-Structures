#pragma once

#include <iostream>

template <class T>
struct Node {
  T value;
  Node *nextNode;
  Node() : Node(T()) {}
  Node(T value) : value(value), nextNode(nullptr) {}
  Node(T value, Node *next) : value(value), nextNode(next) {}
};

template <class T>
class Queue {
 private:
  Node<T> *front;
  Node<T> *back;

 public:
  void enqueue(T inVal);
  T dequeue(void);
  bool empty(void);
};

template <class T>
void Queue<T>::enqueue(T inval) {
  Node *newNode = new Node(inval);
  if (empty()) {
    front = newNode;
    back = newNode;
  } else {
    back->nextNode = newNode;
    back = newNode;
  }
}

template <class T>
T Queue<T>::dequeue(void) {
  if (empty()) {
    std::cout << "Underflow" << std::endl;
    return;
  } else {
    T frontVal = front->value;
    Node *tempNode = front;
    front = front->nextNode;
    delete tempNode;
    return frontVal;
  }
}

template <class T>
bool Queue<T>::empty(void) {
}