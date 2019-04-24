/*
This ADT is a linked list, more specifically this is a doubly linked list as the nodes have
next AND previous node pointers.

You are able to perform a series of actions on the linked list.

Insert: If you do not specify a position for the new value to be inserted, it will be placed at the
start of the list by default. If you provide a position that is larger than the size of the list,
the list will place the value at the end of the list. 
If, however, you provide a valid position, the new value will be inserted at that position. The list
is 0 indexed.

Append: If you want to add a new value to the end of the list you can append it with... append! No
need to specify a postion, there is only one end of this list.

Get: If you want to get the value of a node, but do not want to delete it from the list, you can
just get it.

Remove: If you want to get the value and also remove the node from the list, you can call remove
with a postion.
*/
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

  Node *head;
  int listLength;

 public:
  // Constructor
  LinkedList() : head(new Node()), listLength(0) {}

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
  listLength++;
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
  listLength--;
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
  listLength++;
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
  listLength++;
}