#pragma once

template <class T>
class LinkedList {
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

    // Equivalency operators. Take a reference to another iterator, and check the currents
    bool operator==(const Iterator &i) { return current == i.current; }
    bool operator!=(const Iterator &i) { return current != i.current; }

    // Get the value of current
    T &operator*() { return current->value; }

    // Iterate!
    Iterator &operator++() {
      current = current->next;
      return *this;
    }

    // Yay for operator overloading!
    Iterator operator++(int) {
      Iterator clone(this);
      current = current->next;
      return clone;
    }
  };

  // Traces through the list. COMPLEXITY O(n)
  Node *trace(int pos) {
    Node *currentNode = head;
    for (int i = 0; i < pos + 1; i++) {
      currentNode = currentNode->next;
    }
    return currentNode;
  }

  Node *head;

 public:
  // Constructor
  LinkedList() : head(new Node()) {}

  // Public methods
  void insert(T inVal, int pos);
  void insert(T inVal);
  void append(T inVal);

  T get(int pos);
  T remove(int pos);

  // Iterator stuff (aka the begin and end methods needed...)
  Iterator begin() { return Iterator(head->next); }
  Iterator end() { return Iterator(head); }
};

/*
PUBLIC METHOD: append(T inVal)

Appends a new node to the end of the list.

COMPLEXITY: O(1)
*/
template <class T>
void LinkedList<T>::append(T inVal) {
  (new Node(inVal))->insert(head);
}

/*
PUBLIC METHOD: get(int pos)

Traces through the list and gets the value of the node at pos.

COMPLEXITY: O(n)
*/
template <class T>
T LinkedList<T>::get(int pos) {
  return trace(pos)->value;
}

/*
PUBLIC METHOD: remove(int pos)

Stores the node at pos, has the node remove itself from the list.
Then stores the value, deletes the node, and returns the value.

COMPLEXITY: O(n)
*/
template <class T>
T LinkedList<T>::remove(int pos) {
  Node *temp = trace(pos);
  T tempVal = temp->value;
  temp->remove();
  delete temp;
  return tempVal;
}

/*
PUBLIC METHOD: insert(T inVal)

Adds new node to the front of the list.

COMPLEXITY: O(1)
*/
template <class T>
void LinkedList<T>::insert(T inVal) {
  (new Node(inVal))->insert(head->next);
}

/*
PUBLIC METHOD: insert(T inVal, int pos)

Overloaded method for inserting at a specific location.

Traces through the list until it reaches pos, then inserts the
new node.

COMPLEXITY: O(n)
*/
template <class T>
void LinkedList<T>::insert(T inVal, int pos) {
  (new Node(inVal))->insert(trace(pos));
}