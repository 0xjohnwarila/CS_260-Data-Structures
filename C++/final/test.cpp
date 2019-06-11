#include <iostream>

#include "graph.hpp"
#include "test.hpp"

bool addTest(void) {
  using namespace graph;
  Graph<int> graph;
  auto testNode = new Node(9);
  auto testNode2 = new Node(15);
  auto testNode3 = new Node(15);

  graph.addNode(testNode);
  graph.addNode(testNode2);
  graph.addNode(testNode3);

  graph.addPath(testNode, testNode2, 4);
  graph.addPath(testNode, testNode3, 8);
  graph.addPath(testNode2, testNode3, 1);

  Path<int> minSpanningTree = graph.getMinSpanningTree();

  Path<int> shortPath = graph.getShortestPath(testNode, testNode2);

  return false;
}

bool testSuite(void) {
  // Call all testing methods and return if they pass

  // For now return false as first step (TDD)
  return addTest();
}