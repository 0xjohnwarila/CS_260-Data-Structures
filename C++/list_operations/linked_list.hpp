#pragma once

template <class T>
struct Node {
  T value;
  Node *nextNode;
  Node *prevNode;
  Node() : Node(T()) {}
  Node(T value) : value(value), nextNode(nullptr), prevNode(nullptr) {}
  Node(T value, Node *next) : value(value), nextNode(next), prevNode(nullptr) {}
  Node(T value, Node *next, Node *prev) : value(value), nextNode(next), prevNode(prev) {}
};