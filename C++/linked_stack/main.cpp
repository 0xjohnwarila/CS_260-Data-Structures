#include <iostream>
#include "stack.hpp"

int main() {
  Stack<std::string> newStringStack;
  newStringStack.push("test1");
  std::cout << newStringStack.peek() << std::endl;
  newStringStack.push("test2");
  std::cout << newStringStack.peek() << std::endl;
  newStringStack.pop();
  std::cout << newStringStack.peek() << std::endl;
  newStringStack.push("test3");
  std::cout << newStringStack.peek() << std::endl;
  newStringStack.pop();
  std::cout << newStringStack.peek() << std::endl;
  newStringStack.pop();
  std::cout << newStringStack.peek() << std::endl;
  newStringStack.push("test4");
  newStringStack.push("test4");
  std::cout << newStringStack.peek() << std::endl;

  Stack<int> newIntStack;
  newIntStack.push(5);
  std::cout << newIntStack.peek() << std::endl;
  newIntStack.pop();
  std::cout << newIntStack.peek() << std::endl;
  return EXIT_SUCCESS;
}
