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
  std::vector<std::pair<Node*, int>> weightedConnections_;

 public:
  Node() : Node(T()) {}
  Node(bool isNull) : isNull_(isNull) {}
  Node(T value, int id) : value_(value), id_(id) {}

  void addConnection(Node* connectingNode, int weight, bool originalCall = true) {
    // add the connection
    connections_.pushback(connectingNode);
    weightedConnections_.pushback(std::pair<Node*, int>(connectingNode, weight));

    // If this is the original call of the method, call addConnection on the connectingNode
    if (originalCall)
      connectingNode->addConnection(this, weight, false);
  }

  void removeConnection(Node* connectingNode, bool originalCall = true) {
    /*
    There is an argument to be made that because we are using .erase and std::find it may be
    better to switch to a list instead of a vector. But I think if we ask for connections more
    than we delete connections, it will be better to leave it.
    */

    std::pair<bool, int> connection = findInVector(connections_, connectingNode);

    if (connection.first()) {
      connections_.erase(connection.second());
      weightedConnections_.erase(connection.second());
    } else {
      return;
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
  // Setters
  void setId(int id) {
    id_ = id;
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
Edge Class

Stores a source, destination, and weight.
Has methods to check for connectivity, and overloaded > and < operators

*/

template <class T>
class Edge {
 private:
  Node<T>* source_;
  Node<T>* destination_;
  int weight_;

 public:
  // Constructor
  Edge(void) : Edge(T()){};
  Edge(Node<T>* source, Node<T>* destination, int weight) : source_(source), destination_(destination), weight_(weight) {}

  bool isConnected(Edge otherEdge) {
    return (source_->isConnected(otherEdge.source()) || destination_->isConnected(otherEdge.destination()));
  }

  // Getters
  Node<T>* source(void) const {
    return source_;
  }

  Node<T>* destination(void) const {
    return destination_;
  }

  int weight(void) const {
    return weight_;
  }

  // Operator Overloading
  bool operator>(const Edge& otherEdge) {
    return weight_ > otherEdge.weight();
  }

  bool operator<(const Edge& otherEdge) {
    return weight_ < otherEdge.weight();
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
  std::vector<Edge<T>> steps_;

 public:
  // Empty constructor
  Path() : Path(T()) {}
  // Null Object constructor
  Path(bool isNull) : isNull_(isNull) {}
  // Standard constructor
  Path(Node<T>* source, Node<T>* destination) : source_(source), destination_(destination) {}

  // Add a pair of nodes representing an edge to the steps_ vector
  void addStep(Edge<T> edge) {
    steps_.push_back(edge);
  }

  bool loop(Edge<T>* edge) const {
    for (auto&& currentEdge : steps_) {
      if (edge->isConnected(currentEdge))
        return true;
    }

    return false;
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
  // Vector of all edges in the graph. edges are a pair of int and pair nodes
  std::vector<Edge<T>*> edges_;
  // Map of all Path<T> between each pair of Node<T>* in the graph
  std::map<std::pair<Node<T>*, Node<T>*>, Path<T>> shortestPaths_;
  // Current minimum spanning tree of the graph
  Path<T> minSpanningTree_;
  int nextId;

 public:
  Graph(void) : nextId(0){};

  // Graph building methods; returns true if successfully added, false if not
  bool addNode(Node<T>* inputNode) {
    // null checking
    if (inputNode->isNull())
      return false;

    // checking for clones
    if (findInVector(nodes_, inputNode).first())
      return false;

    // adding
    inputNode->setId(nextId++);
    nodes_.pushback(inputNode);
    return true;
  }

  bool addPath(Node<T>* sourceNode, Node<T>* destinationNode, int weight) {
    // null checking
    if (sourceNode->isNull() || destinationNode->isNull())
      return false;

    // checking for duplicate connections
    if (sourceNode->isConnected(destinationNode))
      return false;

    // add connection
    sourceNode->addConnection(destinationNode, weight);
    edges_.pushback(Edge(sourceNode, destinationNode, weight));

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
  void buildShortestPaths(void) {
  }

  void buildMinSpanTree(void) {
    // sort edges
    std::sort(edges_.begin(), edges_.end());

    // loop through the next smallest edges, adding if it does not create a loop
    for (auto&& edge : edges_) {
      if (!minSpanningTree_.loop(edge))
        minSpanningTree_.addStep(edge);
    }
  }
};

}  // namespace graph
