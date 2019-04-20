/*
Stack ADT

This ADT is a LIFO (Last In First Out) structure. As
you add an item to the 'Stack' you put it ont the 'top'
of the other items. To retrieve and item you can either
'peek' (in the case of this implementation) or 'pop'.

Pop will delete the top item, and in some stacks also
return the value of that item.

Peek returns the value of the top item without deleting
it.

Note: In this stack the method 'get' has been added. The
get method deletes the top node and returns its value, this
mimics pop in some other stacks.
*/

#pragma once

template <class T>
class Stack {
 private:
  /*
  PRIVATE STRUCT: Node

    The node struct is stored inside of the stack class
    in this implementation. The reasoning behind this is
    to make a stack that only holds one type of data, but
    is also templated. Another reason is that having the
    node be a private member hides implementation from
    those who do not care and only wish to put values into
    the stack and take them out again.

    The node structure is quite basic, storing a templated
    value, and a pointer to the next node.
    
    There are three constructors, the first being an empty
    node. (This is used for signifying the absolute bottom
    of a stack)

    The second and third constructors are used for creating
    nodes with a value and optional nextnode pointer.
  */
  struct Node {
    T value;
    Node *nextNode;
    Node() : Node(T()) {}
    Node(T value) : value(value), nextNode(nullptr) {}
    Node(T value, Node *next) : value(value), nextNode(next) {}
  };

  Node *head;

  int stackSize;

 public:
  /*
  CONSTRUCTOR: Stack()

    Creates new stack and sets head to a new empty node.
    This empty node is not counted in the size attribute,
    but instead is used to keep the stack in bounds.

    Note: Please do not attempt to add an empty node to 
    the stack. This will cause all the data below that
    node to become unreachable. We don't want that.
  */
  Stack() : head(new Node()){};

  /*
  PUBLIC METHOD: void pop(void)
  
    Deletes the top node in the stack, and points to new
    top. Pop can be run on an empty stack (nothing will be done).

    Note: In this stack pop does not return the value of
    top, please run peek to get value before popping or use
    get method.

    Complexity O(1)
  */
  void pop(void) {
    if (head->nextNode == nullptr) {
      return;
    } else {
      Node *temp = head;
      head = head->nextNode;
      delete temp;
      stackSize--;
    }
  }

  /*
  PUBLIC METHOD: T get(void)

    Deletes the top node and returns the value.

    Complexity O(1)
  */
  T get(void) {
    if (head->nextNode == nullptr) {
      return head->value;
    } else {
      Node *temp = head;
      T topVal = temp->value;
      head = head->nextNode;
      delete temp;
      stackSize--;
      return topVal;
    }
  }

  /*
  PUBLIC METHOD: void push(T inVal)

    Pushes a new value onto the stack.

    Note: In this stack please use the same data type
    for all nodes.

    Complexity O(1)
  */
  void push(T inVal) {
    Node *inputNode = new Node(inVal, head);
    head = inputNode;
    stackSize++;
  }

  /*
  PUBLIC METHOD: T peek(void)

    Peek will return the value of the top item in the stack.
    If the stack is empty, peek will return 0, an empty string, 
    or similar null value. Please run the size method before
    peeking to ensure valid data.

    Complexity O(1)
  */
  T peek(void) {
    return head->value;
  }

  /*
  PUBLIC METHOD: int size(void)

    Returns the size of the stack. Should be ran before peek and
    pop methods.

    Note: Not actually needed for pop, but is a good practice.

    Complexity O(1)
  */
  int size(void) {
    return stackSize;
  }
};
