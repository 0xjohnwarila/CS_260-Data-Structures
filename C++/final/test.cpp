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

  int numberOfConns1 = testNode->numberOfConnections();
  int numberOfConns2 = testNode2->numberOfConnections();
  int numberOfConns3 = testNode3->numberOfConnections();
  int numberOfConns4 = testNode4->numberOfConnections();

  if (!(numberOfConns1 == 2))
    return false;
  if (!(numberOfConns2 == 2))
    return false;
  if (!(numberOfConns3 == 3))
    return false;
  if (!(numberOfConns4 == 1))
    return false;

  return true;
}
/*
bool minSpanTest(void) {
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

  Path<int> minSpanTree = graph.getMinSpanningTree();

  Path<int> expectedTree = Path<int>();
  expectedTree.addStep(new Edge<int>(testNode, testNode2, 4));
  expectedTree.addStep(new Edge<int>(testNode2, testNode3, 6));
  expectedTree.addStep(new Edge<int>(testNode3, testNode4, 5));

  if (minSpanTree.size() != expectedTree.size())
    return true;

  for (size_t i = 0; i < minSpanTree.size(); i++) {
    std::cout << minSpanTree.step(i)->source()->id() << " " << expectedTree.step(i)->source()->id() << std::endl;
    if (minSpanTree.step(i)->source()->id() != expectedTree.step(i)->source()->id())
      return true;
  }

  return true;
}
*/
bool shortestPathTest(void) {
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

  std::cout << graph.getShortestPath(testNode, testNode4) << std::endl;

  if (graph.getShortestPath(testNode4, testNode) == 15)
    return true;
  return false;
}

bool testSuite(void) {
  // Call all testing methods and return if they pass

  // For now return false as first step (TDD)
  return addTest() && shortestPathTest();
}