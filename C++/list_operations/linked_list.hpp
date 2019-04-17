#pragma once

template <class T>
class LinkedList {
 private:
  struct Node {
    T value;
    Node *next;
    Node *prev;
    Node() : Node(T()) {}
    Node(T value) : Node(value, this, this) {}
    Node(T value, Node *next, Node *prev) : value(value), next(next), prev(prev) {}
    void insert(Node *other) {
      // Insert the Node between other and other-> prev
      next = other;
      prev = other->prev;
      next->prev = prev->next = this;
    }
  };

  Node *head;

 public:
  LinkedList() : head(new Node()) {}
  void add(T inVal, int pos);
  void append(T inVal);
  void insert(T inVal);
  T get(int pos);
};

template <class T>
void LinkedList<T>::add(T inVal, int pos) {
  Node *currentNode = head;
  for (int i = 0; i < pos + 1; i++) {
    currentNode = currentNode->next;
  }
  (new Node(inVal))->insert(currentNode);
}

template <class T>
void LinkedList<T>::append(T inVal) {
  (new Node(inVal))->insert(head);
}

template <class T>
T LinkedList<T>::get(int pos) {
  Node *currentNode = head;
  for (int i = 0; i < pos + 1; i++) {
    currentNode = currentNode->next;
  }
  return currentNode->value;
}

template <class T>
void LinkedList<T>::insert(T inVal) {
  (new Node(inVal))->insert(head->next);
}