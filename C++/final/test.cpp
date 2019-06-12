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

  if (testNode->numberOfConnections() != 2)
    return false;
  if (testNode2->numberOfConnections() != 2)
    return false;
  if (testNode3->numberOfConnections() != 3)
    return false;
  if (testNode4->numberOfConnections() != 1)
    return false;

  return true;
}

bool shortPathTest(void) {
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

  if (graph.getShortestPath(testNode2, testNode4) == 11)
    return true;

  return false;
}

bool minSpanTreeTest(void) {
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
  Path<int> expectedTree = Path<int>();

  expectedTree.addStep(new Edge<int>(testNode, testNode2, 4));
  expectedTree.addStep(new Edge<int>(testNode2, testNode3, 6));
  expectedTree.addStep(new Edge<int>(testNode3, testNode4, 5));

  if (minSpanningTree.size() != expectedTree.size())
    return false;

  for (size_t i = 0; i < expectedTree.size(); i++) {
    if (expectedTree.step(i)->source()->id() != minSpanningTree.step(i)->source()->id())
      return false;
  }
  return true;
}

bool testSuite(void) {
  // Call all testing methods and return if they pass
  return addTest() && shortPathTest() && minSpanTreeTest();
}