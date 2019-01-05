#include <queue>
#include <algorithm>
#include <string>
#include <list>

using std::cout;
using std::endl;

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;

  // BFS
	std::unordered_map<std::string, bool> visited;
	std::list<string> queue;
	std::unordered_map<std::string, string> pred;
	std::unordered_map<std::string, int> dist; // this variable is actually not necessary here, since the graph is unweighted
	bool exit = false; // flag to see whether the destination is found or not, if found, exit the BFS part

  for (auto & i : vertexMap) {
  	visited.insert({i.first, false});
  	dist.insert({i.first, INT_MAX});
  	pred.insert({i.first, "initial"});
  }

  visited[start] = true;
  dist[start] = 0;
  queue.push_back(start);

  while (!queue.empty()) {
  	string u = queue.front();
  	queue.pop_front();
  	std::list<std::reference_wrapper<E>> edges = incidentEdges(u);
  	for (auto & listIt : edges) {
  		string curV;
      // this if loop assuming the graph is undirected
      // since incidentEdges(u) will get both the outgoing and incoming edges
      if (listIt.get().dest().key() == u) { // the edge is the incoming edge
        curV = listIt.get().source().key();
      } else { // the edge is the outgoing edge
        curV = listIt.get().dest().key();
      }
  		if (!visited[curV]) {
  			visited[curV] = true;
  			dist[curV] = dist[u] + 1;
  			pred[curV] = u;
  			queue.push_back(curV);
  			if (curV == end) {
  				exit = true;
  				break;
  			}
  		}
  	}
  	if (exit) {
  		break;
  	}
  }
  // end of BFS

  // trace back the predecessor
  string crawl = end;
  path.push_back(crawl);
  while (pred[crawl] != "initial") {

  	path.push_back(pred[crawl]);
  	crawl = pred[crawl];
  }
  //path.push_back(start); // this line is not needed

  // reverse path
  path.reverse();

  return path;
}
