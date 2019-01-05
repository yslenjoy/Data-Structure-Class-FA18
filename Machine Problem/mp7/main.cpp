#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "DirectedEdge.h"

#include "CYOA.h"

#include <string>
#include <iostream>

int main() {
  // CYOA cyoa;
  // Graph<Vertex, DirectedEdge> g = cyoa.load("data/");
  // std::cout << g << std::endl;

  // Create graph
  Graph<Vertex, Edge> g;
  g.insertVertex("a");
  g.insertVertex("b");
  g.insertVertex("c");
  g.insertVertex("d");
  g.insertVertex("e");
  g.insertVertex("f");
  g.insertVertex("g");
  g.insertVertex("h");

  // Edges on `a`:
  g.insertEdge("a", "b");
  g.insertEdge("a", "c");
  g.insertEdge("a", "d");

  // Additional edges on `b`:
  g.insertEdge("b", "c");

  // Additional edges on `c`:
  g.insertEdge("c", "e");
  g.insertEdge("c", "h");

  // Additional edges on `d`:
  g.insertEdge("d", "e");

  // Additional edges on `e`: (none)

  // Additional edges on `f`:
  g.insertEdge("f", "g");

  // Additional edges on `g`:
  g.insertEdge("g", "h");

  // Additional edges on `h`: (none)

  /* ************* my own test *************/
  // test for removeEdge()

  bool tmp1, tmp2, tmp3, tmp4;

  // tmp1 = g.isAdjacent("a", "d");
  // std::cout << tmp1 << " (should be 1)"<< std::endl;
  // g.removeEdge("a", "d");
  // tmp2 = g.isAdjacent("a", "d");
  // std::cout << tmp2 << " (should be 0)"<< std::endl;

  tmp1 = g.isAdjacent("a", "b");
  tmp4 = g.isAdjacent("c", "b");
  std::cout << tmp1 << " (should be 1)"<< std::endl;
  std::cout << tmp4 << " (should be 1)"<< std::endl;
  g.removeVertex("b");
  tmp2 = g.isAdjacent("a", "b");
  tmp3 = g.isAdjacent("c", "b");
  auto tmp5 = g.incidentEdges("c");
  std::cout << tmp2 << " (should be 0)"<< std::endl;
  std::cout << tmp3 << " (should be 0)" << std::endl;
  std::cout << tmp5.size() << " (should be 3)" << std::endl;
  std::cout << g.incidentEdges("a").size() << "(should) be 2" <<std::endl;
  /* ********/

  // Modify the g.shortestPath call to find the shortest path to your story:
  /*
  std::list<std::string> path = g.shortestPath("waf-zoey", "waf-zoey-oak");
  for (std::string key : path) {
    std::cout << key << " -> ";
  }
  std::cout << "[THE END]" << std::endl;
  */
  // std::list<std::string> path = g.shortestPath("d", "e");
  // for (auto & i : path) {
  //   std::cout << i << std::endl;
  // }

  return 0;
}
