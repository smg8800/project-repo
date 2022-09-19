#pragma once
#include "graph.h"
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <utility>
#include <limits>

using std::unordered_map;
typedef std::pair<int, int> intpair;

/* 
 * Returns a vector of the shortest path from the source in the graph to the
 * destination in the graph. Prioritizes larger edge weights using a Max Heap
 * Time Complexity: O(|e| + nlog(n)) where n is num vertices, e is edges
 */
vector<int> dijkstra(const Graph & g, int source, int dest);
