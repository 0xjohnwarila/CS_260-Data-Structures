#pragma once

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

#include "utils.hpp"

// Graph namespace, has nodes and graphs
namespace graph {

/*
Node Class

Used as the nodes of a graph. Stores a value of any type, and a vector of connections to other
nodes.

Can remove its connections.

*/
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

  void addConnection(Node* connectingNode, bool originalCall = true) {
    numberOfConnections_++;
    // Add the connectingNode to connections_
    connections_.push_back(connectingNode);

    // If this is the original call of the method, call addConnection on the connectingNode
    if (originalCall)
      connectingNode->addConnection(this, false);
  }

  void removeConnection(Node* connectingNode, bool originalCall = true) {
    /*
    There is an argument to be made that because we are using .erase and std::find it may be
    better to switch to a list instead of a vector. But I think if we ask for connections more
    than we delete connections, it will be better to leave it.
    */

    std::pair<bool, int> connection = findInVector(connections_, connectingNode);
    if (connection.first())
      connections_.erase(connection.second());
    else
      return;

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

  bool isConnected(Node<T>* otherNode) {
    return findInVector(connections_, otherNode).first();
  }

  size_t numberOfConnections(void) const {
    return numberOfConnections_;
  }

  Node* connectionAt(size_t index) const {
    return connections_.at(index);
  }
};

/*
Path class

Used to store a series of steps between nodes.

*/
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

/*
Graph Class

Holds information about a set of connected nodes. Can add more nodes and the connections between
them.

Generates Paths for shortest paths and minimum spanning tree.

*/
template <class T>
class Graph {
 private:
  // nodes_ vector of Node<T>* that are in the graph
  // Implementation Note: This might be changed to a set later. Depends on how I use it...
  std::vector<Node<T>*> nodes_;
  // Map of all Path<T> between each pair of Node<T>* in the graph
  std::map<std::pair<Node<T>*, Node<T>*>, Path<T>> shortestPaths_;
  // Current minimum spanning tree of the graph
  Path<T> minSpanningTree_;

 public:
  Graph(void);

  // Graph building methods; returns true if successfully added, false if not
  bool addNode(Node<T>* inputNode) {
    // null checking
    if (inputNode->isNull())
      return false;

    // checking for clones
    if (findInVector(nodes_, inputNode).first())
      return false;

    // adding
    nodes_.pushback(inputNode);
    return true;
  }

  bool addPath(Node<T>* sourceNode, Node<T>* destinationNode) {
    // null checking
    if (sourceNode->isNull() || destinationNode->isNull())
      return false;

    // checking for duplicate connections
    if (sourceNode->isConnected(destinationNode))
      return false;

    // add connection
    sourceNode->addConnection(destinationNode);

    // build shortest path map
    buildShortestPaths();

    // build min spanning tree
    buildMinSpanTree();

    return true;
  }

  // Path returning methods
  Path<T> getShortestPath(Node<T>* sourceNode, Node<T>* destinationNode) const {
    // If there is some error getting the path, return a nullObject

    // null checking
    if (sourceNode->isNull() || destinationNode->isNull())
      return Path(true);

    // checking that nodes are in the graph
    if (!(findInVector(nodes_, sourceNode).first() && findInVector(destinationNode).first()))
      return Path(true);

    // return the value from the map of paths based off the pair of sourceNode and destinationNode
    return shortestPaths_[std::pair<Node<T>*, Node<T>*>(sourceNode, destinationNode)];
  }

  Path<T> getMinSpanningTree(void) const {
    return minSpanningTree_;
  }

 private:
  // Private methods
  void buildMinSpanTree(void);
  void buildShortestPaths(void);
};

}  // namespace graph
