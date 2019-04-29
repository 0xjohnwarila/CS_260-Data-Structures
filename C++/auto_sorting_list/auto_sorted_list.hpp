/*
Auto Sorting List. Base ADT Linked List.

*/
#pragma once

template <class T>
class AutoSortList {
 private:
  /*
  Internal doubly linked node implementation. Very simple, stores value, and two
  node pointers.

  Has three constructors for different use cases. One sets value type, one makes a
  node that just points to itself (used for the first node in a list), one makes a
  node that points to two other nodes and stores a value.

  The node also has a method insert. This is used to place a node before some 'other'
  node.
  */
  class Node {
   public:
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

    void insertHead(Node *head) {
      // Insert the Node before head
      next = head;
      next->prev = prev = this;
    }

    void append(Node *other) {
      // Insert after other
      next = this;
      prev = other;
      other->next = next = this;
    }

    void remove(void) {
      // remove self from list
      next->prev = prev;
      prev->next = next;
    }
  };

  /*
  Internal iterator. Very useful for testing. Also lets user use ranged base for
  loops.

  Basically just some operator definitions, pretty basic stuff that makes life
  a lot easier.

  Note: This implementation of an iterator comes from a linked list I wrote about
  a year ago. It wasn't part of the assignment so I felt OK about putting it in.
  Mostly just a quality of life feature.
  */
  class Iterator {
   private:
    Node *current;

   public:
    Iterator(const Iterator &i) : current(i.current) {}
    Iterator(Node *n) : current(n) {}

    bool operator==(const Iterator &i) { return current == i.current; }
    bool operator!=(const Iterator &i) { return current != i.current; }

    T &operator*() { return current->value; }

    Iterator &operator++() {
      current = current->next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator clone(this);
      current = current->next;
      return clone;
    }
  };

  // Traces through the list. COMPLEXITY O(n)
  Node *trace(int pos) {
    if (pos > listLength - 1)
      return head;

    Node *currentNode = head;
    for (int i = 0; i < pos + 1; i++) {
      currentNode = currentNode->next;
    }
    return currentNode;
  }

  // Traces through list looking for a node with val > inVal
  Node *valTrace(T inVal) {
  }

  Node *head;
  Node *tail;
  int listLength;

 public:
  // Constructor
  AutoSortList() : head(new Node()), tail(new Node(0)), listLength(0) {
    head->next = tail;
    tail->prev = head;
  }

  // Public methods
  void add(T inVal);

  T get(int pos);
  T remove(int pos);

  int length(void);

  // Iterator stuff (aka the begin and end methods needed...)
  Iterator begin() { return Iterator(head->next); }
  Iterator end() { return Iterator(tail); }
};

/*
PUBLIC METHOD: add(T inVal)

Adds a new value to its correct position on the list.
*/

template <class T>
void AutoSortList<T>::add(T inVal) {
  Node *currentNode = head;
  if (currentNode->next == tail) {
    (new Node(inVal))->insert(tail);
    listLength++;
    return;
  }
  currentNode = currentNode->next;
  for (int i = 0; i < listLength; i++) {
    if (currentNode->value > inVal) {
      (new Node(inVal))->insert(currentNode);
      listLength++;
      return;
    }
    if (currentNode->next == tail) {
      (new Node(inVal))->insert(tail);
      listLength++;
      return;
    }
    currentNode = currentNode->next;
  }
}
/*
PUBLIC METHOD: get(int pos)

Traces through the list and gets the value of the node at pos.

COMPLEXITY: O(n)
*/
template <class T>
T AutoSortList<T>::get(int pos) {
  return trace(pos)->value;
}

/*
PUBLIC METHOD: remove(int pos)

Stores the node at pos, has the node remove itself from the list.
Then stores the value, deletes the node, and returns the value.

COMPLEXITY: O(n)
*/
template <class T>
T AutoSortList<T>::remove(int pos) {
  Node *temp = trace(pos);
  T tempVal = temp->value;
  temp->remove();
  delete temp;
  listLength--;
  return tempVal;
}