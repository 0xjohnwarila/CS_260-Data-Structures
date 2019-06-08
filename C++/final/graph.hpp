#pragma once

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

// Graph namespace, has nodes and graphs
namespace graph {

template <class T>
class Node {
 private:
  int id_;
  size_t numberOfConnections_;
  bool isNull_;
  T value_;

  std::vector<Node<T>*> connections_;

 public:
  Node() : Node(T()) {}
  Node(bool isNull) : isNull_(isNull) {}
  Node(T value, int id) : value_(value), id_(id) {}

  void addConnection(Node* connectingNode, bool originalCall) {
    numberOfConnections_++;
    // Add the connectingNode to connections_
    connections_.push_back(connectingNode);

    // If this is the original call of the method, call addConnection on the connectingNode
    if (originalCall)
      connectingNode->addConnection(this, false);
  }

  void removeConnection(Node* connectingNode, bool originalCall) {
    // Increment through connections list until connecting node, then replace with nullptr
    for (size_t i = 0; i < connections_.size(); i++) {
      if (connections_.at(i) == connectingNode) {
        // There is an argument to be made that because we are using .erase it may be better to
        // switch to a list instead of a vector. But I think if we ask for connections more than
        // we delete connections, it will be better to leave it.
        connections_.erase(i);
        numberOfConnections_--;
      }
    }

    // If this is the original call of the method, call removeConnection on the connectingNode
    if (originalCall)
      connectingNode->removeConnection(this, false);
  }

  void removeAllConnections(void) {
    // Increment through connections_ and remove each
    for (auto&& currentNode : connections_) {
      removeConnection(currentNode);
    }
  }

  // Getters
  int id(void) const {
    return id_;
  }

  T value(void) const {
    return value_;
  }

  bool isNull(void) const {
    return isNull_;
  }

  size_t numberOfConnections(void) const {
    return numberOfConnections_;
  }

  Node* connectionAt(size_t index) const {
    return connections_.at(index);
  }
};

template <class T>
class Path {
 private:
  bool isNull_;
  Node<T>* source_;
  Node<T>* destination_;
  std::vector<std::pair<Node<T>*, Node<T>*>> steps_;

 public:
  // Empty constructor
  Path() : Path(T()) {}
  // Null Object constructor
  Path(bool isNull) : isNull_(isNull) {}
  // Standard constructor
  Path(Node<T>* source, Node<T>* destination) : source_(source), destination_(destination) {}

  // Add a pair of nodes representing an edge to the steps_ vector
  void addStep(Node<T>* source, Node<T>* destination) {
    steps_.push_back(std::pair<Node<T>*, Node<T>*>(source, destination));
  }

  // Getters
  Node<T>* source(void) const {
    return source_;
  }

  Node<T>* destination(void) const {
    return destination_;
  }

  std::pair<Node<T>*, Node<T>*> step(size_t stepNumber) const {
    return steps_.at(stepNumber);
  }

  bool isNull(void) const {
    return isNull_;
  }
};

template <class T>
class Graph {
 private:
  // nodes_ vector of Node<T>* that are in the graph
  std::vector<Node<T>*> nodes_;
  // Map of all Path<T> between each pair of Node<T>* in the graph
  std::map<std::pair<Node<T>*, Node<T>*>, Path<T>> shortestPaths_;
  // Current minimum spanning tree of the graph
  Path<T> minSpanningTree_;

 public:
  Graph(void);

  // Graph building methods
  bool addNode(Node<T>* inputNode) {
    // null checking
    if (inputNode->isNull())
      return false;

    // checking for clones
    if (std::find(nodes_.begin(), nodes_.end(), inputNode) != nodes_.end())
      return false;

    // adding
    nodes_.pushback(inputNode);
    return true;
  }
  bool addPath(Node<T>* sourceNode, Node<T>* destinationNode);
  // Path returning methods
  Path<T> getShortestPath(Node<T>* sourceNode, Node<T>* destinationNode);
  Path<T> getMinSpanningTree(void) const {
    return minSpanningTree_;
  }

 private:
  // Private methods
  void buildMinSpanTree(void);
  void buildShortestPaths(void);
};
}  // namespace graph
