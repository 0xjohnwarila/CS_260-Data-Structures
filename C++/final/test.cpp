#include <iostream>

#include "graph.hpp"
#include "test.hpp"

bool addTest(void) {
  using namespace graph;
  Graph<int> graph;
  auto testNode = new Node(42);
  auto testNode2 = new Node(42);
  auto testNode3 = new Node(42);
  auto testNode4 = new Node(42);

  graph.addNode(testNode);
  graph.addNode(testNode2);
  graph.addNode(testNode3);
  graph.addNode(testNode4);

  graph.addPath(testNode, testNode2, 4);
  graph.addPath(testNode, testNode3, 88);
  graph.addPath(testNode2, testNode3, 6);
  graph.addPath(testNode3, testNode4, 5);

  Path<int> minSpanningTree = graph.getMinSpanningTree();

  Path<int> shortPath = graph.getShortestPath(testNode4, testNode2);

  return false;
}

bool testSuite(void) {
  // Call all testing methods and return if they pass

  // For now return false as first step (TDD)
  return addTest();
}