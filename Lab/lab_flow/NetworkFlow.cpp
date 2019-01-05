/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <limits> // positive infinity

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {
  // YOUR CODE HERE
  vector<Vertex> vertexes = g_.getVertices();
  vector <Edge> edges = g_.getEdges();
  // maxFlow_ = std::numeric_limits<int>::max();

  // insert vertex
  for (Vertex & v: vertexes) {
    flow_.insertVertex(v);
    residual_.insertVertex(v);
  }

  // insert edges
  for (Edge & e : edges) {
    Vertex src = e.source;
    Vertex dst = e.dest;
    flow_.insertEdge(src, dst);
    residual_.insertEdge(src, dst);
    residual_.insertEdge(dst, src); // opposite direction too

    // assgin labels and weights
    flow_.setEdgeLabel(src, dst, g_.getEdgeLabel(src, dst));
    flow_.setEdgeWeight(src, dst, 0); // default weight is -1
    residual_.setEdgeLabel(src, dst, g_.getEdgeLabel(src, dst));
    residual_.setEdgeWeight(src, dst, g_.getEdgeWeight(src, dst));
    residual_.setEdgeWeight(dst, src, 0); // opposite direction: 0
  }
  
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int capacity = std::numeric_limits<int>::max();
  for (int i = 0; i < (int)path.size() - 1; i++) {
    Vertex src = path[i];
    Vertex dst = path[i+1];
    if (residual_.getEdgeWeight(src, dst) < capacity) {
      capacity = residual_.getEdgeWeight(src, dst);
    }
  }
  return capacity;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector<Vertex> path;
  // initial maxFlow_ as 0 is important, otherwise it might be some garbage value that is not equal to 0
  maxFlow_ = 0;
  while (findAugmentingPath(source_, sink_, path)) {
    // cout << findAugmentingPath(source_, sink_, path) << endl;
    int capacity = pathCapacity(path);
    // maxFlow_ += capacity;
    for (size_t i = 0; i < path.size() - 1; i++) {
      Vertex src = path[i];
      Vertex dst = path[i + 1];
      // update flow_
      if (flow_.edgeExists(src, dst)) {
        flow_.setEdgeWeight(src, dst, flow_.getEdgeWeight(src, dst) + capacity);
      } else {
        flow_.setEdgeWeight(dst, src, flow_.getEdgeWeight(dst, src) - capacity);
      }
      // update residual_: subtract forward
      residual_.setEdgeWeight(src, dst, residual_.getEdgeWeight(src, dst) - capacity);
      // update residual_: add reverse edge
      residual_.setEdgeWeight(dst, src, residual_.getEdgeWeight(dst, src) + capacity);
    }
  }
  vector<Vertex> adjV = flow_.getAdjacent(flow_.getStartingVertex());
  Vertex start = flow_.getStartingVertex();
  for (auto v : adjV) {
    maxFlow_ += flow_.getEdgeWeight(start, v);
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

