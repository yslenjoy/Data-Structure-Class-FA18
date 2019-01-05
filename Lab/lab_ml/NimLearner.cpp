/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>

using std::to_string;
using std::vector;


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
  // vertexes
  for (unsigned i = 0; i < startingTokens; i++) {
    g_.insertVertex("p1-" + std::to_string(i));
    g_.insertVertex("p2-" + std::to_string(i));
  }
  // edges
  for (unsigned i = startingTokens; i > 1; i--) {
    std::string vi = std::to_string(i);
    std::string vi_minus_1 = std::to_string(i-1);
    std::string vi_minus_2 = std::to_string(i-2);
    g_.insertEdge("p1-" + vi, "p2-" + vi_minus_1);
    g_.insertEdge("p1-" + vi, "p2-" + vi_minus_2);
    g_.insertEdge("p2-" + vi, "p1-" + vi_minus_1);
    g_.insertEdge("p2-" + vi, "p1-" + vi_minus_2);
    g_.setEdgeWeight("p1-" + vi, "p2-" + vi_minus_1, 0);
    g_.setEdgeWeight("p1-" + vi, "p2-" + vi_minus_2, 0);
    g_.setEdgeWeight("p2-" + vi, "p1-" + vi_minus_1, 0);
    g_.setEdgeWeight("p2-" + vi, "p1-" + vi_minus_2, 0);
  }
  if (startingTokens >= 1) {
    g_.insertEdge("p1-1", "p2-0");
    g_.setEdgeWeight("p1-1", "p2-0", 0);
    g_.insertEdge("p2-1", "p1-0");
    g_.setEdgeWeight("p2-1", "p1-0", 0);
  }
  startingVertex_ = "p1-" + to_string(startingTokens);
  start = startingTokens;
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
  // int curToken = (int)start;
  // int randV = 0;
  // bool player1Move = true;
  // while (curToken - randV >= 0) {
  //   randV = rand() % 2;
  //   randV++; // [1, 2]
  //   int nextToken = curToken - randV;
  //   if (player1Move) {
  //     path.push_back(g_.getEdge("p1-" + to_string(curToken), "p2-" + to_string(nextToken)));
  //     player1Move = false;
  //   } else {
  //     path.push_back(g_.getEdge("p2-" + to_string(curToken), "p1-" + to_string(nextToken)));
  //     player1Move = true;
  //   }
  //   curToken = nextToken;
  // }
  // if (curToken == 1 && randV == 2) {
  //   if (player1Move) {
  //     path.push_back(g_.getEdge("p1-" + to_string(curToken), "p2-0"));
  //   } else {
  //     path.push_back(g_.getEdge("p2-" + to_string(curToken), "p1-0"));
  //   }
  // }
  Vertex start = startingVertex_;
  Vertex v;
  int r;
  while (!g_.getAdjacent(start).empty()) {
    vector<Vertex> neighbor = g_.getAdjacent(start);
    r = rand() % neighbor.size();
    v = neighbor[r];
    Edge e = g_.getEdge(start, v);
    path.push_back(e);
    start = v;
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
  // bool tmp;
  // if (path.size() % 2 == 0) { // even, player 2 won
  //   tmp = true; 
  // } else {
  //   tmp = false;
  // }
  // for (auto& e : path) {
  //   if (tmp) {
  //     g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest) - 1);
  //     tmp = false;
  //   } else {
  //     g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest) + 1);
  //     tmp = true;
  //   }
  // }
  int index = (int)path.size() - 1;
  int flip = 1;
  while (index >= 0) {
    Edge e = path[index];
    int oldweight = g_.getEdgeWeight(e.source, e.dest);
    g_.setEdgeWeight(e.source, e.dest, oldweight + flip);
    flip *= -1;
    index--;
  }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
