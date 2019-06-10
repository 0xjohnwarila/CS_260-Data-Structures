#include "test.hpp"
#include "graph.hpp"

bool addTest(void) {
  using namespace graph;
  Graph<int> graph;
  auto testNode = new Node(9);
  auto testNode2 = new Node(15);

  graph.addNode(testNode);
  graph.addNode(testNode2);

  graph.addPath(testNode, testNode2, 4);

  return false;
}

bool testSuite(void) {
  // Call all testing methods and return if they pass

  // For now return false as first step (TDD)
  return addTest();
}