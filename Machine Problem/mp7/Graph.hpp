#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

using std::cout;
using std::endl;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return incidentEdges(v).size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.insert({key, v});
  // vertexMap[key] = v; this cannot work, but insert can work
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  // remove edge from edgeList (source is the key)
  std::list<edgeListIter> adjEdges = adjList.find(key)->second;
  for (auto& adjEIt : adjEdges) {
    // std::cout << (*adjEIt).get().source().key() << (*adjEIt).get().dest().key() << std::endl;
    removeEdge((*adjEIt).get().source().key(), (*adjEIt).get().dest().key());
    // edgeList.erase(adjEIt); // this erase won't remove edges from the edges from the adjacent vertex
  }
  // remove edge from the edgeList (dest is the key)
  
  // the paramter passed in erase() function is the iterator, not the key
  vertexMap.erase(vertexMap.find(key));
  // before erase the key, erase all the values with that key
  // @TODO later
  adjList.erase(adjList.find(key));
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);

  auto adjIt = adjList.find(v1.key());
  if (adjIt != adjList.end()) {
    adjList[v1.key()].push_back(edgeList.begin());
  } else {
    std::list<edgeListIter> tmpList;
    tmpList.push_back(edgeList.begin());
    adjList.insert({v1.key(), tmpList});
  }
  // adjList[v1.key()].push_back(edgeList.begin());
  if (e.directed() == false) {
    // std::cout << "not directed edge!" << std::endl;
    auto adjIt2 = adjList.find(v2.key());
    if (adjIt2 != adjList.end()) {
      adjList[v2.key()].push_back(edgeList.begin());
    } else {
      std::list<edgeListIter> tmpList;
      tmpList.push_back(edgeList.begin());
      adjList.insert({v2.key(), tmpList});
    }
    // adjList[v2.key()].push_back(edgeList.begin());
  }
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  size_t num = edgeList.size();
  if (num == 0 || vertexMap.find(key1) == vertexMap.end() || vertexMap.find(key2) == vertexMap.end()) {
    return;
  }
  // check whether the edge exists in the graph
  std::list<E_byRef> eListK1 = incidentEdges(key1);
  std::list<E_byRef> eListK2 = incidentEdges(key2);
  bool hasEdgeToKey2 = false;
  bool hasEdgeToKey1 = false;
  // the following commented code checks whether there is edges between to keys, if not, return the function early
  // @TODO: has bugs, needed to be fixed.
  // for (auto listIt: eListK1) {
  //   if (listIt.get().dest().key() == key2) {
  //     hasEdgeToKey2 = true;
  //   }
  // }
  // for (auto listIt: eListK2) {
  //   if (listIt.get().dest().key() == key1) {
  //     hasEdgeToKey1 = true;
  //   }
  // }
  // cout << "heresdf" << endl;
  // if (!(hasEdgeToKey2 && hasEdgeToKey1)) {
  //   return;
  // }
  // cout << "here: function not early return" << endl;

  // first method: call the helper function, the most simpler way,
  // it also shows why adjList is a unordered_map with value as edgeListIter
  edgeListIter findedIt = edgeList.begin();
  for (auto it = edgeList.begin(); it != edgeList.end(); ++it) {
    auto v1 = vertexMap.find(key1);
    auto v2 = vertexMap.find(key2);
    if (it->get().source() == v1->second && it->get().dest() == v2->second) {
        findedIt = it;
        // cout << "here: find it" << endl;
      }
    }
  removeEdge(findedIt);

  // Another simplier way to do this is to loop throught the adjList
  // rather than the edgeList, which can reduce the search size.
  // for (auto adjIt : adjList1) {
  //   if (adjIt->get().source() == vertexMap[key1] && adjIt->get().dest() == vertexMap[key2]) {
  //     adjIt = adjList1.erase(adjIt);
  //   } else {
  //     ++adjIt;
  //   }
  // }
  // for (auto & adjIt : adjList2) {
  //   if (adjIt->get().source() == vertexMap[key2] && adjIt->get().dest() == vertexMap[key1]) {
  //     adjIt = adjList2.erase(adjIt);
  //   } else {
  //     ++adjIt;
  //   }
  // }

  // another method: loop through the edgeList
  // for (auto it = edgeList.begin(); it != edgeList.end(); ) {
  //   if (it->get().source() == vertexMap[key1] && it->get().dest() == vertexMap[key2] && it->get().directed()) {
  //     // adjList
  //     std::list<edgeListIter> key1List = adjList[key1];
  //     for (auto adjIt = key1List.begin(); adjIt != key1List.end(); ) {
  //       if (*adjIt == it) {
  //         adjIt = key1List.erase(adjIt);
  //       } else {
  //         ++adjIt;
  //       }
  //     }
  //     // edgeList
  //     it = edgeList.erase(it);
  //   }
  //   else if (it->get().source() == vertexMap[key2] && it->get().dest() == vertexMap[key1] && !it->get().directed()) {
  //     std::list<edgeListIter> key2List = adjList[key2];
  //     for (auto adjIt = key2List.begin(); adjIt != key2List.end(); ) {
  //       if (*adjIt == it) {
  //         adjIt = key2List.erase(adjIt);
  //       } else {
  //         ++adjIt;
  //       }
  //     }
  //     it = edgeList.erase(it);
  //   }
  //   else {
  //     ++it;bool tmp1 = g.isAdjacent("a", "d");
  //   }
  // }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2

  string key1 = it->get().source().key();
  string key2 = it->get().dest().key();
  adjList[key1].remove(it);
  adjList[key2].remove(it);
  edgeList.erase(it);

  // don't need the following staff, since adjList is a map that can be indexing
  // for (auto i = edgeList.begin(); i != edgeList.end(); ) {
  //   if (i->source() == it.source() && i->dest() == it.dest() && i->directed()) {
  //     key1 = i->source().key();
  //     // key2 = i->dest().keys();

  //     std::list<edgeListIter> key1List = adjList[key1];
  //     for (auto adjIt = key1List.begin(); adjIt != key1List.end(); ) {
  //       if (adjIt == it) {
  //         adjIt = key1List.erase(adjIt);
  //       } else {
  //         ++adjIt;
  //       }
  //     }
  //     i = edgeList.erase(i);
  //   } else if (i->source() == it.dest() && i->dest() == it.source() && !i->directed()) {
  //     key2 = i->dest().key();
  //     std::list<edgeListIter> key2List = adjList[key2];
  //     for (auto adjIt = key2List.begin(); adjIt != key2List.end(); ) {
  //       if (adjIt == it) {
  //         adjIt = key2List.erase(adjIt);
  //       } else {
  //         ++adjIt;
  //       }
  //     }
  //   }
  //   else {
  //     ++i;
  //   }
  // }
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;

  std::list<edgeListIter> adjKey = adjList.find(key)->second;
  for (auto adjIt = adjKey.begin(); adjIt != adjKey.end(); ++adjIt) {
    edges.push_back(*(*adjIt));
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  for (auto edgeIt = edgeList.begin(); edgeIt != edgeList.end(); ++edgeIt) {
    // std::cout << edgeIt->get().source() << std::endl;
    // std::cout << edgeIt->get().dest() << std::endl;
    // std::cout << edgeIt->get().directed() << std::endl;


    if (edgeIt->get().source().key() == key1 && edgeIt->get().dest().key() == key2) {
      return true;
    } else if (edgeIt->get().source().key() == key2 && edgeIt->get().dest().key() == key1 && !edgeIt->get().directed()) {
      return true;
    }
  }
  return false;
}
