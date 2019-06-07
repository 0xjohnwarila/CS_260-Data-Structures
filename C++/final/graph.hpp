#pragma once

#include <utility>
#include <vector>

// Graph namespace, has nodes and graphs
namespace graph {

template <class T>
class Node {
 private:
  int id_;
  size_t numberOfConnections_;
  T value_;

  std::vector<Node<T>*> connections_;

 public:
  Node() : Node(T()) {}
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
      this.removeConnection(currentNode);
    }
  }

  // Getters
  int id(void) const {
    return id_;
  }

  T value(void) const {
    return value_;
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
  Node<T>* source_;
  Node<T>* destination_;
  std::vector<std::pair<Node<T>*, Node<T>*>> steps_;

 public:
  Path() : Path(T()) {}
  Path(Node<T>* source, Node<T>* destination) : source_(source), destination_(destination) {}

  Node<T>* source(void) const {
    return source_;
  }

  Node<T>* destination(void) const {
    return destination_;
  }

  std::pair<Node<T>*, Node<T>*> step(size_t stepNumber) const {
    return steps_.at(stepNumber);
  }
};

template <class T>
class Graph {
 private:
 public:
  Graph(void);

  bool addNode(Node<T>* inputNode);
  bool addPath(Node<T>* sourceNode, Node<T>* destinationNode);
  Path<T> getShortestPath(Node<T>* sourceNode, Node<T>* destinationNode);
  Tree getMinSpanningTree(void);
};
}  // namespace graph
