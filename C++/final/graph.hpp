#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

// Graph namespace, has nodes and graphs
namespace graph {

/*
 Ok so I have no clue at all whats happening. If this utility is in a seperate file it will get
 the std::allocator along with the T* in the vecor. But here it works fine...

 ALLRIGHT FINE YOU LIVE HERE NOW

 Bjarne Stroustrup, forgive me for having a random utility function hanging out in my namespace.

 */
template <class T>
inline std::pair<bool, int> findInVector(const std::vector<T*>& inputVector, const T* element) {
  std::pair<bool, int> result;

  auto iter = std::find(inputVector.begin(), inputVector.end(), element);

  if (iter != inputVector.end()) {
    result.first = true;
    result.second = std::distance(inputVector.begin(), iter);
  } else {
    result.first = false;
    result.second = -1;
  }
  return result;
}

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

  std::vector<Node*> connections_;

 public:
  Node() : Node(T()) {}
  Node(bool isNull) : isNull_(isNull) {}
  Node(T value) : value_(value) { this->isNull_ = false; }

  void addConnection(Node* connectingNode, bool originalCall = true) {
    // add the connection
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

    if (connection.first) {
      connections_.erase(connection.second);
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

  bool isConnected(Node* otherNode) {
    return findInVector(connections_, otherNode).first;
  }

  size_t numberOfConnections(void) const {
    return numberOfConnections_;
  }

  Node* connectionAt(size_t index) const {
    return connections_.at(index);
  }

  // Operator Overloading
  bool operator>(const Node& otherNode) {
    return id_ > otherNode.id();
  }

  bool operator<(const Node& otherNode) {
    return id_ < otherNode.id();
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

  bool isConnected(Edge* otherEdge) {
    return (source_->isConnected(otherEdge->source()) || destination_->isConnected(otherEdge->destination()));
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
  std::vector<Edge<T>*> steps_;

 public:
  // Empty constructor
  Path() : Path(T()) {}
  // Null Object constructor
  Path(bool isNull) : isNull_(isNull) {}
  // Standard constructor
  Path(Node<T>* source, Node<T>* destination) : source_(source), destination_(destination) {}

  // Add a pair of nodes representing an edge to the steps_ vector
  void addStep(Edge<T>* edge) {
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

  size_t size(void) const {
    return steps_.size();
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
  // Current minimum spanning tree of the graph
  Path<T> minSpanningTree_;

  int nextId_;

 public:
  Graph(void) : nextId_(0){};

  // Graph building methods; returns true if successfully added, false if not
  bool addNode(Node<T>* inputNode) {
    // null checking
    if (inputNode->isNull())
      return false;

    // checking for clones
    if (findInVector(nodes_, inputNode).first)
      return false;

    // adding
    inputNode->setId(nextId_++);
    nodes_.push_back(inputNode);
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
    sourceNode->addConnection(destinationNode);
    auto edge = new Edge<T>(sourceNode, destinationNode, weight);
    auto edge2 = new Edge<T>(destinationNode, sourceNode, weight);
    edges_.push_back(edge);
    edges_.push_back(edge2);

    // build min spanning tree
    buildMinSpanTree();

    return true;
  }

  double getShortestPath(Node<T>* sourceNode, Node<T>* destinationNode) {
    // If there is some error getting the path, return a nullObject

    // null checking
    if (sourceNode->isNull() || destinationNode->isNull())
      return 0;

    // checking that nodes are in the graph
    if (!(findInVector(nodes_, sourceNode).first && findInVector(nodes_, destinationNode).first))
      return 0;

    // Sort nodes by their id
    std::sort(nodes_.begin(), nodes_.end());

    // Run bellman-ford algorithm
    return bellmanFord(sourceNode, destinationNode);
  }

  Path<T> getMinSpanningTree(void) const {
    return minSpanningTree_;
  }

 private:
  // Private method
  double bellmanFord(Node<T>* source, Node<T>* destination) {
    const size_t size = nodes_.size();
    std::vector<double> distance;
    std::vector<Node<T>*> predecessor;

    // Initialize
    for (size_t i = 0; i < size; i++) {
      // For every node, the distance is infinity
      distance.push_back(std::numeric_limits<double>::infinity());
      // For every predecessor, fill with nullObject
      predecessor.push_back(new Node<T>(true));
    }

    // Distance from source to source is 0
    distance.at(source->id()) = 0;

    // Relax edges
    for (size_t i = 0; i < size; i++) {
      for (auto&& edge : edges_) {
        // if ( dist[edge.src] + edge.weight < dist[edge.dest])
        if ((distance.at(edge->source()->id()) + edge->weight() < distance.at(edge->destination()->id()))) {
          // distance[edge.dest] = distance[edge.src] + edge.weight
          distance.at(edge->destination()->id()) = distance.at(edge->source()->id()) + edge->weight();

          // pred[edge.dest] = edge.dest
          predecessor.at(edge->destination()->id()) = edge->destination();
        }
      }
    }

    // Check for negative weight cylces
    for (auto&& edge : edges_) {
      if (distance.at(edge->source()->id()) + edge->weight() < distance.at(edge->destination()->id())) {
        std::cerr << "ERROR: graph contains a negative-weight cycle" << std::endl;
      }
    }

    return distance.at(destination->id());
  }

  // O(n*e) n: nodes e: edges
  void buildMinSpanTree(void) {
    // sort edges by weight
    std::sort(edges_.begin(), edges_.end());

    // loop through the next smallest edges, adding if it does not create a loop
    for (auto&& edge : edges_) {
      if (!minSpanningTree_.loop(edge))
        minSpanningTree_.addStep(edge);
    }
  }

  // O(n)
  void visitNode(Node<T>* node, std::vector<Node<T>*>& visitedNodes) {
    visitedNodes.push_back(node);

    for (size_t i = 0; i < node->numberOfConnections(); i++) {
      if (!inVector(visitedNodes, node->connectionAt(i)).first)
        visitNode(node->connectionsAt(i));
    }
  }
};

}  // namespace graph
